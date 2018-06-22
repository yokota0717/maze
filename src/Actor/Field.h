#pragma once
#include "Game.h"
#include <vector>
#include <string>


class Map {
public:
	enum State {
		Non,
		Wall,
	};

private:
	State state;
	std::vector<std::vector<State>> map;
	short id;
	unsigned int lineColor;
	unsigned int boxColor;

public:
	Map();
	bool LoadMap(std::string& path, short id);
	void render();
	void renderWall(int x, int y);
	void renderBox(int x, int y);
	bool isWall(int x, int y);

};


class Field : public Object {
	std::vector<Map> map;
	short sizeX_, sizeY_;
	short activeMapID_;
	bool clear;
	
public:
	Field(const std::string& name, Object::Status status);

	void init() override;
	void update() override;
	void render() override;
	
	bool LoadMap(std::vector<std::string> path);
	bool isCleared();
	int sizeX() const;
	int sizeY() const;

	//blockPosからkeyの方向が壁かどうか判定
	bool isWall(KeyCode key, Math::Vec blockPos);
	//プレイヤがアイテムとった
	bool checkGetItem(Math::Vec& pos);

	Math::Vec getGoalPos();
	void checkClear();

	void cleared();
};