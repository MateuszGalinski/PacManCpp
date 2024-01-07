#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPixmap>
#include <QStackedLayout>
#include <QHBoxLayout>
#include <iostream>
#include <vector>

#include "pellet.h"
#include "enemy.h"
#include "powerBall.h"
#include "blinky.h"

class Gameboard : public QWidget {
		Q_OBJECT
		
	private:
		QHBoxLayout* createTopLayout();
		Player* player;
		QTimer* movementTimer;
		QLabel* scoreLabel;
		QVBoxLayout* wholeLayout;
		QHBoxLayout* topLayout;
		QStackedLayout* playingZone;
		std::vector<std::unique_ptr<Pellet>> pelletVector = {};	
		std::vector<std::shared_ptr<Enemy>> enemyVector = {};
		int scoreToWin;
		int score;
		void checkGhostsCollisions();
		void reset();
		void gameWon();
	public:
		Gameboard(QWidget* parent = 0);
		~Gameboard() = default;	
	public slots:
		void updateGame();
		void raiseScore(int value);
		void gameOver();
};
