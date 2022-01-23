#include "helper.h"

/**
  *
 * @brief Helper::pointsCollided
 * @param pos1
 * @param pos1
 * @return
 */
bool Helper::pointsCollided(QPoint pos1, QPoint colliderTopLeft, QPoint colliderBottomRight)
{
  bool collided = false;
  collided = collided || (pos1.x() < colliderBottomRight.x() && pos1.x() > colliderTopLeft.x());

  return (collided && (pos1.y() < colliderBottomRight.y() && pos1.y() > colliderTopLeft.y()));
}
