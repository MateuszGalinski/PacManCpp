#pragma once
#include <QWidget>
#include "player.h"

class Pellet : public QWidget{
		Q_OBJECT
	signals:
		void increaseScore(int value);
	private:
		bool eaten;
		int tileX, tileY, height, width;
		virtual void paintEvent(QPaintEvent*);
	public:
		Pellet(QWidget* parent = 0);
		~Pellet() = default;
		void setXY(int _tileX, int _tileY);
		virtual bool collidesPlayer(const Player& player);
};
