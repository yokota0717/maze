#pragma once
#include "../Input/Input.h"
//#include "../GraphFactory/GraphFactory.h"
#include "../Object/Object.h"
#include "../define.h"

#include "Field.h"

//���[�g�N���X
class Root :public Object {
public:
	Root();
	~Root();
	void init(std::shared_ptr<Object> thisptr);
	void update() override;
	void render() override;
	int frame();

private:
	int frame_;
};

//�Q�[���Ǘ��N���X
//�g���N���X�͂����Ő錾
class Game {
	bool debug_;
public:
	Game();
	~Game();
	void fin();

	Keyboard kb;
	Mouse mouse;
	std::shared_ptr<Root> root;
	//std::unique_ptr<GraphFactory> grafac;
	void doAll();
	bool DebugMode();
};

extern std::unique_ptr<Game> game;