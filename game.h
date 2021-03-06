#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "explosion.h"
#include "health.h"
#include "player.h"
#include "score.h"
#include "supply.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

class Game : public QGraphicsView {
public:
    Game(QWidget* parent = nullptr);
    void displayMainMenu(QString title, QPixmap icon, QPixmap hoverIcon);
    void gameOver();
    void generateSupply();
    void addSupply(Supply* supply);

    QGraphicsScene* scene;
    QGraphicsItem* handle;
    Player* player;
    Score* score;
    Health* health;
    QList<Supply*> supplies;
    int gameSceneWidth;
    int gameSceneHeight;
    QMediaPlayer* backgroundMusic;
    QSound* gameOverSound;
    Explosion* ex;

private:
    QGraphicsTextItem* titleText;
    QTimer* timer;
    QTimer* suppliesTimer;
    Button* playButton;
    Button* quitButton;

    void setBackgroundImage(QImage image);

public slots:
    void start();
};

extern Game* game;

#endif // GAME_H
