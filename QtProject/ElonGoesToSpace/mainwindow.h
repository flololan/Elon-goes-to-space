#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <scenes.h>
#include <hapticcontroller.h>
#include <effect.h>
#include <QMediaPlayer>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Scenes scenes;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_exitButton_clicked();

    void on_joystickButton_pressed();

private:
    Ui::MainWindow *ui;
    HapticController *hapticController;
    QMediaPlayer *player;

    /**
     * @brief draggable : If player/cursor can be dragged
     */
    bool draggable;
    bool isLiftEffectActive;
    std::list<Effect> effects;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void goToScene(int sceneIndex);
    void goToNextScene();

    void activateEffect(Effect effect);
    void activateHapticEffect(HapticEffect hapticEffect);
    void deactivateEffect(Effect effect);
    void deactivateHapticEffect(HapticEffect hapticEffect);

    int MainWindow::getTinyElonYCoordinate();
};

#endif
