#include "mycoin.h"
#include<QPixmap>
#include<QDebug>

// MyCoin::MyCoin(QWidget *parent)
//     : QPushButton{parent}
// {}


MyCoin::MyCoin(QString coinImg){
    QPixmap pix;
    bool isLoad = pix.load(coinImg);
    //判断图片是否加载成功
    if(!isLoad){
        qDebug()<<"Picture Load Fail!";
        return ;
    }

    this->setFixedSize(QSize(pix.width(),pix.height()));
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    this->setStyleSheet("QPushButton{border:0px;}");

    //初始化计时器
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //绑定金币翻银币信号槽
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString path = QString(":/picture/res/Coin000%1.png").arg(min++);
        pix.load(path);

        this->setFixedSize(QSize(pix.width(),pix.height()));
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(min>max){
            min = 1;
            isAnimation = false;
            timer1->stop();
        }
    });

    //绑定银币翻金币信号槽
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString path = QString(":/picture/res/Coin000%1.png").arg(max--);
        pix.load(path);

        this->setFixedSize(QSize(pix.width(),pix.height()));
        this->setIcon(pix);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(max<min){
            max = 8;
            isAnimation = false;
            timer2->stop();
        }
    });

}


//实现金币翻转函数
void MyCoin::changeFlag(){
    //如果是金币
    if(this->flag){
        this->flag = false;
        this->isAnimation = true;
        //调用正面翻反面计时器
        timer1->start(30);
    }else{
        this->flag = true;
        this->isAnimation = true;
        //调用反面翻正面计时器
        timer2->start(30);
    }
}

//重写鼠标按压逻辑 使其在动画播放期间无法触发点击
void MyCoin::mousePressEvent(QMouseEvent*e){
    if(isAnimation || win){
        return ;
    }else{
        return QPushButton::mousePressEvent(e);
    }
}






