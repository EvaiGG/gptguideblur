#include "widget.h"
#include <QImage>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::cutScreen()
{

}

void Widget::gaussBlur(QImage *img)
{
    // 加载图片
    QImage image("test.jpg");
    if (image.isNull())
    {
        qDebug() << "无法加载图片";
        return ;
    }

    // 转换为灰度图像
    QImage grayImage = image.convertToFormat(QImage::Format_Grayscale8);

    // 创建高斯滤波器
    int size = 15;
    int sigma = 5;
    QVector<double> kernel(size);
    for (int i = 0; i < size; i++)
    {
        kernel[i] = exp(-(i - size / 2) * (i - size / 2) / (2.0 * sigma * sigma));
    }
    double sum = std::accumulate(kernel.begin(), kernel.end(), 0.0);
    for (int i = 0; i < size; i++)
    {
        kernel[i] /= sum;
    }

    // 对图像进行高斯卷积
    QImage blurredImage(grayImage.size(), grayImage.format());
    QPainter painter(&blurredImage);
    QLinearGradient gradient(0, 0, 0, blurredImage.height());
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);
    QBrush brush(gradient);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawImage(QPoint(), grayImage);
    for (int i = 0; i < size; i++)
    {
        QPoint offset(i - size / 2, i - size / 2);
        QImage temp = blurredImage.copy(offset.x(), offset.y(), blurredImage.width() - abs(offset.x()), blurredImage.height() - abs(offset.y()));
        temp = temp.copy(0, 0, blurredImage.width(), blurredImage.height());
        double value = kernel[i];
        painter.setOpacity(value);
        painter.drawImage(QPoint(), temp);
    }
    painter.end();

    // 保存卷积结果
    QPixmap pixmap = QPixmap::fromImage(blurredImage);
    pixmap.save("blurred.jpg");
}



