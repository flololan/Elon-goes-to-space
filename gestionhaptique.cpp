#include "gestionhaptique.h"
#include <QApplication>
#include "mainwindow.h"
#include <QDebug>

GestionHaptique::GestionHaptique(MainWindow *fen):mFenetre(fen)
{

    //Initialisation de la souris
    mSouris = new CImmMouse();

    if (!mSouris->Initialize(qWinAppInst(),  (HWND)mFenetre->effectiveWinId()  ))
    {qDebug()<<"===>Erreur chargement souris "<<mSouris;
        delete mSouris;
        mSouris = NULL;
        qApp->quit();
    }

    mProjet = new CImmProject();
    if (mProjet->OpenFile("C:\\Users\\M2IHM\\Desktop\\retour-haptique\\effets.ifr", mSouris))
    { //le chemin par dfaut est celui o se trouve la gnration : xxx-build-desktop/
        qDebug()<<"Projet ifr charg";

        mEau = mProjet->CreateEffect("Eau", mSouris, IMM_PARAM_NODOWNLOAD);
        if (!mEau) {
            qDebug()<<"===>Erreur chargement eau ";
            delete mEau;
            mEau = NULL;
        }


        mSable = mProjet->CreateEffect("Sable", mSouris, IMM_PARAM_NODOWNLOAD);
        if (!mSable) {
            qDebug()<<"===>Erreur chargement sable ";
            delete mSable;
            mSable = NULL;
        }


        mGeant = mProjet->CreateEffect("Geant", mSouris, IMM_PARAM_NODOWNLOAD);
        if (!mGeant) {
            qDebug()<<"===>Erreur chargement Geant ";
            delete mGeant;
            mGeant = NULL;
        }

        mVortex = mProjet->CreateEffect("Vortex", mSouris, IMM_PARAM_NODOWNLOAD);
        if (!mVortex) {
            qDebug()<<"===>Erreur chargement Vortex ";
            delete mVortex;
            mVortex = NULL;
        }

        mVague = mProjet->CreateEffect("Vague", mSouris, IMM_PARAM_NODOWNLOAD);
        if (!mVague) {
            qDebug()<<"===>Erreur chargement Vague ";
            delete mVague;
            mVague = NULL;
        }

        mBouche = mProjet->CreateEffect("Bouche", mSouris, IMM_PARAM_NODOWNLOAD);
        if (!mBouche) {
            qDebug()<<"===>Erreur chargement Vague ";
            delete mBouche;
            mBouche = NULL;
        }


    }
    else
    {
        qDebug()<<"===>Erreur chargement projet IFR avec code "<<CIFCErrors::GetLastErrorCode() ;
    }
}

GestionHaptique::~GestionHaptique()
{/*
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
    if(mSouris)
        delete mSouris;
    if(mProjet)
        delete mProjet;*/
}

// propre méthodes
CImmCompoundEffect *GestionHaptique::GetEau() const
{
    return mEau;
}

CImmCompoundEffect *GestionHaptique::GetVortex() const
{
    return mVortex;
}

CImmCompoundEffect *GestionHaptique::GetSable() const
{
    return mSable;
}

CImmCompoundEffect *GestionHaptique::GetGeant() const
{
    return mGeant;
}

CImmCompoundEffect *GestionHaptique::GetVague() const
{
    return mVague;
}

CImmCompoundEffect *GestionHaptique::GetBouche() const
{
    return mBouche;
}









