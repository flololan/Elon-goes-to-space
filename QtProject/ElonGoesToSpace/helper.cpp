#include "helper.h"

/**
  *
 * @brief Helper::pointsCollided
 * @param pos1
 * @param pos1
 * @return
 */
bool Helper::pointsCollided(QPoint point, QPoint colliderTopLeft, QPoint colliderBottomRight)
{
  return (point.y() < colliderBottomRight.y()
          && point.y() > colliderTopLeft.y()
          && point.x() > colliderTopLeft.x()
          && point.x() < colliderBottomRight.x()
  );
}
