#pragma once
#include "Game.h"


//ゴールに必要なアイテム
class Item : public Object
{
public:
	enum ItemType {
		OvalLength,
		OvalSide,
	};
	Item(const std::string& name, Object::Status status, ItemType type);
	~Item();

	void init() override;
	void update() override;
	void render() override;
	void setBlockPos(Math::Vec pos);
	Math::Vec getPos() const;

	ItemType getType();

	void DrawOvalLength(Math::Vec pos);
	void DrawOvalSide(Math::Vec pos);

private:
	ItemType type;
	Math::Vec blockPos;
	Math::Vec pos;
};

