#include "boat.hpp"

Boat::Boat(QPointF pos, QPointF dir_) :
    route(pos),
    dir(dir_)
{
}

Boat::~Boat() {
}

void Boat::tick() {
}

QPointF Boat::getPos() const {
    return route.tail();
}

QPointF Boat::getDir() const {
    return dir;
}

Route Boat::getRoute() const {
    return route;
}
