#include "vibration.h"



Vibration::Vibration(){

}

Vibration:: Vibration(QPoint colliderHG,
                      QPoint colliderBD,
                      VibrationType vibrationType
                      )
{
    this->colliderHG = colliderHG;
    this->colliderBD = colliderBD;
    this->vibrationType = vibrationType;
    this->isActive = false;
}
