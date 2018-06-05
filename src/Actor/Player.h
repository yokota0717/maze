#pragma once
#include "Game.h"
#include "Field.h"
#include "../Easing/Easing.h"

class Field;


class Player :public Object {
public:
	Player(const string& name, Object::Status status);

	void init() override;
	void update() override;
	void render() override;
	int recieveMsg(std::weak_ptr<Object> sender, int mapnum);
private:
	enum {
		idle	= 1 << 0,
		left	= 1 << 1,
		right	= 1 << 2,	
		up		= 1 << 3,
		down	= 1 << 4,
	};
	Math::Vec pos;			//�s�N�Z���P�ʂ̍��W
	Math::Vec nowBlock;		//�}�X�P�ʂ̍��W
	Math::Vec est;			//�ړ���
	bool move;				//�ړ����Ȃ�true
	Easing easex;
	Easing easey;
	std::shared_ptr<Field> field;	//�}�b�v���擾�p�|�C���^
	int nowMap;				//���ݓK�����̃}�b�vID

	//�ړ��ł��邩�`�F�b�N�A�ł��Ȃ��Ȃ�ړ��ʂ��[���ɂ���
	void CheckMove(int keyFlag);
	//�ǂԂ��蔻��
	bool CheckWall(KeyCode keyCode);
	//�ړ���̃}�b�v�O����
	bool OutofMap(KeyCode keyCode);

};