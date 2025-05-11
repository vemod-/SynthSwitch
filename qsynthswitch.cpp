#include "qsynthswitch.h"
#include <QPainter>
#include "cresourceinitializer.h"

QSynthSwitch::QSynthSwitch(QWidget *parent) :
    QSlider(parent)
{
    CResourceInitializer::initializeResources();
    setAttribute(Qt::WA_StaticContents);
    setAttribute(Qt::WA_NoSystemBackground);
    m_LEDTicks = false;
    backimage = QImage(":/SliderGrooveV.png");
    handleImage = QImage(":/SliderHandle.png");
    setStringList(QStringList() << "Off" << "On");
    setValue(0);
    setLEDTicks(false);
}

void QSynthSwitch::setLEDTicks(bool val)
{
    if (val != m_LEDTicks)
    {
        m_LEDTicks = val;
        update();
    }
}

bool QSynthSwitch::LEDTicks()
{
    return m_LEDTicks;
}

void QSynthSwitch::setStringList(const QStringList& l)
{
    if (l != m_StringList)
    {
        m_StringList = l;
        QSlider::setMaximum(l.size()-1);
        update();
    }
}

void QSynthSwitch::setValue(int val)
{
    if (val != value())
    {
        QSlider::setValue(val);
        update();
    }
}

void QSynthSwitch::setOrientation(Qt::Orientation val)
{
    QSlider::setOrientation(val);
    if (val == Qt::Orientation::Horizontal)
    {
        backimage=QImage(":/SliderGrooveH.png");
        setInvertedAppearance(false);
        setInvertedControls(true);
    }
    else
    {
        backimage=QImage(":/SliderGrooveV.png");
        setInvertedAppearance(true);
        setInvertedControls(false);
    }
    update();
}

void QSynthSwitch::resizeEvent(QResizeEvent* /*event*/)
{
    backpix=QPixmap::fromImage(backimage, Qt::AutoColor | Qt::DiffuseDither | Qt::DiffuseAlphaDither).scaled(rect().size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    backRect=backpix.rect();
    backRect.moveCenter(rect().center());
    handlepix=QPixmap::fromImage(handleImage, Qt::AutoColor | Qt::DiffuseDither | Qt::DiffuseAlphaDither).scaled(backpix.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    QRectF grooveRect = backRect;
    QSizeF s = grooveRect.size();
    s.scale(backRect.size()*0.75,Qt::AspectRatioMode::KeepAspectRatio);
    grooveRect.setSize(s);
    grooveRect.moveCenter(rect().center());
    if (orientation()==Qt::Orientation::Horizontal)
    {
        setStyleSheet("QSlider::groove:horizontal{background:black;position:absolute;left:"+QString::number(grooveRect.left())+"px;right:"+QString::number(rect().width()-grooveRect.right())+"px;}");
    }
    else
    {
        setStyleSheet("QSlider::groove:vertical{background:black;position:absolute;top:"+QString::number(grooveRect.top())+"px;bottom:"+QString::number(rect().height()-grooveRect.bottom())+"px;}");
    }
}

void QSynthSwitch::paintEvent(QPaintEvent* /*event*/)
{
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::TextAntialiasing);
    backRect.moveCenter(rect().center());

    (orientation()==Qt::Orientation::Horizontal) ? backRect.moveBottom(rect().bottom()*0.9) :
                                                   backRect.moveRight(rect().right()*0.9);

    p.drawPixmap(backRect,backpix,backpix.rect());
    double handleCenter;
    double halfRange;
    if (orientation()==Qt::Orientation::Horizontal)
    {
        handleCenter = backRect.left()+(backRect.width()/2);
        halfRange = backRect.width()/4.6;
    }
    else
    {
        handleCenter = backRect.top()+(backRect.height()/2);
        halfRange = backRect.height()/4.6;
    }
    double tickRange = halfRange * 2 / maximum();
    double valueCenter = handleCenter -(tickRange*maximum()/2) + (tickRange * value());
    QRectF handleRect = handlepix.rect();
    if (orientation()==Qt::Orientation::Horizontal)
    {
        handleRect.moveTop(backRect.top());
        handleRect.moveLeft(valueCenter-(handleRect.width()/2));
        p.drawPixmap(handleRect,handlepix,handlepix.rect());
    }
    else
    {
        handleRect.moveLeft(backRect.left());
        handleRect.moveTop(valueCenter-(handleRect.height()/2));
        p.drawPixmap(handleRect,handlepix,handlepix.rect());
    }
    tickRange*=((maximum()-2)*0.3) + 1;
    if (m_LEDTicks)
    {
        for (int i = 0; i <= maximum(); i ++)
        {
            if (i == value())
            {
                p.setPen("#82BCFF");
                p.setBrush(QBrush("#0076FC"));
            }
            else
            {
                p.setPen(Qt::gray);
                p.setBrush(Qt::lightGray);
            }
            const double DotRadius=handleRect.width()/16.0;
            valueCenter = handleCenter -(tickRange*maximum()/2) + (tickRange * i);
            QPointF c(backRect.topLeft()-QPointF(2,2));
            (orientation()==Qt::Orientation::Horizontal) ? c.setX(valueCenter) : c.setY(valueCenter);
            p.drawEllipse(c,DotRadius,DotRadius);
        }
    }
    p.setPen(Qt::black);
    p.setBrush(Qt::NoBrush);
    QFont f(p.font()); f.setPointSizeF(9); p.setFont(f);
    if (orientation()==Qt::Orientation::Horizontal)
    {
        if (maximum()==1)
        {
            QRectF c(0,(backRect.top()-10)/2,rect().width()/2,10);
            drawText(p,c,0,Qt::AlignHCenter);
            c.moveRight(rect().right());
            drawText(p,c,1,Qt::AlignHCenter);
        }
        if (maximum()==2)
        {
            QRectF c(0,(backRect.top()-20)/2,rect().width()/2,10);
            drawText(p,c,0,Qt::AlignHCenter);
            c.moveRight(rect().right());
            drawText(p,c,2,Qt::AlignHCenter);
            c.moveTopLeft(QPointF(rect().width()/4,((backRect.top()-20)/2)+10));
            drawText(p,c,1,Qt::AlignHCenter);
        }
        if (maximum()==3)
        {
            QRectF c(0,(backRect.top()-20)/2,rect().width()/2,10);
            drawText(p,c,0);
            c.moveRight(rect().right());
            drawText(p,c,3,Qt::AlignRight);
            c.moveTopLeft(QPointF(0,((backRect.top()-20)/2)+10));
            drawText(p,c,1,Qt::AlignRight);
            c.moveLeft(rect().width()/2);
            drawText(p,c,2);
        }
    }
    else
    {
        for (int i = 0; i <= maximum(); i ++)
        {
            valueCenter = handleCenter -(tickRange*maximum()/2) + (tickRange * i);
            QRectF c(0,valueCenter-6,backRect.left()-6,10);
            drawText(p,c,i,Qt::AlignRight);
        }
    }
}

void QSynthSwitch::drawText(QPainter& p, const QRectF& r, const int index, const Qt::Alignment align)
{
    QTextOption o=QTextOption(align);
    o.setWrapMode(QTextOption::WrapAnywhere);
    p.setPen(Qt::white);
    p.drawText(r.translated(0,-1),m_StringList[index],o);
    p.setPen(Qt::black);
    p.drawText(r,m_StringList[index],o);
}
