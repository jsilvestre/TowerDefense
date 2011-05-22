#ifndef PIERRE_H
#define PIERRE_H

#include "defense.h"

namespace TOWERDEFENSE{

class Pierre : public Defense
{
public:
    Pierre();
    Pierre(const double niveau,const int x,const int y,QGraphicsItem *parent=0);

    double attaquer();
    bool ameliorer();
};

}

#endif // PIERRE_H
