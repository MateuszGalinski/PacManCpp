#include <QWidget>
#include <QtGui>
#include <iostream>

#include "pellet.h"
#include "player.h"
#include "constNamespace.h"
//#define TILE_SIZE 8

using namespace PMConst;

Pellet::Pellet(QWidget* parent) : QWidget(parent) {
	height = TILE_SIZE/2;
	width = TILE_SIZE/2;	
	eaten = false;
}

void Pellet::setXY(int _tileX, int _tileY){
	tileX = _tileX;
	tileY = _tileY;
}

void Pellet::paintEvent(QPaintEvent*){
	QPainter painter(this);

	painter.setPen(Qt::NoPen);
	
	if(eaten){
		painter.setBrush(Qt::black);	
	} else {
		painter.setBrush(Qt::white);
	}
	
	painter.drawEllipse(QRect(tileX * TILE_SIZE + TILE_SIZE/4, tileY * TILE_SIZE + TILE_SIZE/4, height, width));
}

bool Pellet::collidesPlayer(const Player& player){
	if(eaten){
		return false;	
	}
	
	if(player.getLeftUpperX()/TILE_SIZE == tileX && player.getLeftUpperY()/TILE_SIZE == tileY){
		eaten = true;
		emit increaseScore(PELLET_SCORE);
		update();
		return true;
	}
	
	return false;
}
