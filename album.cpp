#include "album.h"
#include "vibrationtype.h"


Album::Album()
{

    // Création à la main des pages de l'album
    // Attention, voir album.hpp pour le nombre de pages
    page_courante = 0;

    // TODO : Refaire les rectangles de collision
	pages[0] = Page(":/case0.png", QPoint(1200,1200), QPoint(0,0), QPoint(0,0), "", false);
    pages[1] = Page(":/case1.png", QPoint(620,370), QPoint(520,0), QPoint(550,768), "Il est tard, Léo rentre d'une soirée et est épuisé alors il veut rapidement \naller se coucher.", false);
    pages[2] = Page(":/case2.jpg", QPoint(900,570), QPoint(450,320), QPoint(550,420), "Quand soudain, il est aspiré par son oreiller !", false);
    pages[3] = Page(":/case3.png", QPoint(800,570), QPoint(0,0), QPoint(20,768), "Il arrive dans un endroit étrange...\nAvec du sable partout et une chaleur étouffante !\nIl reprend ses esprits quand il entend un drôle de bruit. \nC'est alors qu'il l'aperçoit...Des énormes yeux...Une immense bouche... \nEt un pied gigantesque juste au dessus de lui !\nTerrorisé, il fuit.", false);
    pages[4] = Page(":/case4.png", QPoint(900,570), QPoint(0,0), QPoint(20,768), "Il court, court, escalade les dunes de sable. La chaleur est insupportable. \nLe géant n'a aucun mal à le suivre, il saute par dessus les dunes en un pas. ", false);
    pages[5] = Page(":/case5.png", QPoint(900,570), QPoint(0,0), QPoint(450,768), "Léo arrive enfin à la mer. Heureusement, il y a un bâteau ! \nIl met les voiles.", false);
    pages[6] = Page(":/case6.png", QPoint(800,558), QPoint(0,0), QPoint(20,768), "Mais le vent est contre lui, la mer est déchaînée et \nle ramène inlassablement vers le géant qui salive de plus en plus.", true);
    pages[7] = Page(":/case7.png", QPoint(800,558), QPoint(360,210), QPoint(560,291), "Et puis c'est arrivé... Il ne sent plus le sol sous ses pieds... Le géant l'a attrapé. \nLéo se débat dans tous les sens mais.... BLURG...", false);
    pages[8] = Page(":/casefin.png", QPoint(1200,1200), QPoint(0,0), QPoint(0,0), "Ouf, ce n'était qu'un rêve !\n\nRepiquet Vincent & Schnurr Patrick - Projet Haptique \nAnne Dejaune - Histoire\n\nSources : \nGéant : canstockphoto.fr \nChambre : coloriagesaimprimer.com \nBateau : galerie.coloritou.com \nVortex : scitechdaily.com", false);


    // création modèle vibratoir (haha ça sonne tellement faux)
    pagesVibrations[0] = PageVibration();

    pagesVibrations[1] = PageVibration(); // LIT

    pagesVibrations[2] = PageVibration();
    pagesVibrations[2].addVibration(Vibration(QPoint(0,0),QPoint(1024,768),VibrationType::VORTEX));

    pagesVibrations[3] = PageVibration();
    pagesVibrations[3].addVibration(Vibration(QPoint(0,0),QPoint(1024,768),VibrationType::GEANT));

    pagesVibrations[4] = PageVibration();
    pagesVibrations[4].addVibration(Vibration(QPoint(0,0),QPoint(1024,768),VibrationType::SABLE));
    pagesVibrations[4].addVibration(Vibration(QPoint(0,0),QPoint(1024,768),VibrationType::GEANT));

    pagesVibrations[5] = PageVibration(); // petit niveau va sur bateau
    pagesVibrations[5].addVibration(Vibration(QPoint(0,0),QPoint(1024,768),VibrationType::SABLE));
    pagesVibrations[5].addVibration(Vibration(QPoint(0,0),QPoint(1024,768),VibrationType::GEANT));

    pagesVibrations[6] = PageVibration(); // bateau
    pagesVibrations[6].addVibration(Vibration(QPoint(0,0),QPoint(1024,768),VibrationType::EAU));
    pagesVibrations[6].addVibration(Vibration(QPoint(0,0),QPoint(1024,768),VibrationType::VAGUE));

    pagesVibrations[7] = PageVibration();
    pagesVibrations[7].addVibration(Vibration(QPoint(0,0),QPoint(1024,768),VibrationType::BOUCHE));


}

/**
 * @brief Album::collided
 * @param x Abs du point a tester
 * @param y Ord du point a tester
 * @return Vrai si le point est dans le rectangle de collision
 */
bool Album::collided(int x, int y)
{
    return pages[page_courante].collided(x,y);
}

bool Album::triggersVibration(QPoint posBonhomme)
{
    return pagesVibrations[page_courante].triggersVibration(posBonhomme);
}

/**
 * ERREUR DE COMPILATION
 * @brief listTriggeredVibrations
 * @param posBonhomme
 * @return
 */
std::list<Vibration>  Album::listTriggeredVibrations(QPoint posBonhomme)
{
    return pagesVibrations[this->page_courante].listTriggeredVibrations(posBonhomme);
}
