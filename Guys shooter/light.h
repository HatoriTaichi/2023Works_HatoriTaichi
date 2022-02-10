#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_LIGHT (3)			//ライトの数

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitLight(void);
void UninitLight(void);
void UpdateLight(void);
#endif