#include <QApplication>
#include <QFile>
#include <iostream>
#include <QDir>
#include <QTextStream>

#include "gui/glwidget.hpp"
#include "gui/mainwindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // stylesheet
    QFile f(":/style/style.css");
    if (!f.open(QFile::ReadOnly | QFile::Text))
        std::cout << "Could not open file " << ":/style/style.css" << std::endl;
    QTextStream in(&f);
    app.setStyleSheet(in.readAll());

    // set gl format
    GLWidget::setGLFormat();

    // load the main window
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
