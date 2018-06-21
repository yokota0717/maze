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
		DrawOvalLength(this->pos);	
		break;
	case OvalSide:
		DrawOvalSide(this->pos);
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

Item::ItemType Item::getType()
{
	return this->type;
}

void Item::DrawOvalLength(Math::Vec pos)
{
	DrawOvalAA(pos.x + 50, pos.y + 50, 40, 25, 200, debugRed, false, 3);
}

void Item::DrawOvalSide(Math::Vec pos)
{
	DrawOvalAA(pos.x + 50, pos.y + 50, 25, 40, 200, debugRed, false, 3);
}
