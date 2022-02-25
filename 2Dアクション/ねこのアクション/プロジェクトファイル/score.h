#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_SCOREDIGIT (5)	//スコアの桁数
#define SCORE_Y (25)		//半径
#define SCORE_X (25)		//半径

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
} Score;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int nVolue);
int GetScore(void);
#endif