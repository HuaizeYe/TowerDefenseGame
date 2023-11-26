#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QToolButton>
#include"map.h"
#include"building.h"
class myButton : public QToolButton
{
    Q_OBJECT
public:
    int cost=0;
    //explicit myButton(QWidget *parent = nullptr);
    myButton(QString path="",int i=0,QString text="");

};

#endif // MYBUTTON_H
