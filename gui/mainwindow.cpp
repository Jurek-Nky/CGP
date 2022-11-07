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
    this->ui->sliderAnimationSpeed->setRange(1,100);
    this->ui->sliderAnimationSpeed->setTickPosition(QSlider::TicksBothSides);
    this->ui->sliderAnimationSpeed->setTickInterval(10);

    connect(this->ui->checkBoxDeathStarActive, SIGNAL(clicked(bool)),this, SLOT(setDeathStarActive(bool)));
    connect(this->ui->checkBoxDeathStarPreview, SIGNAL(clicked(bool)),this, SLOT(setDeathStarPreview(bool)));
    connect(this->ui->sliderDeathStarLaserLen, SIGNAL(valueChanged(int)),this, SLOT(setDeathStarLaserLen(int)));
    this->ui->sliderDeathStarLaserLen->setRange(1,20);
    this->ui->sliderDeathStarLaserLen->setTickPosition(QSlider::TicksBothSides);
    this->ui->sliderDeathStarLaserLen->setTickInterval(2);
    connect(this->ui->sliderDeathStarLaserRad, SIGNAL(valueChanged(int)),this, SLOT(setDeathStarLaserRad(int)));
    this->ui->sliderDeathStarLaserRad->setRange(1,20);
    this->ui->sliderDeathStarLaserRad->setTickPosition(QSlider::TicksBothSides);
    this->ui->sliderDeathStarLaserRad->setTickInterval(2);

    connect(this->ui->checkBoxPathPlanet, SIGNAL(clicked(bool)),this, SLOT(setPathActive(bool)));
    connect(this->ui->selectPathPlanet, SIGNAL(highlighted(int)),this, SLOT(setPathPlanet(int)));
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
   Config::globalRotationEnable = value;
}

void MainWindow::setGrid(bool value) {
    Config::gridEnable = value;
}

void MainWindow::setCoorSys(bool value) {
    Config::coordSysEnable = value;
}

void MainWindow::setLighting(bool value) {
    Config::lightingEnable = value;
}

void MainWindow::setOrbit(bool value) {
    Config::orbitEnable = value;
}

void MainWindow::setAnimationSpeed(int value) {
    Config::animationSpeed = float(value);
    QString title = QString("Animation: ") + QString::number(Config::animationSpeed, 'x', 1) + "x";
    this->ui->animationBox->setTitle(title);
}

void MainWindow::setDeathStarActive(bool value) {
    Config::deathStarActive = value;
}

void MainWindow::setDeathStarPreview(bool value) {
    Config::deathStarPreviewEnable = value;
}

void MainWindow::setDeathStarLaserLen(int value) {
    Config::deathStarLaserLen = float(value);
}

void MainWindow::setDeathStarLaserRad(int value) {
    Config::deathStarLaserRad = float(value);
}

void MainWindow::setPathActive(bool value) {
    int planetIndex = this->ui->selectPathPlanet->currentIndex();
    Config::planetPathEnable[planetIndex] = value;
}

void MainWindow::setPathPlanet(int value) {
    if (Config::planetPathEnable[value]){
        this->ui->checkBoxPathPlanet->setCheckState(Qt::Checked);
        return;
    }
    this->ui->checkBoxPathPlanet->setCheckState(Qt::Unchecked);
}

void MainWindow::setResolutionU(int value) {
    Config::resolutionU = float(value);
}

void MainWindow::setResolutionV(int value) {
    Config::resolutionV = float(value);
}

void MainWindow::setResolutionRing(int value) {
    Config::resolutionRing = float(value);
}

