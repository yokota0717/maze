#include "Goal.h"



Goal::Goal(const std::string & name, Object::Status status)
	:
	Object(name, status)
{}

Goal::~Goal()
{}

void Goal::init()
{}

void Goal::setGoalInfo(Math::Vec blockPos, std::vector<Item>& item)
{
	this->blockPos = blockPos;
	this->pos = Math::Vec(blockPos.x * 100 + 200, blockPos.y * 100 + 100);
	this->item = item;
}

void Goal::update()
{
}

void Goal::render()
{
	for (auto i : this->item) {
		switch (i.getType()) {
		case Item::ItemType::OvalLength:
			i.DrawOvalLength(this->pos);
			break;
		case Item::ItemType::OvalSide:
			i.DrawOvalSide(this->pos);
			break;
		}
	}
}

bool Goal::checkClear()
{
	return false;
}

