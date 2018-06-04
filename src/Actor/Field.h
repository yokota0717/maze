#pragma once
#include <fstream>
#include <sstream>
#include "Game.h"
#include "Player.h"

//���H�̃t�B�[���h
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
	vector<vector<Box>> field;	//�}�b�v���
	int sizeX_, sizeY_;			//�}�b�v�T�C�Y
	Math::Vec start, goal;		//�X�^�[�g�ƃS�[���̍��W�A�s�N�Z���P��
	const std::vector<FieldState> LeftWall;
	const std::vector<FieldState> RightWall;
	const std::vector<FieldState> UpWall;
	const std::vector<FieldState> BottomWall;

	void setField(const int x, const int y);	//���ݖ��g�p
	bool loadMap(std::string& path);			//csv�t�@�C������}�b�v�̓ǂݍ���

	void DrawBox(Box box, int color);	//���̃Q�[����p�̃}�b�v�̃}�X�`��֐�
	void renderStart(Math::Vec& start);
	void renderGoal(Math::Vec& goal);
};