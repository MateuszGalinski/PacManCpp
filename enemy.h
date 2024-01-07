#pragma once

#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <iostream>
#include "player.h"

class Enemy : public QWidget {
		Q_OBJECT
	public:
		Enemy(QWidget* parent = 0);
		virtual bool collidesPlayer(const Player& player) = 0;
		virtual void reset() = 0;
		enum moveDirection {
			left = 0,
			right = 1,
			up = 2,
			down = 3
		};
		enum state {
			chase,
			fright,
			died
		};
		void setDead();
		bool isFrightened();
		bool isDead();
	protected:
		moveDirection previousMove;
		state currentState;
		QTimer* ghostFrightTimer;
		
		virtual void paintEvent(QPaintEvent*) = 0;
		moveDirection getNextMove(int ghostTileX, int ghostTileY, int targetX, int targetY, moveDirection previousMove);
	public slots:
		virtual void move(const Player& player) = 0;
		void frightStateOn();
		void frightStateOff();
	signals:
		void collidedPlayer(bool scared);

};

