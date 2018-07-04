#include "Move.h"

Move::Move()
{}

bool Move::OutOfMap(KeyCode key)
{
	switch (key) {
	case KeyCode::LEFT:
		return (blockPos.x - 1) < 0;
	case KeyCode::RIGHT:
		return (blockPos.x + 1) >= field->sizeX();
	case KeyCode::UP:
		return (blockPos.y - 1) < 0;
	case KeyCode::DOWN:
		return (blockPos.y + 1) >= field->sizeY();
	default:
		return true;
	}
}

bool Move::isWall(KeyCode key)
{
	return field->isWall(key, blockPos);
}

bool Move::checkMove(int keyFlag)
{
	//キーの同時押しは押してないことにする
	if (keyFlag != 1 && keyFlag != 2 && keyFlag != 4 && keyFlag != 8) {
		est.Zero();
	}
	return true;
}

void InputMove::move()
{
	if (field->isCleared()) { return; }
	Math::Vec pre;
	if (!this->moving) {	//移動中でなければ入力受付
		int keyFlag = 0;
		if (game->kb.On(LEFT)) {
			if (!OutOfMap(LEFT)) {
				if (!isWall(LEFT)) {
					pre = blockPos;
					est.x -= 1;
					moving = true;
					keyFlag += 1;
				}
			}
		}
		if (game->kb.On(RIGHT)) {
			if (!OutOfMap(RIGHT)) {
				if (!isWall(RIGHT)) {
					pre = blockPos;
					est.x += 1;
					moving = true;
					keyFlag += 2;
				}
			}
		}
		if (game->kb.On(UP)) {
			if (!OutOfMap(UP)) {
				if (!isWall(UP)) {
					pre = blockPos;
					est.y -= 1;
					moving = true;
					keyFlag += 4;
				}
			}
		}
		if (game->kb.On(DOWN)) {
			if (!OutOfMap(DOWN)) {
				if (!isWall(DOWN)) {
					pre = blockPos;
					est.y += 1;
					moving = true;
					keyFlag += 8;
				}
			}
		}
		checkMove(keyFlag);
	}

	//移動先座標を計算
	float endx = (blockPos.x + est.x) * 100.0f + 250.0f;
	float endy = (blockPos.y + est.y) * 100.0f + 150.0f;
	//移動前座標を計算
	Math::Vec prepos(blockPos.x*100.0f + 250.0f, blockPos.y*100.0f + 150.0f);
	//イージングを用いた時の移動量計算
	float x = easex.quint.Out(easex.Time(1), prepos.x, endx - prepos.x, 1);
	float y = easey.quint.Out(easey.Time(1), prepos.y, endy - prepos.y, 1);
	//移動
	pos.x = x;
	pos.y = y;
	//移動終了
	if (pos.x == endx && pos.y == endy) {
		blockPos += est;
		est.x = est.y = 0.0f;
		moving = false;
		easex.init();
		easey.init();
		//アイテム判定
		field->checkGetItem(this->blockPos);
		//ゴール判定
		if (blockPos == field->getGoalPos()) {
			field->cleared();
			//postMsg(this->getParentPtr(), "Goal");
		}
	}

}

void InputMove::init()
{
	field = std::dynamic_pointer_cast<Field>(game->root->getObjectFromChildren("Field").lock());
	blockPos = Math::Vec(0, 0);
	pos = Math::Vec(blockPos.x * 100 + 250, blockPos.y * 100 + 150);
	moving = false;
}

void LeftHandMove::move()
{
	//左手法
	
	
}

void LeftHandMove::init()
{
	field = std::dynamic_pointer_cast<Field>(game->root->getObjectFromChildren("Field").lock());
	blockPos = Math::Vec(10, 3);
	pos = Math::Vec(blockPos.x * 100 + 200, blockPos.y * 100 + 100);
	moving = false;
}
