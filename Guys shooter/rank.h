#pragma once
#ifndef _RANK_H_
#define _RANK_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_RANK (3)		//ランキングの数
#define RANK_Y (25 * 2)		//半径
#define RANK_X (25 * 2)		//半径

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
} RANK;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitRank(void);
void UninitRank(void);
void UpdateRank(void);
void DrawRank(void);
#endif