#include "scenes.h"
#include "effecttype.h"

Scenes::Scenes()
{
    currentScene = 0;

    scenes[0] = Scene(":/assets/scenesimages/scene_start.png", QPoint(1200, 1200), QPoint(0, 0), QPoint(0, 0));
    scenes[1] = Scene(":/assets/scenesimages/scene_elon_to_rocket.png", QPoint(620, 370), QPoint(520, 0), QPoint(550, 768));
    scenes[2] = Scene(":/assets/scenesimages/scene_joystick.png", QPoint(900, 570), QPoint(450, 320), QPoint(550, 420));
    scenes[3] = Scene(":/assets/scenesimages/scene_iss.png", QPoint(800, 570), QPoint(0, 0), QPoint(20, 768));
    scenes[4] = Scene(":/assets/scenesimages/scene_iss_door.png", QPoint(900, 570), QPoint(0, 0), QPoint(20, 768));
    scenes[5] = Scene(":/assets/scenesimages/scene_end.png", QPoint(900, 570), QPoint(0, 0), QPoint(450, 768));
    scenes[6] = Scene(":/assets/scenesimages/scene_bye.png", QPoint(900, 570), QPoint(0, 0), QPoint(450, 768));

    hapticEffects[0] = HapticEffect();

    hapticEffects[1] = HapticEffect();
    hapticEffects[1].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::GROUND));

    hapticEffects[2] = HapticEffect();
    hapticEffects[2].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::STICK));

    hapticEffects[3] = HapticEffect();
    hapticEffects[3].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::PARKING));

    hapticEffects[4] = HapticEffect();
    hapticEffects[4].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::DOOR));

    hapticEffects[5] = HapticEffect();
    hapticEffects[6] = HapticEffect();
}

/**
 * @brief Scenes::collided
 * @param x Abs du point a tester
 * @param y Ord du point a tester
 * @return Vrai si le point est dans le rectangle de collision
 */
bool Scenes::collided(int x, int y)
{
    return scenes[currentScene].collided(x, y);
}

bool Scenes::triggersEffect(QPoint cursorPosition)
{
    return hapticEffects[currentScene].triggersEffect(cursorPosition);
}

/**
 * ERREUR DE COMPILATION
 * @brief listTriggeredEffects
 * @param cursorPosition
 * @return
 */
std::list<Effect> Scenes::listTriggeredEffects(QPoint cursorPosition)
{
    return hapticEffects[this->currentScene].listTriggeredEffects(cursorPosition);
}
