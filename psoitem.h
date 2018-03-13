#ifndef PSOITEM_H
#define PSOITEM_H

#include <QGraphicsItem>
#include "pso.h"

class PSOItem : public QGraphicsItem
{
public:
    PSOItem(PSO& pso_);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
private:
    PSO& pso;
};

#endif // PSOITEM_H
