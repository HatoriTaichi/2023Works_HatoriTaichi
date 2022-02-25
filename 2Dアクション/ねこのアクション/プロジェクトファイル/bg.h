#pragma once
#ifndef _BG_H_
#define _BG_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_BG_TEX (12)		//テクスチャの数
#define MAX_BG (64)			//画像を出す数

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
} BG;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);
void SetBg(D3DXVECTOR3 pos, float fWigth, float fHeight, int nType);	//位置、幅、高さ、種類
#endif 
