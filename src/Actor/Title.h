#pragma once
#include "Game.h"

class Title :public Object {
public:
	Title(const std::string& name, Object::Status status);

	void init() override;
	void update() override;
	void render() override;

	bool StartGame();

	int postMsg(std::weak_ptr<Object> receiver, const std::string& msg);
};