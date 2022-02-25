#pragma once
#ifndef _PAUSE_H_
#define _PAUSE_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_PAUSE_TEX (3)		//テクスチャの数
#define MAX_PAUSE (3)			//画像を出す数
#define PAUSE_X (200.0f)		//Xのサイズ
#define PAUSE_Y (50.0f)			//Yのサイズ1

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3  pos;		//ポリゴンの位置
	float		 fWidth;	//幅
	float		 fHeight;	//高さ
	int			 nType;		//種類
	bool		 bUse;		//使ってるかどうか
} PAUSE;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitPause(void);
void UninitPause(void);
bool UpdatePause(void);
void DrawPause(void);
#endif 
