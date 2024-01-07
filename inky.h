#pragma once

#include <QWidget>
#include <QtGui>
#include <iostream>
#include "enemy.h"
#include "blinky.h"

class Inky : public Enemy {
		Q_OBJECT
	
	private:
		int leftUpperX, leftUpperY, height, width;
		std::shared_ptr<Blinky> inkyBlinky;
	public:
		Inky(QWidget* parent = 0);
		void move(const Player& player);
		bool collidesPlayer(const Player& player);
		void reset();
		void setBlinkyPointer(std::shared_ptr<Blinky> _blinky);
	protected:
		void paintEvent(QPaintEvent*);
};

