#include <cassert>
#include <QPaintEvent>
#include <QPainter>
#include "game.hpp"
#include "util.hpp"

Game::Game(QWidget *parent) :
    QWidget(parent)
{
    boats.append(Boat(QPointF(50, 100), QPointF(0, -1)));
    boats.append(Boat(QPointF(150, 100), QPointF(1, 0)));
}

Boat* Game::findBoat(QPointF pos) {
    const qreal threshold = 20.;

    Boat* candidate = 0;
    qreal candidateDistance = threshold;

    for (QList<Boat>::iterator i = boats.begin(); i != boats.end(); ++i) {
        Boat& boat = *i;

        qreal dist = util::pyth(pos - boat.getPos());
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
            *route = Route(boat->getPos());
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

void Game::drawRoute(QPainter& painter, const Route& route) {
    QList<QPointF> points = route.getPath();

    QPainterPath path;
    path.moveTo(points.front());
    foreach (const QPointF& pt, points) {
        path.lineTo(pt);
    }

    painter.drawPath(path);
}

void Game::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    foreach (const QPoint& pt, penPositions) {
        QPainterPath path;
        path.moveTo(pt - QPoint(0, -5));
        path.lineTo(pt - QPoint(0, +5));
        path.moveTo(pt - QPoint(-5, 0));
        path.lineTo(pt - QPoint(+5, 0));

        painter.drawPath(path);
    }

    foreach (const Boat& boat, boats) {
        QPointF pos = boat.getPos(), dir = boat.getDir(), odir(dir.y(), -dir.x());

        QPainterPath path;
        path.moveTo(pos - 10*dir - 5*odir);
        path.lineTo(pos + 10*dir - 5*odir);
        path.lineTo(pos + 10*dir + 5*odir);
        path.lineTo(pos - 10*dir + 5*odir);
        path.closeSubpath();

        painter.drawPath(path);

        drawRoute(painter, boat.getRoute());
    }
}
