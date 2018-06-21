#pragma once
#include "Game.h"
#include "Field.h"
#include "Move/Move.h"
#include "../Easing/Easing.h"
#include "Item.h"
#include <string>

class Field;
class Move;

class Chara : public Object {
public:
	Chara(const std::string& name, Object::Status status);
	~Chara();
	Move* move;
	void changeBehavior(Move* move);
};

class Player :public Chara {
public:
	Player(const std::string& name, Object::Status status);

	void init() override;
	void update() override;
	void render() override;

	std::vector<Item> nowItem() const;
	void getItem(Item& item);

private:
	std::vector<Item> items;
};

class Enemy : public Chara {
public:
	Enemy(const std::string& name, Object::Status status);

	void init() override;
	void update() override;
	void render() override;
};