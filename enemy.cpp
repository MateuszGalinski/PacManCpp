#include <QWidget>
#include <QtGui>
#include <vector>

#include "enemy.h"
#include "constNamespace.h"
//#define TILE_SIZE 8
#define FRIGHT_TIME 5000

using namespace PMConst;

int distance(int x1, int y1, int x2, int y2){
	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

Enemy::Enemy(QWidget* parent) : QWidget(parent){
	QString deadSprite = "DeadPNG.png";
	QString scaredSprite = "ScaredPNG.png";
	currentState = chase;
	ghostFrightTimer = new QTimer();
	connect(ghostFrightTimer, SIGNAL(timeout()), this, SLOT(frightStateOff()));
	sprites.push_back(QPixmap(deadSprite));
	sprites.push_back(QPixmap(scaredSprite));
}

Enemy::moveDirection Enemy::getNextMove(int ghostTileX, int ghostTileY, int targetX, int targetY, moveDirection previousMove) {
    int minDist = std::numeric_limits<int>::max();
    moveDirection newMove = up;

    std::vector<std::pair<moveDirection, std::pair<int, int>>> moves = {
        {up, {0, -1}},
        {down, {0, 1}},
        {left, {-1, 0}},
        {right, {1, 0}}
    };
    
    if (currentState == died){
		targetX = GATE_X;
		targetY = GATE_Y;
	}
    
    if (currentState == fright){
		std::vector<moveDirection> possibleMoves;
		for (const auto& move : moves) {
			if (move.first != previousMove) {
				int newGhostTileX = ghostTileX + move.second.first;
				int newGhostTileY = ghostTileY + move.second.second;

				if (tileMap[newGhostTileY][newGhostTileX] != 3 && tileMap[newGhostTileY][newGhostTileX] != 4) {
					possibleMoves.push_back(move.first);
				}
			}
		}

		return possibleMoves[std::rand() % possibleMoves.size()];
	}

    for (const auto& move : moves) {
        if (move.first != previousMove) {
            int newGhostTileX = ghostTileX + move.second.first;
            int newGhostTileY = ghostTileY + move.second.second;
            int dist = distance(newGhostTileX, newGhostTileY, targetX, targetY);

            if (dist < minDist && tileMap[newGhostTileY][newGhostTileX] != 3 && tileMap[newGhostTileY][newGhostTileX] != 4) {
                minDist = dist;
                newMove = move.first;
            }
        }
    }
	
    return newMove;
}

void Enemy::frightStateOn(){
	ghostFrightTimer -> start(FRIGHT_TIME);
	if(currentState != died){
		currentState = fright;
	}
}

void Enemy::frightStateOff(){
	ghostFrightTimer -> stop();
	if(currentState != died){
		currentState = chase;
	}
}

void Enemy::setDead(){
	currentState = died;
}

bool Enemy::isFrightened(){
	return currentState == fright;
}

bool Enemy::isDead(){
	return currentState == died;
}
