#ifndef PORT_HPP
#define PORT_HPP

#include <QPoint>

class Port
{
public:
    QPointF corner;
    QPointF leftside; // rightside is 90 deg CW

    Port(QPointF corner, QPointF leftside);
    bool containsPoint(QPointF point) const;

};

#endif // PORT_HPP
