#include <cmath>
#include "util.hpp"

namespace util {

double pyth(QPointF p) {
    return sqrt(sqr(p.x()) + sqr(p.y()));
}

QPointF normalize(QPointF p)
{
    return p / pyth(p);
}

}
