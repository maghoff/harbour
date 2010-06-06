#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <QList>
#include <QPoint>

class Route {
    QList<QPointF> path;
    QPointF taildir;

    void invalidateTailDir();

public:
    Route(QPointF start, QPointF dir);
    ~Route();

    QPointF head() const;
    QPointF tail() const;
    QPointF& tail();
    QPointF getTailDir() const;

    double consume(double len);

    void goThrough(QPointF);

    QList<QPointF> getPath() const;
};

#endif // ROUTE_HPP
