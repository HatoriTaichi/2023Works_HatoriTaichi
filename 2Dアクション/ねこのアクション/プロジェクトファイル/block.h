#pragma once
#ifndef _BLOCK_H_
#define _BLOCK_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define BLOCK_X_SIZE (20.0f)	//ポリゴンの半径Xサイズ
#define BLOCK_Y_SIZE (20.0f)	//ポリゴンの半径Yサイズ
#define MAX_BLOCK (256)			//ブロックの最大数
#define MAX_BLOCK_TEX (3)		//テクスチャの最大数

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 nowmove;//現在の移動量
	float fWidth;		//幅
	float fHeight;		//高さ
	float fTexwidth;	//テクスチャの幅
	float fTexheigth;	//テクスチャの高さ
	int nType;			//ブロックの種類
	bool bPuse;			//透明ぶろっく
	bool bUse;			//使ってるかどうか
} BLOCK;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexwidth, float fTexheight, int nType);	//位置、移動量、横幅、高さ、テクスチャの幅、テクスチャの高さ、種類
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float fWidth, float fHeight, int nType);	//現在位置、前回位置、移動量、横幅、縦幅、種類
BLOCK *GetBlock(void);
#endif 