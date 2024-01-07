#pragma once

#include <QWidget>
#include <QtGui>
#include <iostream>
#include "enemy.h"

class Pinky : public Enemy {
		Q_OBJECT
	
	private:
		int leftUpperX, leftUpperY, height, width;
	public:
		Pinky(QWidget* parent = 0);
		void move(const Player& player);
		bool collidesPlayer(const Player& player);
		void reset();
	protected:
		void paintEvent(QPaintEvent*);
};

