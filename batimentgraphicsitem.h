#ifndef BATIMENTGRAPHICSITEM_H
#define BATIMENTGRAPHICSITEM_H

#include <QGraphicsRectItem>
#include <QString>

class BatimentGraphicsItem : public QGraphicsRectItem {
public:
    BatimentGraphicsItem(const QString& name, const QRectF& rect, QGraphicsItem* parent = nullptr);

private:
    QString name;
};

#endif // BATIMENTGRAPHICSITEM_H
