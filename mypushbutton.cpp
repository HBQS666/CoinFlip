#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>

// MyPushButton::MyPushButton(QWidget *parent)
//     : QPushButton{parent}
// {}


MyPushButton::MyPushButton(QString normalImg,QString pressedImg){
    //路径属性赋值
    this->normalImgPath = normalImg;
    this->pressedImgPath = pressedImg;

    QPixmap pix;
    bool isLoad = pix.load(normalImgPath);

    //判断图片是否成功加载
    if(!isLoad){
        qDebug()<<"Load Picture Fail!";
        return ;
    }

    //设置按钮固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyPushButton::zoom1(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);

    //设置弹跳起点
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳终点
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutCurve);

    //执行动画
    animation->start();

}

void MyPushButton::zoom2(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);

    //设置弹跳起点
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳终点
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutCurve);

    //执行动画
    animation->start();

}

void MyPushButton::mousePressEvent(QMouseEvent*e){

    if(this->pressedImgPath!=""){
        QPixmap pix;
        bool isLoad = pix.load(this->pressedImgPath);
        if(!isLoad){
            qDebug()<<"Picture Load Fail!";
            return ;
        }

        //设置按钮大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

    }

    //交还给父对象
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent*e){
    QPixmap pix;
    bool isLoad = pix.load(this->normalImgPath);
    if(!isLoad){
        qDebug()<<"Picture Load Fail!";
        return ;
    }

    //设置按钮大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图形样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->  setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
    //还给父对象
    return QPushButton::mouseReleaseEvent(e);

}

















