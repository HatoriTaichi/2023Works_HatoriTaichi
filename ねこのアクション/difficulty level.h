#pragma once
#ifndef _DIFFICULTY_LEVE_H_
#define _DIFFICULTY_LEVE_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define TETTER_POS_00_X (SCREEN_WIDTH / 4)	//ESAYのX位置
#define TETTER_POS_00_Y (SCREEN_HEIGHT / 2)	//ESAYのY位置
#define TETTER_POS_01_X ((SCREEN_WIDTH / 4) * 3)	//NORMRのX位置
#define TETTER_POS_01_Y (SCREEN_HEIGHT / 2)	//NORMRのY位置
#define TETTER_POS_02_X (SCREEN_WIDTH / 2)	//HEARDのX位置
#define TETTER_POS_02_Y (SCREEN_HEIGHT / 2)	//HEARDのY位置
#define TETTER_X (100.0f)	//Xの半径
#define TETTER_Y (30.0f)	//Yの半径
#define MAX_LEVEL (3)		//レベルの数

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int	nType;			//種類
	bool nUse;			//使った状態
} LETTER;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitLetter(void);
void UninitLetter(void);
void UpdateLetter(void);
void DrawLetter(void);
void SetLetter(D3DXVECTOR3 pos, int nType);	//位置、種類
LETTER *GetLetter(void);
#endif 
