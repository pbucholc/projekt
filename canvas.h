#ifndef CANVAS_H
#define CANVAS_H

#include <QtWidgets>

class Canvas : public QWidget
{
    Q_OBJECT

    QPoint playerPos;
    QTimer *timer, *pointsTimer,*ammoTimer;
    QImage background;
    QImage player;
    QImage heart;

    QVector<QImage> bullets;
    QVector<QImage> enemies;


    bool right, left;

    QVector<QPoint> points;
    QVector<QPoint> ammo;
    int maxPoints;
    int booster;
    int activeBullet;
    int health;

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    void updatePlayerPos();
    void checkMapBounds();
    void checkEnemyOnFire();
    void addAmmo();
    void checkPlayerCrash();
    void changeBullet();


public:
    void boost(int booster);
    void setHealth(int health);

private slots:
    void updatePos();
    void movePointsDown();
    void moveAmmo();


public:
    explicit Canvas(QWidget *parent = 0);

signals:
    void deadPoint();
    void deadPlayer();

public slots:

};

#endif // CANVAS_H
