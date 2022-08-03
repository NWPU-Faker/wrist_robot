#include"gaugepanel.h"
GaugePanel::GaugePanel(QWidget *parent) : QWidget(parent)
{
    value = hShearValue = vShearValue = 0.0;
    radiusInner = 65.0;
    radiusOuter = 76.25;
    radiusHalo = 87.5;
    colorOuterFrame = QColor(50, 154, 255, 250);
    colorInnerStart = QColor(50, 154, 255, 180);
    colorInnerEnd = QColor(50, 154, 255, 70);
    colorOuterStart = QColor(50, 154, 255, 150);
    colorOuterEnd = QColor(50, 154, 255, 200);
    colorHaloStart = QColor(100, 180, 255, 80);
    colorHaloEnd = QColor(30, 80, 20, 20);

    hShearAnimation = new QPropertyAnimation(this, "hShearValue");
    vShearAnimation = new QPropertyAnimation(this, "vShearValue");
}

GaugePanel::~GaugePanel()
{
    hShearAnimation->stop();
    vShearAnimation->stop();
    delete hShearAnimation;
    delete vShearAnimation;
}

void GaugePanel::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 215.0, side / 215.0);

    painter.shear(double(hShearValue/100.0f), double(vShearValue/100.0f));

    //内层渐变
    drawInnerGradient(&painter);

    //外层渐变
    drawOuterGradient(&painter);

    //外层光晕
    drawOuterHalo(&painter);

    //刻度线
    drawScale(&painter);

    //刻度值
    drawScaleNum(&painter);

    //绘制指针
    drawPointer(&painter);

    //绘制指针扇形
    drawPointerSector(&painter);

    //绘制值
    drawValue(&painter);

    //绘制单位
    drawUnit(&painter);
}

void GaugePanel::drawOuterGradient(QPainter *painter)
{
    if(radiusHalo <= radiusOuter)
        return;

    painter->save();

    QRectF rectangle(0-radiusHalo, 0-radiusHalo, radiusHalo*2, radiusHalo*2);
    QPen framePen(colorOuterFrame);
    framePen.setWidthF(1.5f);
    painter->setPen(framePen);
    painter->drawEllipse(rectangle);

    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;

    float radius = radiusOuter;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius += (radiusHalo - radiusOuter);
    bigCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);

    //大圆抛去小圆部分
    QPainterPath gradientPath = bigCircle - smallCircle;
    QRadialGradient gradient(0, 0, radius, 0, 0);
    //gradient.setSpread(QGradient::ReflectSpread);

    gradient.setColorAt(0.85, colorOuterStart);
    gradient.setColorAt(0.98, colorOuterEnd);
    painter->setBrush(gradient);
    painter->drawPath(gradientPath);

    painter->restore();
}

void GaugePanel::drawInnerGradient(QPainter *painter)
{
    if(radiusOuter <= radiusInner)
        return;

    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;

    float radius = radiusInner;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius += (radiusOuter - radiusInner);
    bigCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);

    //大圆抛去小圆部分
    QPainterPath gradientPath = bigCircle - smallCircle;
    QRadialGradient gradient(0, 0, radius, 0, 0);
    //gradient.setSpread(QGradient::ReflectSpread);

    gradient.setColorAt(0.7, colorInnerStart);
    gradient.setColorAt(1, colorInnerEnd);
    painter->setBrush(gradient);
    painter->drawPath(gradientPath);

    painter->restore();
}

void GaugePanel::drawOuterHalo(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;

    float radius = radiusHalo;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius += (100.0 - radiusHalo);
    bigCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);

    //大圆抛去小圆部分
    QPainterPath gradientPath = bigCircle - smallCircle;
    QRadialGradient gradient(0, 0, 100, 0, 0);
    gradient.setSpread(QGradient::ReflectSpread);

    gradient.setColorAt(radiusHalo/100, colorHaloStart);
    gradient.setColorAt(1, colorHaloEnd);
    painter->setBrush(gradient);
    painter->drawPath(gradientPath);

    painter->restore();
}

void GaugePanel::drawScale(QPainter *painter)
{
    float radius = 85;
    painter->save();
    painter->setPen(QColor(255, 255, 255));

    painter->rotate(30);
    int steps = (30);
    double angleStep = (360.0 - 60) / steps;
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % 3 == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            QLineF line(0.0f, radius - 8.0f, 0.0f, radius);
            painter->drawLine(line);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            QLineF line(0.0f, radius - 3.0f, 0.0f, radius);
            painter->drawLine(line);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void GaugePanel::drawScaleNum(QPainter *painter)
{
    float radius = 95.0f;
    painter->save();
    painter->setPen(QPen(Qt::black, 10, Qt::DashDotLine, Qt::RoundCap));
    //QColor(0,85,127)
    double startRad = (330 - 90) * (M_PI / 180);
    double deltaRad = (300) * (M_PI / 180) / 10;

    for (int i = 0; i <= 10; i++) {
        double sina = sin(startRad - i * deltaRad);
        double cosa = cos(startRad - i * deltaRad);
        double value = 1.0 * i * ((100) / 10);//刻度值范围

        QString strValue = QString("%1").arg((double)value, 0, 'f', 0);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void GaugePanel::drawPointer(QPainter *painter)
{
    painter->save();

    float radius = 83.0;
    painter->rotate(30+int(value*10));
    QPen pen = painter->pen();
    pen.setWidthF(1.0);
    pen.setColor(QColor(50, 154, 255, 200));
    painter->setPen(pen);
    QLineF line(0.0f, 0.0f, 0.0f, radius);
    painter->drawLine(line);

    painter->restore();
}

void GaugePanel::drawPointerSector(QPainter *painter)
{
    float radius = 87.5f;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius, radius * 2, radius * 2);
    painter->setBrush(QColor(50, 154, 255, 50));
    painter->drawPie(rect, -120*16, -value*16*10);

    painter->restore();
}

void GaugePanel::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(QColor(255, 255, 255));
    painter->setFont(QFont("Arial", 22, 22, true));

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)value, 0, 'f', 0);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void GaugePanel::drawUnit(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(QColor(255, 255, 255));
    painter->setFont(QFont("Arial", 9, -1, true));

    QRectF textRect(-radius, -radius+20, radius * 2, radius * 2);
    painter->drawText(textRect, Qt::AlignCenter, "km/h");

    painter->restore();
}

