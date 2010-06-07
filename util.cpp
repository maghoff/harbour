#include <cmath>
#include "util.hpp"

namespace util {

double sqlength(QPointF p) {
    return sqr(p.x()) + sqr(p.y());
}

double length(QPointF p) {
    return sqrt(sqlength(p));
}

QPointF normalize(QPointF p)
{
    return p / length(p);
}

double dotProduct(QPointF a, QPointF b) {
    return a.x() * b.x() + a.y() * b.y();
}

}
