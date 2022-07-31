#ifndef GAME_H
#define GAME_H

#include <QtWidgets>

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(int columns,int rows);

private:
    void autoPlay();
    void createRandomLayout(int colums, int rows);

    int columns = 40;
    int rows = 20;

    QGridLayout *fieldLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *btnsLayout;
    QPushButton *btnNextStep;
    QPushButton *btnNextStepWithoutBorder;

    std::vector <std::vector <QCheckBox*> > field;

private slots:
    void nextStep();
    void nextStepWithoutBorder();
};

#endif // DIALOG_H
