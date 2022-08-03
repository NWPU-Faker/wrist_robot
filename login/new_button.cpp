
#include "new_button.h"
#include "qpainter.h"
#include "qdebug.h"
#pragma execution_character_set("utf-8")

New_Button::New_Button(QWidget *parent) : QPushButton(parent)
{
    paddingLeft = 20;
    paddingRight = 5;
    paddingTop = 5;
    paddingBottom = 5;
    textAlign = TextAlign_Left;

    showTriangle = false;
    triangleLen = 10;
    trianglePosition = TrianglePosition_Right;
    triangleColor = QColor(224, 245, 255);

    showIcon = false;
    iconSpace = 10;
    iconSize = QSize(16, 16);
    iconNormal = QPixmap();
    iconHover = QPixmap();
    iconCheck = QPixmap();

    showLine = true;
    lineSpace = 0;
    lineWidth = 13;
    linePosition = LinePosition_Left;
    lineColor = QColor(0, 187, 158);

    normalBgColor = QColor(77, 212, 183);
    hoverBgColor = QColor(130, 130, 130);
    checkBgColor = QColor(255, 85, 0);
    normalTextColor = QColor(100, 100, 100);
    hoverTextColor = QColor(255, 255, 255);
    checkTextColor = QColor(255, 255, 255);

    normalBgBrush = Qt::NoBrush;
    hoverBgBrush = Qt::NoBrush;
    checkBgBrush = Qt::NoBrush;

    hover = false;
    setCheckable(true);
    setText("导航按钮");
}

void New_Button::enterEvent(QEvent *)
{
    hover = true;
    this->update();
}

void New_Button::leaveEvent(QEvent *)
{
    hover = false;
    this->update();
}

void New_Button::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
    //绘制图标
    drawIcon(&painter);
    //绘制边框线条
    drawLine(&painter);
    //绘制倒三角
    drawTriangle(&painter);
}

void New_Button::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    int width = this->width();
    int height = this->height();

    QRect bgRect;
    if (linePosition == LinePosition_Left) {
        bgRect = QRect(lineSpace, 0, width - lineSpace, height);
    } else if (linePosition == LinePosition_Right) {
        bgRect = QRect(0, 0, width - lineSpace, height);
    } else if (linePosition == LinePosition_Top) {
        bgRect = QRect(0, lineSpace, width, height - lineSpace);
    } else if (linePosition == LinePosition_Bottom) {
        bgRect = QRect(0, 0, width, height - lineSpace);
    }

    //如果画刷存在则取画刷
    QBrush bgBrush;
    if (isChecked()) {
        bgBrush = checkBgBrush;
    } else if (hover) {
        bgBrush = hoverBgBrush;
    } else {
        bgBrush = normalBgBrush;
    }

    if (bgBrush != Qt::NoBrush) {
        painter->setBrush(bgBrush);
    } else {
        //根据当前状态选择对应颜色
        QColor bgColor;
        if (isChecked()) {
            bgColor = checkBgColor;
        } else if (hover) {
            bgColor = hoverBgColor;
        } else {
            bgColor = normalBgColor;
        }

        painter->setBrush(bgColor);
    }

    painter->drawRect(bgRect);

    painter->restore();
}

void New_Button::drawText(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //根据当前状态选择对应颜色
    QColor textColor;
    if (isChecked()) {
        textColor = checkTextColor;
    } else if (hover) {
        textColor = hoverTextColor;
    } else {
        textColor = normalTextColor;
    }

    QRect textRect = QRect(paddingLeft, paddingTop, width() - paddingLeft - paddingRight, height() - paddingTop - paddingBottom);
    painter->setPen(textColor);
    painter->drawText(textRect, textAlign | Qt::AlignVCenter, text());

    painter->restore();
}

void New_Button::drawIcon(QPainter *painter)
{
    if (!showIcon) {
        return;
    }

    painter->save();

    QPixmap pix;
    if (isChecked()) {
        pix = iconCheck;
    } else if (hover) {
        pix = iconHover;
    } else {
        pix = iconNormal;
    }

    if (!pix.isNull()) {
        //等比例平滑缩放图标
        pix = pix.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(iconSpace, (height() - iconSize.height()) / 2, pix);
    }

    painter->restore();
}

void New_Button::drawLine(QPainter *painter)
{
    if (!showLine) {
        return;
    }

    if (!isChecked()) {
        return;
    }

    painter->save();

    QPen pen;
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    painter->setPen(pen);

    //根据线条位置设置线条坐标
    QPoint pointStart, pointEnd;
    if (linePosition == LinePosition_Left) {
        pointStart = QPoint(0, 0);
        pointEnd = QPoint(0, height());
    } else if (linePosition == LinePosition_Right) {
        pointStart = QPoint(width(), 0);
        pointEnd = QPoint(width(), height());
    } else if (linePosition == LinePosition_Top) {
        pointStart = QPoint(0, 0);
        pointEnd = QPoint(width(), 0);
    } else if (linePosition == LinePosition_Bottom) {
        pointStart = QPoint(0, height());
        pointEnd = QPoint(width(), height());
    }

    painter->drawLine(pointStart, pointEnd);

    painter->restore();
}

