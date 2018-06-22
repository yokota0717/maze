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
		Math::Vec itemPos(this->move->pos.x - 50, this->move->pos.y - 50);
		switch (item->getType()) {
		case Item::ItemType::OvalLength:
			item->DrawOvalLength(itemPos, GetColor(255, 80, 80));
			break;
		case Item::ItemType::OvalSide:
			item->DrawOvalSide(itemPos, GetColor(255, 80, 80));
			break;
		default:
			break;
		}
	}
}

std::vector<std::shared_ptr<Item>> Player::nowItem() const
{
	return this->items;
}

void Player::getItem(std::shared_ptr<Item> item)
{
	item->setBlockPos(this->move->blockPos);
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
