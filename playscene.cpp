#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QDebug>
#include"mypushbutton.h"
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>

// playScene::playScene(QWidget *parent)
//     : QMainWindow{parent}
// {}

playScene::playScene(int levelNum){
    //赋值当前第几关
    this->levelIndex = levelNum;

    //设置音效
    this->clickPlayer = new QMediaPlayer(this);
    this->clickOutput = new QAudioOutput(this);
    this->clickPlayer->setAudioOutput(clickOutput);
    //初始化游戏场景

    //设置大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QIcon(":/picture/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币");

    //创建菜单栏
    QMenuBar *bar = new QMenuBar();
    setMenuBar(bar);
    QMenu *startMenu = bar->addMenu("开始");
    QAction *quitAction = startMenu->addAction("退出");

    //实现 点击退出 退出游戏功能
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //初始化胜利图片
    QLabel *successLabel = new QLabel(this);
    QPixmap successPix;
    successPix.load(":/picture/res/LevelCompletedDialogBg.png");
    successLabel->setFixedSize(successPix.width(),successPix.height());
    successLabel->move((this->width()-successPix.width())*0.5,-successPix.height());
    successLabel->setPixmap(successPix);

    //添加一个返回按钮
    MyPushButton *backButton = new MyPushButton(":/picture/res/BackButton.png",":/picture/res/BackButtonSelected.png");
    backButton->setParent(this);
    backButton->move(this->width() - backButton->width(),this->height() - backButton->height());
    //绑定返回事件
    connect(backButton,&MyPushButton::clicked,[=](){
        emit this->playSceneBack();
    });

    //显示当前关卡编号
    QLabel *label = new QLabel();
    label->setParent(this);
    label->setFixedSize(120,50);
    label->move(30,this->height()-50);
    QString string = QString("Level: %1").arg(this->levelIndex);
    label->setText(string);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //将字体设置绑定给标签
    label->setFont(font);

    //用一个二维数组维护金币状态
    dataConfig config;
    this->mp = config.mData[this->levelIndex];

    //初始化存金币数组大小
    coinArr.resize(4);
    for(int i = 0;i<4;i++){
        coinArr[i].resize(4);
    }



    //创建金币的背景
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            QLabel *coinBackgroundLabel = new QLabel;
            QPixmap pix;
            pix.load(":/picture/res/BoardNode.png");
            // pix = pix.scaled(pix.width()*1.5,pix.height()*1.5);
            coinBackgroundLabel->setGeometry(0,0,pix.width(),pix.height());
            coinBackgroundLabel->setPixmap(pix);
            coinBackgroundLabel->setParent(this);
            coinBackgroundLabel->move(57+i*50,200+j*50);

            //设置金币
            QString coinPath = "";
            if(mp[i][j] == 1){
                coinPath = ":/picture/res/Coin0001.png";
            }else{
                coinPath = ":/picture/res/Coin0008.png";
            }

            MyCoin *coin = new MyCoin(coinPath);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = mp[i][j];

            //将金币加入维护数组
            this->coinArr[i][j] = coin;

            //绑定 点击金币事件
            connect(coin,&QPushButton::clicked,[=](){
                //触发音效
                this->clickPlayer->setSource(QUrl("qrc:/picture/res/ConFlipSound.wav"));
                this->clickPlayer->play();
                coin->changeFlag();
                this->mp[i][j] = this->mp[i][j]==1?0:1;

                //设置延时效果
                QTimer::singleShot(300,this,[=](){
                    //翻转四周金币
                    //翻转左侧金币
                    if(coin->posX-1>=0){
                        coinArr[coin->posX-1][coin->posY]->changeFlag();
                        this->mp[coin->posX-1][coin->posY] = this->mp[coin->posX-1][coin->posY]==1?0:1;
                    }

                    //反转右侧金币
                    if(coin->posX+1<4){
                        coinArr[coin->posX+1][coin->posY]->changeFlag();
                        this->mp[coin->posX+1][coin->posY] = this->mp[coin->posX+1][coin->posY]==1?0:1;
                    }

                    //翻转上侧金币
                    if(coin->posY-1>=0){
                        coinArr[coin->posX][coin->posY-1]->changeFlag();
                        this->mp[coin->posX][coin->posY-1] = this->mp[coin->posX][coin->posY-1]==1?0:1;
                    }

                    //翻转下侧金币
                    if(coin->posY+1<4){
                        coinArr[coin->posX][coin->posY+1]->changeFlag();
                        this->mp[coin->posX][coin->posY+1] = this->mp[coin->posX][coin->posY+1]==1?0:1;
                    }

                    if(isWin()){
                        for(int i = 0;i<4;i++){
                            for(int j = 0;j<4;j++){
                                coinArr[i][j]->win = true;
                            }
                            //触发胜利音效
                            this->clickPlayer->setSource(QUrl("qrc:/picture/res/LevelWinSound.wav"));
                            this->clickPlayer->play();

                            //如果胜利 弹下胜利标签
                            QPropertyAnimation *animation = new QPropertyAnimation(successLabel,"geometry");
                            //设置时间
                            animation->setDuration(1000);
                            //设置起始位置
                            animation->setStartValue(QRect(successLabel->x(),successLabel->y(),successLabel->width(),successLabel->height()));
                            //设置结束位置
                            animation->setEndValue(QRect(successLabel->x(),successLabel->y()+114,successLabel->width(),successLabel->height()));
                            //设置弹跳曲线
                            animation->setEasingCurve(QEasingCurve::OutBounce);

                            animation->start();
                        }
                        // qDebug()<<"win!!";
                    }

                });


            });


        }
    }


}


void playScene::paintEvent(QPaintEvent*){
    //加载游戏背景
    QPainter painter(this);
    QPixmap  pix;
    bool isLoad = pix.load(":/picture/res/PlayLevelSceneBg.png");
    if(!isLoad){
        qDebug()<<"Picture Load Fail!";
        return ;
    }
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //加载游戏标题
    isLoad = pix.load(":/picture/res/Title.png");
    if(!isLoad){
        qDebug()<<"Picture Load Fail!";
        return ;
    }
    painter.drawPixmap(0,0,pix);
}

bool playScene::isWin(){
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            if(this->coinArr[i][j]->flag == false){
                return false;
            }
        }
    }
    return true;
}




