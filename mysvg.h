#ifndef __MY_SVG_H_
#define __MY_SVG_H_

#include <QGraphicsSvgItem>

class MySvg : public QGraphicsSvgItem
{
        Q_OBJECT
        public:
                MySvg(const QString &file);
                ~MySvg() {};
        protected:
                virtual void mousePressEvent(QGraphicsSceneMouseEvent *);
        signals:
                void click(void);
};

#endif
