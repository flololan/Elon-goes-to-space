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
            ui->draggableItem->move(event->x(), ui->draggableItem->y());
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
        scenes.currentScene++;
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
    draggable = false;
    effects = scenes.listTriggeredEffects(QPoint(ui->draggableItem->x(), ui->draggableItem->y()));

    // On change l'image de fond
    ui->label->setPixmap((QPixmap((scenes.pages[scenes.currentScene]).ressource->c_str())));

    // On change l'apparence du personnage selon la valeur de bateau

    /*
    * @todo replace with elon and dragon
    */
    if (scenes.pages[scenes.currentScene].bateau)
    {
        ui->draggableItem->setPixmap(QPixmap(":/bateau.png").scaled(QSize(200, 200), Qt::KeepAspectRatio));
        ui->draggableItem->setFixedWidth(200);
        ui->draggableItem->setFixedHeight(200);
    }
    else
    {
        ui->draggableItem->setPixmap(QPixmap(":/draggableItem.png").scaled(QSize(100, 100), Qt::KeepAspectRatio));

        ui->draggableItem->setFixedWidth(65);
        ui->draggableItem->setFixedHeight(100);
    }

    // Place item on start position
    ui->draggableItem->move(scenes.pages[scenes.currentScene].position_draggableItem.x(), scenes.pages[scenes.currentScene].position_draggableItem.y());

    /*
    * @todo Find a better way to handle scene index
    */
    if (scenes.currentScene == 8)
        ui->exitButton->setVisible(true);
}

/**
 * @brief MainWindow::onButtonClicked : Action on clic du bouton page suivante
 */
void MainWindow::onButtonClicked()
{
    if (scenes.currentScene < scenes.scenesAmount - 1)
        scenes.currentScene++;
    goToNextScene();

    // On désactive le bouton, qui n'a lieu d'être que sur la première page pour lancer l'aventure (pour le moment)
    ui->button->hide();
}

void MainWindow::activateEffect(Effect &effect)
{
    if (effect.isActive)
        return;

    effect.isActive = true;
    switch (effect.effectType)
    {
    case EffectType::SABLE:
        if (hapticController->GetSable())
        {
            hapticController->GetSable()->Start();
        }
        break;
    case EffectType::EAU:
        if (hapticController->GetEau())
        {
            hapticController->GetEau()->Start();
        }
        break;
    case EffectType::VAGUE:
        if (hapticController->GetVague())
        {
            hapticController->GetVague()->Start();
        }

        break;
    case EffectType::VORTEX:
        if (hapticController->GetVortex())
        {
            hapticController->GetVortex()->Start();
        }

        break;
    case EffectType::GEANT:
        if (hapticController->GetGeant())
        {
            hapticController->GetGeant()->Start();
        }
        break;

    case EffectType::BOUCHE:
        if (hapticController->GetBouche())
        {
            hapticController->GetBouche()->Start();
        }
        break;
    }
}

void MainWindow::deactivateEffect(Effect &effect)
{

    if (!effect.isActive)
        return;

    effect.isActive = false;
    switch (effect.effectType)
    {
    case EffectType::SABLE:
        if (hapticController->GetSable())
        {
            hapticController->GetSable()->Stop();
        }
        break;
    case EffectType::EAU:
        if (hapticController->GetEau())
        {
            hapticController->GetEau()->Stop();
        }
        break;
    case EffectType::VAGUE:
        if (hapticController->GetVague())
        {
            hapticController->GetVague()->Stop();
        }
        break;
    case EffectType::VORTEX:
        if (hapticController->GetVortex())
        {
            hapticController->GetVortex()->Stop();
        }
        break;
    case EffectType::GEANT:
        if (hapticController->GetGeant())
        {
            hapticController->GetGeant()->Stop();
        }
        break;

    case EffectType::BOUCHE:
        if (hapticController->GetBouche())
        {
            hapticController->GetBouche()->Stop();
        }
        break;
    }
}

void MainWindow::onExitButtonClicked()
{
    QApplication::quit();
}
