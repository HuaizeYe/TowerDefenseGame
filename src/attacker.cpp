#include "attacker.h"
#include<QDebug>
attacker::attacker(QWidget *par,map *ori, QPixmap pix,int category,int stage)
{
    HP=new QLabel(par);
    DEAD  = new QLabel(par);
    this->setParent(par);
    this->show();
    B = new QTimer(this);
    C=new QTimer(this);
    D=new QTimer(this);
    D->start(2000);
    this->setFixedSize(50,50);
    this->setPixmap(pix);
    this->setScaledContents(true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    HP->setAttribute(Qt::WA_TransparentForMouseEvents);
    DEAD->setAttribute(Qt::WA_TransparentForMouseEvents); level=category;
    Map=ori;
    hp=category*(200+20*Map->Level)+10*stage*category;
    if(category==4)
        hp=400+100*Map->Level+10*stage;
    this->category=category;
    choosePath=QRandomGenerator::global()->bounded(0,100)%Map->pathNum;
    for(int i=0;i<ori->pathLen[choosePath];i++)
         path[i]=ori->myPath[choosePath][i];
    curx = path[0].x;
    cury=path[0].y;
    curs=0;
    pixx=curx*50;
    pixy=cury*50+100;
    HP->setText(QString::number(hp));
    HP->move(pixx,pixy+37);
    HP->setFixedSize(50,15);
    HP->setAlignment(Qt::AlignCenter);
    HP->setFont(QFont("华文中宋",7));
    HP->show();
    DEAD->setFixedSize(50,50);
    DEAD->setPixmap(QPixmap(":/Icon4APproject/J.png"));
    DEAD->setScaledContents(true);
    DEAD->hide();
    dead=0;
    newspeed=0;
    connect(B,&QTimer::timeout,[=](){
        newspeed=0;
        B->stop();
    });
    connect(C,&QTimer::timeout,[=](){
        DEAD->hide();
        C->stop();
    });

}

void attacker::Mov1px(int &money,int &deadAtk,building*mybuilding[]){
    //死亡
    if(dead==1){
        this->hide();
        return;
    }    
    if(hp<=0){
        dead=1;
        this->hide();
        HP->hide();
        qDebug()<<"消灭成功";
        money+=level*level*40+80;
        deadAtk++;
        DEAD->move(pixx,pixy);
        DEAD->show();
        C->start(1000);
    }
    iteration++;
    this->move(pixx,pixy);
    HP->setText(QString::number(hp));
    HP->move(pixx,pixy+37);
    //遇到H
    if(Map->Map[curx][cury]>=13&&Map->Map[curx][cury]<=15&&iteration%2==0&&dead==0){
        hp-=Map->Map[curx][cury]-12;
        if(category>3){
            hp-=(Map->Map[curx][cury]-12)*5;
        }
        if(mybuilding[13*cury+curx]->hp>0){
            mybuilding[13*cury+curx]->hp-=1;
            mybuilding[13*cury+curx]->HP->setText(QString::number( mybuilding[13*cury+curx]->hp));
        }
        else{
            Map->Map[curx][cury]=1;
            mybuilding[13*cury+curx]->setIcon(QPixmap());
            mybuilding[13*cury+curx]->HP->setText(QString::number(0));
            mybuilding[13*cury+curx]->HP->hide();
        }

    }
    //速度调控
    if(speed<newspeed){
        speed++;
        return;
    }
    speed=0;
    //A暂停
    if(antistop<stop&&stop!=0&&category<=3){
        if(mybuilding[13*cury+curx]->hp>0){
            mybuilding[13*cury+curx]->hp-=1;
            mybuilding[13*cury+curx]->HP->setText(QString::number( mybuilding[13*cury+curx]->hp));
        }
        else{
            Map->Map[curx][cury]=1;
            stop=0;
            antistop=0;
            mybuilding[13*cury+curx]->setIcon(QPixmap());
            mybuilding[13*cury+curx]->HP->setText(QString::number(0));
            mybuilding[13*cury+curx]->HP->hide();
        }
        if(antistop==stop-1){
            stop=0;
            antistop=0;
        }
        antistop++;
        return;
    }
    if(curs<Map->pathLen[choosePath]-1){
        if(path[curs].x<path[curs+1].x&&curx<path[curs+1].x&&iter==0){
            pixx++;
        }
        else if(path[curs].x>path[curs+1].x&&curx>path[curs+1].x&&iter==0){
            pixx--;
        }
        else if(path[curs].y<path[curs+1].y&&cury<path[curs+1].y&&iter==0){
            pixy++;
        }
        else if(path[curs].y>path[curs+1].y&&cury>path[curs+1].y&&iter==0){
            pixy--;
        }
        if(pixx%50==0&&pixy%50==0){
           curx=pixx/50;
           cury=(pixy-100)/50;
           //遇到A
           if(Map->Map[curx][cury]>=6&&Map->Map[curx][cury]<=8&&category<=3){
               hp-=(Map->Map[curx][cury]-5)*50;
               stop=100*(Map->Map[curx][cury]-5);
               if(mybuilding[13*cury+curx]->hp>0){
                   mybuilding[13*cury+curx]->hp-=1;
                   mybuilding[13*cury+curx]->HP->setText(QString::number( mybuilding[13*cury+curx]->hp));
               }
               else{
                   Map->Map[curx][cury]=1;
                   mybuilding[13*cury+curx]->setIcon(QPixmap());
                   mybuilding[13*cury+curx]->HP->setText(QString::number(0));
                   mybuilding[13*cury+curx]->HP->hide();
               }
           }
           //遇到B
           else if(Map->Map[curx][cury]>=9&&Map->Map[curx][cury]<=11){
               newspeed=Map->Map[curx][cury]-8;
               B->start(6000*newspeed);
               if(mybuilding[13*cury+curx]->hp>0){
                   mybuilding[13*cury+curx]->hp-=1;
                   mybuilding[13*cury+curx]->HP->setText(QString::number( mybuilding[13*cury+curx]->hp));
               }
               else{
                   Map->Map[curx][cury]=1;
                   mybuilding[13*cury+curx]->setIcon(QPixmap());
                   mybuilding[13*cury+curx]->HP->setText(QString::number(0));
                   mybuilding[13*cury+curx]->HP->hide();
               }
           }
           //遇到G
           else if(Map->Map[curx][cury]==12&&category<=3){
               hp=0;
               Map->Map[curx][cury]=1;
               mybuilding[13*cury+curx]->setIcon(QPixmap());
           }
           //遇到I
           else if(Map->Map[curx][cury]>=16&&Map->Map[curx][cury]<=18&&category<=3){
               if(mybuilding[13*cury+curx]->hp>hp){
                   mybuilding[13*cury+curx]->hp-=hp;
                   hp=0;
                   mybuilding[13*cury+curx]->HP->setText(QString::number( mybuilding[13*cury+curx]->hp));
               }
               else{
                   hp-=mybuilding[13*cury+curx]->hp;
                   Map->Map[curx][cury]=1;
                   mybuilding[13*cury+curx]->setIcon(QPixmap());
                   mybuilding[13*cury+curx]->HP->setText(QString::number(0));
                   mybuilding[13*cury+curx]->HP->hide();
               }
           }
        }
        if(curx==path[curs+1].x&&cury==path[curs+1].y)
            curs++;
    }
    else{
        emit loss();
        dead=1;
        qDebug()<<"我到终点了";
    }
}
int attacker::getDistance(){
    if(dead==1)
        return 999;
    int distance=0;
    if(curx==path[curs+1].x)
        distance=path[curs+1].y>cury?path[curs+1].y-cury:cury-path[curs+1].y;
    else
        distance=path[curs+1].x>curx?path[curs+1].x-curx:curx-path[curs+1].x;
    for(int i=curs+1;i<Map->pathLen[choosePath]-1;i++){
       if(path[i].x==path[i+1].x){
           distance+=path[i+1].y>path[i].y?path[i+1].y-path[i].y:path[i].y-path[i+1].y;
       }
       else{
           distance+=path[i+1].x>path[i].x?path[i+1].x-path[i].x:path[i].x-path[i+1].x;
       }
    }
    return distance;
}
void attacker::setHP(int p){
    hp=p;
    HP->setText(QString::number(hp));
}
