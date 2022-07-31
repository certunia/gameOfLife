// qt 6.3.1

#include <QApplication>

#include "game.h"

int main(int argc, char *argv[])
{
    int columns = 40;
    int rows = 20;

    QApplication app(argc, argv);

    Game *game = new Game(columns, rows);

    game->show();

    return app.exec();
}
