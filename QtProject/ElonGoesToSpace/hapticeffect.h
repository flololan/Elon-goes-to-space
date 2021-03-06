#ifndef HAPTICEFFECT_H
#define HAPTICEFFECT_H
#include "effect.h"
#include <list>

class HapticEffect
{
public:
        HapticEffect();

    std::list<Effect> effects;

    void stopEffects();
    void startEffects();

    void addEffect(Effect effect);

    bool triggersEffect(QPoint cursorPosition);

    std::list<Effect> listTriggeredEffects(QPoint cursorPosition);
};

#endif
