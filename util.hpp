#ifndef UTIL_HPP
#define UTIL_HPP

#include <QPoint>

namespace util {

template <typename T>
T sqr(T x) { return x*x; }

double pyth(QPointF p);
QPointF normalize(QPointF p);
}

#endif // UTIL_HPP
