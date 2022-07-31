#include <QtWidgets>

#include <iostream>
#include <random>

#include "game.h"

Game::Game(int columns, int rows) {
    fieldLayout = new QGridLayout();
    mainLayout = new QVBoxLayout(this); // 'this' means we pass it to main window
    btnsLayout = new QHBoxLayout();
    btnNextStep = new QPushButton("Next step");
    btnNextStepWithoutBorder = new QPushButton("Next step without border");

    field.resize(columns, std::vector<QCheckBox *>(rows));
    createRandomLayout(columns, rows);

    QObject::connect(btnNextStep, SIGNAL(clicked()), this,SLOT(nextStep()));
    QObject::connect(btnNextStepWithoutBorder, SIGNAL(clicked()), this,SLOT(nextStepWithoutBorder()));

    fieldLayout->setContentsMargins(5, 5, 5, 5);
    btnsLayout->addWidget(btnNextStep);
    btnsLayout->addWidget(btnNextStepWithoutBorder);
    mainLayout->addLayout(fieldLayout);
    mainLayout->addLayout(btnsLayout);
}

void Game::createRandomLayout(int columns, int rows) {
    float temp;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 10.0);

    for(int i=0 ; i<columns ; i++){
        for(int j=0 ; j<rows; j++){
            field[i][j] = new QCheckBox();
            fieldLayout->addWidget(field[i][j], j, i);

            temp = dist(mt);
            if (temp > 5.0) {
                field[i][j]->setChecked(true);
            }
            else {
                field[i][j]->setChecked(false);
            }
        }
    }
}

void Game::nextStepWithoutBorder() {
    int columns = field.size();
    int rows = field[0].size();
    int newField[columns][rows];
    int neighbours = 0;

    for(int i=0 ; i<columns ; i++){
        for(int j=0 ; j<rows; j++){
            if (i > 0 && j > 0 && i < columns-1 && j < rows-1) {
                if (field[i-1][j]->checkState()) {
                    neighbours += 1;
                }
                if (field[i+1][j]->checkState()) {
                    neighbours += 1;
                }
                if (field[i][j-1]->checkState()) {
                    neighbours += 1;
                }
                if (field[i][j+1]->checkState()) {
                    neighbours += 1;
                }
                if (field[i+1][j+1]->checkState()) {
                    neighbours += 1;
                }
                if (field[i-1][j-1]->checkState()) {
                    neighbours += 1;
                }
                if (field[i+1][j-1]->checkState()) {
                    neighbours += 1;
                }
                if (field[i-1][j+1]->checkState()) {
                    neighbours += 1;
                }

                newField[i][j] = neighbours;
                neighbours = 0;
            }
        }
    }

    for(int i=0 ; i<columns ; i++){
        for(int j=0 ; j<rows; j++){
            if (i > 0 && j > 0 && i < columns-1 && j < rows-1) {
                if (newField[i][j] == 3) {
                    field[i][j]->setChecked(true);
                }
                else if (newField[i][j] == 2 && field[i][j]->checkState()) {
                    field[i][j]->setChecked(true);
                }
                else {
                    field[i][j]->setChecked(false);
                }
            }
        }
    }
}

void Game::nextStep() {
    int columns = field.size();
    int rows = field[0].size();
    int newField[columns][rows];
    int neighbours = 0;

    for(int i=0 ; i<columns ; i++){
        for(int j=0 ; j<rows; j++){
            // left
            if (i > 0 && field[i-1][j]->checkState()) {
                neighbours += 1;
            }
            // right
            if (i < columns-1 && field[i+1][j]->checkState()) {
                neighbours += 1;
            }
            // top
            if (j > 0 && field[i][j-1]->checkState()) {
                neighbours += 1;
            }
            // bottom
            if (j < rows-1 && field[i][j+1]->checkState()) {
                neighbours += 1;
            }
            // right bottom
            if (i < columns-1 && j < rows-1 && field[i+1][j+1]->checkState()) {
                neighbours += 1;
            }
            // top left
            if (j > 0 && i > 0 && field[i-1][j-1]->checkState()) {
                neighbours += 1;
            }
            // right top
            if (i < columns-1 && j > 0 && field[i+1][j-1]->checkState()) {
                neighbours += 1;
            }
            // left bottom
            if (i > 0 && j < rows-1 && field[i-1][j+1]->checkState()) {
                neighbours += 1;
            }

            newField[i][j] = neighbours;
            neighbours = 0;
        }
    }

    for(int i=0 ; i<columns ; i++){
        for(int j=0 ; j<rows; j++){
            if (newField[i][j] == 3) {
                field[i][j]->setChecked(true);
            }
            else if (newField[i][j] == 2 && field[i][j]->checkState()) {
                field[i][j]->setChecked(true);
            }
            else {
                field[i][j]->setChecked(false);
            }
        }
    }
}
