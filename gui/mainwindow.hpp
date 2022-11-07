#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// add to namespace Ui
namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 *
 * This class handles the QMainWindow that is defined
 * in the mainwindow.ui
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow constructor
     * @param parent the parent widget
     */
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui; /**< references all ui elements */

private slots:

    /*
     * Define slots to connect the ui elements with
     */

    // checkbox options
    void setLocalRotation(bool value);
    void setGlobalRotation(bool value);
    void setGrid(bool value);
    void setCoorSys(bool value);
    void setLighting(bool value);
    void setOrbit(bool value);

    // animations
    void setAnimationSpeed(int value);

    // deathStar
   void setDeathStarActive(bool value);
   void setDeathStarPreview(bool value);
   void setDeathStarLaserLen(int value);
   void setDeathStarLaserRad(int value);

   // paths
   void setPathActive(bool value);
   void setPathPlanet(int value);

    // resolution
    void setResolutionU(int value);
    void setResolutionV(int value);
    void setResolutionRing(int value);

    void resetCam();

protected:
    virtual void keyPressEvent(QKeyEvent* event);

};

#endif // MAINWINDOW_H
