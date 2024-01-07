#include <QApplication>
#include <iostream>
#include "player.h"
#include "gameboard.h"

#define BEST_SIZE_X 475
#define BEST_SIZE_Y 550

int main(int argc, char* argv[]){
	QApplication app(argc, argv);
	Player player;
	Gameboard board;
	board.resize(BEST_SIZE_X,BEST_SIZE_Y);
	board.setFixedSize(board.size());
    board.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	board.show();
	return app.exec();
}
