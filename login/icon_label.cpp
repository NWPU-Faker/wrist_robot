#include"icon_label.h"
#include<QPainter>
 icon_label::icon_label(QWidget *parent) : QLabel(parent)
{

}

void icon_label::paintevent(QPainter *p)
{
    p->save();
    QSize iconSize = QSize(16, 16);
    QPixmap pix(15, 15);
    pix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen("#292929");
    int icon=0xf007;
    QFont iconFont;
    iconFont.setPixelSize(15);
    painter.setFont(iconFont);
    painter.drawText(pix.rect(), Qt::AlignCenter, (QChar)icon);
    painter.end();
     pix = pix.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    p->drawPixmap(10, (height() - iconSize.height()) / 2, pix);
    p->restore();
}

/*
QPixmap IconHelper::getPixmap1(const QColor &color, int icon, quint32 size,
                               quint32 width, quint32 height, int flags)
{
    //主动绘制图形字体到图片
    QPixmap pix(width, height);
    pix.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(color);

    iconFont.setPixelSize(size);
    painter.setFont(iconFont);
    painter.drawText(pix.rect(), flags, (QChar)icon);
    painter.end();
    return pix;
}
*/
