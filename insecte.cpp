#include "insecte.h"

namespace TOWERDEFENSE{

Insecte::Insecte(){}

Insecte::Insecte(const double taille, const double vitalite, const double resistance, const double vitesse, const Type_deplacement deplacement,QGraphicsPixmapItem *parent):taille(taille),vitalite(vitalite),resistance(resistance),vitesse(vitesse),deplacement(deplacement), counter(0)
{
    this->vitesseStandard = vitesse;
    this->counterTempsRalentissement = 200;
}

void Insecte::setCounter(int counter)
{
    this->counter = counter;
}

double Insecte::getTaille()const { return taille; }

double Insecte::getVitalite()const { return vitalite; }

double Insecte::getVitesse()const { return vitesse; }

QList<int>* Insecte::getPath()const { return path; }

int Insecte::getCounter()const { return counter; }

Type_deplacement Insecte::getDeplacement()const { return deplacement; }

void Insecte::recevoirDegats(double degats)
{
    vitalite -= (degats - resistance);
    if(this->vitalite <= 0)
    {
        emit supprimerInsecte(this,false);
    }
}

void Insecte::ralentir()
{
    if(this->vitesse > 1)
    {
        this->vitesse = this->vitesse/2;
    }
}

void Insecte::increaseAnimationStep() {

    // Avance à la frame suivante de l'animation
    animState++;
    if(animState >= animPixmap.size())
        animState = 0;
}

void Insecte::advance(int phase)
{
// Si 'phase' vaut 0, rien ne se passe
    if(!phase)
        return;
    // ...sinon, on met à jour la position de l'item

    this->setPixmap(*animPixmap[animState]);
    this->increaseAnimationStep();

    if(vitesse < vitesseStandard)
    {
        counterTempsRalentissement--;
        if(counterTempsRalentissement == 0)
        {
            vitesse = vitesseStandard;
            counterTempsRalentissement = 200;
        }
    }

    if(path->count() == counter)
    {
        emit this->supprimerInsecte(this,true);
        return;
    }

    int dir = path->at(counter), deltaX, deltaY;
    double newX = x(), newY = y();

    double speed = vitesse*32*0.02; // en pixel/20ms

    if(dir == 1)
    {
        newY=newY-speed;
    }
    else if(dir == 2)
    {
        newY=y()+speed;
    }
    else if(dir == 4)
    {
        newX=newX+speed;
    }
    else if(dir == 8)
    {
        newX=newX-speed;
    }
    else if(dir == 5 || dir == 6 || dir == 9 || dir == 10)
    {
        if(path->at(counter+1) == 1)
        {
            newY=newY-speed;
            newX=floor(newX / 32)*32;
        }
        if(path->at(counter+1) == 2)
        {
            newY=y()+speed;
            newX=floor(newX / 32)*32;
        }
        if(path->at(counter+1) == 4)
        {
            newX=newX+speed;
            newY=floor(newY / 32)*32;
        }
        if(path->at(counter+1) == 8)
        {
            newX=newX-speed;
            newY=floor(newY / 32)*32;
        }
    }
    else if(dir == 32)
        return;

    deltaX = abs(floor(x() / 32) - floor(newX / 32));
    deltaY = abs(floor(y() / 32) - floor(newY / 32));

    this->setPos(newX,newY);

    int tempCounter = counter;
    this->resetTransform();

    if(path->at(counter) == 5 || path->at(counter) == 6 || path->at(counter) == 9 || path->at(counter) == 10)
    {
        tempCounter++;
    }

    double tailleInsectePixel = taille*32;


    if(path->at(tempCounter) == 1)
    {
        this->translate(16,16);
        this->rotate(-90);
        this->translate(-16,-16);
        if(taille > 1)
            this->translate(tailleInsectePixel/4,-tailleInsectePixel/4);
    }
    if(path->at(tempCounter) == 2)
    {
        this->translate(16,16);
        this->rotate(90);
        this->translate(-16,-16);
        if(taille > 1)
            this->translate(tailleInsectePixel/4,-tailleInsectePixel/4);
    }
    if(path->at(tempCounter) == 4)
    {
        // défault
        if(taille > 1)
            this->translate(-tailleInsectePixel/4,-tailleInsectePixel/4);
    }
    if(path->at(tempCounter) == 8)
    {
        this->translate(16,16);
        this->rotate(180);
        this->translate(-16,-16);
        if(taille > 1)
            this->translate(-tailleInsectePixel/4,-tailleInsectePixel/4);
    }

    if(deltaX != 0 || deltaY != 0) {
        counter++;
    }
}

void Insecte::setPath(QList<int> *path)
{
    this->path = path;
}

}
