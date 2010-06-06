#include <cassert>
#include <QPaintEvent>
#include <QPainter>
#include "game.hpp"

Game::Game(QWidget *parent) :
    QWidget(parent)
{
    boats.append(Boat(QPointF(50, 100), QPointF(0, -1)));
}

void Game::tabletEvent(QTabletEvent *event) {
    QMap<id_t, Route>::iterator r = routes.find(event->uniqueId());
    QMap<id_t, QPoint>::iterator penPosition = penPositions.find(event->uniqueId());

    switch (event->type()) {
    case QEvent::TabletPress:
        assert(r == routes.end());
        routes.insert(event->uniqueId(), Route(event->pos()));
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
        assert(r != routes.end());
        r->goThrough(event->pos());
        //
        routes.erase(r);
        break;

    case QEvent::TabletMove:
        if (r != routes.end()) r->goThrough(event->pos());

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

void Game::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    foreach (const Route& r, routes) {
        QList<QPointF> points = r.getPath();

        QPainterPath path;
        path.moveTo(points.front());
        foreach (const QPointF& pt, points) {
            path.lineTo(pt);
        }

        painter.drawPath(path);
    }

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
    }
}
