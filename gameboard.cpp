#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QPixmap>
#include <vector>
#include <memory>

#include "gameboard.h"
#include "player.h"
#include "blinky.h"
#include "pinky.h"
#include "inky.h"
#include "clyde.h"
#include "constNamespace.h"

using namespace PMConst;

Gameboard::Gameboard(QWidget* parent) : QWidget(parent){
	QString path = "PCMmap.png";
	QPixmap img(path);
	img = img.scaled(img.size()*2);
	
	score = 0;
	scoreToWin = 0;
	scoreLabel = new QLabel();
	scoreLabel -> setText(QString::number(score));
	
	auto blinky = std::make_shared<Blinky>();
	auto inky = std::make_shared<Inky>();
	inky.get() -> setBlinkyPointer(blinky);
	auto pinky = std::make_shared<Pinky>();
	auto clyde = std::make_shared<Clyde>();
	enemyVector.push_back(blinky);
	enemyVector.push_back(pinky);
	enemyVector.push_back(clyde);
	enemyVector.push_back(inky);
	
	for (unsigned int i = 0; i < tileMap.size(); i++){
		for (unsigned int j = 0; j < tileMap[0].size(); j++){
			if(tileMap[i][j] == 1){
				auto newPellet = std::make_unique<Pellet>();
				newPellet -> setXY(j, i);
				connect(newPellet.get(), SIGNAL(increaseScore(int)), this, SLOT(raiseScore(int)));
				pelletVector.push_back(std::move(newPellet));
				scoreToWin += PELLET_SCORE;
			}
			if(tileMap[i][j] == 2){
				auto newPowerBall = std::make_unique<PowerBall>();
				newPowerBall -> setXY(j, i);
				connect(newPowerBall.get(), SIGNAL(increaseScore(int)), this, SLOT(raiseScore(int)));
				
				for(auto& i : enemyVector){
					connect(newPowerBall.get(), SIGNAL(powerBallEaten()), i.get(), SLOT(frightStateOn()));
				}
				pelletVector.push_back(std::move(newPowerBall));
				scoreToWin += POWERBALL_SCORE;
			}
		}
	}
	
	player = new Player;
	
	//////////////////////////////////////////////////////
	
	movementTimer = new QTimer(this);
	connect(movementTimer, SIGNAL(timeout()), this, SLOT(updateGame()));
	connect(player, SIGNAL(gameOver()), this, SLOT(gameOver()));
	movementTimer->start(GAME_TICK);
	
	topLayout = createTopLayout();
	topLayout -> addWidget(scoreLabel);
	wholeLayout = new QVBoxLayout;
	
	QLabel* boardImg = new QLabel();
	boardImg -> setPixmap(img);
	boardImg -> setFixedSize(img.size());
	boardImg->setScaledContents(true);
    boardImg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	
	playingZone = new QStackedLayout;
	playingZone -> setStackingMode(QStackedLayout::StackAll);
	
	playingZone -> addWidget(boardImg);
	for(auto& i : pelletVector){
		playingZone -> addWidget(i.get());
	}
	playingZone -> addWidget(player);
	for(auto& i : enemyVector){
		playingZone -> addWidget(i.get());
	}
	
	wholeLayout -> addLayout(topLayout);
	wholeLayout -> addLayout(playingZone);
	setLayout(wholeLayout);
	player -> setFocus();
}

void Gameboard::updateGame(){
	player -> move();
	
	for(auto& i : pelletVector){
		i.get() -> collidesPlayer(*player);
	}
	
	for(auto& i : enemyVector){
		checkGhostsCollisions();
		i.get() -> move(*player);
		checkGhostsCollisions();
	}
	
	scoreLabel -> setText(QString::number(score));
	if(score >= scoreToWin){
		gameWon();
	}
}

void Gameboard::raiseScore(int value){
	score += value;
}

QHBoxLayout* Gameboard::createTopLayout(){
	QLabel* score = new QLabel(tr("SCORE:"));
	QHBoxLayout* topLayout = new QHBoxLayout;
	topLayout -> addWidget(score);
	
	return topLayout;
}

void Gameboard::reset(){
	for(auto& i : enemyVector){
		i.get() -> reset();	
	}
}

void Gameboard::checkGhostsCollisions(){
	for(auto& i : enemyVector){
		if(i.get() -> collidesPlayer(*player)){
			if(i.get() -> isFrightened()){
				i.get() -> setDead();
			}
			else if (!i.get() -> isDead()){
				player -> loseLife();
				reset();
			}
		}
	}
}


void Gameboard::gameOver(){
	QLabel* empty = new QLabel();
	QLabel* text = new QLabel(tr("You Lost!"));
	wholeLayout -> insertWidget(0, text, 0, Qt::AlignCenter);
	playingZone -> addWidget(empty);
	playingZone -> setCurrentWidget(empty);
	playingZone -> setStackingMode(QStackedLayout::StackOne);
	movementTimer -> stop();
	playingZone -> update();
}

void Gameboard::gameWon(){
	QLabel* empty = new QLabel();
	QLabel* text = new QLabel(tr("You Won!"));
	wholeLayout -> insertWidget(0, text, 0, Qt::AlignCenter);
	playingZone -> addWidget(empty);
	playingZone -> setCurrentWidget(empty);
	playingZone -> setStackingMode(QStackedLayout::StackOne);
	movementTimer -> stop();
	playingZone -> update();
}
