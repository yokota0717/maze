#pragma once
#include <fstream>
#include <sstream>
#include "Game.h"
#include "Player.h"

//迷路のフィールド
class Field :public Object {
public:
	enum FieldState {
		Non,
		Up, Left, Right, Bottom,
		UpLeft, UpBottom, UpRight, LeftRight, LeftBottom, RightBottom,
		UpRightBottom, UpLeftRight,UpLeftBottom, LeftRightBottom,
		All,
	};

	Field(const string& name, Object::Status status);

	void init() override;
	void update() override;
	void render() override;
	int sizeX();
	int sizeY();
	FieldState getState(Math::Vec& pos);
	bool isLeftWall(Math::Vec& pos);
	bool isRightWall(Math::Vec& pos);
	bool isUpWall(Math::Vec& pos);
	bool isBottomWall(Math::Vec& pos);
	bool isLeftWall(float x, float y);
	bool isRightWall(float x, float y);
	bool isUpWall(float x, float y);
	bool isBottomWall(float x, float y);
	Math::Vec setPlayerPos();

private:
	struct Box {
		Math::Box2D box;
		FieldState state;
	};
	vector<vector<Box>> field;	//マップ情報
	int sizeX_, sizeY_;			//マップサイズ
	Math::Vec start, goal;		//スタートとゴールの座標、ピクセル単位
	const std::vector<FieldState> LeftWall;
	const std::vector<FieldState> RightWall;
	const std::vector<FieldState> UpWall;
	const std::vector<FieldState> BottomWall;

	void setField(const int x, const int y);	//現在未使用
	bool loadMap(std::string& path);			//csvファイルからマップの読み込み

	void DrawBox(Box box, int color);	//このゲーム専用のマップのマス描画関数
	void renderStart(Math::Vec& start);
	void renderGoal(Math::Vec& goal);
};