#include "batimentgraphicsitem.h"

#include <QBrush>

BatimentGraphicsItem::BatimentGraphicsItem(const QString& name, const QRectF& rect, QGraphicsItem* parent)
    : QGraphicsRectItem(rect, parent), name(name) {
    setBrush(Qt::lightGray);
    setToolTip(name);
}
