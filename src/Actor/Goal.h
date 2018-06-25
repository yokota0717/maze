#pragma once
#include "Game.h"
#include "Field.h"
#include "Item.h"


//プレイヤが自分と同じアイテムを所持しているかチェック
class Goal : public Object
{
public:
	Goal(const std::string& name, Object::Status status);
	~Goal();

	void init() override;
	void setGoalInfo(Math::Vec blcokPos, std::vector<Item>& item);
	void update() override;
	void render() override;

	Math::Vec getBlockPos() const;

private:
	std::vector<Item> item;
	Math::Vec blockPos;
	Math::Vec pos;
	std::shared_ptr<Field> field;
};

