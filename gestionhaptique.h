#ifndef GESTIONHAPTIQUE_H
#define GESTIONHAPTIQUE_H


//Compilation en mode non unicode
#undef UNICODE



#include <ifc.h>
#include <QPoint>
#include <QMainWindow>

class MainWindow;

class GestionHaptique
{
public:
    GestionHaptique(MainWindow *fen);
    ~GestionHaptique();



    // méthodes album-enfant
    CImmCompoundEffect *GetEau() const;
    CImmCompoundEffect *GetSable() const;
    CImmCompoundEffect *GetGeant() const;
    CImmCompoundEffect *GetVortex() const;
    CImmCompoundEffect *GetVague() const;
    CImmCompoundEffect *GetBouche() const;
private:

    CImmMouse* mSouris;
    CImmProject* mProjet;
    MainWindow *mFenetre;

    // attributs album-enfant
    CImmCompoundEffect *mEau;
    CImmCompoundEffect *mSable;
    CImmCompoundEffect *mGeant;
    CImmCompoundEffect *mVortex;
    CImmCompoundEffect *mVague;
    CImmCompoundEffect *mBouche;
};


#endif // GESTIONHAPTIQUE_H

