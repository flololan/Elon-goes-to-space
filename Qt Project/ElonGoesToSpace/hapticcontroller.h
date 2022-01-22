#ifndef HAPTICCONTROLLER_H
#define HAPTICCONTROLLER_H

//To not compile in unicode mode
#undef UNICODE

//IFC Libraries
#include <IFC.h>
#include <QMainWindow>
#include <QPoint>

//Link to main window where haptic feedback is managed
class MainWindow;

class HapticController
{
public:
    //Link to main window where haptic feedback is managed
    HapticController(MainWindow *fen);
    ~HapticController();

    // méthodes album-enfant
    CImmCompoundEffect *GetEau() const;
    CImmCompoundEffect *GetSable() const;
    CImmCompoundEffect *GetGeant() const;
    CImmCompoundEffect *GetVortex() const;
    CImmCompoundEffect *GetVague() const;
    CImmCompoundEffect *GetBouche() const;

private:
    CImmMouse *mMouse;
    CImmProject *mProject;
    MainWindow *mWindow;

    // attributs album-enfant
    CImmCompoundEffect *mEau;
    CImmCompoundEffect *mSable;
    CImmCompoundEffect *mGeant;
    CImmCompoundEffect *mVortex;
    CImmCompoundEffect *mVague;
    CImmCompoundEffect *mBouche;
};

#endif // HAPTICCONTROLLER_H
