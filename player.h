#pragma once

#include <QWidget>
#include <QtGui>
#include <iostream>

class Player : public QWidget {
		Q_OBJECT
	public:
		enum angleDirections {
			left = 0,
			right = 180,
			up = 270,
			down = 90
		};
		Player(QWidget* parent = 0);
		~Player() = default;	
		int getLeftUpperX() const;
		int getLeftUpperY() const;
		angleDirections getDirection() const;
		void move();
		void loseLife();
	private:
		int LeftUpperX, LeftUpperY, mouthMode, numberOfLives;
		const int P_HEIGHT, P_WIDTH;
		angleDirections angle;
	protected:
		void paintEvent(QPaintEvent*);
		void keyPressEvent(QKeyEvent* event);
	signals:
		void lifeLost();
		void gameOver();
};
