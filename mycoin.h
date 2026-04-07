#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString coinImg);

    //金币属性
    int posX;
    int posY;
    bool flag;

    //改变金币函数
    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min = 1;
    int max = 8;

    //判断当前动画是否完成
    bool isAnimation = false;

    //重写按下鼠标逻辑
    void mousePressEvent(QMouseEvent*e);

    //记录当前是否胜利
    bool win = false;

signals:
};

#endif // MYCOIN_H
