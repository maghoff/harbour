#ifndef GAME_HPP
#define GAME_HPP

#include <QWidget>
#include <QPoint>
#include <QMap>
#include <QList>
#include "boat.hpp"
#include "route.hpp"
#include "port.hpp"

class QPen;
class QBrush;
class QPaintEvent;
class QTabletEvent;
class QTimer;

class Game : public QWidget {
    Q_OBJECT

    typedef qint64 id_t;

    QTimer* timer;

    QMap<id_t, Route*> routes;
    QMap<id_t, QPoint> penPositions;

    QList<Boat> boats;
    QList<Port> ports;

    QPen* routePen;
    QPen* routeInPortPen;
    QPen* boatPen;
    QBrush* boatBrush;

    Boat* findBoat(QPointF pos);

    void drawRoute(QPainter& painter, const Route& route);
    bool isPointInPort(QPointF pt) const;

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

protected:
    void tabletEvent(QTabletEvent *event);
    void paintEvent(QPaintEvent *event);

signals:

public slots:

private slots:
    void tick();
};

#endif // GAME_HPP
