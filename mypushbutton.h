#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数 参数 1:用户传入的图片路径 参数 2:用户传入的按压状态图片路径
    MyPushButton(QString normalImg,QString pressedImg = "");

    //成员属性 用来存储传入的 默认图片路径 和 按压状态图片路径
    QString normalImgPath;
    QString pressedImgPath;

    //弹跳动画
    void zoom1();//向上跳
    void zoom2();//向下跳

    //鼠标按压和释放操作
    void mousePressEvent(QMouseEvent*e );
    void mouseReleaseEvent(QMouseEvent*e);

signals:
};

#endif // MYPUSHBUTTON_H
