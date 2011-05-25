#include "projectile.h"

namespace TOWERDEFENSE{

Projectile::Projectile(const double vitesse, const double frappe, const int x, const int y, const double cibleX, const double cibleY, MyQGraphicsScene *carte):vitesse(vitesse),frappe(frappe),cibleX(cibleX),cibleY(cibleY),carte(carte)
{
    this->setPos(x,y);

    double vecteurX = cibleX - this->x();
    double vecteurY = cibleY - this->y();

    this->mouvementVecteur.setX(vecteurX/sqrt(pow(vecteurX,2) + pow(vecteurY,2)));
    this->mouvementVecteur.setY(vecteurY/sqrt(pow(vecteurX,2) + pow(vecteurY,2)));
}

void Projectile::advance(int phase)
{
    if(!phase)
            return;

        // Collision avec ennemi
        // . Recherche des ennemis de la map
        QList<Insecte*> insectes = carte->getInsectes();

        for(int i = 0 ; i < insectes.length() ; ++i)
        {
                if(this->collidesWithItem(insectes.at(i),Qt::IntersectsItemBoundingRect))
                {
                    // On retire le projectile de la scène
                    this->scene()->removeItem(this);
                    // Inflige des dommages au monstre
                    insectes[i]->recevoirDegats(frappe);
                    return;
                }
        }



        // Déplacement du projectile selon le vecteur de déplacement et la vitesse
        double newx = this->x() + vitesse*mouvementVecteur.x();
        double newy = this->y() + vitesse*mouvementVecteur.y();

        // Si le projectile est en dehors de l'écran, on le supprime
        if(newx < 0 || newx > 512 || newy < 0 || newy > 512){
            carte->removeItem(this);
            return;
        }
        this->setPos(newx,newy);
}

QRectF Projectile::boundingRect()const
{
    return QRectF(0,0,5,5);
}

void Projectile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);
    painter->drawRect(0,0,5,5);
}

}