#include "Player.h"


Chara::Chara(const std::string & name, Object::Status status)
	:
	Object(name, status)
{}

Chara::~Chara()
{
	delete move;
}

void Chara::changeBehavior(Move* move)
{
	this->move = move;
}

Player::Player(const std::string & name, Object::Status status)
	:
	Chara(name, status)
{}

void Player::init()
{
	this->move = new InputMove();
	move->init();
}

void Player::update()
{
	if (!move->field) { return; }
	move->move();
}

void Player::render()
{
	DrawCircleAA(move->pos.x, move->pos.y, 20, 200, debugRed, true);
	//ŠŽƒAƒCƒeƒ€‚É‚æ‚Á‚Ä’Ç‰Á
	for (auto item : this->items) {
		switch (item.getType()) {
		case Item::ItemType::OvalLength:
			item.DrawOvalLength(this->move->pos);
			break;
		case Item::ItemType::OvalSide:
			item.DrawOvalSide(this->move->pos);
			break;
		default:
			break;
		}
	}
	//DrawOvalAA(move->pos.x, move->pos.y, 40, 25, 200, debugRed, false, 3);
	//DrawOvalAA(move->pos.x, move->pos.y, 25, 40, 200, debugRed, false, 3);

}

std::vector<Item> Player::nowItem() const
{
	return this->items;
}

void Player::getItem(Item & item)
{
	this->items.push_back(item);
}

Enemy::Enemy(const std::string & name, Object::Status status)
	:
	Chara(name, status)
{}

void Enemy::init()
{

}

void Enemy::update()
{
}

void Enemy::render()
{
}
