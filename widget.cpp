#include "widget.h"
#include "canvas.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    game_over=new QLabel("GAME OVER",this);
    game_over->setStyleSheet("font-family: courier; color: #a64dff; font-size: 50px;");
    game_over->setGeometry(350,200,300,100);

    counter = 0;
    game_time=0;
    level=1;


    canvas=new Canvas(this);
    canvas->setGeometry(320,10,1,1);

    info=new QLabel("  Press space to shoot enemies.\n"
                    "  You have to collect 40 points\n"
                    "     before one minute expires.\n"
                    "    If it's done you level up.\n"
                    "       You have 3 lifes.\n "
                    "   If the enemies fly into you\n"
                    "       you lose one life.\n"
                    "    To change weapon press up.",this);

    info->setStyleSheet("font-family: courier; color: #a64dff; font-size: 15px;");
    info->setGeometry(10,10,300,105);


    lcd=new QLCDNumber(3,this);
    lcd->setMaximumHeight(35);
    lcd->setMaximumWidth(35);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->setGeometry(10,125,35,35);

    lcdLabel=new QLabel("POINTS",this);
    lcdLabel->setStyleSheet("font-family: courier; color: #a64dff; font-size: 15px;");
    lcdLabel->setGeometry(55,125,50,30);


    lcdTimer=new QLCDNumber(3,this);
    lcdTimer->setMaximumHeight(35);
    lcdTimer->setMaximumWidth(35);
    lcdTimer->setSegmentStyle(QLCDNumber::Flat);
    lcdTimer->setGeometry(10,170,35,35);

    lcdTimerLabel=new QLabel("TIME",this);
    lcdTimerLabel->setStyleSheet("font-family: courier; color: #a64dff; font-size: 15px;");
    lcdTimerLabel->setGeometry(55,170,50,30);


    lcdLevel=new QLCDNumber(3,this);
    lcdLevel->setMaximumHeight(35);
    lcdLevel->setMaximumWidth(35);
    lcdLevel->setSegmentStyle(QLCDNumber::Flat);
    lcdLevel->display(level);
    lcdLevel->setGeometry(10,215,35,35);


    lcdLevelLabel=new QLabel("LEVEL",this);
    lcdLevelLabel->setStyleSheet("font-family: courier; color: #a64dff; font-size: 15px;");
    lcdLevelLabel->setGeometry(55,215,50,30);



    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            SLOT(changeGameLevelAndTime()));
    timer->start(1000);


    connect(canvas,SIGNAL(deadPoint()),SLOT(increment_and_display()));
    connect(canvas,SIGNAL(deadPlayer()),SLOT(gameOverInfo()));

}

void Widget::gameOverInfo() {

    canvas->hide();

}
void Widget::increment_and_display(){
    counter++;
    lcd->display(counter);

}
void Widget::changeGameLevelAndTime(){

    game_time++;
    lcdTimer->display(game_time);

    if (counter>=40 && game_time<=59){

        game_time=0;
        counter=0;
        level++;
        canvas->setHealth(3);
        canvas->boost(level);
        lcdLevel->display(level);
    }
    else if (counter<40 && game_time == 59){
        gameOverInfo();
    }
}

Widget::~Widget()
{

}
