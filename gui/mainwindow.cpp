#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <iostream>

#include "gui/config.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    // setup ui elements
    ui->setupUi(this);

    // connect ui elements to slots
    connect(this->ui->checkBoxLocalRotation, SIGNAL(clicked(bool)), this, SLOT(setLocalRotation(bool)));
    connect(this->ui->checkBoxGlobalRotation, SIGNAL(clicked(bool)), this, SLOT(setGlobalRotation(bool)));
    connect(this->ui->checkBoxCoorSystem, SIGNAL(clicked(bool)), this, SLOT(setCoorSys(bool)));
    connect(this->ui->checkBoxGrid, SIGNAL(clicked(bool)), this, SLOT(setGrid(bool)));
    connect(this->ui->checkBoxLighting, SIGNAL(clicked(bool)), this, SLOT(setLighting(bool)));
    connect(this->ui->checkBoxShowPaths, SIGNAL(clicked(bool)), this, SLOT(setOrbit(bool)));

    connect(this->ui->sliderAnimationSpeed, SIGNAL(valueChanged(int)), this, SLOT(setAnimationSpeed(int)));

    connect(this->ui->checkBoxDeathStarActive, SIGNAL(clicked(bool)),this, SLOT(setDeathStarActive(bool)));
    connect(this->ui->checkBoxDeathStarPreview, SIGNAL(clicked(bool)),this, SLOT(setDeathStarPreview(bool)));
    connect(this->ui->sliderDeathStarLaserLen, SIGNAL(valueChanged(int)),this, SLOT(setDeathStarLaserLen(int)));
    connect(this->ui->sliderDeathStarLaserRad, SIGNAL(valueChanged(int)),this, SLOT(setDeathStarLaserRad(int)));

    connect(this->ui->checkBoxPathPlanet, SIGNAL(clicked(bool)),this, SLOT(setPathActive(bool)));
    connect(this->ui->selectPathPlanet, SIGNAL(currentIndexChanged(int)),this, SLOT(setPathPlanet(int)));
    this->ui->selectPathPlanet->addItem("earth",0);
    this->ui->selectPathPlanet->addItem("moon",1);
    this->ui->selectPathPlanet->addItem("sun",2);
    this->ui->selectPathPlanet->addItem("mercury",3);
    this->ui->selectPathPlanet->addItem("venus",4);
    this->ui->selectPathPlanet->addItem("mars",5);
    this->ui->selectPathPlanet->addItem("jupiter",6);
    this->ui->selectPathPlanet->addItem("saturn",7);
    this->ui->selectPathPlanet->addItem("io",8);
    this->ui->selectPathPlanet->addItem("europa",9);
    this->ui->selectPathPlanet->addItem("ganymede",10);
    this->ui->selectPathPlanet->addItem("callisto",11);

    connect(this->ui->spinnerU, SIGNAL(valueChanged(int)),this, SLOT(setResolutionU(int)));
    connect(this->ui->spinnerV, SIGNAL(valueChanged(int)), this, SLOT(setResolutionV(int)));
    connect(this->ui->spinnerRing, SIGNAL(valueChanged(int)), this, SLOT(setResolutionRing(int)));
}

MainWindow::~MainWindow() {
    delete ui;
}


/* Qt mouse and keyboard events */

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // enable control via keyboard
    switch (event->key()) {
        case Qt::Key_F:
            if (isFullScreen()) {
                showNormal();
            } else {
                showFullScreen();
            }
            break;
        case Qt::Key_Escape:
        case Qt::Key_Q:
            close();
            break;
    }
}


void MainWindow::setLocalRotation(bool value) {
    Config::localRotationEnable = value;
}

void MainWindow::setGlobalRotation(bool value) {
    return;
}

void MainWindow::setGrid(bool value) {

    return;
}

void MainWindow::setCoorSys(bool value) {

    return;
}

void MainWindow::setLighting(bool value) {

    return;
}

void MainWindow::setOrbit(bool value) {

    return;
}

void MainWindow::setAnimationSpeed(int value) {
    Config::animationSpeed = float(value) / 2.0f;
    QString title = QString("Animation: ") + QString::number(Config::animationSpeed, 'x', 1) + "x";
    this->ui->animationBox->setTitle(title);
}

void MainWindow::setDeathStarActive(bool value) {
    return;
}

void MainWindow::setDeathStarPreview(bool value) {
    return;
}

void MainWindow::setDeathStarLaserLen(int value) {

    return;
}

void MainWindow::setDeathStarLaserRad(int value) {

    return;
}

void MainWindow::setPathActive(bool value) {

    return;
}

void MainWindow::setPathPlanet(int value) {
    return;
}

void MainWindow::setResolutionU(int value) {
    return;
}

void MainWindow::setResolutionV(int value) {
    return;

}

void MainWindow::setResolutionRing(int value) {
    return;

}

