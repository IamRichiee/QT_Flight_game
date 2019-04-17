#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "health.h"
#include "player.h"
#include "score.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

class Game : public QGraphicsView {
public:
    Game(QWidget* parent = nullptr);
    void displayMainMenu(QString title, QString play);
    void gameOver();

    QGraphicsScene* scene;
    Player* player;
    Score* score;
    Health* health;
    int gameSceneWidth;
    int gameSceneHeight;

private:
    QGraphicsTextItem* titleText;
    QTimer* timer;
    QGraphicsItem* handle;

public slots:
    void start();
};

extern Game* game;

#endif // GAME_H
