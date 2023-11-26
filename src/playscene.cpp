#include "playscene.h"
#include "ui_playscene.h"

playscene::playscene(QWidget *parent,int i) :
    QMainWindow(parent),
    ui(new Ui::playscene)
{
    ui->setupUi(this);
    basicSetUp(i);
    signalSetUp();
    attackerSetUp();
}

playscene::~playscene()
{
    delete ui;
}
void playscene::basicSetUp(int lev){
    this->level=lev;
    this->Level=QString::number(lev);
    //基础设置
    this->setFixedSize(900,600);
    this->setWindowIcon(QPixmap(":/Icon4APproject/A3.png"));
    this->setWindowTitle("简笔塔防—第"+Level+"关");
    this->money=5000+1000*level;
    ui->labelInfo->setText("第"+Level+"关");
    ui->labelInfo->move(0,0);
    ui->labelMoney->setText("金钱:"+QString::number(money));
    ui->labelMoney->move(90,0);
    ui->labellose->move(270,0);
    ui->labelwin->move(270,0);
    ui->labellose->hide();
    ui->labelwin->hide();
    ui->pushButtonBack->move(780,8);
    ui->labelchoose->move(640,50);
    ui->labelchoose->hide();
    ui->labelchoose_2->move(640,50);
    ui->labelchoose_2->hide();
    ui->pushButtonRemove->move(650,160);
    ui->pushButtonRemove->hide();
    ui->pushButtonUpdate->move(760,160);
    ui->pushButtonUpdate->hide();
    ui->pushButtonPause->move(680,8);
    ui->pushButtonHelp->move(580,8);
    ui->pushButtonExport->move(480,8);
    ui->pushButtonInport->move(380,8);
    ui->labelHelp->move(600,100);
    ui->labelDetails->move(690,250);
    ui->labelDetails->setFixedWidth(190);
    timer1 = new QTimer(this);
    timer1->start(25);
    timer2=new QTimer(this);
    timer2->start(500);
    timer3=new QTimer(this);
    timer3->start(5000);
    timer4=new QTimer(this);
    timer4->start(100);
    Mymap = map(level);
    drawMap();
    drawBuilding();
    drawButton();
}
void playscene::signalSetUp(){
    connect(ui->pushButtonBack,&QPushButton::clicked,[=](){
        emit this->chooseBack();
    });
    //移除信号
    connect(ui->pushButtonRemove,&QPushButton::clicked,[=](){
        emit this->chooseRemove();
        choosebuilding->setIcon(QPixmap());
        choosebuilding->hp=0;
        choosebuilding->name=0;
        if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]<19){
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=1;
            }
        else{
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=0;
            }
        money+=choosebuilding->level*choosebuilding->cost/2;
        choosebuilding->HP->hide();
        choosebuilding->level=0;
        updateMoney();
        hideButton(2);
    });
    connect(ui->pushButtonUpdate,&QPushButton::clicked,[=](){
        //emit this->chooseUpdate();
        if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==6&&money>=a1->cost){
            money-=a1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=1000;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=7;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=20;
              choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/A2.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==7&&money>=a1->cost){
            money-=a1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=1000;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=8;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=20;
              choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/A3.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==9&&money>=b1->cost){
            money-=b1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=800;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=10;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=20;
              choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/B2.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==10&&money>=b1->cost){
            money-=b1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=800;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=11;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=20;
              choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/B3.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==13&&money>=h1->cost){
            money-=h1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=2000;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=14;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=20;
              choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/H2.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==14&&money>=h1->cost){
            money-=h1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=2000;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=15;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=20;
              choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/H3.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==16&&money>=i1->cost){
            money-=i1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=1000;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=17;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=500;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/I2.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==17&&money>=i1->cost){
            money-=i1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=1000;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=18;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=500;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/I3.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==19&&money>=k1->cost){
            money-=k1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=500;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]++;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=500;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/K2.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==20&&money>=k1->cost){
            money-=k1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=500;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]++;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=500;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/K3.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==22&&money>=l1->cost){
            money-=l1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=500;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]++;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=200;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/L2.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==23&&money>=l1->cost){
            money-=l1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=500;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]++;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=500;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/L3.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==25&&money>=m1->cost){
            money-=m1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=500;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]++;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=500;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/M2.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==26&&money>=m1->cost){
            money-=m1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=500;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]++;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=500;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/M3.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==28&&money>=p1->cost){
            money-=p1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=500;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]++;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=500;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/P2.png"));
        }
        else if(Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]==29&&money>=p1->cost){
            money-=p1->cost;updateMoney();choosebuilding->level++;choosebuilding->hp+=500;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]++;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]+=500;
            choosebuilding->HP->setText(QString::number(choosebuilding->hp));
             choosebuilding->setIcon(QPixmap(":/Icon4APproject/P3.png"));
        }
        hideButton(2);
        hideButton(3);
    });
    //暂停信号
    connect(ui->pushButtonPause,&QPushButton::clicked,[=](){
        if(condition==0){
            condition=1;
            ui->pushButtonPause->setText("继续");
        }
        else{
            condition=0;
            ui->pushButtonPause->setText("暂停");
        }
    });
    //帮助信号
    connect(ui->pushButtonHelp,&QPushButton::clicked,[=](){
        if(ui->labelHelp->isHidden()){
            hideButton(1);
            hideButton(2);
            hideButton(3);
            ui->labelHelp->show();
        }
        else
            ui->labelHelp->hide();
    });
    //时钟信号
    connect(timer3,&QTimer::timeout,[=](){
        if(condition==0)
            stage++;
        switch (stage%9) {
        case 0:
                ui->labelTips->setText("当前阶段:"+QString::number(stage)+"   升级价格与1级建筑相同，移除返还50%");
            break;
        case 1:
                ui->labelTips->setText("当前阶段:"+QString::number(stage)+"   近战建筑只能放置在道路上");
            break;
        case 2:
                ui->labelTips->setText("当前阶段:"+QString::number(stage)+"   远程建筑只能放置在道路以外");
            break;
        case 3:
                ui->labelTips->setText("当前阶段:"+QString::number(stage)+"   再次点击建筑可以选择升级或移除");
            break;
        case 4:
                ui->labelTips->setText("当前阶段:"+QString::number(stage)+"   建筑名称中若含有数字说明此建筑可以升级");
            break;
        case 5:
                ui->labelTips->setText("当前阶段:"+QString::number(stage)+"   单个建筑最多可以升级2次，每次升级均可增加耐久值");
            break;
        case 6:
                ui->labelTips->setText("当前阶段:"+QString::number(stage)+"   建筑上的数字代表建筑耐久值，耐久值为0建筑会被清除");
            break;
        case 7:
                ui->labelTips->setText("当前阶段:"+QString::number(stage)+"   敌方血量会随阶段数的增加而增加");
            break;
        case 8:
                ui->labelTips->setText("当前阶段:"+QString::number(stage)+"   无地图的关卡你可以导入地图");
            break;
        default:
            break;
        }
    });
    //导出信号
    connect(ui->pushButtonExport,&QPushButton::clicked,[=](){
        QString fileName = QFileDialog::getSaveFileName(this,
                tr("导出地图"),
                "",
                tr("文本文件(*.txt)"));
        Mymap.Export(fileName);
        ui->pushButtonExport->setText("已导出");
    });
    connect(ui->pushButtonInport,&QPushButton::clicked,[=](){
        QString fileName = QFileDialog::getOpenFileName(this,
                                                            tr("导入地图"),
                                                            "F:",
                                                            tr("文本文件(*txt)"));
        Mymap.Import(fileName);

        ui->pushButtonInport->setText("已导入");
        drawMap();
    });
}
void playscene::drawMap(){
    if(Mymap.exist==0)
        return;
    loc last;
    for(int s=0;s<Mymap.pathNum;s++){
        //qDebug()<<s;
        addPng(":/Icon4APproject/E8.png",Mymap.myPath[s][0].x,Mymap.myPath[s][0].y);
        for(int i=0;i<Mymap.pathLen[s]-1;i++){
            loc start=Mymap.myPath[s][i];
            loc end=Mymap.myPath[s][i+1];
            if(i>0){
                if((last.x<start.x&&start.y<end.y)||(last.y>start.y&&start.x>end.x)){
                    addPng(":/Icon4APproject/E3.png",start.x,start.y);
                }
                else  if((last.y<start.y&&start.x>end.x)||(last.x<start.x&&start.y>end.y)){
                    addPng(":/Icon4APproject/E4.png",start.x,start.y);
                }
                else  if((last.y<start.y&&start.x<end.x)||(last.x>start.x&&start.y>end.y)){
                    addPng(":/Icon4APproject/E5.png",start.x,start.y);
                }
                else  if((last.x>start.x&&start.y<end.y)||(last.y>start.y&&start.x<last.x)){
                    addPng(":/Icon4APproject/E6.png",start.x,start.y);
                }
            }
            if(i==Mymap.pathLen[s]-2){
                addPng(":/Icon4APproject/E7.png",end.x,end.y);
            }
            if(start.x==end.x){
                if(start.y<end.y){
                    for(int s=start.y+1;s<end.y;s++){
                    addPng(":/Icon4APproject/E2.png",start.x,s);
                }
                }
                else{
                for(int s=start.y-1;s>end.y;s--){
                    addPng(":/Icon4APproject/E2.png",start.x,s);
                }}
            }
            else{
                if(start.x<end.x){
                for(int s=start.x+1;s<end.x;s++){
                    addPng(":/Icon4APproject/E1.png",s,start.y);
                }}
                else{
                for(int s=start.x-1;s>end.x;s--){
                    addPng(":/Icon4APproject/E1.png",s,start.y);
                }}
            }
            last=start;
        }
    }
}
void playscene::addPng(QString path, int x, int y){
    QPixmap pix=QPixmap(path);
    QLabel * label=new QLabel;
    label->setGeometry(0,0,50,50);
    label->setParent(this);
    label->setPixmap(pix);
    label->setScaledContents(true);
    label->move(x*50,y*50+100);
    label->show();
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
}
void playscene::updateMoney(){
     ui->labelMoney->setText("金钱:"+QString::number(money));
}
void playscene::drawBuilding(){
    for(int m=0;m<9;m++){
        for(int i=0;i<13;i++){
            loc temp=loc(i,m);
            int s=13*m+i;
            mybuilding[s]=new building(temp,this);
           mybuilding[s]->setParent(this);
           mybuilding[s]->HP->setParent(this);
            setupBuildingSlot(mybuilding[s]);
            mybuilding[s]->HP->hide();
            //设置炮塔攻击的特效和动作
            int rann=randomNumber(10);
            int ranb=randomNumber(30);
            connect(mybuilding[s]->T,&QTimer::timeout,[=](){
                if(condition==1){

                }
                else if(mybuilding[s]->name==7&&mybuilding[s]->iteration%(41-mybuilding[s]->level*10)==rann){
                    int x=0,y=0;
                    int max=999;
                    for(int p=0;p<atkNum;p++){
                        if(atk[p]->getDistance()<max&&atk[p]->category<=3){
                            if(abs(mybuilding[s]->location.x*50-atk[p]->pixx)<110&&abs(mybuilding[s]->location.y*50+100-atk[p]->pixy)<110){
                                x=atk[p]->pixx;
                                y=atk[p]->pixy;
                                max = atk[p]->getDistance();
                            }
                        }
                    }
                    if(max!=999){
                        QLabel *s1=new QLabel(this);
                        s1->setPixmap(QPixmap(":/Icon4APproject/O3.png"));
                        s1->setFixedSize(50,50);
                        s1->setScaledContents(true);
                        s1->move(x,y);
                        s1->show();
                        S1(s1);
                        QLabel *s2=new QLabel(this);
                        s2->setPixmap(QPixmap(":/Icon4APproject/O4.png"));
                        s2->setFixedSize(50,50);
                        s2->setScaledContents(true);
                        s2->move(x+y,0);
                        S2(s2,x,y,s);
                        QLabel *s6=new QLabel(this);
                        s6->setPixmap(QPixmap(":/Icon4APproject/O13.png"));
                        s6->setFixedSize(50,50);
                        s6->setScaledContents(true);
                        s6->move(mybuilding[s]->location.x*50,mybuilding[s]->location.y*50+100);
                        s6->show();
                        S1(s6);
                    }
                }
                else if(mybuilding[s]->name==8&&mybuilding[s]->iteration%(26-mybuilding[s]->level*6)==0){
                    int x=0,y=0;
                    int max=999;
                    int maxindex=0;
                    for(int p=0;p<atkNum;p++){
                        if(atk[p]->getDistance()<max){
                            if(abs(mybuilding[s]->location.x*50-atk[p]->pixx)<160&&abs(mybuilding[s]->location.y*50+100-atk[p]->pixy)<160){
                                x=atk[p]->pixx;
                                y=atk[p]->pixy;
                                max = atk[p]->getDistance();
                                maxindex=p;
                            }
                        }
                    }
                    if(max!=999){
                        QLabel *s1=new QLabel(this);
                        s1->setPixmap(QPixmap(":/Icon4APproject/O5.png"));
                        s1->setFixedSize(50,50);
                        s1->setScaledContents(true);
                        s1->move(mybuilding[s]->location.x*50,mybuilding[s]->location.y*50+100);
                        s1->show();
                        S3(s1,atk[maxindex],s);

                        QLabel *s6=new QLabel(this);
                        s6->setPixmap(QPixmap(":/Icon4APproject/O13.png"));
                        s6->setFixedSize(50,50);
                        s6->setScaledContents(true);
                        s6->move(mybuilding[s]->location.x*50,mybuilding[s]->location.y*50+100);
                        s6->show();
                        S1(s6);
                    }
                }
               else if(mybuilding[s]->name==6&&mybuilding[s]->iteration%(50-mybuilding[s]->level*5)==0){
                    int mindistance=999;
                    building *min=NULL;
                    for(int a=0;a<117;a++){
                            if(Mymap.Map[a%13][a/13]==1){
                                if(abs(mybuilding[a]->location.x-mybuilding[s]->location.x)*abs(mybuilding[a]->location.x-mybuilding[s]->location.x)+abs(mybuilding[a]->location.y-mybuilding[s]->location.y)*abs(mybuilding[a]->location.y-mybuilding[s]->location.y)<mindistance){
                                        mindistance=abs(mybuilding[a]->location.x-mybuilding[s]->location.x)*abs(mybuilding[a]->location.x-mybuilding[s]->location.x)+abs(mybuilding[a]->location.y-mybuilding[s]->location.y)*abs(mybuilding[a]->location.y-mybuilding[s]->location.y);
                                        min=mybuilding[a];
                                 }
                            }

                    }
                    if(mindistance<=4){
                        QLabel *s1=new QLabel(this);
                        s1->setPixmap(QPixmap(":/Icon4APproject/O6.png"));
                        s1->setFixedSize(40,40);
                        s1->setScaledContents(true);
                        s1->move(min->location.x*50+5,min->location.y*50+105);
                        s1->show();
                        S1(s1);
                        QLabel *s6=new QLabel(this);
                        s6->setPixmap(QPixmap(":/Icon4APproject/O13.png"));
                        s6->setFixedSize(50,50);
                        s6->setScaledContents(true);
                        s6->move(mybuilding[s]->location.x*50,mybuilding[s]->location.y*50+100);
                        s6->show();
                        S1(s6);
                        Mymap.Map[min->location.x][min->location.y]=16;
                        min->setIcon(QPixmap(":/Icon4APproject/I1.png"));
                        min->level=1;
                        min->name=5;
                        min->cost=i1->cost;
                        min->hp=300+200*mybuilding[s]->level;
                        Mymap.HpMap[min->location.x][min->location.y]=300+200*mybuilding[s]->level;
                        min->HP->setText(QString::number(300+200*mybuilding[s]->level));
                        min->HP->show();
                    }
                }
                else if(mybuilding[s]->name==9&&mybuilding[s]->iteration%(100-mybuilding[s]->level*20)==ranb){
                    int x=0,y=0;
                    int max=999;
                    int maxindex=0;
                    for(int p=0;p<atkNum;p++){
                        if(atk[p]->getDistance()<max){
                            if(abs(mybuilding[s]->location.x*50-atk[p]->pixx)<110&&abs(mybuilding[s]->location.y*50+100-atk[p]->pixy)<110){
                                x=atk[p]->pixx;
                                y=atk[p]->pixy;
                                max = atk[p]->getDistance();
                                maxindex=p;
                            }
                        }
                    }
                    if(max!=999){
                        QLabel *s1=new QLabel(this);
                        s1->setPixmap(QPixmap(":/Icon4APproject/O12.png"));
                        s1->setFixedSize(150,150);
                        s1->setScaledContents(true);
                        s1->move(atk[maxindex]->pixx-50,atk[maxindex]->pixy-50);
                        s1->show();
                        S5(s1,mybuilding[s]->level,atk[maxindex]->pixx,atk[maxindex]->pixy);
                        QLabel *s6=new QLabel(this);
                        s6->setPixmap(QPixmap(":/Icon4APproject/O13.png"));
                        s6->setFixedSize(50,50);
                        s6->setScaledContents(true);
                        s6->move(mybuilding[s]->location.x*50,mybuilding[s]->location.y*50+100);
                        s6->show();
                        S1(s6);
                    }
                 }
                mybuilding[s]->iteration++;
            });

            //this->setStyleSheet("background-color: rgba(0, 0, 0, 0)");
            connect(mybuilding[s],&building::clicked,[=](){
                choosebuilding = mybuilding[s];
                qDebug()<<"你选择了第（"<<choosebuilding->location.x<<','<<choosebuilding->location.y<<"）个点";
                qDebug()<<choosebuilding->level;
                emit mybuilding[s]->chooseBuilding();
            });
        }
    }
}
void playscene::S3(QLabel *s3,attacker *atk,int s){
    QTimer *temp3=new QTimer(this);
    temp3->start(3);
    connect(temp3,&QTimer::timeout,[=](){
        if(s3->x()!=atk->pixx||s3->y()!=atk->pixy){
            if(abs(atk->pixx-s3->x())>abs(atk->pixy-s3->y())){
                if(atk->pixx>s3->x()){
                    s3->move(s3->x()+1,s3->y());
                }
                else{
                    s3->move(s3->x()-1,s3->y());
                }
            }
           else{
                if(atk->pixy>s3->y()){
                    s3->move(s3->x(),s3->y()+1);
                }
                else{
                    s3->move(s3->x(),s3->y()-1);
                }
            }
        }
        else{
            atk->setHP(atk->hp-60-mybuilding[s]->level*20);
            QLabel *s7=new QLabel(this);
            s7->setPixmap(QPixmap(":/Icon4APproject/O14.png"));
            s7->setFixedSize(50,50);
            s7->setScaledContents(true);
            s7->move(atk->pixx+35,atk->pixy);
            s7->show();
            S6(s7);
            s3->hide();
            delete s3;
            delete temp3;
        }
    });
}
void playscene::S1(QLabel *s1){
    s1->setAttribute(Qt::WA_TransparentForMouseEvents);
    s1->show();
    QTimer *temp=new QTimer(this);
    temp->start(500);
    connect(temp,&QTimer::timeout,[=](){
        s1->hide();
        delete temp;
        delete s1;
    });
}
void playscene::S5(QLabel *s1,int level,int x,int y){
    s1->setAttribute(Qt::WA_TransparentForMouseEvents);
    s1->show();
    QTimer *temp=new QTimer(this);
    temp->start(2000+500*level);
    QTimer *temp2=new QTimer(this);
    temp2->start(200);
    connect(temp,&QTimer::timeout,[=](){
        s1->hide();
        delete temp;
        delete s1;
        temp2->stop();
        delete temp2;
    });
    connect(temp2,&QTimer::timeout,[=](){
        for(int p=0;p<atkNum;p++){
                if(abs(x-atk[p]->pixx)<55&&abs(y-atk[p]->pixy)<55&&atk[p]->dead==0){
                    QLabel *s7=new QLabel(this);
                    s7->setPixmap(QPixmap(":/Icon4APproject/O14.png"));
                    s7->setFixedSize(50,50);
                    s7->setScaledContents(true);
                    s7->move(atk[p]->pixx+35,atk[p]->pixy);
                    s7->show();
                    S6(s7);
                    atk[p]->setHP(atk[p]->hp-10-5*level);
                }

        }
    });
}
void playscene::S6(QLabel *s6){
    if(randomNumber(3)!=1){
        delete s6;
        return;
    }
    s6->setAttribute(Qt::WA_TransparentForMouseEvents);
    s6->show();
    QTimer *temp=new QTimer(this);
    temp->start(15);
    int y = s6->y();
    connect(temp,&QTimer::timeout,[=](){
       if(y-s6->y()>30){
           temp->stop();
           delete s6;
           delete temp;
       }
       else{
           s6->move(s6->x(),s6->y()-1);
       }
    });
}
void playscene::S2(QLabel *s2,int x,int y,int s){
    QTimer *temp2=new QTimer(this);
    s2->setAttribute(Qt::WA_TransparentForMouseEvents);
    temp2->start(2);
    s2->show();
    QLabel *S3=new QLabel(this);
    S3->setAttribute(Qt::WA_TransparentForMouseEvents);
    S3->setPixmap(QPixmap(":/Icon4APproject/O1.png"));
    S3->setFixedSize(70,70);
    S3->setScaledContents(true);
    S3->move(x-10,y-10);
    connect(temp2,&QTimer::timeout,[=](){
        if(s2->y()!=y){
            s2->move(s2->x()-1,s2->y()+1);
        }
        else{
            s2->hide();
            S1(S3);
            temp2->stop();
            delete s2;
            delete temp2;
            for(int p=0;p<atkNum;p++){
                if(abs(x-atk[p]->pixx)<50&&abs(y-atk[p]->pixy)<50&&atk[p]->dead==0&&atk[p]->category<=3){
                        atk[p]->setHP(atk[p]->hp-60-10*mybuilding[s]->level);
                        QLabel *s7=new QLabel(this);
                        s7->setPixmap(QPixmap(":/Icon4APproject/O14.png"));
                        s7->setFixedSize(50,50);
                        s7->setScaledContents(true);
                        s7->move(atk[p]->pixx+35,atk[p]->pixy);
                        s7->show();
                        S6(s7);
                 }
            }
        }
    });
}
void playscene::S4(int x,int y){
    QLabel *s[4];
    for(int i=0;i<4;i++){
        s[i]=new QLabel(this);
        s[i]->setPixmap(QPixmap(":/Icon4APproject/O7.png"));
        s[i]->setScaledContents(true);
        s[i]->setFixedSize(50,50);
        s[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
        s[i]->move(x,y);
        s[i]->show();
    }
    QTimer *temp4=new QTimer(this);
    temp4->start(5);
    connect(temp4,&QTimer::timeout,[=](){
        if(s[0]->x()==0&&s[1]->x()==900&&s[2]->y()==0&&s[3]->y()==600){
            temp4->stop();
            delete s[0];
            delete s[1];
            delete s[2];
            delete s[3];
            delete temp4;
        }
        else{
            for(int g=0;g<4;g++){
                int cx=s[g]->x()/50,cy=(s[g]->y()-100)/50;
                if(cx<13&&cy<9&&cy>=0&&cx>=0){
                    if(mybuilding[cx+13*cy]->hp>0){
                        mybuilding[cx+13*cy]->hp-=1+level/5+stage/10;
                        mybuilding[cx+13*cy]->HP->setText(QString::number(mybuilding[cx+13*cy]->hp));
                        if(mybuilding[cx+13*cy]->hp<=0){
                            mybuilding[cx+13*cy]->setIcon(QPixmap());
                            mybuilding[cx+13*cy]->HP->hide();
                            mybuilding[cx+13*cy]->name=0;
                            if(Mymap.Map[mybuilding[cx+13*cy]->location.x][mybuilding[cx+13*cy]->location.y]<19){
                                Mymap.Map[mybuilding[cx+13*cy]->location.x][mybuilding[cx+13*cy]->location.y]=1;
                                }
                            else{
                                Mymap.Map[mybuilding[cx+13*cy]->location.x][mybuilding[cx+13*cy]->location.y]=0;
                                }
                            mybuilding[cx+13*cy]->level=0;
                        }
                    }
                }
            }
            if(s[0]->x()>0){
                s[0]->move(s[0]->x()-1,s[0]->y());
            }
            else{
                s[0]->hide();
            }
            if(s[1]->x()<900){
                s[1]->move(s[1]->x()+1,s[1]->y());
            }
            else{
                s[1]->hide();
            }
            if(s[2]->y()>0){
                s[2]->move(s[2]->x(),s[2]->y()-1);

            }
            else{
                s[2]->hide();
            }
            if(s[3]->y()<600){
                s[3]->move(s[3]->x(),s[3]->y()+1);

            }
            else{
                s[3]->hide();
            }
        }

    });
}
void playscene::setupBuildingSlot(building *build){
    connect(build,&building::chooseBuilding,[=](){
        if(Mymap.Map[build->location.x][build->location.y]==1){
           hideButton(2);
           hideButton(3);
           showButton(1);
        }
        else if(Mymap.Map[build->location.x][build->location.y]==0){
            hideButton(1);
            hideButton(2);
            showButton(3);
        }
        else if(Mymap.Map[build->location.x][build->location.y]>=6){
            showButton(2);
            hideButton(1);
            hideButton(3);
        }
        else{
            hideButton(1);
            hideButton(2);
            hideButton(3);
        }
    });
    connect(build,&QPushButton::clicked,[=](){
        QString text="建筑名称：";
        switch (build->name) {
        case 1:
            text+="A";
            break;
        case 2:
            text+="B";
            break;
        case 3:
            text+="G";
            break;
        case 4:
            text+="H";
            break;
        case 5:
            text+="I";
            break;
        case 6:
            text+="K";
            break;
        case 7:
            text+="L";
            break;
        case 8:
            text+="M";
            break;
        case 9:
            text+="P";
            break;
        }
        text+="\n\n";
        text+="等级：";
        text+=QString::number(build->level);
        text+="\n\n";
        text+="血量：";
        text+=QString::number(build->hp);
        text+="\n\n";
        text+="升级价格：";
        if(build->level==3)
            text+="已满级";
        else
            text+=QString::number(build->cost);
        text+="\n\n";
        text+="移除返还：";
        text+=QString::number(build->cost*build->level/2);
        text+="\n\n";
        text+="坐标：";
        text+="X："+QString::number(build->location.x)+"   Y："+QString::number(build->location.y);
        text+="\n\n";
        text+="描述：";
        switch (build->name) {
        case 1:
            text+="阻止地面单位行进一段时间，造成固定伤害。等级越高，禁锢时间越长，伤害越高。";
            break;
        case 2:
            text+="减缓所有单位行进速度。等级越高，减速时间越长，幅度越大。";
            break;
        case 3:
            text+="清除一个地面单位。此建筑无法升级。";
            break;
        case 4:
            text+="对经过单位造成持续伤害，对飞行单位伤害更高。等级越高，伤害越高。";
            break;
        case 5:
            text+="清除血量低于自身血量的地面单位。等级越高，血量越高。";
            break;
        case 6:
            text+="在路径上生成低血量I单位。等级越高，生成频率越高，生成建筑血量越高。";
            break;
        case 7:
            text+="召唤流星攻击地面单位，造成范围伤害。等级越高，攻击频率越高，伤害越高。";
            break;
        case 8:
            text+="单体远程攻击地面单位和飞行单位。等级越高，攻击频率越高，伤害越高。";
            break;
        case 9:
            text+="生成一块感应区，持续攻击地面单位和飞行单位。等级越高，持续时间越长，伤害越高。";
            break;
        }
        ui->labelDetails->setText(text);
    });
    connect(build,&QPushButton::pressed,[=](){
       if(build->name==6) {
            QLabel *s=new QLabel(this);
            s->setPixmap(QPixmap(":/Icon4APproject/O11.png"));
            s->setFixedSize(180,180);
            s->setScaledContents(true);
            s->move(build->location.x*50-65,build->location.y*50+35);
            s->show();
            S1(s);
       }
      else  if(build->name==7) {
            QLabel *s=new QLabel(this);
            s->setPixmap(QPixmap(":/Icon4APproject/O10.png"));
            s->setFixedSize(250,250);
            s->setScaledContents(true);
            s->move(build->location.x*50-100,build->location.y*50);
            s->show();
            S1(s);
       }
       else  if(build->name==8) {
             QLabel *s=new QLabel(this);
             s->setPixmap(QPixmap(":/Icon4APproject/O10.png"));
             s->setFixedSize(400,400);
             s->setScaledContents(true);
             s->move(build->location.x*50-175,build->location.y*50-75);
             s->show();
             S1(s);
        }
       else  if(build->name==9) {
             QLabel *s=new QLabel(this);
             s->setPixmap(QPixmap(":/Icon4APproject/O10.png"));
             s->setFixedSize(250,250);
             s->setScaledContents(true);
             s->move(build->location.x*50-100,build->location.y*50);
             s->show();
             S1(s);
        }
    });
}
void playscene::drawButton(){
    //A按钮
    a1 = new myButton(":/Icon4APproject/A1.png",1,"A1 $400");
    QPixmap pix = QPixmap(":/Icon4APproject/A1.png");
    a1->setParent(this);
    a1->hide();
    a1->cost=400;
    connect(a1,&myButton::clicked,[=](){
        if(money>=a1->cost){
            money-=a1->cost;
            choosebuilding->setIcon(pix);
            choosebuilding->level=1;
            choosebuilding->cost=a1->cost;
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=6;
            choosebuilding->name=1;
            choosebuilding->hp=1000;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]=20;
            choosebuilding->HP->setText(QString::number(1000));
            choosebuilding->HP->show();
            hideButton(1);
            updateMoney();
        }
    });
    //B按钮
    b1 = new myButton(":/Icon4APproject/B1.png",2,"B1 $400");
    pix = QPixmap(":/Icon4APproject/B1.png");
    b1->setParent(this);
    b1->hide();
    b1->cost=400;
    connect(b1,&myButton::clicked,[=](){
        if(money>=b1->cost){
            money-=b1->cost;
            choosebuilding->setIcon(pix);
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=9;
            choosebuilding->name=2;
            choosebuilding->level=1;
            choosebuilding->cost=b1->cost;
            choosebuilding->hp=800;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]=800;
            choosebuilding->HP->setText(QString::number(800));
            choosebuilding->HP->show();
            hideButton(1);
            updateMoney();
        }
    });
    //G按钮
    g = new myButton(":/Icon4APproject/G.png",3,"G $800");
    pix = QPixmap(":/Icon4APproject/G.png");
    g->setParent(this);
    g->hide();
    g->cost=800;
    connect(g,&myButton::clicked,[=](){
        if(money>=g->cost){
            money-=g->cost;
            choosebuilding->setIcon(pix);
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=12;
            choosebuilding->name=3;
            choosebuilding->level=1;
            choosebuilding->cost=g->cost;
            choosebuilding->T->start(100);
            hideButton(1);
            updateMoney();
        }
    });
    //H按钮
    h1 = new myButton(":/Icon4APproject/H1.png",4,"H1 $500");
    pix = QPixmap(":/Icon4APproject/H1.png");
    h1->setParent(this);
    h1->hide();
    h1->cost=500;
    connect(h1,&myButton::clicked,[=](){
        if(money>=h1->cost){
            money-=h1->cost;
            choosebuilding->setIcon(pix);
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=13;
            choosebuilding->level=1;
            choosebuilding->name=4;
            choosebuilding->cost=h1->cost;
            choosebuilding->hp=2000;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]=20;
            choosebuilding->HP->setText(QString::number(2000));
            choosebuilding->HP->show();
            hideButton(1);
            updateMoney();
        }
    });
    //I按钮
    i1 = new myButton(":/Icon4APproject/I1.png",5,"I1 $700");
    pix = QPixmap(":/Icon4APproject/I1.png");
    i1->setParent(this);
    i1->hide();
    i1->cost=700;
    connect(i1,&myButton::clicked,[=](){
        if(money>=i1->cost){
            money-=i1->cost;
            choosebuilding->setIcon(pix);
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=16;
            choosebuilding->level=1;
            choosebuilding->name=5;
            choosebuilding->cost=i1->cost;
            choosebuilding->hp=1000;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]=1000;
            choosebuilding->HP->setText(QString::number(1000));
            choosebuilding->HP->show();
            hideButton(1);
            updateMoney();
        }
    });
    //K按钮
    k1 = new myButton(":/Icon4APproject/K1.png",1,"K1 $500");
    pix = QPixmap(":/Icon4APproject/K1.png");
    k1->setParent(this);
    k1->hide();
    k1->cost=500;
    connect(k1,&myButton::clicked,[=](){
        if(money>=k1->cost){
            money-=k1->cost;
            choosebuilding->setIcon(pix);
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=19;
            choosebuilding->level=1;
            choosebuilding->name=6;
            choosebuilding->cost=k1->cost;
            choosebuilding->hp=500;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]=500;
            choosebuilding->HP->setText(QString::number(500));
            choosebuilding->T->start(100);
            choosebuilding->HP->show();
            hideButton(3);
            updateMoney();
        }
    });
    //L按钮
    l1 = new myButton(":/Icon4APproject/L1.png",2,"L1 $800");
    pix = QPixmap(":/Icon4APproject/L1.png");
    l1->setParent(this);
    l1->hide();
    l1->cost=800;
    connect(l1,&myButton::clicked,[=](){
        if(money>=l1->cost){
            money-=l1->cost;
            choosebuilding->setIcon(pix);
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=22;
            choosebuilding->level=1;
            choosebuilding->name=7;
            choosebuilding->cost=l1->cost;
            choosebuilding->hp=500;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]=500;
            choosebuilding->HP->setText(QString::number(500));
            choosebuilding->HP->show();            
            choosebuilding->T->start(100);
            hideButton(3);
            updateMoney();
        }
    });
    //M按钮
    m1 = new myButton(":/Icon4APproject/M1.png",3,"M1 $800");
    pix = QPixmap(":/Icon4APproject/M1.png");
    m1->setParent(this);
    m1->hide();
    m1->cost=800;
    connect(m1,&myButton::clicked,[=](){
        if(money>=m1->cost){
            money-=m1->cost;
            choosebuilding->setIcon(pix);
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=25;
            choosebuilding->level=1;
            choosebuilding->name=8;
            choosebuilding->cost=m1->cost;
            choosebuilding->hp=500;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]=500;
            choosebuilding->HP->setText(QString::number(500));
            choosebuilding->HP->show();            
            choosebuilding->T->start(100);
            hideButton(3);
            updateMoney();
        }
    });
    //P按钮
    p1 = new myButton(":/Icon4APproject/P1.png",4,"P1 $800");
    pix = QPixmap(":/Icon4APproject/P1.png");
    p1->setParent(this);
    p1->hide();
    p1->cost=800;
    connect(p1,&myButton::clicked,[=](){
        if(money>=p1->cost){
            money-=p1->cost;
            choosebuilding->setIcon(pix);
            Mymap.Map[choosebuilding->location.x][choosebuilding->location.y]=28;
            choosebuilding->level=1;
            choosebuilding->name=9;
            choosebuilding->cost=m1->cost;
            choosebuilding->hp=500;
            Mymap.HpMap[choosebuilding->location.x][choosebuilding->location.y]=500;
            choosebuilding->HP->setText(QString::number(500));
            choosebuilding->HP->show();
            choosebuilding->T->start(100);
            hideButton(3);
            updateMoney();
        }
    });
}
void playscene::hideButton(int i){
    switch (i) {
    case 1:
        a1->hide();
        b1->hide();
        g->hide();
        h1->hide();
        i1->hide();
        ui->labelchoose->hide();
        break;
    case 2:
        ui->pushButtonUpdate->hide();
        ui->pushButtonRemove->hide();
        ui->labelchoose_2->hide();
        ui->labelDetails->hide();
        break;
    case 3:
        k1->hide();
        l1->hide();
        m1->hide();
        p1->hide();
        ui->labelchoose->hide();
        break;
    default:
        break;
    }
}
void playscene::showButton(int i){
    switch (i) {
    case 1:
        a1->show();
        b1->show();
        g->show();
        h1->show();
        i1->show();
        ui->labelchoose->show();
        ui->labelHelp->hide();
        break;
     case 2:
        ui->pushButtonUpdate->show();
        ui->pushButtonRemove->show();
        ui->labelchoose_2->show();
        ui->labelDetails->show();
        ui->labelHelp->hide();
    case 3:
        k1->show();
        l1->show();
        m1->show();
        p1->show();
        ui->labelchoose->show();
        ui->labelHelp->hide();
        break;
    default:
        break;
    }
}
int playscene::randomNumber(int i){
    return QRandomGenerator::global()->bounded(0,i);
}
void playscene::loss(){
    timer1->stop();
    timer2->stop();
    ui->labellose->show();
}
void playscene::win(){
    timer1->stop();
    timer2->stop();
    condition=1;
    ui->labelwin->show();
}
void playscene::attackerSetUp(){
    connect(timer2,&QTimer::timeout,[=](){
        if(condition==1||Mymap.exist==0)
            return ;
        if(atkNum<10+20*level&&randomNumber(100)<=10+level*2){
            createAttacker(atkNum);
            atkNum++;
        }
    });
    connect(timer1,&QTimer::timeout,[=](){
        if(condition==1)
            return ;
        updateMoney();

        for(int i=0;i<atkNum;i++){
            loc temp(0,0);
            atk[i]->Mov1px(money,deadAtk,mybuilding);
        }
        if(deadAtk==10+20*level){
            win();
        }
    });
}
void playscene::createAttacker(int cur){
    int rand =randomNumber(100);
    if(rand<=5+stage/20){
        atk[atkNum]=new attacker(this,&Mymap,QPixmap(":/Icon4APproject/F6.png"),2,stage);
        connect(atk[cur]->D,&QTimer::timeout,[=](){
            if(condition==0){
              if(atk[cur]->dead==0){
                for(int i=0;i<atkNum;i++){
                    if(cur==i)
                        continue;
                    if(atk[i]->dead==1)
                        continue;
                    if(abs(atk[i]->pixx-atk[cur]->pixx)<=60&&abs(atk[i]->pixy-atk[cur]->pixy)<=60){
                        atk[i]->setHP(atk[i]->hp+=10+2*stage);

                    }
                }
                QLabel *s=new QLabel(this);
                s->setPixmap(QPixmap(":/Icon4APproject/O9.png"));
                s->setFixedSize(80,80);
                s->setScaledContents(true);
                s->move(atk[cur]->pixx-15,atk[cur]->pixy-15);
                s->show();
                S1(s);
              }
            }
        });
    }
    else if(rand<=10+stage/17){
        atk[atkNum]=new attacker(this,&Mymap,QPixmap(":/Icon4APproject/F5.png"),2,stage);
        connect(atk[cur]->D,&QTimer::timeout,[=](){
            if(condition==0){
              if(atk[cur]->dead==0){
                for(int i=-1;i<2;i++){
                    for(int m=-1;m<2;m++){
                        if(atk[cur]->curx+i+13*(atk[cur]->cury+m)>=117)
                            continue;
                        if(mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->hp>0){
                            mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->hp-=30+level*5+stage;
                            mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->HP->setText(QString::number(mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->hp));
                            if(mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->hp<=0){
                                mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->setIcon(QPixmap());
                                mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->HP->hide();
                                mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->name=0;
                                if(Mymap.Map[mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.x][mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.y]<19){
                                    Mymap.Map[mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.x][mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.y]=1;
                                    }
                                else{
                                    Mymap.Map[mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.x][mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.y]=0;
                                    }
                                mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->level=0;
                            }
                        }
                    }
                }
                QLabel *s=new QLabel(this);
                s->setPixmap(QPixmap(":/Icon4APproject/O8.png"));
                s->setFixedSize(150,150);
                s->setScaledContents(true);
                s->move(atk[cur]->pixx-50,atk[cur]->pixy-50);
                s->show();
                S1(s);
              }
            }
        });
    }
    else if(rand<=15+stage/14){
        atk[atkNum]=new attacker(this,&Mymap,QPixmap(":/Icon4APproject/F4.png"),2,stage);
        connect(atk[cur]->D,&QTimer::timeout,[=](){
            if(condition==0){
              if(atk[cur]->dead==0){
                S4(atk[cur]->pixx,atk[cur]->pixy);
              }
            }
        });
    }
    else if(rand<=20+stage/11){
        atk[atkNum]=new attacker(this,&Mymap,QPixmap(":/Icon4APproject/N1.png"),4,stage);
        connect(atk[cur]->D,&QTimer::timeout,[=](){
            if(condition==0){
              if(atk[cur]->dead==0){
                  S4(atk[cur]->pixx,atk[cur]->pixy);
              }
            }
        });
    }
    else if(rand<=25+stage/8){
        atk[atkNum]=new attacker(this,&Mymap,QPixmap(":/Icon4APproject/N2.png"),4,stage);
        connect(atk[cur]->D,&QTimer::timeout,[=](){
            if(condition==0){
              if(atk[cur]->dead==0){
                  atk[cur]->iter=0;
                  for(int i=-1;i<2;i++){
                      for(int m=-1;m<2;m++){
                          if(atk[cur]->curx+i+13*(atk[cur]->cury+m)>=117)
                              continue;
                          if(mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->hp>0){
                              atk[cur]->iter=1;
                              mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->hp-=30+level*5+stage;
                              mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->HP->setText(QString::number(mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->hp));
                              if(mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->hp<=0){
                                  mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->setIcon(QPixmap());
                                  mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->HP->hide();
                                  mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->name=0;
                                  if(Mymap.Map[mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.x][mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.y]<19){
                                      Mymap.Map[mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.x][mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.y]=1;
                                      }
                                  else{
                                      Mymap.Map[mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.x][mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->location.y]=0;
                                      }
                                  mybuilding[atk[cur]->curx+i+13*(atk[cur]->cury+m)]->level=0;
                              }
                          }
                      }
                  }
                QLabel *s=new QLabel(this);
                s->setPixmap(QPixmap(":/Icon4APproject/O8.png"));
                s->setFixedSize(150,150);
                s->setScaledContents(true);
                s->move(atk[cur]->pixx-50,atk[cur]->pixy-50);
                s->show();
                S1(s);
              }
            }
        });
    }
    else if(rand<=30+stage/5)
        atk[atkNum]=new attacker(this,&Mymap,QPixmap(":/Icon4APproject/F3.png"),3,stage);
    else if(rand<=40+stage/5)
        atk[atkNum]=new attacker(this,&Mymap,QPixmap(":/Icon4APproject/F2.png"),2,stage);
    else
        atk[atkNum]=new attacker(this,&Mymap,QPixmap(":/Icon4APproject/F1.png"),1,stage);
    connect(atk[atkNum],&attacker::loss,[=](){
        loss();
    });
}
void playscene::createSpecificAttacker(int category,int cur){

}
