#include <QWidget>
#include <QtGui>
#include "inky.h"
#include "constNamespace.h"

#define BODY_ANGLE 280
#define QT_ANG 16
#define MOUTH_ANGLE 360 - BODY_ANGLE
#define TILES_AHEAD 2

using namespace PMConst;

Inky::Inky(QWidget* parent) : Enemy(parent){
    leftUpperX = TILE_SIZE * GATE_X;
    leftUpperY = TILE_SIZE * GATE_Y + TILE_SIZE;
    height = TILE_SIZE;
    width = TILE_SIZE;
    previousMove = down;
}

void Inky::paintEvent(QPaintEvent*){
	QPainter painter(this);

	painter.setPen(Qt::NoPen);
	
	if(currentState == fright){
		painter.setBrush(Qt::white);
	} else if(currentState == chase) {
		painter.setBrush(QColorConstants::Svg::turquoise);
	} else{
		painter.setBrush(Qt::green);
	}
	painter.drawPie(leftUpperX, leftUpperY, width, height, MOUTH_ANGLE/2 * QT_ANG, BODY_ANGLE * QT_ANG);
}

void Inky::move(const Player& player){
	int playerTileX = player.getLeftUpperX() / TILE_SIZE;
    int playerTileY = player.getLeftUpperY() / TILE_SIZE;
    int blinkyTileX = inkyBlinky.get() -> getLeftUpperX() / TILE_SIZE;
    int blinkyTileY = inkyBlinky.get() -> getLeftUpperY() / TILE_SIZE;
    int ghostTileX = leftUpperX / TILE_SIZE;
    int ghostTileY = leftUpperY / TILE_SIZE;
    moveDirection nextMove;
    
    int targetX = playerTileX - (blinkyTileX - playerTileX);
    int targetY = playerTileY + TILES_AHEAD - (blinkyTileY - playerTileY);
    
    if(currentState == died){
		nextMove = getNextMove(ghostTileX, ghostTileY, GATE_X, GATE_Y, previousMove);
		if(ghostTileX == GATE_X && ghostTileY == GATE_Y){
			currentState = chase;
			nextMove = left;
		}
	} else{
		nextMove = getNextMove(ghostTileX, ghostTileY, targetX, targetY, previousMove);
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

bool Inky::collidesPlayer(const Player& player){
	if(player.getLeftUpperX()/TILE_SIZE == leftUpperX/TILE_SIZE && player.getLeftUpperY()/TILE_SIZE == leftUpperY/TILE_SIZE){
		update();
		return true;
	}
	
	return false;
}

void Inky::reset(){
	leftUpperX = TILE_SIZE * GATE_X;
    leftUpperY = TILE_SIZE * GATE_Y + TILE_SIZE;
    previousMove = down;
    currentState = chase;
}

void Inky::setBlinkyPointer(std::shared_ptr<Blinky> _blinky){
	inkyBlinky = _blinky;
}
