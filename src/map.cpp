#include "map.h"

map::map(int level)
{
    Level=level;
    switch (level) {
    case 1:
        Import(":/Level/1.txt");
//        pathLen[0]=4;
//        myPath[0][0]=loc(1,2);
//        myPath[0][1]=loc(6,2);
//        myPath[0][2]=loc(6,7);
//        myPath[0][3]=loc(1,7);
//        for(int i=0;i<13;i++)
//            for(int m=0;m<9;m++){
//                Map[i][m]=0;
//                HpMap[i][m]=0;
//            }
//        for(int n=2;n<=6;n++)
//            Map[n][2]=1;
//        for(int n=2;n<=6;n++)
//            Map[6][n]=1;
//        for(int n=6;n>=1;n--)
//            Map[n][7]=1;
//        Map[1][2]=4;
//        Map[1][7]=5;
//        start[0]=loc(1,2);
//        end[0]=loc(1,7);
//        pathLen[1]=4;
//        myPath[1][0]=loc(11,2);
//        myPath[1][1]=loc(7,2);
//        myPath[1][2]=loc(7,7);
//        myPath[1][3]=loc(11,7);
//        for(int n=11;n>=6;n--)
//            Map[n][2]=1;
//        for(int n=2;n<=6;n++)
//            Map[7][n]=1;
//        for(int n=7;n<=11;n++)
//            Map[n][7]=1;
//        Map[11][2]=4;
//        Map[11][7]=5;
//        start[1]=loc(11,2);
//        end[1]=loc(11,7);
//        pathNum=2;
        break;
    case 2:
        Import(":/Level/2.txt");
//        for(int i=0;i<13;i++)
//            for(int m=0;m<9;m++){
//                Map[i][m]=0;
//                HpMap[i][m]=0;
//            }
//        pathNum=3;
//        pathLen[0]=2;
//        pathLen[1]=2;
//        pathLen[2]=2;
//        myPath[0][0]=loc(3,1);
//        myPath[0][1]=loc(3,7);
//        myPath[1][0]=loc(7,1);
//        myPath[1][1]=loc(7,7);
//        myPath[2][0]=loc(0,8);
//        myPath[2][1]=loc(11,8);
//        Map[3][1]=4;
//        Map[3][7]=5;
//        Map[7][1]=4;
//        Map[7][7]=5;
//        Map[0][8]=4;
//        Map[11][8]=5;
//        start[0]=loc(3,1);
//        end[0]=loc(3,7);
//        start[1]=loc(7,1);
//        end[1]=loc(7,7);
//        start[2]=loc(0,8);
//        end[2]=loc(11,8);
//        for(int i=2;i<7;i++){
//            Map[3][i]=1;
//            Map[7][i]=1;
//        }
//        for(int i=1;i<11;i++)
//            Map[i][8]=1;
        break;
    case 3:
        Import(":/Level/3.txt");
        break;
    case 4:
        Import(":/Level/4.txt");
        break;
    case 5:
        Import(":/Level/5.txt");
        break;
    case 6:
        Import(":/Level/6.txt");
        break;
    default:
        exist=0;
        break;
    }
}
void map::Export(QString fileName){
    QFile outmap(fileName);
    if(!outmap.open(QIODevice::WriteOnly|QIODevice::Text))
        return;
    QTextStream out(&outmap);
    out<<"Level Num\n"<<Level<<"\n";
    out<<"Path Num\n"<<pathNum<<"\n";
    out<<"Length and Path\n";
    for(int i=0;i<pathNum;i++){
        out<<pathLen[i]<<"\n";
        for(int s=0;s<pathLen[i];s++){
            out<<myPath[i][s].x<<" "<<myPath[i][s].y<<" ";
        }
        out<<"\n";
    }
    outmap.close();
}

void map::Import(QString root){
    QFile inmap(root);
    if(!inmap.open(QIODevice::ReadOnly))
     {
             return;
     }
    QTextStream in(&inmap);

    int signal=0;
    int pn=0;
    while(!in.atEnd()){
            QString line = in.readLine();
            if(line=="#Level Num"){
                signal=1;
            }
            else if(line =="Path Num"){
                signal=2;
            }
            else if(line =="Length and Path"){
                signal=3;
            }
            else if(signal==1){
                 Level=line.toInt();
                 signal=0;
            }
            else if(signal==2){
                pathNum=line.toInt();
                signal=0;
            }
            else if(signal==3){
                pathLen[pn]=line.toInt();
                signal=4;
            }
            else if(signal==4){
                QTextStream p(&line);
                int tmp=0;
                while(!p.atEnd()){
                    p>>myPath[pn][tmp].x>>myPath[pn][tmp].y;
                    tmp++;
                }
                pn++;
                signal=3;
            }
    }
    for(int i=0;i<pathNum;i++){
        start[i]=myPath[i][0];
        end[i]=myPath[i][pathLen[i]-1];
    }
    for(int i=0;i<13;i++)
        for(int s=0;s<9;s++)
            Map[i][s]=0;
    for(int i=0;i<pathNum;i++){
        for(int s=0;s<pathLen[i]-1;s++){
            if(myPath[i][s].x==myPath[i][s+1].x){
                if(myPath[i][s].y<myPath[i][s+1].y){
                    for(int m=myPath[i][s].y;m<=myPath[i][s+1].y;m++){
                        Map[myPath[i][s].x][m]=1;
                    }
                }
                else{
                    for(int m=myPath[i][s+1].y;m<=myPath[i][s].y;m++){
                        Map[myPath[i][s].x][m]=1;
                    }
                }
            }
            else{
                if(myPath[i][s].x<myPath[i][s+1].x){
                    for(int m=myPath[i][s].x;m<=myPath[i][s+1].x;m++){
                        Map[m][myPath[i][s].y]=1;
                    }
                }
                else{
                    for(int m=myPath[i][s+1].x;m<=myPath[i][s].x;m++){
                        Map[m][myPath[i][s].y]=1;
                    }
                }
            }
        }
    }
    for(int i=0;i<pathNum;i++){
        Map[start[i].x][start[i].y]=4;
        Map[end[i].x][end[i].y]=5;
    }
    exist=1;
    inmap.close();

}
