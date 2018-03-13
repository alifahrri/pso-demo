#include "psoitem.h"
#include <QPainter>

PSOItem::PSOItem(PSO &pso_) :
    pso(pso_)
{

}

void PSOItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto particles = pso.getParticles();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkMagenta);
    for(auto &p : particles)
        painter->drawEllipse(QPoint(p.first.state[0],-p.first.state[1]),3,3);
}

QRectF PSOItem::boundingRect() const
{
    return QRectF(-300,-300,600,600);
}
