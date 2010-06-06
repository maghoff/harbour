#ifndef BOAT_HPP
#define BOAT_HPP

#include <QPoint>
#include "route.hpp"

class Boat {
    Route route;
    QPointF dir;

public:
    Boat(QPointF pos, QPointF dir);
    ~Boat();

    void tick();

    QPointF getPos() const;
    QPointF getDir() const;
    Route getRoute() const;

    Route* getRoutePointer();
};

#endif // BOAT_HPP
