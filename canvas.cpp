#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    srand(QDateTime::currentMSecsSinceEpoch());

    maxPoints=5;
    for (int i=0; i<maxPoints; i++){
        QPoint point((i+1)*100,0);
        points.push_back(point);
    }

    this->setFixedSize(640,480);

    background = QImage(":/images/background.png");
    player=QImage(":/images/player.png");
    heart=QImage(":/images/heart.png");

    bullets.push_back(QImage(":/images/bullet1.png"));
    bullets.push_back(QImage(":/images/bullet2.png"));
    bullets.push_back(QImage(":/images/bullet3.png"));

    enemies.push_back(QImage(":/images/enemy1.png"));
    enemies.push_back(QImage(":/images/enemy2.png"));
    enemies.push_back(QImage(":/images/enemy3.png"));
    enemies.push_back(QImage(":/images/enemy4.png"));
    enemies.push_back(QImage(":/images/enemy5.png"));


    playerPos=QPoint(width()/2, height()-16);
    this->setFocusPolicy(Qt::StrongFocus);

    right=left=false;
    booster=1;
    activeBullet=0;
    health=3;

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            SLOT(updatePos()));
    timer->start(1000./300);

    pointsTimer=new QTimer(this);
    connect(pointsTimer,SIGNAL(timeout()),
            SLOT(movePointsDown()));
    pointsTimer->start(10);

    ammoTimer=new QTimer(this);
    connect(ammoTimer,SIGNAL(timeout()),
            SLOT(moveAmmo()));
    ammoTimer->start(3);


}

void Canvas::paintEvent(QPaintEvent *) {

    QPainter painter(this);
    painter.drawImage(0,0,background);


    for(int i=0; i<points.size(); i++)
        painter.drawImage(points[i].x()-12,points[i].y()-9,enemies[i]);

    painter.drawImage(playerPos.x()-15,playerPos.y()-18,player);

    painter.setBrush(QColor(233,56,31));
    painter.setPen(QColor(255,0,0));

    for(int i=0; i<ammo.size(); i++)
        painter.drawImage(ammo[i].x()-5,ammo[i].y()-9,bullets[activeBullet]);

    if(health==3){
        painter.drawImage(510,10,heart);
        painter.drawImage(560,10,heart);
        painter.drawImage(610,10,heart);
    }

    else if(health==2){
        painter.drawImage(560,10,heart);
        painter.drawImage(610,10,heart);
    }

    else if(health==1)
        painter.drawImage(610,10,heart);

}
void Canvas::checkEnemyOnFire() {

    for (int i=0; i<ammo.size(); i++)

        for (int j=0; j<points.size(); j++)

            if (ammo[i].y() <= points[j].y() &&
                    ammo[i].x() >= points[j].x()-13 &&
                    ammo[i].x() <= points[j].x()+13){
                points[j] = QPoint (rand()%width(),0);
                deadPoint();
            }
}
void Canvas::checkPlayerCrash(){

    for(int i=0;i<points.size();i++)
        if(playerPos.y()<=points[i].y() &&
                playerPos.x()>=points[i].x()-15 &&
                playerPos.x()<=points[i].x()+15){

                if(health==0)
                    deadPlayer();
                else{
                    health--;
                    playerPos.setX(width()/2);
                    playerPos.setY(height()-16);
                    for(int i=0;i<points.size();i++)
                        points[i]=QPoint ((i+1)*100,0);
                }

        }


}

void Canvas::movePointsDown() {

    for (int i=0; i<points.size(); i++){
        points[i].setY(points[i].y()+1);
        if (points[i].y() >= height()-1)
            points[i] = QPoint (rand()%width(),0);
    }

}

void Canvas::moveAmmo(){

    for(int i=0; i<ammo.size(); i++){
        ammo[i].setY(ammo[i].y()-1);
        if(ammo[i].y()==0)
            ammo.erase(ammo.begin()+i);
    }

}
void Canvas::addAmmo(){

    QPoint a(playerPos.x(),playerPos.y()-27);
    ammo.push_back(a);

}
void Canvas::boost(int booster){

    this->booster=booster;
    pointsTimer->start(10-booster);

}
void Canvas::changeBullet(){

    activeBullet++;

    if(activeBullet>=3)
        activeBullet=0;

}
void Canvas::setHealth(int health){

    this->health=health;
}

void Canvas::updatePos() {

    updatePlayerPos();
    checkMapBounds();
    checkEnemyOnFire();
    checkPlayerCrash();
    update();
}
//liza.umcs.lublin.pl/~kdmitruk/gra.zip

void Canvas::checkMapBounds() {

    if(playerPos.x()<0) playerPos.setX(width()-1);
    if(playerPos.x()>width()-1) playerPos.setX(0);
    if(playerPos.y()<0) playerPos.setY(height()-1);
    if(playerPos.y()>height()-1) playerPos.setY(0);
}

void Canvas::updatePlayerPos() {

    if(left)    playerPos+=QPoint(-1,0);
    if(right)   playerPos+=QPoint(1,0);
}

void Canvas::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Left:  left=true; break;
    case Qt::Key_Right: right=true; break;

    }
}

void Canvas::keyReleaseEvent(QKeyEvent *event) {

    switch(event->key()) {
    case Qt::Key_Left:  left=false; break;
    case Qt::Key_Right: right=false; break;
    case Qt::Key_Space: addAmmo(); break;
    case Qt::Key_Up:    changeBullet(); break;
    }
}

