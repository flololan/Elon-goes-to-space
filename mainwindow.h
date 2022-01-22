#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <album.h>
#include <gestionhaptique.h>
#include <vibration.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Album album;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void on_button_clicked();

    void on_bouton_quitter_clicked();

    void on_butquitter_clicked();

private:
    Ui::MainWindow *ui;

    GestionHaptique *mHaptique;

    /**
     * @brief movable : Représente l'état de notre personnage, s'il doit bouger, ou non
     */
    bool movable;
    std::list<Vibration> vibrations;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void changePage();

    void activateEffect(Vibration& vibration);
    void deactivateEffect(Vibration& vibration);
};

#endif // MAINWINDOW_H
