#include "DxLib.h"
#include "./Input.h"
#include <iostream>

Keyboard::Keyboard()
{
	Key[256] = {};
	preKey[256] = {};
}
// �L�[�̓��͏�ԍX�V
void Keyboard::update() 
{
	char tmpKey[256];				// ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);		// �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		preKey[i] = Key[i];
		if (tmpKey[i] != 0) {		// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;				// ���Z
		}
		else {						// ������Ă��Ȃ����
			Key[i] = 0;				// 0�ɂ���
		}
	}
}

// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Keyboard::getKey(KeyCode KeyCode) 
{
	return Key[KeyCode];			// KeyCode�̓��͏�Ԃ�Ԃ�
}
int Keyboard::getPreKey(KeyCode keycode) 
{
	return preKey[keycode];
}

bool Keyboard::Down(KeyCode keycode) 
{
	return (getKey(keycode) == 1);
}
bool Keyboard::On(KeyCode keycode) 
{
	return (getKey(keycode) > 1);
}
bool Keyboard::Up(KeyCode keycode) 
{
	return ((getPreKey(keycode) >= 1) && getKey(keycode) == 0);
}
bool Keyboard::Off(KeyCode keycode) 
{
	return ((getPreKey(keycode) == 0) && getKey(keycode) == 0);
}


GPad::GPad(int id):
	padID(id)
{}

void GPad::update()
{
	//�O�t���[���̏�Ԃ�ۑ�
	pre = input;
	// ���͏�Ԃ��擾
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
}

unsigned int GPad::getPadNum() 
{
	return GetJoypadNum();
}

bool GPad::On(PadCode in)
{
	return ((input.Buttons[(int)in] == 128) && (pre.Buttons[(int)in] == 128));
}
bool GPad::Down(PadCode in)
{
	return ((input.Buttons[(int)in] == 128) && (pre.Buttons[(int)in] == 0));
}
bool GPad::Up(PadCode in)
{
	return ((input.Buttons[(int)in] == 0) && (pre.Buttons[(int)in] == 128));
}
bool GPad::Off(PadCode in)
{
	return ((input.Buttons[(int)in] == 0) && (pre.Buttons[(int)in] == 0));
}

//0xffffffff:���͂Ȃ� 0:�� 4500:�E�� 9000:�E 13500:�E�� 18000:�� 22500:���� 27000:�� 31500:����
bool GPad::On(PadAng in)
{
	switch (in) {
	case PadAng::LEFT:
		return ((input.POV[0] == 27000) && (pre.POV[0] == 27000));
	case PadAng::RIGHT:
		return ((input.POV[0] == 9000) && (pre.POV[0] == 9000));
	case PadAng::UP:
		return ((input.POV[0] == 0) && (pre.POV[0] == 0));
	case PadAng::DOWN:
		return ((input.POV[0] == 18000) && (pre.POV[0] == 18000));
	default:
		return false;
	}
}

bool GPad::Down(PadAng in)
{
	switch (in) {
	case PadAng::LEFT:
		return ((input.POV[0] == 27000) && (pre.POV[0] != 27000));
	case PadAng::RIGHT:
		return ((input.POV[0] == 9000) && (pre.POV[0] != 9000));
	case PadAng::UP:
		return ((input.POV[0] == 0) && (pre.POV[0] != 0));
	case PadAng::DOWN:
		return ((input.POV[0] == 18000) && (pre.POV[0] != 18000));
	default:
		return false;
	}
}

bool GPad::Up(PadAng in)
{
	switch (in) {
	case PadAng::LEFT:
		return ((input.POV[0] == 0xffffffff) && (pre.POV[0] == 27000));
	case PadAng::RIGHT:
		return ((input.POV[0] == 0xffffffff) && (pre.POV[0] == 9000));
	case PadAng::UP:
		return ((input.POV[0] == 0xffffffff) && (pre.POV[0] == 0));
	case PadAng::DOWN:
		return ((input.POV[0] == 0xffffffff) && (pre.POV[0] == 18000));
	default:
		return false;
	}
}

bool GPad::Off(PadAng in)
{
	switch (in) {
	case PadAng::LEFT:
		return ((input.POV[0] == 0xffffffff) && (pre.POV[0] == 0xffffffff));
	case PadAng::RIGHT:
		return ((input.POV[0] == 0xffffffff) && (pre.POV[0] == 0xffffffff));
	case PadAng::UP:
		return ((input.POV[0] == 0xffffffff) && (pre.POV[0] == 0xffffffff));
	case PadAng::DOWN:
		return ((input.POV[0] == 0xffffffff) && (pre.POV[0] == 0xffffffff));
	default:
		return false;
	}
}

void Mouse::update() {
	prex = x;
	prey = y;
	if (GetMousePoint(&x, &y) == -1)
		return;
	for (int i = 0; i < 3; ++i) {
		prebutton[i] = button[i];
	}
	int input = GetMouseInput();
	if (input&MOUSE_INPUT_LEFT) { button[0]++; }
	else { button[0] = 0; }
	if (input&MOUSE_INPUT_RIGHT) { button[1]++; }
	else { button[1] = 0; }
	if (input&MOUSE_INPUT_MIDDLE) { button[2]++; }
	else { button[2] = 0; }
	wheel = GetMouseWheelRotVol();
}
Math::Vec Mouse::getPos() const {
	return Math::Vec((float)x, (float)y);
}
int Mouse::getWheel() const {
	return wheel;
}
bool Mouse::DownLeft() {
	return button[0] == 1;
}
bool Mouse::DownRight() {
	return button[1] == 1;
}
bool Mouse::DownCenter() {
	return button[2] == 1;
}
bool Mouse::OnLeft() {
	return button[0] >= 1;
}
bool Mouse::OnRight() {
	return button[1] >= 1;
}
bool Mouse::OnCenter() {
	return button[2] >= 1;
}
bool Mouse::UpLeft() {
	return button[0] == 0 && prebutton[0] >= 1;
}
bool Mouse::UpRight() {
	return button[1] == 0 && prebutton[1] >= 1;
}
bool Mouse::UpCenter() {
	return button[2] == 0 && prebutton[2] >= 1;
}
bool Mouse::OffLeft() {
	return button[0] == 0 && prebutton[0] == 0;
}
bool Mouse::OffRight() {
	return button[1] == 0 && prebutton[1] == 0;
}
bool Mouse::OffCenter() {
	return button[2] == 0 && prebutton[2] == 0;
}