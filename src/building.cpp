#include "building.h"
#include<cmath>
building::building(loc location,QWidget *parent){
    this->setFixedSize(50,50);
    this->setFlat(true);
    this->move(location.x*50,location.y*50+100);
    this->setIconSize(QSize(40,40));
    this->location=location;
    par =parent;
    HP= new QLabel;
    HP->setAttribute(Qt::WA_TransparentForMouseEvents);
    HP->setText(QString::number(hp));
    HP->move(location.x*50,location.y*50+95);
    HP->setFixedSize(50,15);
    HP->setAlignment(Qt::AlignCenter);
    HP->setFont(QFont("华文中宋",7));
    T=new QTimer(parent);
    T->start(100);

}
void building::attack1(){

}
