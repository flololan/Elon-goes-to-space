#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <list>
#include <effect.h>

MainWindow::MainWindow(QWidget *parent) :

                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    // Initialisation de champs
    draggable = false;
    scenes = Scenes();

    ui->setupUi(this);

    ui->exitButton->setVisible(false);
    // Pour initialiser l'scenes, on appelle goToNextScene sans changer le numéro de page (qui est donc à 0)
    goToNextScene();

    this->hapticController = new HapticController(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (hapticController)
        delete hapticController;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // If user clicks on player icon it can be dragged, otherwise nothing happens
    /*
    * @todo change this crap
    */

    draggable = event->x() >= ui->draggableItem->x() && event->x() <= ui->draggableItem->x() + ui->draggableItem->height();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Si l'image ne dépasse pas du cadre à droite en bougeant, elle bouge
    if (draggable && event->x() <= this->maximumWidth() - ui->draggableItem->width())
    {
        switch (scenes.currentScene) // Le switch pour dire que dans certaines pages, on peut bouger aussi verticalement. C'est pas super beau, mais plus rapide que l'ajout d'un champ
        {
        case 2: // page vortex
        case 7: // page du g"ant qui l'avale
            ui->draggableItem->move(event->x(), event->y());
            break;
        default:
            ui->draggableItem->move(event->x(), 300);
            break;
        }

        // Detection si une effect doit être créée
        for (std::list<Effect>::iterator it = effects.begin(); it != effects.end(); it++)
        {
            this->activateEffect(*it);
        }
    }

    // Si on entre en collision avec le rectangle de collision, alors on change de page
    if (scenes.collided(ui->draggableItem->x(), ui->draggableItem->y()) && (scenes.currentScene < scenes.scenesAmount - 1)) // diff derniere page
    {
        for (std::list<Effect>::iterator it = effects.begin(); it != effects.end(); it++)
        { // avant de changer de page on supprime les effets
            this->deactivateEffect(*it);
        }
        goToNextScene();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (draggable)
    {
        for (std::list<Effect>::iterator it = effects.begin(); it != effects.end(); it++)
        {
            this->deactivateEffect(*it);
        }
    }
    draggable = false;
}

void MainWindow::goToNextScene()
{
    scenes.currentScene++;
    draggable = false;
    effects = scenes.listTriggeredEffects(QPoint(ui->draggableItem->x(), ui->draggableItem->y()));

    ui->scene->setPixmap((QPixmap((scenes.scenes[scenes.currentScene]).ressource->c_str())));

    if(scenes.currentScene == 1) {
        ui->draggableItem->move(0, 400);
    }
    if (scenes.currentScene == 3 )
    {
        ui->draggableItem->setPixmap(QPixmap(":/assets/draggableitems/asset_elon_on_rocket_to_iss.png").scaled(QSize(200, 200), Qt::KeepAspectRatio));
        ui->draggableItem->setFixedWidth(200);
        ui->draggableItem->setFixedHeight(200);
    }
    else
    {
        ui->draggableItem->setPixmap(QPixmap(":/assets/draggableitems/asset_tiny_elon.png").scaled(QSize(100, 100), Qt::KeepAspectRatio));
    }

    // Place item on start position
    ui->draggableItem->move(
                scenes.scenes[scenes.currentScene].cursorPosition.x(),
            scenes.scenes[scenes.currentScene].cursorPosition.y()
    );

    /*
    * @todo Find a better way to handle scene index
    */
    if (scenes.currentScene == 5)
        ui->exitButton->setVisible(true);
}

void MainWindow::activateEffect(Effect& effect)
{
    qDebug() << "start effect";
    if (effect.isActive)
        return;
    qDebug() << "start effect success";

    effect.isActive = true;

    switch (effect.effectType)
    {
    case EffectType::GROUND:
        if (hapticController->GetGround())
        {
            hapticController->GetGround()->Start();
        }
        break;
    }
}

void MainWindow::deactivateEffect(Effect& effect)
{
    if (!effect.isActive)
        return;

    effect.isActive = false;
    switch (effect.effectType)
    {
    case EffectType::GROUND:
        if (hapticController->GetGround())
        {
            hapticController->GetGround()->Stop();
        }
        break;
     }
}

void MainWindow::onExitButtonClicked()
{
    QApplication::quit();
}

void MainWindow::on_startButton_clicked()
{
    goToNextScene();
    ui->startButton->hide();
}
