#include "mainscene.h"
#include "./ui_mainscene.h"
#include<Qpainter>
#include "mypushbutton.h"
#include<QTimer>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置声音文件
    mediaPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/picture/res/TapButtonSound.wav"));

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/picture/res/Coin0001.png"));
    // qDebug() << QIcon(":/picture/res/Coin0001.png").isNull();

    //设置主场景名字
    setWindowTitle("翻金币游戏");

    //实现退出功能
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //设置开始按钮
    MyPushButton *startButton = new MyPushButton(":/picture/res/MenuSceneStartButton.png");
    startButton->setParent(this);
    startButton->move(this->width()*0.5-startButton->width()*0.5,this->height()*0.7);

    choseSence = new choseLevelScene;

    //设置点击开始按钮的动画
    connect(startButton,&MyPushButton::clicked,[=](){
        startButton->zoom1();
        startButton->zoom2();

        //点击按钮
        //触发音效
        this->mediaPlayer->play();
        //延时进入下一个界面
        QTimer::singleShot(300,this,[=](){
            //设置场景居中
            this->choseSence->setGeometry(this->geometry());

            //隐藏 主页面
            this->hide();
            //显示 选择关卡 页面
            choseSence->show();
        });

        //监听返回按钮
        connect(choseSence,&choseLevelScene::choseLevelSceneBack,this,[=](){

            QTimer::singleShot(300,this,[=](){
                //设置场景居中
                this->setGeometry(choseSence->geometry());
                //显示主页面
                this->show();
                //隐藏选择关卡页面
                choseSence->hide();
            });

        });

    });


}

//重写 QPainter
void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;

    //绘制主场景背景
    pix.load(":/picture/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //绘制游戏标题图片
    pix.load(":/picture/res/Title.png");
    //缩小标题图片为原大小的 0.5 倍
    // pix = pix.scaled(pix.width()*0.5,pix.width()*0.5);
    painter.drawPixmap(0,0,pix);
}

MainScene::~MainScene()
{
    delete ui;
}

