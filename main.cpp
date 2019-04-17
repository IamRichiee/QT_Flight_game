#include "game.h"
#include <QApplication>
#include <QIcon>

Game* game;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    game->setWindowTitle("air plane");
    game->setWindowIcon(QIcon(":/images/bullet.png"));
    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/Map.wav"));
    music->play();
    game->displayMainMenu("飞机", "开始");

    return a.exec();
}
