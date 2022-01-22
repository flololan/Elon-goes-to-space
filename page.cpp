#include "page.h"
#include <util.h>

/**
 * @brief Page::Page : Constructeur par défaut
 */
Page::Page()
{

}

/**
 * @brief Page::Page
 * @param res : La resource (image) de la page
 * @param pos_bonhomme : la position initiale du bonhomme
 * @param colliderH : le point Haut Gauche du rectangle de collision
 * @param colliderB : le point Bas Droit du rectangle de collision
 * @param text : Le texte de la page
 * @param bat : Vrai si le personnage est dans un bateau, faux sinon
 */
Page::Page(std::string res, QPoint pos_bonhomme, QPoint colliderH, QPoint colliderB, std::string text, bool bat )
{

    ressource = new std::string(res);
    position_bonhomme = pos_bonhomme;
    colliderHG = colliderH;
    colliderBD = colliderB;
    texte = new std::string(text);
    bateau = bat;
}

/**
 * @brief Page::collided
 * @param x Abs du point a tester
 * @param y Ord du point a tester
 * @return Vrai si le point en par. est dans le rectangle de collision, faux sinon
 */
bool Page::collided(int x, int y)
{

    /*bool b = false;

    // On teste d'abord la coord x du point
    b = b || (x<colliderBD.x() && x>colliderHG.x());
    // Puis la coord y
    b = b && (y<colliderBD.y() && y>colliderHG.y());
    return b;*/

    return Util::pointsCollided(QPoint(x,y), colliderHG, colliderBD);
}
