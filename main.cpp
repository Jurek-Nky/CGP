#include <QApplication>
#include <QFile>
#include <iostream>
#include <QDir>

#include "gui/glwidget.hpp"
#include "gui/mainwindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // stylesheet
    QFile file("./style/style.css");
    file.open(QFile::ReadOnly);
    if (file.exists()) {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
    } else {
        std::cerr << "stylesheet not found." << std::endl;
    }

    // set gl format
    GLWidget::setGLFormat();

    // load the main window
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
