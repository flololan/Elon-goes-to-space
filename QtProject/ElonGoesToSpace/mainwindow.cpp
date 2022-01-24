#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helper.h"
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <list>
#include <QtMultimedia/QMediaPlayer>
#include <QUrl>
#include <QString>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :

                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    draggable = false;
    isLiftEffectActive = false;
    scenes = Scenes();

    ui->setupUi(this);

    ui->exitButton->setVisible(false);
    this->hapticController = new HapticController(this);
    // init audio
    playerLift = new QMediaPlayer;
    playerDecollage = new QMediaPlayer;
    playerLift->setMedia(QUrl("https://github.com/flololan/Elon-goes-to-space/raw/master/QtProject/ElonGoesToSpace/assets/sf_elevator3.wav"));
    playerDecollage->setMedia(QUrl("https://github.com/flololan/Elon-goes-to-space/raw/master/QtProject/ElonGoesToSpace/assets/scene2.wav"));
    playerLift->setVolume(100);
    playerDecollage->setVolume(100);

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
    draggable = mouseX >= ui->draggableItem->x() && mouseX <= ui->draggableItem->x() + ui->draggableItem->height();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int mouseX = event->x();
    int mouseY = event->y();

    bool isDraggableItemInWindow = mouseX <= (this->maximumWidth() - ui->draggableItem->width());
    bool draggableItemCanMove = draggable && isDraggableItemInWindow;

    if (draggableItemCanMove)
    {
        if (scenes.currentScene == 1)
        {
            int y = this->getTinyElonYCoordinate();
            CImmCompoundEffect *liftEffect = this->hapticController->GetLift();

            bool canTinyElonGoUpOnRocket = Helper::pointsCollided(
                QPoint(ui->draggableItem->x(), ui->draggableItem->y()),
                QPoint(640, 0),
                QPoint(800, this->getTinyElonYCoordinate() + (ui->draggableItem->height() / 1.8)));
            bool isTinyElonInShuttle = Helper::pointsCollided(
                QPoint(event->x(), event->y()),
                QPoint(800, 0),
                QPoint(900, 400));

            if (isTinyElonInShuttle)
            {
                liftEffect->Stop();
                this->goToNextScene();
            }
            if (canTinyElonGoUpOnRocket)
            {
                y = event->y() - (ui->draggableItem->height() / 2);

                if (!this->isLiftEffectActive)
                {
                    isLiftEffectActive = true;
                    qDebug() << "start";
                    liftEffect->Start();

                    this->playerLift->play();
                }
            }

            ui->draggableItem->move(
                event->x() - (ui->draggableItem->width() / 2),
                y);
        }
        else
        {
            ui->draggableItem->move(
                mouseX - (ui->draggableItem->width() / 2),
                mouseY - (ui->draggableItem->height() / 2));
            if (scenes.currentScene == 3)
            {
                bool isShuttleDocked = Helper::pointsCollided(
                    QPoint(event->x(), event->y()),
                    QPoint(200, 290),
                    QPoint(260, 330));
                if (isShuttleDocked)
                {
                    this->goToNextScene();
                }
            }
        }
    }

    // If collision with rectangle, go to next scene
    bool isCollision = scenes.collided(
        mouseX,
        mouseY);

    if (isCollision)
        goToNextScene();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    draggable = false;
}

void MainWindow::goToNextScene()
{
    this->deactivateHapticEffect(scenes.hapticEffects[scenes.currentScene]);
    this->goToScene(scenes.currentScene + 1);
}

void MainWindow::goToScene(int sceneIndex)
{
    scenes.currentScene = sceneIndex;
    this->activateHapticEffect(scenes.hapticEffects[sceneIndex]);
    draggable = false;
    effects = scenes.listTriggeredEffects(QPoint(ui->draggableItem->x(), ui->draggableItem->y()));

    ui->scene->setPixmap((QPixmap((scenes.scenes[sceneIndex]).ressource->c_str())));
    ui->draggableItem->setPixmap(QPixmap(":/assets/draggableitems/asset_tiny_elon.png"));
    ui->startButton->setVisible(false);
    ui->joystickButton->setVisible(false);
    ui->draggableItem->hide();

    this->playerLift->stop();
    this->playerDecollage->stop();

    if (sceneIndex == 0)
    {
        ui->startButton->setVisible(true);
    }
    if (sceneIndex == 1 || sceneIndex == 3)
    {
        ui->draggableItem->show();
    }
    if (sceneIndex == 1)
    {
        ui->draggableItem->move(QPoint(0, this->getTinyElonYCoordinate()));
        ui->draggableItem->setFixedWidth(101);
        ui->draggableItem->setFixedHeight(111);
    }
    if (sceneIndex == 2)
    {
        this->playerDecollage->play();
        ui->joystickButton->setVisible(true);
    }
    if (sceneIndex == 3)
    {
        ui->draggableItem->setPixmap(QPixmap(":/assets/draggableitems/asset_elon_on_rocket_to_iss.png"));
        ui->draggableItem->setFixedWidth(150);
        ui->draggableItem->setFixedHeight(187);
        ui->draggableItem->move(QPoint(
            this->maximumWidth() - ui->draggableItem->width() - 50,
            this->maximumHeight() - ui->draggableItem->height() - 50));
    }
    if (sceneIndex == 4)
    {
        // go to next scene after 6seconds
        QTimer::singleShot(6000, this, &MainWindow::goToNextScene);
    }
    if (sceneIndex == 5)
    {
        ui->exitButton->setVisible(true);
    }
    if (sceneIndex == 6)
    {
        ui->exitButton->setVisible(false);
    }
}

int MainWindow::getTinyElonYCoordinate()
{
    return 485 - ui->draggableItem->height();
}

void MainWindow::activateHapticEffect(HapticEffect hapticEffect)
{
    for (Effect effect : hapticEffect.effects)
    {
        this->activateEffect(effect);
    }
}

void MainWindow::deactivateHapticEffect(HapticEffect hapticEffect)
{
    for (Effect effect : hapticEffect.effects)
    {
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

void MainWindow::on_startButton_clicked() { goToNextScene(); }
void MainWindow::on_joystickButton_pressed() { goToNextScene(); }
void MainWindow::on_exitButton_clicked()
{
    goToNextScene();

    // close application after 2seconds to see the end scene
    QTimer::singleShot(2000, this, &QApplication::quit);
}
