#include "Player.h"
#include <iostream>


Player::Player(const string& name, Object::Status status)
	:
	Object(name, status)
{}

void Player::init() {
	field = dynamic_pointer_cast<Field>(getParentPtr().lock());
	Math::Vec startBlock = field->setPlayerPos();
	pos = Math::Vec(200.0f + 100 * startBlock.x + 45, 100.0f + 100 * startBlock.y + 45);
	nowBlock = Math::Vec((pos.x - 245) / 100, (pos.y - 145) / 100);	//posから計算
	nowMap = field->getActiveMapID();
	move = false;
}
void Player::update() {
	if (!field) { return; }
	if (field->isCleared()) { return; }
	Math::Vec pre;
	if (!move) {	//移動中でなければ入力受付
		int keyFlag = 0;
		if (game->kb.On(LEFT)) {
			if (!OutofMap(LEFT)) {
				if (CheckWall(LEFT)) {
					pre = nowBlock;
					est.x -= 1;
					move = true;
					keyFlag += 1;
				}
			}
		}
		if (game->kb.On(RIGHT)) {
			if (!OutofMap(RIGHT)) {
				if (CheckWall(RIGHT)) {
					pre = nowBlock;
					est.x += 1;
					move = true;
					keyFlag += 2;
				}
			}
		}
		if (game->kb.On(UP)) {
			if (!OutofMap(UP)) {
				if (CheckWall(UP)) {
					pre = nowBlock;
					est.y -= 1;
					move = true;
					keyFlag += 4;
				}
			}
		}
		if (game->kb.On(DOWN)) {
			if (!OutofMap(DOWN)) {
				if (CheckWall(DOWN)) {
					pre = nowBlock;
					est.y += 1;
					move = true;
					keyFlag += 8;
				}
			}
		}
		CheckMove(keyFlag);
	}
	
	//移動先座標を計算
	float endx = (nowBlock.x + est.x) * 100.0f + 245.0f;
	float endy = (nowBlock.y + est.y) * 100.0f + 145.0f;
	//移動前座標を計算
	Math::Vec prepos(nowBlock.x*100.0f + 245.0f, nowBlock.y*100.0f + 145.0f);
	//イージングを用いた時の移動量計算
	float x = easex.quint.Out(easex.Time(1), prepos.x, endx - prepos.x, 1);
	float y = easey.quint.Out(easey.Time(1), prepos.y, endy - prepos.y, 1);
	//移動
	pos.x = x;
	pos.y = y;
	//移動終了
	if (pos.x == endx && pos.y == endy) {
		nowBlock += est;
		est.x = est.y = 0.0f;
		move = false;
		easex.init();
		easey.init();
		//ゴール判定
		if (nowBlock == field->getGoalPos()) {
			postMsg(this->getParentPtr(), "Goal");
		}
	}
}
void Player::render() {
	DrawCircleAA(pos.x, pos.y, 35, 200, debugRed, true);
	//DrawCircle(pos.x, pos.y, 35, GetColor(255, 80, 80), true);
}
void Player::CheckMove(int keyFlag) {
	//キーの同時押しは押してないことにする
	if (keyFlag != 1 && keyFlag != 2 && keyFlag != 4 && keyFlag != 8) {
		est.Zero();
	}
}

bool Player::CheckWall(KeyCode keyCode){
	switch (keyCode) {
	case LEFT:
		return !field->isLeftWall(nowMap, nowBlock) && !field->isRightWall(nowMap, nowBlock.x - 1, nowBlock.y);
	case RIGHT:
		return !field->isRightWall(nowMap, nowBlock) && !field->isLeftWall(nowMap, nowBlock.x + 1, nowBlock.y);
	case UP:
		return !field->isUpWall(nowMap, nowBlock) && !field->isBottomWall(nowMap, nowBlock.x, nowBlock.y - 1);
	case DOWN:
		return !field->isBottomWall(nowMap, nowBlock) && !field->isUpWall(nowMap, nowBlock.x, nowBlock.y + 1);
	default:
		return false;
	}
}
bool Player::OutofMap(KeyCode keyCode) {
	switch (keyCode) {
	case LEFT:
		return (nowBlock.x - 1) < 0;
	case RIGHT:
		return (nowBlock.x + 1) >= field->sizeX();
	case UP:
		return (nowBlock.y - 1) < 0;
	case DOWN:
		return (nowBlock.y + 1) >= field->sizeY();
	default:
		return true;
	}
}

int Player::recieveMsg(std::weak_ptr<Object> sender, int mapnum){
	if (mapnum < 0 || mapnum >= 4) { return -1; }
	this->nowMap = mapnum;
	return 0;
}
