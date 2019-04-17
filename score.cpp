#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem* parent)
    : QGraphicsTextItem(parent)
    , score(0)
{
    // draw the text
    display();
    setDefaultTextColor(Qt::green);
    setFont(QFont("Roboto", 18));
    setPos(0, 0);
}

void Score::increase()
{
    score++;
    display();
}

int Score::getScore()
{
    return score;
}

void Score::setScore(int initScore)
{
    this->score = initScore;
}

void Score::display()
{
    setPlainText(QString("Score: ") + QString::number(score));
}
