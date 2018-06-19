#pragma once
#include "Game.h"
#include "Player.h"


class Map {
public:
	enum State {
		Non,
		Wall,
	};
	enum Angle {

	};

private:
	State state;
	vector<vector<State>> map;
	short id;
	unsigned int lineColor;
	unsigned int boxColor;

public:
	Map();
	bool LoadMap(string& path, short id);
	//bool checkWall(int x, int y, Player::Angle ang);
	void render();
	void renderWall(int x, int y);
	//void renderWallLength(int x, int y);
	//void renderWallSide(int x, int y);
	void renderBox(int x, int y);
};


class Field : public Object {
	vector<Map> map;
	short sizeX_, sizeY_;
	short activeMapID_;
	
public:
	Field(const string& name, Object::Status status);
	void init() override;
	void update() override;
	void render() override;
	bool LoadMap(vector<string> path);
};


////迷路のフィールド
//class Field :public Object {
//public:
//	enum FieldState {
//		Non,
//		Up, Left, Right, Bottom,
//		UpLeft, UpBottom, UpRight, LeftRight, LeftBottom, RightBottom,
//		UpRightBottom, UpLeftRight,UpLeftBottom, LeftRightBottom,
//		All,
//	};
//
//	Field(const string& name, Object::Status status);
//
//	void init() override;
//	void update() override;
//	void render() override;
//	int sizeX();
//	int sizeY();
//	FieldState getState(int nowMap, Math::Vec& pos);
//	bool isLeftWall(int nowMap, Math::Vec& pos);
//	bool isRightWall(int nowMap, Math::Vec& pos);
//	bool isUpWall(int nowMap, Math::Vec& pos);
//	bool isBottomWall(int nowMap, Math::Vec& pos);
//	bool isLeftWall(int nowMap, float x, float y);
//	bool isRightWall(int nowMap, float x, float y);
//	bool isUpWall(int nowMap, float x, float y);
//	bool isBottomWall(int nowMap, float x, float y);
//	Math::Vec setPlayerPos();
//	Math::Vec getGoalPos();
//	int getActiveMapID();
//	bool isCleared();
//
//private:
//	enum MapChangeKey {
//		UP,LEFT,RIGHT,BOTTOM,
//	};
//	//一マス分の情報を保持する構造体
//	struct Box {
//		Math::Box2D box;
//		FieldState state;
//	};
//	vector<vector<Box>> field[4];	//マップ情報
//	int activeMapID;				//現在適応中のマップID
//	int sizeX_, sizeY_;				//マップサイズ
//	Math::Vec start, goal;			//スタートとゴールの座標、マス単位
//	const std::vector<FieldState> LeftWall;
//	const std::vector<FieldState> RightWall;
//	const std::vector<FieldState> UpWall;
//	const std::vector<FieldState> BottomWall;
//
//	bool cleared;		//ゴールに到達したらtrue
//
//	bool loadMap(std::string& path, int id);			//csvファイルからマップの読み込み
//	bool loadMaps(std::vector<std::string>& pathes);	//1ステージ分の4マップをまとめて読みこみ
//	void changeMap(MapChangeKey key);					//マップの切り替え
//
//	void DrawBox(Box box, int color);			//このゲーム専用のマップのマス描画関数
//	void DrawOutLine();							//マップの外枠を描画
//	void renderStart(Math::Vec& start);
//	void renderGoal(Math::Vec& goal);
//
//	int postMsg(std::weak_ptr<Object> reciever, int mapnum);
//	int receiveMsg(std::weak_ptr<Object> sender, const std::string& msg) override;
//};