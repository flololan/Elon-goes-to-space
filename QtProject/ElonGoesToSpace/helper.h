#ifndef HELPER_H
#define HELPER_H

#include <QPoint>

class Helper
{
public:
    static bool pointsCollided(QPoint pos1, QPoint colliderHG, QPoint colliderBD);

private:
    Helper() {}
};

#endif
