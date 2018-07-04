#pragma once
#include "DxLib.h"
#include "../Math/Math.h"


//�L�[�{�[�h����
enum KeyCode {
	LEFT = KEY_INPUT_LEFT,
	RIGHT = KEY_INPUT_RIGHT,
	UP = KEY_INPUT_UP,
	DOWN = KEY_INPUT_DOWN,
	BACK = KEY_INPUT_BACK,
	ENTER = KEY_INPUT_RETURN,
	ESCAPE = KEY_INPUT_ESCAPE,
	SPACE = KEY_INPUT_SPACE,
	TAB = KEY_INPUT_TAB,

	A = KEY_INPUT_A,
	B = KEY_INPUT_B,
	C = KEY_INPUT_C,
	D = KEY_INPUT_D,
	E = KEY_INPUT_E,
	F = KEY_INPUT_F,
	G = KEY_INPUT_G,
	H = KEY_INPUT_H,
	I = KEY_INPUT_I,
	J = KEY_INPUT_J,
	K = KEY_INPUT_K,
	L = KEY_INPUT_L,
	M = KEY_INPUT_M,
	N = KEY_INPUT_N,
	O = KEY_INPUT_O,
	P = KEY_INPUT_P,
	Q = KEY_INPUT_Q,
	R = KEY_INPUT_R,
	S = KEY_INPUT_S,
	T = KEY_INPUT_T,
	U = KEY_INPUT_U,
	V = KEY_INPUT_V,
	W = KEY_INPUT_W,
	X = KEY_INPUT_X,
	Y = KEY_INPUT_Y,
	Z = KEY_INPUT_Z,

	LSHIFT = KEY_INPUT_LSHIFT,
	RSHIFT = KEY_INPUT_RSHIFT,
	LCTRL = KEY_INPUT_LCONTROL,
	RCTRL = KEY_INPUT_RCONTROL,



	//KEY_INPUT_PGUP			
	//KEY_INPUT_PGDN			
	//KEY_INPUT_END				
	//KEY_INPUT_HOME			
	//KEY_INPUT_INSERT			
	//KEY_INPUT_DELETE			
	//
	//KEY_INPUT_MINUS			
	//KEY_INPUT_YEN				
	//KEY_INPUT_PREVTRACK		
	//KEY_INPUT_PERIOD			
	//KEY_INPUT_SLASH			
	//KEY_INPUT_LALT			
	//KEY_INPUT_RALT			
	//KEY_INPUT_SCROLL			
	//KEY_INPUT_SEMICOLON		
	//KEY_INPUT_COLON			
	//KEY_INPUT_LBRACKET		
	//KEY_INPUT_RBRACKET		
	//KEY_INPUT_AT				
	//KEY_INPUT_BACKSLASH		
	//KEY_INPUT_COMMA			
	//KEY_INPUT_KANJI			
	//KEY_INPUT_CONVERT			
	//KEY_INPUT_NOCONVERT		
	//KEY_INPUT_KANA			
	//KEY_INPUT_APPS			
	//KEY_INPUT_CAPSLOCK		
	//KEY_INPUT_SYSRQ			
	//KEY_INPUT_PAUSE			
	//KEY_INPUT_LWIN			
	//KEY_INPUT_RWIN			
	//
	//KEY_INPUT_NUMLOCK			
	//KEY_INPUT_NUMPAD0			
	//KEY_INPUT_NUMPAD1			
	//KEY_INPUT_NUMPAD2			
	//KEY_INPUT_NUMPAD3			
	//KEY_INPUT_NUMPAD4			
	//KEY_INPUT_NUMPAD5			
	//KEY_INPUT_NUMPAD6			
	//KEY_INPUT_NUMPAD7			
	//KEY_INPUT_NUMPAD8			
	//KEY_INPUT_NUMPAD9			
	//KEY_INPUT_MULTIPLY		
	//KEY_INPUT_ADD				
	//KEY_INPUT_SUBTRACT		
	//KEY_INPUT_DECIMAL			
	//KEY_INPUT_DIVIDE			
	//KEY_INPUT_NUMPADENTER		
	//
	F1 = KEY_INPUT_F1,
	F2 = KEY_INPUT_F2,
	F3 = KEY_INPUT_F3,				
	F4 = KEY_INPUT_F4,
	F5 = KEY_INPUT_F5,				
	F6 = KEY_INPUT_F6,		
	F7 = KEY_INPUT_F7,				
	F8 = KEY_INPUT_F8,				
	F9 = KEY_INPUT_F9,				
	F10 = KEY_INPUT_F10,				
	F11 = KEY_INPUT_F11,			
	F12 = KEY_INPUT_F12,			

	KEY_0 = KEY_INPUT_0,
	KEY_1 = KEY_INPUT_1,
	KEY_2 = KEY_INPUT_2,
	KEY_3 = KEY_INPUT_3,
	KEY_4 = KEY_INPUT_4,
	KEY_5 = KEY_INPUT_5,
	KEY_6 = KEY_INPUT_6,
	KEY_7 = KEY_INPUT_7,
	KEY_8 = KEY_INPUT_8,
	KEY_9 = KEY_INPUT_9,

};