double GaugePanel::getValue() const
{
    return this->value;
}

int GaugePanel::getHShearValue() const
{
    return this->hShearValue;
}

int GaugePanel::getVShearValue() const
{
    return this->vShearValue;
}

double GaugePanel::getRadiusInner() const
{
    return radiusInner;
}

double GaugePanel::getRadiusOuter() const
{
    return radiusOuter;
}

double GaugePanel::getRadiusHalo() const
{
    return radiusHalo;
}

QColor GaugePanel::getColorOuterFrame() const
{
    return colorOuterFrame;
}

QColor GaugePanel::getColorInnerStart() const
{
    return colorInnerStart;
}

QColor GaugePanel::getColorInnerEnd() const
{
    return colorInnerEnd;
}

QColor GaugePanel::getColorOuterStart() const
{
    return colorOuterStart;
}

QColor GaugePanel::getColorOuterEnd() const
{
    return colorOuterEnd;
}

QColor GaugePanel::getColorHaloStart() const
{
    return colorHaloStart;
}

QColor GaugePanel::getColorHaloEnd() const
{
    return colorHaloEnd;
}

void GaugePanel::setValue(int value)
{
    setValue(double(value));
}

void GaugePanel::setValue(double value) {
    updateValue(value);
}

void GaugePanel::setHShearValue(int value)
{
    if(value > 100 || value < -100)
        return;

    this->hShearValue = value;
    update();
}

void GaugePanel::setVShearValue(int value)
{
    if(value > 100 || value < -100)
        return;

    this->vShearValue = value;
    update();
}

void GaugePanel::setColorOuterFrame(QColor color)
{
    colorOuterFrame = color;
}

void GaugePanel::setRadiusInner(int radius)
{
    setRadiusInner(double(radius));
}

void GaugePanel::setRadiusInner(double radius)
{
    if(radius >= 0.0f && radius < 100.0f){
        radiusInner = radius;
        update();
    }
}

void GaugePanel::setRadiusOuter(int radius)
{
    setRadiusOuter(double(radius));
}

void GaugePanel::setRadiusOuter(double radius)
{
    if(radius > 0.0f && radius < 100.0f){
        radiusOuter = radius;
        update();
    }
}

void GaugePanel::setRadiusHalo(int radius)
{
    setRadiusHalo(double(radius));
}

void GaugePanel::setRadiusHalo(double radius)
{
    if(radius > 0.0f && radius < 100.0f){
        radiusHalo = radius;
        update();
    }
}

void GaugePanel::setColorInnerStart(QColor color)
{
    colorInnerStart = color;
}

void GaugePanel::setColorInnerEnd(QColor color)
{
    colorInnerEnd = color;
}

void GaugePanel::setColorOuterStart(QColor color)
{
    colorOuterStart = color;
}

void GaugePanel::setColorOuterEnd(QColor color)
{
    colorOuterEnd = color;
}

void GaugePanel::setColorHaloStart(QColor color)
{
    colorHaloStart = color;
}

void GaugePanel::setColorHaloEnd(QColor color)
{
    colorHaloEnd = color;
}

void GaugePanel::startShearAnimal(int duration, int hShearValue, int vShearValue)
{
    if(hShearValue == this->hShearValue && vShearValue == this->vShearValue){
        return;
    }

    if(hShearAnimation->state() != QPropertyAnimation::Stopped){
        hShearAnimation->stop();
    }

    if(vShearAnimation->state() != QPropertyAnimation::Stopped){
        vShearAnimation->stop();
    }

    hShearAnimation->setDuration(duration);
    hShearAnimation->setStartValue(this->hShearValue);
    hShearAnimation->setEndValue(hShearValue);
    hShearAnimation->start();

    vShearAnimation->setDuration(duration);
    vShearAnimation->setStartValue(this->vShearValue);
    vShearAnimation->setEndValue(vShearValue);
    vShearAnimation->start();
}

void GaugePanel::updateValue(double value)
{
    if(value > 30.0 || value < 0.0){
        return;
    }

    this->value = value;
    //update();
    this->update();
   // emit valueChanged(value);
}
