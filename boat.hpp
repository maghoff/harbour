#ifndef BOAT_HPP
#define BOAT_HPP

#include <QPoint>
#include "route.hpp"

class Boat {
    Route route;

public:
    Boat(QPointF pos, QPointF dir);
    ~Boat();

    void tick();
};

#endif // BOAT_HPP
