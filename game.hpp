#ifndef GAME_HPP
#define GAME_HPP

#include <QWidget>
#include <QPoint>
#include <QMap>
#include <QList>
#include "boat.hpp"
#include "route.hpp"

class QPaintEvent;
class QTabletEvent;

class Game : public QWidget {
    Q_OBJECT

    typedef qint64 id_t;

    QMap<id_t, Route> routes;
    QMap<id_t, QPoint> penPositions;

    QList<Boat> boats;

public:
    explicit Game(QWidget *parent = 0);

protected:
    void tabletEvent(QTabletEvent *event);
    void paintEvent(QPaintEvent *event);

signals:

public slots:

};

#endif // GAME_HPP
