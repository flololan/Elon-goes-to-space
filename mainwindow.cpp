#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include <list>
#include <vibration.h>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Initialisation de champs
    movable=false;
    album = Album();

    ui->setupUi(this);

    ui->butquitter->setVisible(false);
    // Pour initialiser l'album, on appelle changePage sans changer le numéro de page (qui est donc à 0)
    changePage();


    this->mHaptique = new GestionHaptique(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (mHaptique)
        delete mHaptique;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Si l'utilisateur clique sur l'image, l'image devient movable, sinon, rien ne se passe
    if(event->x()>=ui->bonhomme->x() && event->x() <= ui->bonhomme->x()+ui->bonhomme->height()){
        movable = true;
    }
    else {
        movable = false;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Si l'image ne dépasse pas du cadre à droite en bougeant, elle bouge
    if(movable && event->x() <= this->maximumWidth()-ui->bonhomme->width()) {
        switch(album.page_courante) // Le switch pour dire que dans certaines pages, on peut bouger aussi verticalement. C'est pas super beau, mais plus rapide que l'ajout d'un champ
        {
        case 2 : // page vortex
        case 7 : // page du g"ant qui l'avale
            ui->bonhomme->move(event->x(), event->y());
            break;
        default :
            ui->bonhomme->move(event->x(), ui->bonhomme->y());
            break;
        }

        // Detection si une vibration doit être créée
        for (std::list<Vibration>::iterator it = vibrations.begin(); it != vibrations.end(); it++) {
            this->activateEffect(*it);
        }
    }

    // Si on entre en collision avec le rectangle de collision, alors on change de page
    if(album.collided(ui->bonhomme->x(), ui->bonhomme->y()) && (album.page_courante<album.nb_pages-1)) // diff derniere page
    {
        for (std::list<Vibration>::iterator it = vibrations.begin(); it != vibrations.end(); it++) { // avant de changer de page on supprime les effets
            this->deactivateEffect(*it);
        }
        album.page_courante++;
        changePage();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if (movable){

        for (std::list<Vibration>::iterator it = vibrations.begin(); it != vibrations.end(); it++) {
            this->deactivateEffect(*it);
        }
    }
    movable=false;
}


void MainWindow::changePage()
{

    movable=false;
    vibrations = album.listTriggeredVibrations(QPoint( ui->bonhomme->x(), ui->bonhomme->y()));

    // On change l'image de fond
    ui->label->setPixmap((QPixmap((album.pages[album.page_courante]).ressource->c_str())));

    // On change le texte
    ui->textePage->setText((album.pages[album.page_courante]).texte->c_str());

    // On change l'apparence du personnage selon la valeur de bateau
    if(album.pages[album.page_courante].bateau)
    {
        ui->bonhomme->setPixmap(QPixmap(":/bateau.png").scaled(QSize(200,200),  Qt::KeepAspectRatio));
        ui->bonhomme->setFixedWidth(200);
        ui->bonhomme->setFixedHeight(200);
    }
    else
    {
        ui->bonhomme->setPixmap(QPixmap(":/bonhomme.png").scaled(QSize(100,100),  Qt::KeepAspectRatio));

        ui->bonhomme->setFixedWidth(65);
        ui->bonhomme->setFixedHeight(100);
    }

    // On déplace notre personnage à l'endroit de départ de la page
    ui->bonhomme->move(album.pages[album.page_courante].position_bonhomme.x(),album.pages[album.page_courante].position_bonhomme.y());

    if(album.page_courante==8)
        ui->butquitter->setVisible(true);
}

/**
 * @brief MainWindow::on_button_clicked : Action on clic du bouton page suivante
 */
void MainWindow::on_button_clicked()
{
    if(album.page_courante<album.nb_pages-1)
        album.page_courante++;
    changePage();

    // On désactive le bouton, qui n'a lieu d'être que sur la première page pour lancer l'aventure (pour le moment)
    ui->button->hide();
}

void MainWindow::activateEffect(Vibration& vibration)
{
    if (vibration.isActive)
        return;

    vibration.isActive = true;
    switch (vibration.vibrationType) {
    case VibrationType::SABLE:
        if (mHaptique->GetSable()){
            mHaptique->GetSable()->Start();
        }
        break;
    case VibrationType::EAU:
        if (mHaptique->GetEau()){
            mHaptique->GetEau()->Start();
        }
        break;
    case VibrationType::VAGUE:
        if (mHaptique->GetVague()){
            mHaptique->GetVague()->Start();
        }

        break;
    case VibrationType::VORTEX:
        if (mHaptique->GetVortex()){
            mHaptique->GetVortex()->Start();
        }

        break;
    case VibrationType::GEANT:
        if (mHaptique->GetGeant()){
            mHaptique->GetGeant()->Start();
        }
        break;

    case VibrationType::BOUCHE:
        if (mHaptique->GetBouche()){
            mHaptique->GetBouche()->Start();
        }
        break;
    }
}

void MainWindow::deactivateEffect(Vibration& vibration)
{

    if (!vibration.isActive)
        return;

    vibration.isActive = false;
    switch (vibration.vibrationType) {
    case VibrationType::SABLE:
        if (mHaptique->GetSable()){
            mHaptique->GetSable()->Stop();
        }
        break;
    case VibrationType::EAU:
        if (mHaptique->GetEau()){
            mHaptique->GetEau()->Stop();
        }
        break;
    case VibrationType::VAGUE:
        if (mHaptique->GetVague()){
            mHaptique->GetVague()->Stop();
        }
        break;
    case VibrationType::VORTEX:
        if (mHaptique->GetVortex()){
            mHaptique->GetVortex()->Stop();
        }
        break;
    case VibrationType::GEANT:
        if (mHaptique->GetGeant()){
            mHaptique->GetGeant()->Stop();
        }
        break;

    case VibrationType::BOUCHE:
        if (mHaptique->GetBouche()){
            mHaptique->GetBouche()->Stop();
        }
        break;
    }
}




void MainWindow::on_bouton_quitter_clicked()
{
    QApplication::quit();
}

void MainWindow::on_butquitter_clicked()
{
    QApplication::quit();
}
