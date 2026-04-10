#ifndef INFINITESCENE_H
#define INFINITESCENE_H

#include <QMainWindow>
#include<QPainter>
#include"mycoin.h"
#include<QMediaPlayer>
#include<QAudioOutput>
#include<QPropertyAnimation>
#include<QLabel>

class InfiniteScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit InfiniteScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);

    //创建游戏硬币初始状态
    QVector<QVector<int>>coinInt;
    QVector<QVector<MyCoin*>>coinArr;

    bool isWin();

    QLabel *winLabel = NULL;

    //硬币音效
    QMediaPlayer *player;
    QAudioOutput *audio;

    QPropertyAnimation *animation = NULL;

    int mp[4][4];

    QPushButton *next;

    void resetLevel();

signals:
    void infiniteSceneBack();

    void nextLevel();
};

#endif // INFINITESCENE_H
