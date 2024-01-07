#include <QWidget>
#include <QtGui>
#include "pinky.h"
#include "constNamespace.h"

#define BODY_ANGLE 280
#define QT_ANG 16
#define MOUTH_ANGLE 360 - BODY_ANGLE
#define TILES_AHEAD 4

using namespace PMConst;

Pinky::Pinky(QWidget* parent) : Enemy(parent){
	leftUpperX = TILE_SIZE * GATE_X + TILE_SIZE;
    leftUpperY = TILE_SIZE * GATE_Y;
    height = TILE_SIZE;
    width = TILE_SIZE;
    previousMove = left;
}

void Pinky::paintEvent(QPaintEvent*){
	QPainter painter(this);

	painter.setPen(Qt::NoPen);
	
	if(Enemy::currentState == Enemy::fright){
		painter.setBrush(Qt::white);
	} else if (currentState == chase){
		painter.setBrush(Qt::magenta);
	} else{
		painter.setBrush(Qt::green);
	}
	
	painter.drawPie(leftUpperX, leftUpperY, width, height, MOUTH_ANGLE/2 * QT_ANG, BODY_ANGLE * QT_ANG);
}

void Pinky::move(const Player& player){
	int targetTileX = 0, targetTileY = 0;
	int playerTileX = player.getLeftUpperX() / TILE_SIZE;
    int playerTileY = player.getLeftUpperY() / TILE_SIZE;
    Player::angleDirections currentPlayerDirection = player.getDirection();
    int ghostTileX = leftUpperX / TILE_SIZE;
    int ghostTileY = leftUpperY / TILE_SIZE;
    moveDirection nextMove;
    
    switch(currentPlayerDirection){
		case Player::up:
			targetTileX = playerTileX;
			targetTileY = playerTileY - TILES_AHEAD;
			break;
		case Player::down:
			targetTileX = playerTileX;
			targetTileY = playerTileY + TILES_AHEAD;
			break;
		case Player::left:
			targetTileX = playerTileX - TILES_AHEAD;
			targetTileY = playerTileY;
			break;
		case Player::right:
			targetTileX = playerTileX + TILES_AHEAD;
			targetTileY = playerTileY;
			break;
	}
    
    if(currentState == died){
		nextMove = getNextMove(ghostTileX, ghostTileY, GATE_X, GATE_Y, previousMove);
		if(ghostTileX == GATE_X && ghostTileY == GATE_Y){
			currentState = chase;
			nextMove = left;
		}
	} else {
		nextMove = getNextMove(ghostTileX, ghostTileY, targetTileX, targetTileY, previousMove);
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

bool Pinky::collidesPlayer(const Player& player){
	if(player.getLeftUpperX()/TILE_SIZE == leftUpperX/TILE_SIZE && player.getLeftUpperY()/TILE_SIZE == leftUpperY/TILE_SIZE){
		update();
		return true;
	}
	
	return false;
}

void Pinky::reset(){
	leftUpperX = TILE_SIZE * GATE_X + TILE_SIZE;
    leftUpperY = TILE_SIZE * GATE_Y;
    previousMove = left;
    currentState = chase;
}
