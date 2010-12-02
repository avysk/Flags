#include "mysvg.h"

MySvg::MySvg(const QString &file) : QGraphicsSvgItem(file) { }

void MySvg::mousePressEvent(QGraphicsSceneMouseEvent *e) {
        emit click();
}
