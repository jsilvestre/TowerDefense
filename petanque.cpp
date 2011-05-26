#include "petanque.h"

namespace TOWERDEFENSE{

Petanque::Petanque()
{
}

Petanque::Petanque(const double niveau,const int x,const int y,QGraphicsItem *parent)//:Defense(niveau,3+niveau,0.5,15*pow(niveau,1.5),15,40,80,20,parent,RAMPANT,BOULE)
{
    setData(0,"PETANQUE");

    QPixmap* tour = new QPixmap("data/Tour/tourPetanque.png");

    // Image et taille
    this->setPixmap(*tour);

    // Position
    this->setPos(x,y);
}

double Petanque::attaquer()
{
    return frappe;
}

bool Petanque::ameliorer()
{
    try
    {
        if(niveau == 1)
        {
            niveau++;
            portee = 3 + niveau;
            frappe = 15 * pow(niveau,1.5);
            cout += amelioration_1;
            return true;
        }
        else if(niveau == 2)
        {
            niveau++;
            portee = 3 + niveau;
            frappe = 15 * pow(niveau,1.5);
            cout += amelioration_2;
            return true;
        }
        else throw std::exception();
    }
    catch(std::exception& e)
    {
        QMessageBox(QMessageBox::Information,"Amelioration impossible","La tour est de niveau maximal").exec();
        return false;
    }
}
}
