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

    CImmCompoundEffect *GetGround() const;
    CImmCompoundEffect *GetDoor() const;
    CImmCompoundEffect *GetParking() const;
    CImmCompoundEffect *GetLift() const;
    CImmCompoundEffect *GetStick() const;

private:
    CImmMouse *mMouse;
    CImmProject *mProject;
    MainWindow *mWindow;

    CImmCompoundEffect *mGround;
    CImmCompoundEffect *mDoor;
    CImmCompoundEffect *mParking;
    CImmCompoundEffect *mLift;
    CImmCompoundEffect *mStick;
};

#endif
