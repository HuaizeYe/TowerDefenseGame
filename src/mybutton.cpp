#include "mybutton.h"
#include<QDebug>

myButton::myButton(QString path,int i,QString text){
    QPixmap pix;
    pix.load(path);
    this->setStyleSheet("border-style: flat;background: transparent;");
    this->setFixedSize(100,100);
    this->move(670+((i-1)%2)*100,((i-1)/2)*120+150);
    this->setIcon(pix);
    this->setIconSize(QSize(80,80));
    this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    this->setText(text);
    this->setFont(QFont("华文中宋",12));
}

