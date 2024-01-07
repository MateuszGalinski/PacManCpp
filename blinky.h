#pragma once

#include <QWidget>
#include <QtGui>
#include <iostream>
#include "enemy.h"

class Blinky : public Enemy {
		Q_OBJECT
	
	private:
		int leftUpperX, leftUpperY, height, width;
	public:
		Blinky(QWidget* parent = 0);
		void move(const Player& player);
		bool collidesPlayer(const Player& player);
		void reset();
		int getLeftUpperX() const;
		int getLeftUpperY() const;
	protected:
		void paintEvent(QPaintEvent*);
};

