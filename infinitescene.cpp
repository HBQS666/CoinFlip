#include "infinitescene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QLabel>
#include<QPixmap>
#include"mycoin.h"
#include<QRandomGenerator>
#include<QTimer>
#include<QDebug>
#include<QPropertyAnimation>
#include<QMenuBar>

InfiniteScene::InfiniteScene(QWidget *parent)
    : QMainWindow{parent}
{
    //初始化音效
    this->player = new QMediaPlayer(this);
    this->audio = new QAudioOutput(this);
    this->player->setAudioOutput(audio);

    this->setFixedSize(320,588);
    this->setWindowTitle("无限模式");

    //下一关按钮初始化
    this->next = new QPushButton(this);
    QPixmap pixNext;
    pixNext.load(":/picture/res/next.png");
    pixNext = pixNext.scaled(QSize(100,60),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    next->setIcon(pixNext);
    next->setFixedSize(pixNext.width(),pixNext.height());
    next->setIconSize(QSize(pixNext.width(),pixNext.height()));
    next->setStyleSheet("QPushButton{border:0px;}");
    next->move(0,-100);

    //创造一个菜单栏
    QMenuBar*bar = new QMenuBar(this);
    setMenuBar(bar);
    QMenu *Menu = bar->addMenu("开始");

    connect(Menu->addAction("重新开始"),&QAction::triggered,[=](){
        for(int i = 0;i<4;i++){
            for(int j = 0;j<4;j++){
                if(mp[i][j]){
                    coinArr[i][j]->flag = 1;
                    coinArr[i][j]->coinImgPath = ":/picture/res/Coin0001.png";
                    coinArr[i][j]->setIcon(QIcon(coinArr[i][j]->coinImgPath));
                    coinInt[i][j] = mp[i][j];
                }else{
                    coinArr[i][j]->flag = 0;
                    coinArr[i][j]->coinImgPath = ":/picture/res/Coin0008.png";
                    coinArr[i][j]->setIcon(QIcon(coinArr[i][j]->coinImgPath));
                    coinInt[i][j] = mp[i][j];
                }
            }
        }
    });

    //添加返回按钮
    MyPushButton *backBtn = new MyPushButton(":/picture/res/BackButton.png",":/picture/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(),this->height() - backBtn->height());

    //点击返回按钮发出信号
    connect(backBtn,&QPushButton::clicked,[=](){
        player->setSource(QUrl("qrc:/picture/res/BackButtonSound.wav"));
        this->player->play();
        emit this->infiniteSceneBack();
    });

    //加载胜利图片
    this->winLabel = new QLabel(this);
    QPixmap pix;
    pix.load(":/picture/res/LevelCompletedDialogBg.png");
    winLabel->setFixedSize(QSize(pix.width(),pix.height()));
    winLabel->setPixmap(pix);
    winLabel->move((this->width()-pix.width())*0.5,-pix.height());
    QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");

    //绑定下一关按钮 实现点击动画效果
    connect(next,&QPushButton::pressed,[=](){
        this->next->setGeometry(next->x()+2,next->y()+2,next->width()-4,next->height()-4);
    });

    connect(next,&QPushButton::released,[=](){
        this->next->setGeometry(next->x()-2,next->y()-2,next->width()+4,next->height()+4);
        this->winLabel->move((this->width()-pix.width())*0.5,-pix.height());
        emit this->nextLevel();
    });

    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++) mp[i][j] = 1;
    }

    this->coinInt.resize(4);
    for(int i = 0;i<4;i++){
        coinInt[i].resize(4);
    }
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++) coinInt[i][j] = 1;
    }

    this->coinArr.resize(4);
    for(int i = 0;i<4;i++) coinArr[i].resize(4);

    //添加硬币背景
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            QLabel *label = new QLabel(this);
            QPixmap pix;
            pix.load(":/picture/res/BoardNode.png");
            label->setPixmap(pix);

            label->setFixedSize(pix.width(),pix.height());
            label->move(57+i*50,200+j*50);

            QString coinPath = "";
            if(this->coinInt[i][j]){
                coinPath = ":/picture/res/Coin0001.png";
            }else{
                coinPath = ":/picture/res/Coin0008.png";
            }

            MyCoin *coin = new MyCoin(coinPath);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX = i;
            coin->posY = j;
            coin->flag = 1;
            coinArr[i][j] = coin;
        }
    }

    for(int t = 0;t<10;t++){
        int i = QRandomGenerator::global()->bounded(4);
        int j = QRandomGenerator::global()->bounded(4);
        coinArr[i][j]->justChange();

        this->mp[i][j] = mp[i][j] == 1?0:1;
        this->coinInt[i][j] = coinInt[i][j] == 1?0:1;

        if(coinArr[i][j]->posX-1>=0){
            coinArr[i-1][j]->justChange();
            coinInt[i-1][j] = coinInt[i-1][j] == 1?0:1;
            mp[i-1][j] = mp[i-1][j] == 1?0:1;
        }

        //反转右侧金币
        if(coinArr[i][j]->posX+1<4){
            coinArr[i+1][j]->justChange();
            coinInt[i+1][j] = coinInt[i+1][j] == 1?0:1;
            mp[i+1][j] = mp[i+1][j] == 1?0:1;
        }

        //翻转上侧金币
        if(coinArr[i][j]->posY-1>=0){
            coinArr[i][j-1]->justChange();
            coinInt[i][j-1] = coinInt[i][j-1] == 1?0:1;
            mp[i][j-1] = mp[i][j-1] == 1?0:1;
        }

        //翻转下侧金币
        if(coinArr[i][j]->posY+1<4){
            coinArr[i][j+1]->justChange();
            coinInt[i][j+1] = coinInt[i][j+1] == 1?0:1;
            mp[i][j+1] = mp[i][j+1] == 1?0:1;
        }

    }

    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            QString coinPath = "";

            if(coinInt[i][j]){
                coinPath = ":/picture/res/Coin0001.png";
            }else{
                coinPath = ":/picture/res/Coin0008.png";
            }
            coinArr[i][j]->coinImgPath = coinPath;

            MyCoin *coinTemp = coinArr[i][j];

            connect(coinTemp,&QPushButton::clicked,[=](){
                coinTemp->changeFlag();
                this->coinInt[coinTemp->posX][coinTemp->posY] = coinInt[coinTemp->posX][coinTemp->posY] == 1?0:1;

                //添加翻转硬币音效
                this->player->setSource(QUrl("qrc:/picture/res/ConFlipSound.wav"));
                this->player->play();

                QTimer::singleShot(300,this,[=](){
                    if(coinTemp->posX-1>=0){
                        coinArr[coinTemp->posX-1][coinTemp->posY]->changeFlag();
                        coinInt[coinTemp->posX-1][coinTemp->posY] = coinInt[coinTemp->posX-1][coinTemp->posY] == 1?0:1;
                    }

                    //反转右侧金币
                    if(coinTemp->posX+1<4){
                        coinArr[coinTemp->posX+1][coinTemp->posY]->changeFlag();
                        coinInt[coinTemp->posX+1][coinTemp->posY] = coinInt[coinTemp->posX+1][coinTemp->posY] == 1?0:1;
                    }

                    //翻转上侧金币
                    if(coinTemp->posY-1>=0){
                        coinArr[coinTemp->posX][coinTemp->posY-1]->changeFlag();
                        coinInt[coinTemp->posX][coinTemp->posY-1] = coinInt[coinTemp->posX][coinTemp->posY-1] == 1?0:1;
                    }

                    //翻转下侧金币
                    if(coinTemp->posY+1<4){
                        coinArr[coinTemp->posX][coinTemp->posY+1]->changeFlag();
                        coinInt[coinTemp->posX][coinTemp->posY+1] = coinInt[coinTemp->posX][coinTemp->posY+1] == 1?0:1;
                    }

                    if(isWin()){
                        for(int i = 0;i<4;i++){
                            for(int j = 0;j<4;j++){
                                coinArr[i][j]->win = 1;
                            }
                        }

                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->setDuration(1000);
                        animation->start();

                        //添加胜利音效
                        this->player->setSource(QUrl("qrc:/picture/res/LevelWinSound.wav"));
                        this->player->play();

                        //显示下一关按钮
                        next->move((this->width()-next->width())*0.5,this->height()*0.7);
                    }


                });


            });

        }
    }
}

