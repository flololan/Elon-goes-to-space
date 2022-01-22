#ifndef PAGEVIBRATION_H
#define PAGEVIBRATION_H
#include "vibration.h"
#include <list>


class PageVibration
{
public:
    //PageVibration(); // default constructor


    PageVibration();

    // attributs
    std::list<Vibration> vibrations;

    void deactivateEffects();

    // methods
    void addVibration(Vibration vibration);

    bool triggersVibration(QPoint posBonhomme);

    std::list<Vibration> listTriggeredVibrations(QPoint posBonhomme);

};

#endif // PAGEVIBRATION_H
