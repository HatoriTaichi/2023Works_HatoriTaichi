#pragma once
#ifndef _ROUND_H_
#define _ROUND_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_ROUND_TEX (1)	//テクスチャの数
#define MAX_ROUNDDIGIT (2)	//残段数の桁数
#define ROUND_X (30)			//X
#define ROUND_Y (30)			//Y

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//ポリゴンの位置
	float fWidth;		//幅
	float fHeight;		//高さ
} Round;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitRound(void);
void UninitRound(void);
void UpdateRound(void);
void DrawRound(void);
void AddRound(int nRound);
int GetRound(void);
#endif