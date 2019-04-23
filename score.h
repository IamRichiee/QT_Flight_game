#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem {
public:
    Score(QGraphicsItem* parent = nullptr);
    void increase();
    int getScore();
    void setScore(int initScore);
    void display();

private:
    int score;
    QString m_score;
};

#endif // SCORE_H
