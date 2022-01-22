#ifndef PAGE_H
#define PAGE_H
#include <string>
#include <QPoint>
#include <QString>

class Page
{
public:
    Page();
    Page(std::string res, QPoint pos_bonhomme, QPoint colliderH, QPoint colliderB, std::string text, bool bateau);
    bool collided(int x, int y);


    const std::string *ressource;
    const std::string *texte;
    QPoint position_bonhomme, colliderHG, colliderBD;
    bool bateau;



};

#endif // PAGE_H
