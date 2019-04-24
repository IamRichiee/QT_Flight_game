#include "game.h"
#include <QApplication>
#include <QIcon>

Game* game;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    game->setWindowTitle("飞机大战");
    game->setWindowIcon(QIcon(":/images/bullet.png"));
    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/Map.wav"));
    music->play();
    game->displayMainMenu("飞机大战", QPixmap(":/button/new.png"), QPixmap(":/button/newHover.png"));

    return a.exec();
}