void InfiniteScene::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/picture/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

bool InfiniteScene::isWin(){
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            if(coinInt[i][j] == 0)
                return false;
        }
    }
    return true;
}

void InfiniteScene::resetLevel(){


    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            this->mp[i][j] = 1;
            this->coinInt[i][j] = 1;
            this->coinArr[i][j]->flag = 1;
            this->coinArr[i][j]->win = 0;
        }
    }

    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            QString coinPath = "";
            if(coinInt[i][j]){
                coinPath = ":/picture/res/Coin0001.png";
            }else{
                coinPath = ":/picture/res/Coin0008.png";
            }
            coinArr[i][j]->coinImgPath = coinPath;
            coinArr[i][j]->setIcon(QIcon(coinArr[i][j]->coinImgPath));
        }
    }

    for(int t = 0;t<10;t++){
        int i = QRandomGenerator::global()->bounded(4);
        int j = QRandomGenerator::global()->bounded(4);
        coinArr[i][j]->justChange();

        this->mp[i][j] = mp[i][j] == 1?0:1;
        this->coinInt[i][j] = coinInt[i][j] == 1?0:1;

        if(coinArr[i][j]->posX-1>=0){
            coinArr[i-1][j]->justChange();
            coinInt[i-1][j] = coinInt[i-1][j] == 1?0:1;
            mp[i-1][j] = mp[i-1][j] == 1?0:1;
        }

        //反转右侧金币
        if(coinArr[i][j]->posX+1<4){
            coinArr[i+1][j]->justChange();
            coinInt[i+1][j] = coinInt[i+1][j] == 1?0:1;
            mp[i+1][j] = mp[i+1][j] == 1?0:1;
        }

        //翻转上侧金币
        if(coinArr[i][j]->posY-1>=0){
            coinArr[i][j-1]->justChange();
            coinInt[i][j-1] = coinInt[i][j-1] == 1?0:1;
            mp[i][j-1] = mp[i][j-1] == 1?0:1;
        }

        //翻转下侧金币
        if(coinArr[i][j]->posY+1<4){
            coinArr[i][j+1]->justChange();
            coinInt[i][j+1] = coinInt[i][j+1] == 1?0:1;
            mp[i][j+1] = mp[i][j+1] == 1?0:1;
        }

    }


}







