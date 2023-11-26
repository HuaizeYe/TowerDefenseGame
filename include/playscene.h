#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QTimer>
#include<QDebug>
#include<QRandomGenerator>
#include"map.h"
#include"QPixmap"
#include"building.h"
#include"mybutton.h"
#include"attacker.h"
#include<cmath>
#include<algorithm>
#include<vector>
namespace Ui {
class playscene;
}

class playscene : public QMainWindow
{
    Q_OBJECT

public:
    int level;
    QString Level;
    map Mymap;
    myButton *a1=NULL,*b1=NULL,*g=NULL,*h1=NULL,*i1=NULL;
    myButton *k1=NULL,*l1=NULL,*m1=NULL,*p1=NULL;
    int money=0;
    int condition=0;
    building *mybuilding[120]={NULL};//有严重错误
    building *choosebuilding=NULL;
    int atkNum=0;
    int curAtk=0;
    int deadAtk=0;
    int stage=0;
    attacker *atk[200]={NULL};
    QTimer *timer1=NULL,*timer2=NULL,*timer3=NULL,*timer4=NULL;
    explicit playscene(QWidget *parent = nullptr,int i=0);
    ~playscene();
    void basicSetUp(int lev);
    void signalSetUp();
    void drawMap();//绘图
    void drawBuilding();
    void addPng(QString path, int x,int y);//加图片标签
    void updateMoney();
    void setupBuildingSlot(building *build=NULL);    
    void drawButton();
    void showButton(int category);
    void hideButton(int category);
    int randomNumber(int i);
    void loss();
    void win();
    void attackerSetUp();
    void createAttacker(int cur);
    void S1(QLabel *s1);
    void S2(QLabel *s2,int x,int y,int s);
    void S3(QLabel *s3,attacker *atk,int s);
    void S4(int x,int y);
    void S5(QLabel *s5,int level,int x,int y);
    void S6(QLabel *s6);
    void createSpecificAttacker(int category,int cur);

signals:
    void chooseBack();
    void chooseRemove();
    void chooseUpdate();
    void chooseBuilding();
private:
    Ui::playscene *ui;
};

#endif // PLAYSCENE_H
