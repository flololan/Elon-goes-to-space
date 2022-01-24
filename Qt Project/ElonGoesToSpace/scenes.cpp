#include "scenes.h"
         "
#include "effecttype.h"
         "

Scenes::Scenes()
{
    
    currentScene = 0;

    scenes[0] = Scene(":/case0.png", QPoint(1200, 1200), QPoint(0, 0), QPoint(0, 0), "", false);
    scenes[1] = Scene(":/case1.png", QPoint(620, 370), QPoint(520, 0), QPoint(550, 768), "Il est tard, Léo rentre d'une soirée et est épuisé alors il veut rapidement \naller se coucher.", false);
    scenes[2] = Scene(":/case2.jpg", QPoint(900, 570), QPoint(450, 320), QPoint(550, 420), "Quand soudain, il est aspiré par son oreiller !", false);
    scenes[3] = Scene(":/case3.png", QPoint(800, 570), QPoint(0, 0), QPoint(20, 768), "Il arrive dans un endroit étrange...\nAvec du sable partout et une chaleur étouffante !\nIl reprend ses esprits quand il entend un drôle de bruit. \nC'est alors qu'il l'aperçoit...Des énormes yeux...Une immense bouche... \nEt un pied gigantesque juste au dessus de lui !\nTerrorisé, il fuit.", false);
    scenes[4] = Scene(":/case4.png", QPoint(900, 570), QPoint(0, 0), QPoint(20, 768), "Il court, court, escalade les dunes de sable. La chaleur est insupportable. \nLe géant n'a aucun mal à le suivre, il saute par dessus les dunes en un pas. ", false);
    scenes[5] = Scene(":/case5.png", QPoint(900, 570), QPoint(0, 0), QPoint(450, 768), "Léo arrive enfin à la mer. Heureusement, il y a un bâteau ! \nIl met les voiles.", false);
    scenes[6] = Scene(":/case6.png", QPoint(800, 558), QPoint(0, 0), QPoint(20, 768), "Mais le vent est contre lui, la mer est déchaînée et \nle ramène inlassablement vers le géant qui salive de plus en plus.", true);

    hapticEffects[0] = HapticEffects();

    hapticEffects[1] = HapticEffects();

    hapticEffects[2] = HapticEffects();
    hapticEffects[2].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::VORTEX));

    hapticEffects[3] = HapticEffects();
    hapticEffects[3].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::GEANT));

    hapticEffects[4] = HapticEffects();
    hapticEffects[4].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::SABLE));
    hapticEffects[4].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::GEANT));

    hapticEffects[5] = HapticEffects();
    hapticEffects[5].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::SABLE));
    hapticEffects[5].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::GEANT));

    hapticEffects[6] = HapticEffects();
    hapticEffects[6].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::EAU));
    hapticEffects[6].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::VAGUE));

    hapticEffects[7] = HapticEffects();
    hapticEffects[7].addEffect(Effect(QPoint(0, 0), QPoint(1024, 768), EffectType::BOUCHE));
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
