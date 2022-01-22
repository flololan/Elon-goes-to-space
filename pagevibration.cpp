#include "pagevibration.h"
#include <list>
#include <util.h>
#include <vibration.h>

PageVibration::PageVibration()
{
}
/**
 * @brief PageVibration::addVibration
 * @param vibration
 */
void PageVibration::addVibration(Vibration vibration)
{
    this->vibrations.push_back(vibration);
}

/**
  * Methode potentiellement, on peut aussi tester longueur de liste en retour de listTriggeredVibrations (par ex == 0)
 * @brief PageVibration::triggersVibration
 * @param posBonhomme
 * @return
 */
bool PageVibration::triggersVibration(QPoint posBonhomme){

    for (std::list<Vibration>::iterator it = this->vibrations.begin(); it != this->vibrations.end(); it++){

        Vibration vibration;

        if (Util::pointsCollided(posBonhomme, vibration.colliderHG, vibration.colliderBD))
            return true;
    }
    return false;
}


/**
 * @brief listTriggeredVibrations
 * @param posBonhomme
 * @return
 */
std::list<Vibration> PageVibration::listTriggeredVibrations(QPoint posBonhomme){

    std::list<Vibration> triggeredVibrations;

    for (std::list<Vibration>::iterator it = vibrations.begin(); it != this->vibrations.end(); it++) {
        if (Util::pointsCollided(posBonhomme, it->colliderHG, it->colliderBD))
            triggeredVibrations.push_back (*it);
    }

    return triggeredVibrations;
}







