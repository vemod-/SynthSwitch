#ifndef QSYNTHSWITCH_H
#define QSYNTHSWITCH_H

#include <QSlider>
#include <QImage>

class QSynthSwitch : public QSlider
{
    Q_OBJECT
    Q_PROPERTY( bool LEDTicks READ LEDTicks WRITE setLEDTicks)
public:
    explicit QSynthSwitch(QWidget *parent = 0);
    bool LEDTicks();
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
public slots:
    void setLEDTicks(bool val);
    void setStringList(const QStringList& l);
    void setValue(int val);
    void setOrientation(Qt::Orientation val);
private:
    bool m_LEDTicks;
    QImage backimage;
    QPixmap backpix;
    QRectF backRect;
    QImage handleImage;
    QPixmap handlepix;
    QStringList m_StringList;
    void drawText(QPainter& p, const QRectF& r, const int index, const Qt::Alignment align = Qt::AlignLeft);
};

#endif // QSYNTHSWITCH_H
