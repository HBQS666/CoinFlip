#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"
#include<QMediaPlayer>
#include<QAudioOutput>

class playScene : public QMainWindow
{
    Q_OBJECT
public:
    // explicit playScene(QWidget *parent = nullptr);

    //构造方式
    playScene(int levelNum);

    //记录当前关卡数
    int levelIndex;

    //重写绘图事件
    void paintEvent(QPaintEvent*);

    //维护当前关卡的金银币状态
    QVector<QVector<int> >mp;

    //维护每一个金币的状态
    QVector<QVector<MyCoin*>>coinArr;

    //判断是否胜利
    bool isWin();

    //设置音效
    QMediaPlayer *clickPlayer;
    QAudioOutput *clickOutput;




signals:
    //发出一个返回信号
    void playSceneBack();
};

#endif // PLAYSCENE_H
