#pragma once
#include "../Input/Input.h"
//#include "../GraphFactory/GraphFactory.h"
#include "../Object/Object.h"
#include "../define.h"


//ルートクラス
class Root :public Object {
public:
	Root();
	~Root();
	void init(std::shared_ptr<Object> thisptr);
	void update() override;
	void render() override;
	int frame();
	int receiveMsg(std::weak_ptr<Object> sender, const std::string& msg);

private:
	int frame_;
};

//ゲーム管理クラス
//使うクラスはここで宣言
class Game {
	bool debug_;
public:
	Game();
	~Game();
	void fin();

	Keyboard kb;
	Mouse mouse;
	GPad pad;
	std::shared_ptr<Root> root;
	//std::unique_ptr<GraphFactory> grafac;
	void doAll();
	bool DebugMode();
};

extern std::unique_ptr<Game> game;