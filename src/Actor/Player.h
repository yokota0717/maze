#pragma once
#include "Game.h"
#include "Field.h"
#include "../Easing/Easing.h"






//class Field;
//
//
//class Player :public Object {
//public:
//	Player(const string& name, Object::Status status);
//
//	void init() override;
//	void update() override;
//	void render() override;
//	int recieveMsg(std::weak_ptr<Object> sender, int mapnum);
//	enum Angle{
//		idle	= 1 << 0,	//1
//		left	= 1 << 1,	//2
//		right	= 1 << 2,	//4
//		up		= 1 << 3,	//8
//		down	= 1 << 4,	//16
//	};
//private:
//	Math::Vec pos;			//ピクセル単位の座標
//	Math::Vec nowBlock;		//マス単位の座標
//	Math::Vec est;			//移動量
//	bool move;				//移動中ならtrue
//	Easing easex;
//	Easing easey;
//	std::shared_ptr<Field> field;	//マップ情報取得用ポインタ
//	int nowMap;				//現在適応中のマップID
//
//	//移動できるかチェック、できないなら移動量をゼロにする
//	void CheckMove(int keyFlag);
//	//壁ぶつかり判定
//	bool CheckWall(KeyCode keyCode);
//	//移動先のマップ外判定
//	bool OutofMap(KeyCode keyCode);
//
//};