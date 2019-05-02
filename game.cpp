#include "game.h"
#include "enemy.h"
#include "supply.h"
#include <QBrush>
#include <QElapsedTimer>
#include <QFont>
#include <QGraphicsTextItem>
#include <QImage>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>

Game::Game(QWidget* parent)
    : gameSceneWidth(800)
    , gameSceneHeight(600)
{
    Q_UNUSED(parent)

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, gameSceneWidth, gameSceneHeight);

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
    suppliesTimer = new QTimer();

    // set music
    QMediaPlaylist* backgroundMusicList = new QMediaPlaylist();
    backgroundMusicList->addMedia(QUrl("qrc:/sounds/Map.wav"));
    backgroundMusicList->setCurrentIndex(1);
    backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    backgroundMusic = new QMediaPlayer;
    backgroundMusic->setPlaylist(backgroundMusicList);
    // play background
    backgroundMusic->play();

    gameOverSound = new QSound(":/sounds/game_over.wav", this);
}

void Game::displayMainMenu(QString title, QPixmap icon, QPixmap hoverIcon)
{
    setBackgroundImage(QImage(":/images/menubg.png"));

    // Create the title
    titleText = new QGraphicsTextItem(title);
    titleText->setDefaultTextColor(Qt::yellow);
    QFont titleFont("Roboto", 50);
    titleText->setFont(titleFont);
    auto xPos = width() / 2 - titleText->boundingRect().width() / 2;
    auto yPos = 150;
    titleText->setPos(xPos, yPos);
    scene->addItem(titleText);

    // create Button
    playButton = new Button(icon, hoverIcon, titleText);
    xPos = (width() - playButton->boundingRect().width()) / 2;
    yPos = 300;
    playButton->setPos(xPos, yPos);
    scene->addItem(playButton);

    connect(playButton, &Button::clicked,
        this, &Game::start);

    // Create Quit Button
    quitButton = new Button(QPixmap(":/button/quit.png"), QPixmap(":/button/quitHover.png"), titleText);
    xPos = (width() - quitButton->boundingRect().width()) / 2;
    yPos = 350;
    quitButton->setPos(xPos, yPos);
    scene->addItem(quitButton);
    connect(quitButton, &Button::clicked,
        this, &QGraphicsView::close);
}

void Game::start()
{
    scene->removeItem(titleText);
    scene->removeItem(playButton);
    scene->removeItem(quitButton);
    delete titleText;
    handle = new QGraphicsSimpleTextItem();
    ex = new Explosion();
    scene->addItem(ex);

    setBackgroundImage(QImage(":images/bg.png"));

    // create the player
    player = new Player(handle);
    player->setOffset(-player->boundingRect().width() / 2, 0);

    player->setPos(gameSceneWidth / 2, 500);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add the player to the scene
    scene->addItem(player);

    // display score/health
    score->setVisible(true);
    score->setScore(0);
    score->display();
    health->setVisible(true);
    health->setHealth(3);

    // spawn enemies
    connect(timer, &QTimer::timeout,
        player, &Player::spawn);
    timer->start(2000);

    // generate supplies
    connect(suppliesTimer, &QTimer::timeout,
        this, &Game::generateSupply);
    suppliesTimer->start(2000);
}

void Game::gameOver()
{
    gameOverSound->play();
    disconnect(timer, &QTimer::timeout,
        player, &Player::spawn);
    disconnect(suppliesTimer, &QTimer::timeout,
        this, &Game::generateSupply);
    delete handle;
    for (Supply* item : supplies) {
        if (item) {
            delete item;
        }
    }
    health->setVisible(false);
    qDebug() << "game over";
    QElapsedTimer t;
    t.start();
    while (t.elapsed() < 500) {
    }
    displayMainMenu("Game Over!!", QPixmap(":/button/new.png"), QPixmap(":/button/newHover.png"));
    scene->removeItem(player);
    player->die();
}

void Game::generateSupply()
{
    Supply* supply = new Supply(handle);
    supply->setPixmap(QPixmap(":/images/supply.png"));
    supply->setPos(gameSceneWidth / 2, gameSceneHeight / 2);
    supplies.append(supply);
    scene->addItem(supply);
}

void Game::addSupply(Supply* supply)
{
    if (typeid(*(supply)) == typeid(Supply)) {
        health->increase();
        supplies.removeOne(supply);
    }
}

void Game::setBackgroundImage(QImage image)
{
    setBackgroundBrush(QBrush(image));
}
