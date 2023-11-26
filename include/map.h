#ifndef MAP_H
#define MAP_H
#include<QFile>
#include<QTextStream>
#include<QFileDialog>
#include<QObject>
#include<QDebug>
struct loc{
    int x;
    int y;
    loc(int x=0,int y=0){
        this->x=x;
        this->y=y;
    }
};

class map
{
public:
    map(int level=1);
    int Map[13][9];//0空 1路 2近战 4起点 5终点 6 1级近战 7 2级近战 8 3级近战
    int HpMap[13][9];
    loc myPath[5][10];//路径：起点 一系列转折点 终点
    loc start[5],end[5];
    int pathLen[5];
    int pathNum=0;
    int Level=0;
    int exist=1;
    void Export(QString fileName);
    void Import(QString root);
};

#endif // MAP_H
