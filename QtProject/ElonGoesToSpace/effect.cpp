#include "effect.h"

Effect::Effect()
{
}

Effect::Effect(QPoint colliderTopLeft,
               QPoint colliderBottomRight,
               EffectType effectType)
{
    this->colliderTopLeft = colliderTopLeft;
    this->colliderBottomRight = colliderBottomRight;
    this->effectType = effectType;
    this->isActive = false;
}
