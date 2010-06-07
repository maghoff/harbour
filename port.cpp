#include "port.hpp"
#include "util.hpp"

Port::Port(QPointF corner_, QPointF leftside_) :
    corner(corner_),
    leftside(leftside_)
{
}

bool Port::containsPoint(QPointF point) const {
    QPointF rightside(-leftside.y(), leftside.x());
    double d1 = util::dotProduct(point - corner, leftside);
    double d2 = util::dotProduct(point - corner, rightside);
    double l1 = util::sqlength(leftside);
    double l2 = util::sqlength(rightside);

    return d1 >= 0 && d1 <= l1 && d2 >= 0 && d2 <= l2;
}
