#ifndef ATTACKER_H
#define ATTACKER_H

#include <QLabel>
#include"map.h"
#include<QTimer>
#include<building.h>
#include<QRandomGenerator>
class attacker : public QLabel
{
    Q_OBJECT
public:
    attacker(QWidget *par,map *ori,QPixmap pix=QPixmap(),int category=0,int stage=0);
    int hp=0;
    int speed=1;
    map *Map=NULL;
    loc path [20];
    int curx=0,cury=0,curs=0;
    int pixx=0,pixy=0;
    int newspeed=0;
    int dead=0;
    int level=0;
    int iteration=0;
    int choosePath=0;
    int stop=0;
    int antistop=0;
    int iter=0;
    int category=0;
    void Mov1px(int &money,int &deadAtk,building *mybuilding[]);//沿路径移动1像素
    QTimer *B=NULL,*C=NULL,*D=NULL;
    QLabel *HP=NULL;
    QLabel *DEAD=NULL;
    int getDistance();
    void setHP(int p);
signals:
    void loss();
    void win();
    void eliminate();
    void g();
};

#endif // ATTACKER_H
