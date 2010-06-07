#include <cassert>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include "game.hpp"
#include "util.hpp"

Game::Game(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this))
{
    routePen =        new QPen  (QColor::fromHslF(0.1, 0.7, 0.4, 0.6));
    routeInPortPen =  new QPen  (QColor::fromHslF(0.6, 0.7, 0.4, 0.6));
    boatPen =         new QPen  (QColor::fromHslF(0.4, 0.5, 0.5));
    boatBrush =       new QBrush(QColor::fromHslF(0.4, 0.7, 0.5));

    boats.append(Boat(QPointF(50, 100), QPointF(0, -1)));
    for (int i = 70; i < 300; i+=25)
        boats.append(Boat(QPointF(i, 100), QPointF(1, 0)));

    ports.append(Port(QPoint(100,100), QPoint(50, 0)));
    ports.append(Port(QPoint(200,200), QPoint(40, 10)));

    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

    timer->setSingleShot(false);
    timer->start(10);
}

Game::~Game() {

}

void Game::tick() {
    for (QList<Boat>::iterator i = boats.begin(); i != boats.end(); ++i) {
        Boat& boat = *i;
        boat.tick();
    }
    update();
}

Boat* Game::findBoat(QPointF pos) {
    const qreal threshold = 20.;

    Boat* candidate = 0;
    qreal candidateDistance = threshold;

    for (QList<Boat>::iterator i = boats.begin(); i != boats.end(); ++i) {
        Boat& boat = *i;

        qreal dist = util::length(pos - boat.getPos());
        if (dist < candidateDistance) {
            candidate = &boat;
            candidateDistance = dist;
        }
    }

    return candidate;
}

void Game::tabletEvent(QTabletEvent *event) {
    QMap<id_t, Route*>::iterator r = routes.find(event->uniqueId());
    QMap<id_t, QPoint>::iterator penPosition = penPositions.find(event->uniqueId());

    switch (event->type()) {
    case QEvent::TabletPress:
        assert(r == routes.end());

        if (Boat* boat = findBoat(event->pos())) {
            Route* route = boat->getRoutePointer();

            routes.insert(event->uniqueId(), route);
            *route = Route(boat->getPos(), boat->getDir());
        }

        break;
/*
    case QEvent::TabletEnterProximity:
        assert(penPosition == penPositions.end());
        penPositions.insert(event->uniqueId(), event->pos());
        break;

    case QEvent::TabletLeaveProximity:
        assert(penPosition != penPositions.end());
        penPositions.erase(penPosition);
        break;
*/
    case QEvent::TabletRelease:
        if (r != routes.end()) {
            r.value()->goThrough(event->pos());
            routes.erase(r);
        }
        break;

    case QEvent::TabletMove:
        if (r != routes.end()) r.value()->goThrough(event->pos());

        if (penPosition == penPositions.end())
            penPositions.insert(event->uniqueId(), event->pos());
        else
            penPosition.value() = event->pos();
        break;

    default:
        break;
    }
    update();
}

bool Game::isPointInPort(QPointF pt) const {
    foreach (const Port& port, ports) {
        if (port.containsPoint(pt))
            return true;
    }
    return false;
}

void Game::drawRoute(QPainter& painter, const Route& route) {
    QList<QPointF> points = route.getPath();

    QPainterPath path;
    path.moveTo(points.front());
    foreach (const QPointF& pt, points) {
        path.lineTo(pt);
    }

    if (isPointInPort(route.head()))
        painter.setPen(*routeInPortPen);
    else
        painter.setPen(*routePen);
    painter.setBrush(QBrush());
    painter.drawPath(path);
}

void Game::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    foreach (const Boat& boat, boats) {
        QPointF pos = boat.getPos(), dir = boat.getDir(), odir(dir.y(), -dir.x());

        QPainterPath path;
        path.moveTo(pos - 10*dir - 5*odir);
        path.lineTo(pos + 10*dir - 5*odir);
        path.lineTo(pos + 15*dir - 0*odir);
        path.lineTo(pos + 10*dir + 5*odir);
        path.lineTo(pos - 10*dir + 5*odir);
        path.closeSubpath();

        painter.setPen(*boatPen);
        painter.setBrush(*boatBrush);
        painter.drawPath(path);
    }

    foreach (const Boat& boat, boats) {
        drawRoute(painter, boat.getRoute());
    }

    foreach (const Port& port, ports) {
        QPainterPath path;
        QPointF rightside(-port.leftside.y(), port.leftside.x());
        path.moveTo(port.corner);
        path.lineTo(port.corner + port.leftside);
        path.lineTo(port.corner + port.leftside + rightside);
        path.lineTo(port.corner + rightside);
        path.closeSubpath();

        painter.setPen(*boatPen);
        painter.setBrush(QBrush());
        painter.drawPath(path);
    }

    painter.setPen(QPen());
    foreach (const QPoint& pt, penPositions) {
        QPainterPath path;
        path.moveTo(pt - QPoint(0, -5));
        path.lineTo(pt - QPoint(0, +5));
        path.moveTo(pt - QPoint(-5, 0));
        path.lineTo(pt - QPoint(+5, 0));

        painter.drawPath(path);
    }

}
