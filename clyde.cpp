#include <QWidget>
#include <QtGui>
#include "clyde.h"
#include "constNamespace.h"
//#include <cstdlib>

#define BODY_ANGLE 280
#define QT_ANG 16
#define MOUTH_ANGLE 360 - BODY_ANGLE
#define CORNER_TILE_X 0
#define CORNER_TILE_Y 30

using namespace PMConst;

int tileDistance(int x1, int y1, int x2, int y2){
	return std::abs((x2 - x1) + (y2 - y1));
}

Clyde::Clyde(QWidget* parent) : Enemy(parent){
	QString fileName = "Clyde.png";
	sprites.push_back(QPixmap(fileName));
	leftUpperX = TILE_SIZE * GATE_X - TILE_SIZE;
    leftUpperY = TILE_SIZE * GATE_Y;
    height = TILE_SIZE;
    width = TILE_SIZE;
    previousMove = down;
}

void Clyde::paintEvent(QPaintEvent*){
	QPainter painter(this);
	painter.drawPixmap(leftUpperX, leftUpperY, width, height, sprites[currentState]);
}

void Clyde::move(const Player& player){
	int playerTileX = player.getLeftUpperX() / TILE_SIZE;
    int playerTileY = player.getLeftUpperY() / TILE_SIZE;
    int ghostTileX = leftUpperX / TILE_SIZE;
    int ghostTileY = leftUpperY / TILE_SIZE;
    moveDirection nextMove;
    
    if(currentState == died){
		nextMove = getNextMove(ghostTileX, ghostTileY, GATE_X, GATE_Y, previousMove);
		if(ghostTileX == GATE_X && ghostTileY == GATE_Y){
			currentState = chase;
			nextMove = left;
		}
	} else{
		if(tileDistance(ghostTileX, ghostTileY, playerTileX, playerTileX) > 8){
			nextMove = getNextMove(ghostTileX, ghostTileY, playerTileX, playerTileY, previousMove);
		} else {
			nextMove = getNextMove(ghostTileX, ghostTileY, CORNER_TILE_X, CORNER_TILE_Y, previousMove);
		}
	}
    
    if (nextMove == down) {
        previousMove = up;
        leftUpperY += TILE_SIZE;
    } else if (nextMove == up) {
        previousMove = down;
        leftUpperY -= TILE_SIZE;
    } else if (nextMove == left) {
        previousMove = right;
        leftUpperX -= TILE_SIZE;
        if(leftUpperX/TILE_SIZE < 0){
			leftUpperX = 27 * TILE_SIZE;
		}
    } else if (nextMove == right) {
        previousMove = left;
        leftUpperX += TILE_SIZE;
        if(leftUpperX/TILE_SIZE > 27){
			leftUpperX = 0;
		}
    }
	
	update();
}

bool Clyde::collidesPlayer(const Player& player){
	if(player.getLeftUpperX()/TILE_SIZE == leftUpperX/TILE_SIZE && player.getLeftUpperY()/TILE_SIZE == leftUpperY/TILE_SIZE){
		update();
		return true;
	}
	
	return false;
}

void Clyde::reset(){
	leftUpperX = TILE_SIZE * GATE_X - TILE_SIZE;
    leftUpperY = TILE_SIZE * GATE_Y;
    previousMove = down;
    currentState = chase;
}
