#ifndef CHOSELEVELSCENE_H
#define CHOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"
#include<QMediaPlayer>
#include<QAudioOutput>

class choseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit choseLevelScene(QWidget *parent = nullptr);

    //绘制选择关卡界面背景
    void paintEvent(QPaintEvent*);

    //设立游戏场景指针
    playScene *play = NULL;

    //设置音效
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;


signals:
    void choseLevelSceneBack();//发出返回信号
};

#endif // CHOSELEVELSCENE_H
