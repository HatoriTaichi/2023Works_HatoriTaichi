#pragma once
#ifndef _FADE_H_
#define _FADE_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//列挙型
//---------------------------
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
} FADE;

//---------------------------
//マクロ定義
//---------------------------
#define FADE_POLYGON_WIDTH (1280)
#define FADE_POLYGON_HEIGHT (720)

//---------------------------
//プロトタイプ宣言
//---------------------------
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE modeNext);
FADE GetFade(void);
#endif 
