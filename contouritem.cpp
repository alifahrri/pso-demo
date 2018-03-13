#include "contouritem.h"
#include <thread>
#include <cmath>
#include <QPainter>

ContourItem::ContourItem()
{
    contour = [](double x, double y)
    {
        return sin((x+275/2)/275.0*M_PI) + cos((y)/275.0*M_PI);
    };
    calculateContour();
}

void ContourItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(auto& p : color_pts)
    {
        painter->setPen(p.second);
        painter->setBrush(p.second);
        painter->drawPoint(p.first);
    }
}

QRectF ContourItem::boundingRect() const
{
    return QRectF(-275,-275,550,550);
}

inline
void ContourItem::calculateContour()
{
    if(!contour)
        return;
    points.clear();
    max_value = 0.0;
    min_value = 0.0;
    double val[4];
    std::thread t[4];
    for(int i=-275; i<275; i++)
        for(int j=-275; j<275; j++)
        {
            double value = contour(i,j);
            QPointF p(i,j);
            if(value < min_value)
                min_value = value;
            else if(value > max_value)
                max_value = value;
            points.push_back(std::make_pair(p,value));
            /*
#pragma GCC ivdep
            for(int x=0; x<4; x++)
                t[x] = std::thread([&val,x,i,j,this]{ val[x] = contour(i,j+x); });
#pragma GCC ivdep
            for(int x=0; x<4; x++)
                if(t[x].joinable())
                    t[x].join();
            for(int x=0; x<4; x++)
            {
                QPointF p(i,j+x);
                if(val[x]>max_value)
                    max_value = val[x];
                else if(val[x]<min_value)
                    min_value = val[x];
                points.push_back(std::make_pair(p,val[x]));
            }
            */
        }
    for(auto p : points)
    {
        auto c = (p.second+fabs(min_value))/(max_value-min_value)*255;
        QColor color;
        color = QColor::fromHsv((int)(255-c),255,255);
        color_pts.push_back(std::make_pair(p.first,color));
    }
}
