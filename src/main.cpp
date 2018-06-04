#include "DxLib.h"
#include "Console\Console.h"
#include ".\define.h"
#include "Input\Input.h"
#include "Object\Object.h"
#include "Actor\Game.h"

//-------------------------------------------------------------------------------------------------------------------
//メインループの処理をまとめる
int ProcessLoop() {
	if (ScreenFlip() != 0) return -1;
	if (ProcessMessage() != 0) return -1;
	if (ClearDrawScreen() != 0) return -1;
	return 0;
}
//-------------------------------------------------------------------------------------------------------------------
//初期化関連をまとめる
void DXinit() {
	SetOutApplicationLogValidFlag(FALSE);			//ログ消し
	SetMainWindowText("Maze");						//ウインドウタイトルを変更
	SetGraphMode(1920, 1080, 16);	//画面解像度、色深度バッファ？変更
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//画面サイズ変更
	ChangeWindowMode(true);							//ウィンドウモード変更
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);		//初期化
	DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);	//裏画面設定
}
//-------------------------------------------------------------------------------------------------------------------




int Object::uid_ = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ShowConsole();
	DXinit();

	while (ProcessLoop() == 0) {
		game->doAll();
		if (game->kb.Down(ESCAPE)) { break; }
	};

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}