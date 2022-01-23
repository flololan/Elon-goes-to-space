#include "hapticcontroller.h"
#include <QApplication>
#include "mainwindow.h"
#include <QDebug>

HapticController::HapticController(MainWindow *fen) : mWindow(fen)
{

    //Initialisation de la souris
    mMouse = new CImmMouse();

    if (!mMouse->Initialize(qWinAppInst(), (HWND)mWindow->effectiveWinId()))
    {
        qDebug() << "===>Erreur chargement souris " << mMouse;
        delete mMouse;
        mMouse = NULL;
        qApp->quit();
    }

    mProject = new CImmProject();
    if (mProject->OpenFile("C:\\Users\\M2IHM\\Desktop\\ProjetFloetJojo\\projet_haptique\\QtProject\\ElonGoesToSpace\\assets\\HapticEffects.ifr", mMouse))
    {
        qDebug() << "IFR project has been loaded";

        mGround = mProject->CreateEffect("Scene1-ground", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mGround)
        {
            qDebug() << "===>Error loading the ground effect";
            delete mGround;
            mGround = NULL;
        }
    }
    else
    {
        qDebug() << "===>Erreur chargement projet IFR avec code " << CIFCErrors::GetLastErrorCode();
    }
}

HapticController::~HapticController()
{ }

// propre méthodes
CImmCompoundEffect *HapticController::GetGround() const
{
    return mGround;
}
