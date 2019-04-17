#include "game.h"
#include "enemy.h"
#include <QBrush>
#include <QFont>
#include <QGraphicsTextItem>
#include <QImage>
#include <QMediaPlayer>
#include <QTimer>

Game::Game(QWidget* parent)
    : handle(nullptr)
    , gameSceneWidth(800)
    , gameSceneHeight(600)
{
    Q_UNUSED(parent);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, gameSceneWidth, gameSceneHeight);
    setBackgroundBrush(QBrush(QImage(":images/bg.png")));

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(gameSceneWidth, gameSceneHeight);

    // create the score/health
    score = new Score();
    health = new Health();
    health->visivle(true);
    scene->addItem(score);
    health->setPos(health->x(), health->y() + 25);
    scene->addItem(health);
    score->setVisible(false);
    health->setVisible(false);

    timer = new QTimer();

    // play background music
}

void Game::displayMainMenu(QString title, QString play)
{
    // Create the title
    titleText = new QGraphicsTextItem(title);
    titleText->setDefaultTextColor(Qt::yellow);
    QFont titleFont("Roboto", 50);
    titleText->setFont(titleFont);
    int xPos = static_cast<int>(
        width() / 2 - titleText->boundingRect().width() / 2);
    int yPos = 150;
    titleText->setPos(xPos, yPos);
    scene->addItem(titleText);

    // create Button
    Button* playButton = new Button(play, titleText);
    playButton->setPos(160, 160);

    QObject::connect(playButton, &Button::clicked,
        this, &Game::start);

    // Create Quit Button
    Button* quitButton = new Button("退出", titleText);
    quitButton->setPos(160, 220);
    connect(quitButton, &Button::clicked,
        this, &QGraphicsView::close);
}

void Game::start()
{
    scene->removeItem(titleText);
    delete titleText;

    // create the player
    player = new Player(handle);

    player->setPos(400, 500);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add the player to the scene
    scene->addItem(player);

    // display score/health
    score->setVisible(true);
    score->setScore(0);
    health->setVisible(true);
    health->setHealth(3);

    // spawn enemies
    QObject::connect(timer, &QTimer::timeout,
        player, &Player::spawn);
    timer->start(2000);
}

void Game::gameOver()
{
    QObject::disconnect(timer, &QTimer::timeout,
        player, &Player::spawn);
    health->setVisible(false);
    displayMainMenu("Game Over!", "新游戏");
    scene->removeItem(player);
    player->die();
}
