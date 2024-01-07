#include <QWidget>
#include <QtGui>
#include <iostream>

#include "powerBall.h"
#include "player.h"
#include "constNamespace.h"
//#define TILE_SIZE 8
#define SCORE_FOR_PELLET 50

using namespace PMConst;

PowerBall::PowerBall(QWidget* parent) : Pellet(parent) {
	height = TILE_SIZE;
	width = TILE_SIZE;	
	eaten = false;
}

void PowerBall::paintEvent(QPaintEvent*){
	QPainter painter(this);

	painter.setPen(Qt::NoPen);
	
	if(eaten){
		painter.setBrush(Qt::black);	
	} else {
		painter.setBrush(Qt::white);
	}
	
	painter.drawEllipse(QRect(tileX * TILE_SIZE, tileY * TILE_SIZE, height, width));
}

bool PowerBall::collidesPlayer(const Player& player){
	if(eaten){
		return false;	
	}
	
	if(player.getLeftUpperX()/TILE_SIZE == tileX && player.getLeftUpperY()/TILE_SIZE == tileY){
		eaten = true;
		emit increaseScore(POWERBALL_SCORE);
		emit powerBallEaten();
		update();
		return true;
	}
	
	return false;
}

void PowerBall::setXY(int _tileX, int _tileY){
	tileX = _tileX;
	tileY = _tileY;
}
