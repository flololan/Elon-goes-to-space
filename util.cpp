#include "util.h"



/**
  *
 * @brief Util::pointsCollided
 * @param pos1
 * @param pos1
 * @return
 */
bool Util::pointsCollided(QPoint pos1, QPoint colliderHG, QPoint colliderBD)
{
    bool collided = false;
    collided = collided || (pos1.x()<colliderBD.x() && pos1.x()>colliderHG.x());

    return (collided && (pos1.y()<colliderBD.y() && pos1.y()>colliderHG.y()));
}
