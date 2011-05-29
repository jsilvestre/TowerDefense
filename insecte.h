#ifndef INSECTE_H
#define INSECTE_H

//#include <QGraphicsPixmapItem>
#include <QList>
#include <QString>

#include "math.h"
#include "entite.h"

#include "constantes.h"
#include <iostream>

namespace TOWERDEFENSE{

class Insecte : public Entite
{
    Q_OBJECT
protected:
    double taille;
    double vitalite;
    double resistance;
    double vitesse;
    QList<int> *path;

    Type_deplacement deplacement;
    QList<QPixmap*> animPixmap;
    int animState;
    int counter;

    void advance(int phase);

public:
    Insecte();
    Insecte(const double taille, const double vitalite, const double resistance, const double vitesse, const Type_deplacement deplacement, QGraphicsPixmapItem *parent=0);

    /*!
      * Accesseur modifiant l'attribut vitalite
      * \param vitalite la nouvelle vitalite de l'insecte
      */
    void setVitalite(double vitalite);

    /*!
     * Accesseur modifiant l'attribut resistance
     *\param resistance la nouvelle resistante de l'insecte
     */
    void setResistance(double resistance);

    /*!
      * Accesseur modifiant l'attribut vitesse
      * \param vitesse la nouvelle vitesse de l'insecte
      */
    void setVitesse(double vitesse);

    /*!
      * Accesseur modifiant l'attribut deplacement
      * \param deplacement le nouveau type de deplacement de l'insecte
      */
    void setDeplacement(Type_deplacement deplacement);

    void setPath(QList<int> *path);

    /*!
      * Methode virtuelle pure permettant de traiter les degats recus par un insecte
      * \param degats les degats subis par l'attaque
      */
    virtual void recevoirDegats(double degats);

    double getTaille()const;
    double getVitalite()const;
    double getVitesse()const;

    void increaseAnimationStep();

signals:
    void supprimerInsecte(Insecte* I);
};
}

#endif // INSECTE_H
