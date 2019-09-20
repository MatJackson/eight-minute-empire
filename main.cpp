#include <iostream>
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {

    QApplication EditorApp(argc, argv);
    QPushButton *button = new QPushButton("&Hi this is my QT application lol");
    button->show();

    return EditorApp.exec();
}