#ifndef UTIL_H
#define UTIL_H

#include <QPoint>

/**
 * @brief The Util class
 * Classe statique avec fonction d'aide
 */
class Util
{
public:
    static bool pointsCollided(QPoint pos1, QPoint colliderHG, QPoint colliderBD);
private:
    // Cette methode empeche creation d'instance de l'objet
    Util() {} // le constructeur est privé
};

#endif // UTIL_H
