#ifndef ALBUM_H
#define ALBUM_H
#include "scene.h"
#include "hapticeffects.h"

class Scenes
{
public:
    Scenes();

    /**
     * @brief sceneAmount : Defines the amount of scenes
     */
    static const int scenesAmount = 6;

    int currentScene;

    /**
     * @brief scenes[] Table of the scenes
     */
    Scene scenes[scenesAmount];
    HapticEffects hapticEffects[scenesAmount];

    bool collided(int x, int y);
    bool triggersEffect(QPoint cursorPosition);
    std::list<Effect> listTriggeredEffects(QPoint cursorPosition);
};

#endif // ALBUM_H
