#ifndef BUILDING_H
#define BUILDING_H

#include <QPushButton>
#include"map.h"
#include<QTimer>
#include<QLabel>
class building : public QPushButton
{
    Q_OBJECT
public:

    building(loc location,QWidget *parent);
    QLabel *HP=NULL;
    QTimer *T=NULL;
    QWidget *par;
    loc location;
    int name=0;
    int level=0;
    int cost=0;
    int iteration=0;
    int hp=0;
    void attack1();
signals:
    void chooseBuilding();
};

#endif // BUILDING_H
