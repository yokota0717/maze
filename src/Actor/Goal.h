#pragma once
#include "Game.h"
#include "Item.h"


//�v���C���������Ɠ����A�C�e�����������Ă��邩�`�F�b�N
class Goal : public Object
{
public:
	Goal(const std::string& name, Object::Status status);
	~Goal();

	void init() override;
	void setGoalInfo(Math::Vec blcokPos, std::vector<Item>& item);
	void update() override;
	void render() override;

	bool checkClear();


private:
	std::vector<Item> item;
	Math::Vec blockPos;
	Math::Vec pos;
};
