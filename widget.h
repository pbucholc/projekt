#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>

class Canvas;

class Widget : public QWidget
{
    Q_OBJECT


    Canvas *canvas;
    QLCDNumber *lcd;
    QLabel *lcdLabel;
    QLCDNumber *lcdTimer;
    QLabel *lcdTimerLabel;
    QLCDNumber *lcdLevel;
    QLabel *lcdLevelLabel;

    QTimer *timer;
    QLabel *info;
    QLabel *game_over;


    int counter;
    int game_time;
    int level;

private slots:
    void increment_and_display();
    void changeGameLevelAndTime();
    void gameOverInfo();

public:
    Widget(QWidget *parent = 0);
    ~Widget();

};

#endif // WIDGET_H
