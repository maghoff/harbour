#include "route.hpp"
#include "util.hpp"

Route::Route(QPointF start, QPointF dir)
    : taildir(dir)
{
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

QPointF& Route::tail() {
    return path.front();
}

QPointF Route::getTailDir() const {
    return taildir;
}

void Route::invalidateTailDir()
{
    QList<QPointF>::const_iterator it = path.begin();
    it++;
    if (it != path.end())
    {
        taildir = util::normalize(*it - path.front());
    }
}

double Route::consume(double len) {
    QList<QPointF>::const_iterator it = path.begin();
    it++;
    if (it != path.end()) {
        QPointF firstLine = *it - path.front();
        double lineLength = util::pyth(firstLine);
        if (len > lineLength) {
            // We want to consume more than the first segment
            path.pop_front();
            invalidateTailDir();
            return consume(len - lineLength);
        } else {
            path.front() += taildir * len;
            return 0;
        }
    } else {
        return len;
    }
}

void Route::goThrough(QPointF p) {
    if (util::pyth(p - head()) > 5.) {
        path.append(p);
    }
    invalidateTailDir();
}

QList<QPointF> Route::getPath() const {
    return path;
}
