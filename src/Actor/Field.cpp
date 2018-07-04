#include <fstream>
#include <sstream>
#include "Field.h"
#include "Player.h"
#include "Item.h"
#include "Goal.h"


Map::Map()
	:
	lineColor(GetColor(200, 200, 200)),
	boxColor(GetColor(100, 100, 0))
{
	this->map.resize(8 * 2 + 1);
	for (int y = 0; y < 8 * 2 + 1; ++y) {
		this->map[y].resize(15 * 2 + 1);
	}
}

bool Map::LoadMap(std::string & path, short id)
{
	path = "./data/map/" + path;
	//バイナリファイルを読み取り専用で開く
	std::ifstream fin(path, std::ios::in | std::ios::binary);
	if (!fin) { return false; }
	//マップ情報を読み込み
	for (int y = 0; y < 8 * 2 + 1; ++y) {
		std::string lineText;
		std::getline(fin, lineText);
		std::istringstream is_lt(lineText);
		for (int x = 0; x < 15 * 2 + 1; ++x) {
			//一文字分取り出す
			std::string text;
			std::getline(is_lt, text, ',');
			//改行文字が入っていたら除く
			if (text.find("\r") != std::string::npos) {
				text.erase(text.find("\r"));
			}
			assert(std::all_of(text.cbegin(), text.cend(), isdigit));
			//データ格納
			int state;
			(std::stringstream)text >> state;
			this->map[y][x] = (State)state;
		}
	}
	fin.close();
	return true;
}

void Map::render()
{
	for (int y = 0; y < 8 * 2 + 1; ++y) {
		for (int x = 0; x < 15 * 2 + 1; ++x) {
			if (x % 2 == 0 || y % 2 == 0) {
				renderWall(x, y);
			}
			//マスの描画
			renderBox(x, y);
		}
	}
}
void Map::renderWall(int x, int y)
{
	if (this->map[y][x] == State::Non) { return; }
	//ウィンドウ座標に変換
	Math::Vec pos(200.0f + (x / 2) * 100, 100.0f + (y / 2) * 100);
	if (x % 2 == 0 && y % 2 == 0) {
		//柱
		DrawCircle((int)pos.x, (int)pos.y, 5, lineColor);
	}
	if (x % 2 != 0 && y % 2 == 0) {
		//横
		DrawLine((int)pos.x, (int)pos.y, (int)pos.x + 100, (int)pos.y, lineColor, 5);
	}
	if (x % 2 == 0 && y % 2 != 0) {
		//縦
		DrawLine((int)pos.x, (int)pos.y, (int)pos.x, (int)pos.y + 100, lineColor, 5);
	}
}

void Map::renderBox(int x, int y)
{
	if (x == 30 || y == 16) { return; }
	//ウィンドウ座標に変換
	Math::Vec pos(200.0f + (x / 2) * 100, 100.0f + (y / 2) * 100);
	DrawBox((int)pos.x + 5, (int)pos.y + 5, (int)pos.x + 95, (int)pos.y + 95, boxColor, false);
}

bool Map::isWall(int x, int y)
{
	return this->map[y][x] == 1;
}

Field::Field(const std::string & name, Object::Status status)
	:
	Object(name, status),
	sizeX_(15),
	sizeY_(8)
{}

void Field::init()
{
	insertAsChild(new Player("Player", Object::Status::run));
	auto item1 = insertAsChild(new Item("Item", Object::Status::run, Item::ItemType::OvalLength));
	std::dynamic_pointer_cast<Item>(item1.lock())->setBlockPos(Math::Vec(10, 3));
	auto item2 = insertAsChild(new Item("Item", Object::Status::run, Item::ItemType::OvalSide));
	std::dynamic_pointer_cast<Item>(item2.lock())->setBlockPos(Math::Vec(5, 6));
	auto goal = insertAsChild(new Goal("Goal", Object::Status::run));
	std::dynamic_pointer_cast<Goal>(goal.lock())->setGoalInfo(Math::Vec(14, 7), std::vector<Item>{Item("Item", Object::Status::run, Item::ItemType::OvalLength), Item("Item", Object::Status::run, Item::ItemType::OvalSide)});
	this->map.clear();
	this->map.resize(4);
	LoadMap(std::vector<std::string>{(std::string)"map1.csv", (std::string)"map2.csv", (std::string)"map3.csv", (std::string)"map4.csv"});
	this->activeMapID_ = 0;
	this->clear = false;
}

void Field::update()
{
	if (game->kb.Down(W) || game->pad.Down(PadCode::Y)) { activeMapID_ = 0; }
	if (game->kb.Down(A) || game->pad.Down(PadCode::X)) { activeMapID_ = 1; }
	if (game->kb.Down(D) || game->pad.Down(PadCode::B)) { activeMapID_ = 2; }
	if (game->kb.Down(S) || game->pad.Down(PadCode::A)) { activeMapID_ = 3; }

	if (game->kb.Down(ENTER) || game->pad.Down(PadCode::START)) {
		BackToTitle();
	}
}

void Field::render()
{
	map[this->activeMapID_].render();

	if (this->clear) {
		SetFontSize(100);
		DrawFormatString(600, 400, debugRed, "CLEARED!");
	}
}

bool Field::LoadMap(std::vector<std::string> path)
{
	for (int i = 0; i < 4; ++i) {
		map[i].LoadMap(path[i], i);
	}
	return true;
}

bool Field::isCleared()
{
	return this->clear;
}

int Field::sizeX() const
{
	return this->sizeX_;
}

int Field::sizeY() const
{
	return this->sizeY_;
}

bool Field::isWall(KeyCode key, Math::Vec blockPos)
{
	//マス座標を壁含むマス座標に変換
	blockPos.x = blockPos.x * 2 + 1;
	blockPos.y = blockPos.y * 2 + 1;
	switch (key) {
	case KeyCode::UP:
		return map[this->activeMapID_].isWall((int)blockPos.x, (int)blockPos.y - 1);	break;
	case KeyCode::LEFT:
		return map[this->activeMapID_].isWall((int)blockPos.x - 1, (int)blockPos.y); break;
	case KeyCode::RIGHT:
		return map[this->activeMapID_].isWall((int)blockPos.x + 1, (int)blockPos.y); break;
	case KeyCode::DOWN:
		return map[this->activeMapID_].isWall((int)blockPos.x, (int)blockPos.y + 1); break;
	default:
		return true;
		break;
	}
}

bool Field::checkGetItem(Math::Vec & blockPos)
{
	auto items = this->getObjectsFromChildren(std::vector<std::string>{("Item")});
	if (!items.empty()) {
		for (auto item : items) {
			auto p = std::dynamic_pointer_cast<Item>(item.lock())->getBlockPos();
			if (blockPos == std::dynamic_pointer_cast<Item>(item.lock())->getBlockPos()) {
				auto player = this->getObjectFromChildren("Player");
				std::dynamic_pointer_cast<Player>(player.lock())->getItem(std::shared_ptr<Item>(new Item("Item", Object::Status::run, std::dynamic_pointer_cast<Item>(item.lock())->getType())));
				item.lock()->kill();
				return true;
			}
		}
	}
	return false;
}

Math::Vec Field::getGoalPos()
{
	return std::dynamic_pointer_cast<Goal>(this->getObjectFromChildren("Goal").lock())->getBlockPos();
}

void Field::checkClear()
{
	
}

void Field::cleared()
{
	this->clear = true;
}

bool Field::BackToTitle()
{
	postMsg(getParentPtr(), "Title");
	this->kill();
	return true;
}
