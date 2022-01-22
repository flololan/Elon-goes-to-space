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
    if (mProject->OpenFile("C:\\Users\\M2IHM\\Desktop\\retour-haptique\\effets.ifr", mMouse))
    { //le chemin par dfaut est celui o se trouve la gnration : xxx-build-desktop/
        qDebug() << "Projet ifr charg";

        mEau = mProject->CreateEffect("Eau", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mEau)
        {
            qDebug() << "===>Erreur chargement eau ";
            delete mEau;
            mEau = NULL;
        }

        mSable = mProject->CreateEffect("Sable", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mSable)
        {
            qDebug() << "===>Erreur chargement sable ";
            delete mSable;
            mSable = NULL;
        }

        mGeant = mProject->CreateEffect("Geant", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mGeant)
        {
            qDebug() << "===>Erreur chargement Geant ";
            delete mGeant;
            mGeant = NULL;
        }

        mVortex = mProject->CreateEffect("Vortex", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mVortex)
        {
            qDebug() << "===>Erreur chargement Vortex ";
            delete mVortex;
            mVortex = NULL;
        }

        mVague = mProject->CreateEffect("Vague", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mVague)
        {
            qDebug() << "===>Erreur chargement Vague ";
            delete mVague;
            mVague = NULL;
        }

        mBouche = mProject->CreateEffect("Bouche", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mBouche)
        {
            qDebug() << "===>Erreur chargement Vague ";
            delete mBouche;
            mBouche = NULL;
        }
    }
    else
    {
        qDebug() << "===>Erreur chargement projet IFR avec code " << CIFCErrors::GetLastErrorCode();
    }
}

HapticController::~HapticController()
{ /*
    if (mEau)
        delete mEau;
    if (mVortex)
        delete mVortex;
    if (mSable)
        delete mSable;
    if (mGeant)
        delete mGeant;
    //if (mVague)
      //  delete mVague;
    if(mMouse)
        delete mMouse;
    if(mProject)
        delete mProject;*/
}

// propre méthodes
CImmCompoundEffect *HapticController::GetEau() const
{
    return mEau;
}

CImmCompoundEffect *HapticController::GetVortex() const
{
    return mVortex;
}

CImmCompoundEffect *HapticController::GetSable() const
{
    return mSable;
}

CImmCompoundEffect *HapticController::GetGeant() const
{
    return mGeant;
}

CImmCompoundEffect *HapticController::GetVague() const
{
    return mVague;
}

CImmCompoundEffect *HapticController::GetBouche() const
{
    return mBouche;
}