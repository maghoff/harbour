#include <cmath>
#include "route.hpp"

namespace {

template <typename T>
T sqr(T x) { return x*x; }

double pyth(QPointF p) {
    return sqrt(sqr(p.x()) + sqr(p.y()));
}

}

Route::Route(QPointF start) {
    path.append(start);
}

Route::~Route() {

}

QPointF Route::head() const {
    return path.back();
}

void Route::goThrough(QPointF p) {
    if (pyth(p - head()) > 5.) {
        path.append(p);
    }
}

QList<QPointF> Route::getPath() const {
    return path;
}
