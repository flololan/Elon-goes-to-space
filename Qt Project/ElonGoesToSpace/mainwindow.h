#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <scenes.h>
#include <hapticcontroller.h>
#include <effect.h>

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
    void onExitButtonClicked();

    //void on_exitButton_clicked();

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    HapticController *hapticController;

    /**
     * @brief draggable : If player/cursor can be dragged
     */
    bool draggable;
    std::list<Effect> effects;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void goToNextScene();

    void activateEffect(Effect& effect);
    void deactivateEffect(Effect& effect);
};

#endif
