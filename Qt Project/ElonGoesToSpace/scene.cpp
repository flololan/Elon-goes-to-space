#include "scene.h"
#include <helper.h>
#include <QDebug>

Scene::Scene()
{
}

/**
 * @brief Scene::Scene
 * @param res : Image of scene
 * @param cursorPosition : initial position of cursor
 * @param colliderTopLeft : Top left corner of collision
 * @param colliderBottomRight : Bottom right corner of collision
 */
Scene::Scene(std::string res, QPoint cursorPosition, QPoint colliderTopLeft, QPoint colliderBottomRight)
{
    ressource = new std::string(res);
    cursorPosition = cursorPosition;
    colliderTopLeft = colliderTopLeft;
    colliderBottomRight = colliderBottomRight;
}

/**
 * @brief Scene::collided
 * @param x Abs du point a tester
 * @param y Ord du point a tester
 * @return Vrai si le point en par. est dans le rectangle de collision, faux sinon
 */
bool Scene::collided(int x, int y)
{
    return Helper::pointsCollided(QPoint(x, y), colliderTopLeft, colliderBottomRight);
}
