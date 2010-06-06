#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <QList>
#include <QPoint>

class Route {
    QList<QPointF> path;

    QPointF head() const;

public:
    Route(QPointF start);
    ~Route();

    void goThrough(QPointF);

    QList<QPointF> getPath() const;
};

#endif // ROUTE_HPP
