#ifndef UTIL_HPP
#define UTIL_HPP

#include <QPoint>

namespace util {

template <typename T>
T sqr(T x) { return x*x; }

double length(QPointF p);
double sqlength(QPointF p);
QPointF normalize(QPointF p);
double dotProduct(QPointF a, QPointF b);

}

#endif // UTIL_HPP
