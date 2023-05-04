#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

   QImage bkgImg;

   QPixmap blurImg;
   void cutScreen();
   void gaussBlur(QImage *img);

protected:
   void paintEvent(QPaintEvent * event) override;
};


#endif // WIDGET_H
