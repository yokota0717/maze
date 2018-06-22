#include "Item.h"



Item::Item(const std::string& name, Object::Status status, ItemType type)
	:
	Object(name, status),
	type(type)
{}


Item::~Item()
{}

void Item::init()
{
	pos = Math::Vec(blockPos.x * 100 + 200, blockPos.y * 100 + 100);
}

void Item::update()
{
}

void Item::render()
{
	switch (this->type) {
	case OvalLength:
		DrawOvalLength(this->pos, GetColor(200, 80, 80));
		break;
	case OvalSide:
		DrawOvalSide(this->pos, GetColor(200, 80, 80));
		break;
	default:
		break;
	}
}

void Item::setBlockPos(Math::Vec blockPos)
{
	this->blockPos = blockPos;
}

Math::Vec Item::getPos() const
{
	return this->pos;
}

Math::Vec Item::getBlockPos() const
{
	return this->blockPos;
}

Item::ItemType Item::getType()
{
	return this->type;
}

void Item::DrawOvalLength(Math::Vec pos, int color)
{
	DrawOvalAA(pos.x + 50, pos.y + 50, 40, 25, 200, color, false, 3);
}

void Item::DrawOvalSide(Math::Vec pos, int color)
{
	DrawOvalAA(pos.x + 50, pos.y + 50, 25, 40, 200, color, false, 3);
}
