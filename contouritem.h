#ifndef CONTOURITEM_H
#define CONTOURITEM_H

#include <QGraphicsItem>
#include <functional>

typedef std::function<double(double,double)> ContourCallback;

class ContourItem : public QGraphicsItem
{
public:
    ContourItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public:
    ContourCallback contour;

private:
    typedef std::vector<std::pair<QPointF,double>> ContourPoints;
    typedef std::vector<std::pair<QPointF,QColor>> ColorPoints;
    ContourPoints points;
    ColorPoints color_pts;
    double max_value;
    double min_value;

private:
    void calculateContour();
};

#endif // CONTOURITEM_H
