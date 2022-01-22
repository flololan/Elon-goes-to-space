#ifndef ALBUM_H
#define ALBUM_H
#include "page.h"
#include "pagevibration.h"

class Album
{
public:
    Album();

    /**
     * @brief nb_pages : Défini le nombre de pages de l'album
     */
    static const int nb_pages=9;

    int page_courante;

    /**
     * @brief pages Tableau static (pour simplifier les choses) contennant les pages de l'album
     */
    Page pages[nb_pages];
    PageVibration pagesVibrations[nb_pages];



    // Méhtode
    bool collided(int x, int y);
    bool triggersVibration(QPoint posBonhomme);
    std::list<Vibration> listTriggeredVibrations(QPoint posBonhomme);


};

#endif // ALBUM_H
