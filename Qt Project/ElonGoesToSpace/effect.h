#ifndef EFFECT_H
#define EFFECT_H
#include "effecttype.h"
#include <qpoint.h>

class Effect
{
public:
    Effect();

    Effect(QPoint colliderTopLeft,
           QPoint colliderBottomRight,
           EffectType effectType);

    QPoint colliderTopLeft;
    QPoint colliderBottomRight;
    EffectType effectType;
    bool isActive;
};

#endif
