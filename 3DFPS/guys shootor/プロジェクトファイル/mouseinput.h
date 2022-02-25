#pragma once
#ifndef _MOUSE_INPUT_H_
#define _MOUSE_INPUT_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MOUSE_LEFT_BOTTON (0)	//左クリック
#define MOUSE_RIGHT_BOTTON (1)	//右クリック
#define MOUSE_WHEEL_BOTTON (2)	//ホイールクリック

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
bool MouseDowan(int Botton_Type);
#endif