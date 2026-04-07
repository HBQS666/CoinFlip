#include "choselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QPixmap>
#include<QDebug>
#include"mypushbutton.h"
#include<QLabel>
#include"playscene.h"
#include<QTimer>
#include<QMediaPlayer>
#include<QAudioOutput>

choseLevelScene::choseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{

    //配置音效
    this->mediaPlayer = new QMediaPlayer(this);
    this->audioOutput = new QAudioOutput(this);
    this->mediaPlayer->setAudioOutput(audioOutput);

    //配置选择关卡页面大小
    this->setFixedSize(320,588);

    //配置图标
    this->setWindowIcon(QIcon(":/picture/res/Coin0002.png"));

    //设置页面名称
    this->setWindowTitle("选择关卡");

    //设置菜单栏
    QMenuBar*bar = menuBar();
    setMenuBar(bar);

    //设置开始项
    QMenu *startMenu = bar->addMenu("开始");
    //设置退出项
    QAction *quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //设置返回按钮
    MyPushButton *backButton = new MyPushButton(":/picture/res/BackButton.png",":/picture/res/BackButtonSelected.png");
    backButton->setParent(this);
    backButton->move(this->width() - backButton->width(),this->height() - backButton->height());

    connect(backButton,&QPushButton::clicked,[=](){
        //触发返回音效
        this->mediaPlayer->setSource(QUrl("qrc:/picture/res/BackButtonSound.wav"));
        this->mediaPlayer->play();

        emit this->choseLevelSceneBack();
    });


    //设置关卡按钮
    for(int i = 0;i<20;i++){
        MyPushButton *menuBar = new MyPushButton(":/picture/res/LevelIcon.png");
        menuBar->setParent(this);
        menuBar->move(25+i%4*70,130+i/4*70);

        //设置按钮关卡数
        QLabel *label = new QLabel(this);
        label->setFixedSize(menuBar->width(),menuBar->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        //设置数字居中
        label->setAlignment(Qt::AlignCenter);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        connect(menuBar,&QPushButton::clicked,[=](){
            //触发音效
            this->mediaPlayer->setSource(QUrl("qrc:/picture/res/TapButtonSound.wav"));
            this->mediaPlayer->play();
           //点击关卡按钮进入
            this->play = new playScene(i+1);
            //设置场景居中
            this->play->setGeometry(this->geometry());
            this->hide();
            this->play->show();
            //设置从游戏页面返回关卡选择页面
            connect(play,&playScene::playSceneBack,[=](){
                //触发音效
                this->mediaPlayer->setSource(QUrl("qrc:/picture/res/BackButtonSound.wav"));
                this->mediaPlayer->play();
                QTimer::singleShot(300,this,[=](){
                    //设置场景居中
                    this->setGeometry(this->play->geometry());
                    this->show();
                    delete this->play;
                    play = NULL;
                });
            });
        });


    }

}

void choseLevelScene::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;

    bool isLoad = pix.load(":/picture/res/OtherSceneBg.png");
    if(!isLoad){
        qDebug()<<"Picture Load Fail!";
        return ;
    }

    //绘制选择界面背景
    painter.drawPixmap( 0,0,pix.width(),pix.height(),pix);

    //加载标题图片
    isLoad = pix.load(":/picture/res/Title.png");
    if(!isLoad){
        qDebug()<<"Picture Load Fail!";
        return ;
    }

    painter.drawPixmap(0,0,pix);

}





