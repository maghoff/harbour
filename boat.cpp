#include "boat.hpp"

Boat::Boat(QPointF pos, QPointF dir) :
    route(pos, dir)
{
}

Boat::~Boat() {
}

void Boat::tick() {
    double remaining = route.consume(0.1);
    if (remaining > 0)
    {
        route.tail() += route.getTailDir() * remaining;
    }
}

QPointF Boat::getPos() const {
    return route.tail();
}

QPointF Boat::getDir() const {
    return route.getTailDir();
}

Route Boat::getRoute() const {
    return route;
}

Route* Boat::getRoutePointer() {
    return &route;
}
