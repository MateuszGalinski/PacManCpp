#pragma once
#include "pellet.h"

class PowerBall : public Pellet{
		Q_OBJECT
	private:
		bool eaten;
		int tileX, tileY, height, width;
		void paintEvent(QPaintEvent*);
	public:
		PowerBall(QWidget* parent = 0);
		~PowerBall() = default;
		void setXY(int _tileX, int _tileY);
		bool collidesPlayer(const Player& player);
	signals:
		void powerBallEaten();
};
