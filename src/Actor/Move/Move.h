#pragma once
#include "../Game.h"
#include "../../Easing/Easing.h"
#include "../Field.h"


class Field;

class Move {
public:
	Move();
	virtual void move() = 0;
	virtual void init() = 0;

	bool OutOfMap(KeyCode key);
	bool isWall(KeyCode key);
	bool checkMove(int keyFlag);
	Math::Vec blockPos;		//�}�X�P�ʂ̍��W
	Math::Vec pos;			//�s�N�Z���P�ʂ̍��W
	Math::Vec est;
	Easing easex, easey;

	std::shared_ptr<Field> field;
	bool moving;
};

class InputMove : public Move {
public:
	void move() override;
	void init() override;
};

class LeftHandMove : public Move {
public:
	void move() override;
	void init() override;
};