class Keyboard {
	int Key[256];		// �L�[�̓��͏�Ԋi�[�p�ϐ�
	int preKey[256];	//1�t���[���O�̓��͏��
	// KeyCode�̃L�[�̓��͏�Ԃ��擾����
	int getKey(KeyCode KeyCode);
	int getPreKey(KeyCode keycode);

public:
	Keyboard();
	// �L�[�̓��͏�ԍX�V
	void update();

	bool On(KeyCode keycode);
	bool Down(KeyCode keycode);
	bool Up(KeyCode keycode);
	bool Off(KeyCode keycode);
};
/*


typedef struct tagDINPUT_JOYSTATE
{
int						X ;								// �X�e�B�b�N�̂w���p�����[�^( -1000�`1000 )		���F�}�C�i�X�@�E�F�v���X
int						Y ;								// �X�e�B�b�N�̂x���p�����[�^( -1000�`1000 )		��F�}�C�i�X�@���F�v���X
int						Z ;								// �X�e�B�b�N�̂y���p�����[�^( -1000�`1000 )		���g�p
int						Rx ;							// �X�e�B�b�N�̂w����]�p�����[�^( -1000�`1000 )	�E�X�e�B�b�NX
int						Ry ;							// �X�e�B�b�N�̂x����]�p�����[�^( -1000�`1000 )	�E�X�e�B�b�NY
int						Rz ;							// �X�e�B�b�N�̂y����]�p�����[�^( -1000�`1000 )	���g�p
int						Slider[ 2 ] ;					// �X���C�_�[���		�Ȃ���I�I�I�I
unsigned int			POV[ 4 ] ;						// �n�b�g�X�C�b�`�S��( 0xffffffff:���͂Ȃ� 0:�� 4500:�E�� 9000:�E 13500:�E�� 18000:�� 22500:���� 27000:�� 31500:���� )�@�\���L�[
unsigned char			Buttons[ 32 ] ;					// �{�^���R�Q��( �����ꂽ�{�^���� 128 �ɂȂ� )
} DINPUT_JOYSTATE ;
#define PAD_INPUT_DOWN								(0x00000001)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_LEFT								(0x00000002)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_RIGHT								(0x00000004)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_UP								(0x00000008)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_A									(0x00000010)	// �`�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_B									(0x00000020)	// �a�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_C									(0x00000040)	// �b�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_X									(0x00000080)	// �w�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Y									(0x00000100)	// �x�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Z									(0x00000200)	// �y�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_L									(0x00000400)	// �k�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_R									(0x00000800)	// �q�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_START								(0x00001000)	// �r�s�`�q�s�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_M									(0x00002000)	// �l�{�^���`�F�b�N�}�X�N

*/


//�p�b�h����
enum class PadCode {
	A,			
	B,
	X,			
	Y,
	LB,			
	RB,
	BACK,
	START,
	LSTICK,
	RSTICK,
};
enum class PadAng {
	DOWN,
	LEFT,
	RIGHT,
	UP,
};

class GPad {
public:
	//enum PadType {
	//	one,
	//	two,
	//	three,
	//	four,
	//};
	enum class Pad {
		LEFT, RIGHT, UP, DOWN,
	};
	DINPUT_JOYSTATE input;		//���͏��
	DINPUT_JOYSTATE pre;		//�O�t���[���̓��͏��
	unsigned int padNum;		//�ڑ�����Ă���p�b�h�̐�

	GPad(int id);
	void update();
	unsigned int getPadNum();
	//bool onLeft();
	//bool onRight();
	//bool onUp();
	//bool onDown();
	bool On(PadCode input);
	bool Down(PadCode input);
	bool Up(PadCode input);
	bool Off(PadCode input);
	bool On(PadAng input);
	bool Down(PadAng input);
	bool Up(PadAng input);
	bool Off(PadAng input);

private:
	unsigned int padID;
};


//�}�E�X����
class Mouse {
	int x, y;				//���W
	int prex, prey;
	int wheel;				//�z�C�[���̏��
	int prewheel;
	unsigned int button[3];	//�{�^���̏��
	unsigned int prebutton[3];
	bool visible;			//�}�E�X�|�C���^�̕\���̗L��

public:
	void update();			//�X�V����
	Math::Vec getPos() const;		//�}�E�X���W���擾����
	int getWheel() const;			//�z�C�[���̏�Ԃ��擾����
	bool DownLeft();
	bool DownRight();
	bool DownCenter();
	bool OnLeft();
	bool OnRight();
	bool OnCenter();
	bool UpLeft();
	bool UpRight();
	bool UpCenter();
	bool OffLeft();
	bool OffRight();
	bool OffCenter();

};