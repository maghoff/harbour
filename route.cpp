#include "route.hpp"
#include "util.hpp"

Route::Route(QPointF start) {
    path.append(start);
}

Route::~Route() {

}

QPointF Route::head() const {
    return path.back();
}

QPointF Route::tail() const {
    return path.front();
}

void Route::goThrough(QPointF p) {
    if (util::pyth(p - head()) > 5.) {
        path.append(p);
    }
}

QList<QPointF> Route::getPath() const {
    return path;
}
