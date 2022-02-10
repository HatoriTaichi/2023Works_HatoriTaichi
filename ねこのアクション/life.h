#pragma once
#ifndef _LIFE_H_
#define _LIFE_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define LIFE_Y (25)		//半径
#define LIFE_X (75)		//半径
#define MAX_LIFE (10)	//体力の数

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
} LIFE;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void AddLife(int nMinus);
#endif