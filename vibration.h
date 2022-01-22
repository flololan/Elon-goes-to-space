#ifndef VIBRATION_H
#define VIBRATION_H
#include "vibrationtype.h"
#include <qpoint.h>


class Vibration
{
public:

    Vibration();

    Vibration(QPoint colliderHG,
              QPoint colliderBD,
              VibrationType vibrationType
              );


    QPoint colliderHG;
    QPoint colliderBD;
    VibrationType vibrationType;
    bool isActive;
};

#endif // VIBRATION_H
