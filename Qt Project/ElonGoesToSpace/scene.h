#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <QPoint>
#include <QString>

class Scene
{
public:
    Scene();
    Scene(std::string res, QPoint cursorPosition, QPoint colliderTopLeft, QPoint colliderBottomRight);
    bool collided(int x, int y);

    const std::string *ressource;
    QPoint cursorPosition, colliderTopLeft, colliderBottomRight;
};

#endif
