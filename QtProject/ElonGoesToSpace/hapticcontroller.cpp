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
        mDoor = mProject->CreateEffect("Scene4-circle", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mDoor)
        {
            qDebug() << "===>Error loading the door effect";
            delete mDoor;
            mDoor = NULL;
        }
        mStick = mProject->CreateEffect("Scene2-Stick", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mStick)
        {
            qDebug() << "===>Error loading the stick effect";
            delete mStick;
            mStick = NULL;
        }
        mLift = mProject->CreateEffect("Scene1-Lift", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mLift)
        {
            qDebug() << "===>Error loading the lift effect";
            delete mLift;
            mLift = NULL;
        }
        mParking = mProject->CreateEffect("Scene3-Parking", mMouse, IMM_PARAM_NODOWNLOAD);
        if (!mParking)
        {
            qDebug() << "===>Error loading the parking effect";
            delete mParking;
            mParking = NULL;
        }
    }
    else
    {
        qDebug() << "===>Erreur chargement projet IFR avec code " << CIFCErrors::GetLastErrorCode();
    }
}

HapticController::~HapticController()
{ }


CImmCompoundEffect *HapticController::GetGround() const
{
    return mGround;
}
CImmCompoundEffect *HapticController::GetDoor() const
{
    return mDoor;
}
CImmCompoundEffect *HapticController::GetParking() const
{
    return mParking;
}
CImmCompoundEffect *HapticController::GetLift() const
{
    return mLift;
}
CImmCompoundEffect *HapticController::GetStick() const
{
    return mStick;
}
