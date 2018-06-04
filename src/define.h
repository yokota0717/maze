#pragma once
#include "DxLib.h"
#include "Math\Math.h"

const int SCREEN_WIDTH = 1440,
SCREEN_HEIGHT = 810;

const int debugRed = GetColor(255, 50, 50);
const int lineColor = GetColor(200, 200, 200);
const int blue = GetColor(50, 50, 255);

//DXライブラリの描画関数をラッピング
void DrawImage(Math::Box2D draw, Math::Box2D src, int handle);
void DrawImageRotate(Math::Box2D draw, Math::Box2D src, int handle, float radian);
void DrawBox2D(Math::Box2D draw, int color, bool fill = false);
void DrawLineF(float x1, float y1, float x2, float y2, int color, int thickness = 1);
