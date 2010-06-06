#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <QList>
#include <QPoint>

class Route {
    QList<QPointF> path;

public:
    Route(QPointF start);
    ~Route();

    QPointF head() const;
    QPointF tail() const;

    void goThrough(QPointF);

    QList<QPointF> getPath() const;
};

#endif // ROUTE_HPP
