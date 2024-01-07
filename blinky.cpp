#include <QWidget>
#include <QtGui>
#include "blinky.h"
#include "constNamespace.h"

#define BODY_ANGLE 280
#define QT_ANG 16
#define MOUTH_ANGLE 360 - BODY_ANGLE
//#define TILE_SIZE 8

using namespace PMConst;

Blinky::Blinky(QWidget* parent) : Enemy(parent){
	leftUpperX = TILE_SIZE * GATE_X;
    leftUpperY = TILE_SIZE * GATE_Y;
    height = TILE_SIZE;
    width = TILE_SIZE;
    previousMove = down;
}

void Blinky::paintEvent(QPaintEvent*){
	QPainter painter(this);

	painter.setPen(Qt::NoPen);
	
	if(currentState == fright){
		painter.setBrush(Qt::white);
	} else if(currentState == chase) {
		painter.setBrush(Qt::red);
	} else{
		painter.setBrush(Qt::green);
	}
	painter.drawPie(leftUpperX, leftUpperY, width, height, MOUTH_ANGLE/2 * QT_ANG, BODY_ANGLE * QT_ANG);
}

void Blinky::move(const Player& player){
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
		nextMove = getNextMove(ghostTileX, ghostTileY, playerTileX, playerTileY, previousMove);
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

bool Blinky::collidesPlayer(const Player& player){
	if(player.getLeftUpperX()/TILE_SIZE == leftUpperX/TILE_SIZE && player.getLeftUpperY()/TILE_SIZE == leftUpperY/TILE_SIZE){
		update();
		return true;
	}
	
	return false;
}

void Blinky::reset(){
	leftUpperX = TILE_SIZE * GATE_X;
    leftUpperY = TILE_SIZE * GATE_Y;
    previousMove = down;
    currentState = chase;
}

int Blinky::getLeftUpperX() const{
	return leftUpperX;
}

int Blinky::getLeftUpperY() const{
	return leftUpperY;
}
