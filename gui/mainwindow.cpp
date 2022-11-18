#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <iostream>

#include "gui/config.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    // setup ui elements
    ui->setupUi(this);

    // connect ui elements to slots
    connect(this->ui->checkBoxLocalRotation, SIGNAL(clicked(bool)), this, SLOT(setLocalRotation(bool)));
    this->ui->checkBoxLocalRotation->setChecked(Config::localRotationEnable);
    connect(this->ui->checkBoxGlobalRotation, SIGNAL(clicked(bool)), this, SLOT(setGlobalRotation(bool)));
    this->ui->checkBoxGlobalRotation->setChecked(Config::globalRotationEnable);
    connect(this->ui->checkBoxCoorSystem, SIGNAL(clicked(bool)), this, SLOT(setCoorSys(bool)));
    this->ui->checkBoxCoorSystem->setChecked(Config::coordSysEnable);
    connect(this->ui->checkBoxGrid, SIGNAL(clicked(bool)), this, SLOT(setGrid(bool)));
    this->ui->checkBoxGrid->setChecked(Config::gridEnable);
    connect(this->ui->checkBoxLighting, SIGNAL(clicked(bool)), this, SLOT(setLighting(bool)));
    this->ui->checkBoxLighting->setChecked(Config::lightingEnable);
    connect(this->ui->checkBoxShowPaths, SIGNAL(clicked(bool)), this, SLOT(setOrbit(bool)));
    this->ui->checkBoxShowPaths->setChecked(Config::orbitEnable);

    connect(this->ui->sliderAnimationSpeed, SIGNAL(valueChanged(int)), this, SLOT(setAnimationSpeed(int)));
    this->ui->sliderAnimationSpeed->setRange(1, 50);
    this->ui->sliderAnimationSpeed->setTickPosition(QSlider::TicksBothSides);
    this->ui->sliderAnimationSpeed->setTickInterval(10);
    this->ui->sliderAnimationSpeed->setValue(Config::animationSpeed);

    connect(this->ui->checkBoxDeathStarActive, SIGNAL(clicked(bool)), this, SLOT(setDeathStarActive(bool)));
    connect(this->ui->checkBoxDeathStarPreview, SIGNAL(clicked(bool)), this, SLOT(setDeathStarPreview(bool)));
    connect(this->ui->sliderDeathStarLaserLen, SIGNAL(valueChanged(int)), this, SLOT(setDeathStarLaserLen(int)));
    this->ui->sliderDeathStarLaserLen->setRange(1, 20);
    this->ui->sliderDeathStarLaserLen->setTickPosition(QSlider::TicksBothSides);
    this->ui->sliderDeathStarLaserLen->setTickInterval(2);
    connect(this->ui->sliderDeathStarLaserRad, SIGNAL(valueChanged(int)), this, SLOT(setDeathStarLaserRad(int)));
    this->ui->sliderDeathStarLaserRad->setRange(1, 20);
    this->ui->sliderDeathStarLaserRad->setTickPosition(QSlider::TicksBothSides);
    this->ui->sliderDeathStarLaserRad->setTickInterval(2);

    connect(this->ui->checkBoxPathPlanet, SIGNAL(clicked(bool)), this, SLOT(setPathActive(bool)));
    connect(this->ui->selectPathPlanet, SIGNAL(currentIndexChanged(int)), this, SLOT(setPathPlanet(int)));
    this->ui->selectPathPlanet->addItem("Erde", 0);
    this->ui->selectPathPlanet->addItem("Mond", 1);
    this->ui->selectPathPlanet->addItem("Sonne", 2);
    this->ui->selectPathPlanet->addItem("Merkur", 3);
    this->ui->selectPathPlanet->addItem("Venus", 4);
    this->ui->selectPathPlanet->addItem("Mars", 5);
    this->ui->selectPathPlanet->addItem("Jupiter", 6);
    this->ui->selectPathPlanet->addItem("Saturn", 7);
    this->ui->selectPathPlanet->addItem("Io", 8);
    this->ui->selectPathPlanet->addItem("Europa", 9);
    this->ui->selectPathPlanet->addItem("Ganymed", 10);
    this->ui->selectPathPlanet->addItem("Callisto", 11);

    connect(this->ui->spinnerU, SIGNAL(valueChanged(int)), this, SLOT(setResolutionU(int)));
    this->ui->spinnerU->setValue(Config::resolutionU);
    this->ui->spinnerU->setRange(4, 1000);
    connect(this->ui->spinnerV, SIGNAL(valueChanged(int)), this, SLOT(setResolutionV(int)));
    this->ui->spinnerV->setValue(Config::resolutionV);
    this->ui->spinnerV->setRange(2, 1000);
    connect(this->ui->spinnerRing, SIGNAL(valueChanged(int)), this, SLOT(setResolutionRing(int)));
    this->ui->spinnerRing->setValue(Config::resolutionRing);
    this->ui->spinnerRing->setRange(4, 1000);
    connect(this->ui->buttonCamReset, SIGNAL(clicked(bool)), this, SLOT(resetCam()));
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
    Config::animationSpeed = float(value) / 2.0f;
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
    if (value) {
        Config::currentPathPlanet = this->ui->selectPathPlanet->currentText().toStdString();
        return;
    }
    Config::currentPathPlanet = "";
}

void MainWindow::setPathPlanet(int value) {
    this->ui->checkBoxPathPlanet->setCheckState(Qt::Unchecked);
    Config::currentPathPlanet = "";
}

void MainWindow::setResolutionU(int value) {
    Config::resolutionU = value;
}

void MainWindow::setResolutionV(int value) {
    Config::resolutionV = value;
}

void MainWindow::setResolutionRing(int value) {
    Config::resolutionRing = value;
}

void MainWindow::resetCam() {
    Config::viewPoint = glm::vec3(0, 0, 5);
    Config::viewPointCenter = glm::vec3(0, 0, 0);
}

