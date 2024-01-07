#include <QWidget>
#include <QtGui>
#include <vector>

#include "player.h"
#include "constNamespace.h"
#define BODY_ANGLE 260
#define QT_ANG 16
#define MOUTH_ANGLE 360 - BODY_ANGLE
// #define TILE_SIZE 8

using namespace PMConst;

Player::Player(QWidget* parent) : QWidget(parent), P_HEIGHT(TILE_SIZE), P_WIDTH(TILE_SIZE){
	
	LeftUpperX = TILE_SIZE * PLAYER_START_X;
    LeftUpperY = TILE_SIZE * PLAYER_START_Y;
    mouthMode = 0;
	numberOfLives = 3;
	
	angle = up;
}

int Player::getLeftUpperX() const{
	return LeftUpperX;
}

int Player::getLeftUpperY() const{
	return LeftUpperY;
}

Player::angleDirections Player::getDirection() const{
	return angle;
}

void Player::paintEvent(QPaintEvent*){
	QPainter painter(this);

	painter.setPen(Qt::NoPen);
	
	painter.setBrush(Qt::yellow);
	painter.drawPie(LeftUpperX, LeftUpperY, P_WIDTH, P_HEIGHT, (angle - MOUTH_ANGLE/2) * QT_ANG, (BODY_ANGLE + mouthMode * int(MOUTH_ANGLE/8)) * QT_ANG);
}

void Player::keyPressEvent(QKeyEvent* event){
	int TilesY = LeftUpperY / TILE_SIZE;
	int TilesX = LeftUpperX / TILE_SIZE;
	
	if(event -> key() == Qt::Key_W){
		if(tileMap[TilesY - 1][TilesX] == 3){
			return;
		}
		angle = up;
	}
	else if(event -> key() == Qt::Key_S){
		if(tileMap[TilesY + 1][TilesX] == 3){
			return;
		}
		angle = down;
	}
	else if(event -> key() == Qt::Key_D){
		if(tileMap[TilesY][TilesX + 1] == 3){
			return;
		}
		angle = right;
	}
	else if(event -> key() == Qt::Key_A){
		if(tileMap[TilesY][TilesX - 1] == 3){
			return;
		}
		angle = left;
	}
	
	update();
}


void Player::move(){
	int TilesY = LeftUpperY / TILE_SIZE;
	int TilesX = LeftUpperX / TILE_SIZE;
	
	if(mouthMode >= 1){
		mouthMode = 0;
	} else {
		mouthMode += 1;
	}
	
	if(angle == up){
		if(tileMap[TilesY - 1][TilesX] == 3){
			return;
		}
		LeftUpperY -= TILE_SIZE;
	}
	else if(angle == down){
		if(tileMap[TilesY + 1][TilesX] == 3){
			return;
		}
		LeftUpperY += TILE_SIZE;
	}
	else if(angle == right){
		if(tileMap[TilesY][TilesX + 1] == 3){
			return;
		}
		LeftUpperX += TILE_SIZE;
		
		if(LeftUpperX/TILE_SIZE > 27){
			LeftUpperX = 0;
		}
	}
	else if(angle == left){
		if(tileMap[TilesY][TilesX - 1] == 3){
			return;
		}
		
		LeftUpperX -= TILE_SIZE;
		
		if(LeftUpperX/TILE_SIZE < 0){
			LeftUpperX = 27 * TILE_SIZE;
		}
	}
	
	update();
}

void Player::loseLife(){
	numberOfLives -= 1;
	if (numberOfLives <= 0){
		emit gameOver();
	} else {
		LeftUpperX = PLAYER_START_X * TILE_SIZE;
		LeftUpperY = PLAYER_START_Y * TILE_SIZE;
	}
}