void New_Button::drawTriangle(QPainter *painter)
{
    if (!showTriangle) {
        return;
    }

    //选中或者悬停显示
    if (!hover && !isChecked()) {
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(triangleColor);

    //绘制在右侧中间,根据设定的倒三角的边长设定三个点位置
    int width = this->width();
    int height = this->height();
    int midWidth = width / 2;
    int midHeight = height / 2;

    QPolygon pts;
    if (trianglePosition == TrianglePosition_Left) {
        pts.setPoints(3, triangleLen, midHeight, 0, midHeight - triangleLen, 0, midHeight + triangleLen);
    } else if (trianglePosition == TrianglePosition_Right) {
        pts.setPoints(3, width - triangleLen, midHeight, width, midHeight - triangleLen, width, midHeight + triangleLen);
    } else if (trianglePosition == TrianglePosition_Top) {
        pts.setPoints(3, midWidth, triangleLen, midWidth - triangleLen, 0, midWidth + triangleLen, 0);
    } else if (trianglePosition == TrianglePosition_Bottom) {
        pts.setPoints(3, midWidth, height - triangleLen, midWidth - triangleLen, height, midWidth + triangleLen, height);
    }

    painter->drawPolygon(pts);

    painter->restore();
}

int New_Button::getPaddingLeft() const
{
    return this->paddingLeft;
}

int New_Button::getPaddingRight() const
{
    return this->paddingRight;
}

int New_Button::getPaddingTop() const
{
    return this->paddingTop;
}

int New_Button::getPaddingBottom() const
{
    return this->paddingBottom;
}

New_Button::TextAlign New_Button::getTextAlign() const
{
    return this->textAlign;
}

bool New_Button::getShowTriangle() const
{
    return this->showTriangle;
}

int New_Button::getTriangleLen() const
{
    return this->triangleLen;
}

New_Button::TrianglePosition New_Button::getTrianglePosition() const
{
    return this->trianglePosition;
}

QColor New_Button::getTriangleColor() const
{
    return this->triangleColor;
}

bool New_Button::getShowIcon() const
{
    return this->showIcon;
}

int New_Button::getIconSpace() const
{
    return this->iconSpace;
}

QSize New_Button::getIconSize() const
{
    return this->iconSize;
}

QPixmap New_Button::getIconNormal() const
{
    return this->iconNormal;
}

QPixmap New_Button::getIconHover() const
{
    return this->iconHover;
}

QPixmap New_Button::getIconCheck() const
{
    return this->iconCheck;
}

bool New_Button::getShowLine() const
{
    return this->showLine;
}

int New_Button::getLineSpace() const
{
    return this->lineSpace;
}

int New_Button::getLineWidth() const
{
    return this->lineWidth;
}

New_Button::LinePosition New_Button::getLinePosition() const
{
    return this->linePosition;
}

QColor New_Button::getLineColor() const
{
    return this->lineColor;
}

QColor New_Button::getNormalBgColor() const
{
    return this->normalBgColor;
}

QColor New_Button::getHoverBgColor() const
{
    return this->hoverBgColor;
}

QColor New_Button::getCheckBgColor() const
{
    return this->checkBgColor;
}

QColor New_Button::getNormalTextColor() const
{
    return this->normalTextColor;
}

QColor New_Button::getHoverTextColor() const
{
    return this->hoverTextColor;
}

QColor New_Button::getCheckTextColor() const
{
    return this->checkTextColor;
}

QSize New_Button::sizeHint() const
{
    return QSize(100, 30);
}

QSize New_Button::minimumSizeHint() const
{
    return QSize(20, 10);
}

void New_Button::setPaddingLeft(int paddingLeft)
{
    if (this->paddingLeft != paddingLeft) {
        this->paddingLeft = paddingLeft;
        this->update();
    }
}

void New_Button::setPaddingRight(int paddingRight)
{
    if (this->paddingRight != paddingRight) {
        this->paddingRight = paddingRight;
        this->update();
    }
}

void New_Button::setPaddingTop(int paddingTop)
{
    if (this->paddingTop != paddingTop) {
        this->paddingTop = paddingTop;
        this->update();
    }
}

void New_Button::setPaddingBottom(int paddingBottom)
{
    if (this->paddingBottom != paddingBottom) {
        this->paddingBottom = paddingBottom;
        this->update();
    }
}

void New_Button::setPadding(int padding)
{
    setPadding(padding, padding, padding, padding);
}

void New_Button::setPadding(int paddingLeft, int paddingRight, int paddingTop, int paddingBottom)
{
    this->paddingLeft = paddingLeft;
    this->paddingRight = paddingRight;
    this->paddingTop = paddingTop;
    this->paddingBottom = paddingBottom;
    this->update();
}

void New_Button::setTextAlign(const New_Button::TextAlign &textAlign)
{
    if (this->textAlign != textAlign) {
        this->textAlign = textAlign;
        this->update();
    }
}

void New_Button::setShowTriangle(bool showTriangle)
{
    if (this->showTriangle != showTriangle) {
        this->showTriangle = showTriangle;
        this->update();
    }
}

void New_Button::setTriangleLen(int triangleLen)
{
    if (this->triangleLen != triangleLen) {
        this->triangleLen = triangleLen;
        this->update();
    }
}

void New_Button::setTrianglePosition(const New_Button::TrianglePosition &trianglePosition)
{
    if (this->trianglePosition != trianglePosition) {
        this->trianglePosition = trianglePosition;
        this->update();
    }
}

void New_Button::setTriangleColor(const QColor &triangleColor)
{
    if (this->triangleColor != triangleColor) {
        this->triangleColor = triangleColor;
        this->update();
    }
}

void New_Button::setShowIcon(bool showIcon)
{
    if (this->showIcon != showIcon) {
        this->showIcon = showIcon;
        this->update();
    }
}

void New_Button::setIconSpace(int iconSpace)
{
    if (this->iconSpace != iconSpace) {
        this->iconSpace = iconSpace;
        this->update();
    }
}

void New_Button::setIconSize(const QSize &iconSize)
{
    if (this->iconSize != iconSize) {
        this->iconSize = iconSize;
        this->update();
    }
}

void New_Button::setIconNormal(const QPixmap &iconNormal)
{
    this->iconNormal = iconNormal;
    this->update();
}

void New_Button::setIconHover(const QPixmap &iconHover)
{
    this->iconHover = iconHover;
    this->update();
}

void New_Button::setIconCheck(const QPixmap &iconCheck)
{
    this->iconCheck = iconCheck;
    this->update();
}

void New_Button::setShowLine(bool showLine)
{
    if (this->showLine != showLine) {
        this->showLine = showLine;
        this->update();
    }
}

void New_Button::setLineSpace(int lineSpace)
{
    if (this->lineSpace != lineSpace) {
        this->lineSpace = lineSpace;
        this->update();
    }
}

void New_Button::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        this->update();
    }
}

