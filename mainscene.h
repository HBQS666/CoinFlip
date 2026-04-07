#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include"choselevelscene.h"
#include<QMediaPlayer>
#include<QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //绘制主场景界面图片函数 以及 标题
    void paintEvent(QPaintEvent *);


    //声音
    QMediaPlayer *mediaPlayer;
    QAudioOutput *audioOutput;

    choseLevelScene *choseSence = NULL;
private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H


