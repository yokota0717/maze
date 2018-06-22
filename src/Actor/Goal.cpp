#include "Goal.h"



Goal::Goal(const std::string & name, Object::Status status)
	:
	Object(name, status)
{}

Goal::~Goal()
{}

void Goal::init()
{
	field = std::dynamic_pointer_cast<Field>(this->getParentPtr().lock());
}

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
	int color = (field->isCleared()) ? GetColor(200, 200, 200) : GetColor(80, 80, 80);
	for (auto i : this->item) {
		switch (i.getType()) {
		case Item::ItemType::OvalLength:
			i.DrawOvalLength(this->pos, color);
			break;
		case Item::ItemType::OvalSide:
			i.DrawOvalSide(this->pos, color);
			break;
		}
	}
}

Math::Vec Goal::getBlockPos() const
{
	return this->blockPos;
}