void New_Button::setLinePosition(const New_Button::LinePosition &linePosition)
{
    if (this->linePosition != linePosition) {
        this->linePosition = linePosition;
        this->update();
    }
}

void New_Button::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void New_Button::setNormalBgColor(const QColor &normalBgColor)
{
    if (this->normalBgColor != normalBgColor) {
        this->normalBgColor = normalBgColor;
        this->update();
    }
}

void New_Button::setHoverBgColor(const QColor &hoverBgColor)
{
    if (this->hoverBgColor != hoverBgColor) {
        this->hoverBgColor = hoverBgColor;
        this->update();
    }
}

void New_Button::setCheckBgColor(const QColor &checkBgColor)
{
    if (this->checkBgColor != checkBgColor) {
        this->checkBgColor = checkBgColor;
        this->update();
    }
}

void New_Button::setNormalTextColor(const QColor &normalTextColor)
{
    if (this->normalTextColor != normalTextColor) {
        this->normalTextColor = normalTextColor;
        this->update();
    }
}

void New_Button::setHoverTextColor(const QColor &hoverTextColor)
{
    if (this->hoverTextColor != hoverTextColor) {
        this->hoverTextColor = hoverTextColor;
        this->update();
    }
}

void New_Button::setCheckTextColor(const QColor &checkTextColor)
{
    if (this->checkTextColor != checkTextColor) {
        this->checkTextColor = checkTextColor;
        this->update();
    }
}

void New_Button::setNormalBgBrush(const QBrush &normalBgBrush)
{
    if (this->normalBgBrush != normalBgBrush) {
        this->normalBgBrush = normalBgBrush;
        this->update();
    }
}

void New_Button::setHoverBgBrush(const QBrush &hoverBgBrush)
{
    if (this->hoverBgBrush != hoverBgBrush) {
        this->hoverBgBrush = hoverBgBrush;
        this->update();
    }
}

void New_Button::setCheckBgBrush(const QBrush &checkBgBrush)
{
    if (this->checkBgBrush != checkBgBrush) {
        this->checkBgBrush = checkBgBrush;
        this->update();
    }
}
