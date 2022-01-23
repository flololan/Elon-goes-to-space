#include "hapticeffect.h"
#include <list>
#include <helper.h>
#include <effect.h>

HapticEffect::HapticEffect()
{
}
/**
 * @brief HapticEffect::addEffect
 * @param effect
 */
void HapticEffect::addEffect(Effect effect)
{
    this->effects.push_back(effect);
}

/**
  * Methode potentiellement, on peut aussi tester longueur de liste en retour de listTriggeredEffects (par ex == 0)
 * @brief HapticEffect::triggersEffect
 * @param cursorPosition
 * @return
 */
bool HapticEffect::triggersEffect(QPoint cursorPosition)
{

    for (std::list<Effect>::iterator it = this->effects.begin(); it != this->effects.end(); it++)
    {

        Effect effect;

        if (Helper::pointsCollided(cursorPosition, effect.colliderTopLeft, effect.colliderBottomRight))
            return true;
    }
    return false;
}

/**
 * @brief listTriggeredEffects
 * @param cursorPosition
 * @return
 */
std::list<Effect> HapticEffect::listTriggeredEffects(QPoint cursorPosition)
{

    std::list<Effect> triggeredEffects;

    for (std::list<Effect>::iterator it = effects.begin(); it != this->effects.end(); it++)
    {
        if (Helper::pointsCollided(cursorPosition, it->colliderTopLeft, it->colliderBottomRight))
            triggeredEffects.push_back(*it);
    }

    return triggeredEffects;
}