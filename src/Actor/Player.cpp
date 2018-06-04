#include "Player.h"
#include <iostream>


Player::Player(const string& name, Object::Status status)
	:
	Object(name, status)
{}

void Player::init() {
	field = dynamic_pointer_cast<Field>(getParentPtr().lock());
	pos = field->setPlayerPos();
	nowBlock = Math::Vec((pos.x - 245) / 100, (pos.y - 145) / 100);	//posから計算
	move = false;
}
void Player::update() {
	if (!field) { return; }

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
	if (pos.x == endx && pos.y == endy) {
		nowBlock += est;
		est.x = est.y = 0.0f;
		move = false;
		easex.init();
		easey.init();
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
		return !field->isLeftWall(nowBlock) && !field->isRightWall(nowBlock.x - 1, nowBlock.y);
	case RIGHT:
		return !field->isRightWall(nowBlock) && !field->isLeftWall(nowBlock.x + 1, nowBlock.y);
	case UP:
		return !field->isUpWall(nowBlock) && !field->isBottomWall(nowBlock.x, nowBlock.y - 1);
	case DOWN:
		return !field->isBottomWall(nowBlock) && !field->isUpWall(nowBlock.x, nowBlock.y + 1);
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