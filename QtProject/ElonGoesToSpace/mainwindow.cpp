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
    this->hapticController = new HapticController(this);
    this->goToScene(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (hapticController)
        delete hapticController;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int mouseX = event->x();
    // If user clicks on player icon it can be dragged, otherwise nothing happens
    /*
    * @todo change this crap
    */

    draggable = mouseX >= ui->draggableItem->x() && mouseX <= ui->draggableItem->x() + ui->draggableItem->height();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int mouseX = event->x();
    int mouseY = event->y();

    bool isDraggableItemInWindow = mouseX <= (this->maximumWidth() - ui->draggableItem->width());
    bool draggableItemCanMove =draggable && isDraggableItemInWindow ;

    if (draggableItemCanMove)
    {
        // Le switch pour dire que dans certaines pages, on peut bouger aussi verticalement. C'est pas super beau, mais plus rapide que l'ajout d'un champ
        switch (scenes.currentScene)
        {
        default:
            ui->draggableItem->move(
                        mouseX -  (ui->draggableItem->width() / 2),
                        mouseY -  (ui->draggableItem->height() / 2)
           );
            break;
        case 1:
            ui->draggableItem->move(
                        event->x() - (ui->draggableItem->width() / 2),
                        485 - ui->draggableItem->height()
            );
            break;
        }

        /*
        for (std::list<Effect>::iterator it = effects.begin(); it != effects.end(); it++)
        {
            this->activateEffect(*it);
        }
        */
    }

    // Si on entre en collision avec le rectangle de collision, alors on change de page
    bool isCollision = scenes.collided(
                ui->draggableItem->x(),
                ui->draggableItem->y()
    );

    if (isCollision)
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

void MainWindow::goToNextScene(){
     this->deactivateHapticEffect(scenes.hapticEffects[scenes.currentScene]);
    scenes.currentScene++;
    this->goToScene( scenes.currentScene);
}

void MainWindow::goToScene(int sceneIndex)
{
    this->activateHapticEffect(scenes.hapticEffects[sceneIndex]);
    draggable = false;
    effects = scenes.listTriggeredEffects(QPoint(ui->draggableItem->x(), ui->draggableItem->y()));

    ui->scene->setPixmap((QPixmap((scenes.scenes[sceneIndex]).ressource->c_str())));

    if(sceneIndex == 1) {
        ui->draggableItem->move(0, 400);
    }
    if (sceneIndex == 3 )
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
            scenes.scenes[sceneIndex].cursorPosition.x(),
            scenes.scenes[sceneIndex].cursorPosition.y()
    );

    /*
    * @todo Find a better way to handle scene index
    */
    if (scenes.currentScene == 5)
        ui->exitButton->setVisible(true);
}

void MainWindow::activateHapticEffect(HapticEffect hapticEffect){
    for(Effect effect : hapticEffect.effects) {
        this->activateEffect(effect);
    }
}

void MainWindow::deactivateHapticEffect(HapticEffect hapticEffect){
    for(Effect effect : hapticEffect.effects) {
        this->deactivateEffect(effect);
    }
}

void MainWindow::activateEffect(Effect effect)
{
    effect.isActive;
    switch (effect.effectType)
    {
    case EffectType::GROUND:
        hapticController->GetGround()->Start();
        break;
    case EffectType::STICK:
        hapticController->GetStick()->Start();
        break;
    case EffectType::DOOR:
        hapticController->GetDoor()->Start();
        break;
    case EffectType::LIFT:
        hapticController->GetLift()->Start();
        break;
    case EffectType::PARKING:
        hapticController->GetParking()->Start();
        break;
    }
}

void MainWindow::deactivateEffect(Effect effect)
{
    effect.isActive = false;
    switch (effect.effectType)
    {
    case EffectType::GROUND:
        hapticController->GetGround()->Stop();
        break;
    case EffectType::STICK:
        hapticController->GetStick()->Stop();
        break;
    case EffectType::DOOR:
        hapticController->GetDoor()->Stop();
        break;
    case EffectType::LIFT:
        hapticController->GetLift()->Stop();
        break;
    case EffectType::PARKING:
        hapticController->GetParking()->Stop();
        break;
     }
}

void MainWindow::on_startButton_clicked()
{
    goToNextScene();
    // ui->startButton->hide();
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}
