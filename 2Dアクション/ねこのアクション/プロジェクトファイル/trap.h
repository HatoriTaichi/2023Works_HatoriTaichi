#pragma once
#ifndef _TRAP_H_
#define _TRAP_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define TRAP_X_SIZE (20.0f)	//ポリゴンの半径Xサイズ
#define TRAP_Y_SIZE (20.0f)	//ポリゴンの半径Yサイズ
#define MAX_TEX_TRAP (4)	//トラップのテクスチャ数
#define MAX_TRAP (128)		//ブロックの最大数

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posold;	//前回の位置
	D3DXVECTOR3 move;	//移動量
	float fWidth;		//幅
	float fHeight;		//高さ
	float fTexwidth;	//テクスチャの幅
	float fTexheigth;	//テクスチャの高さ
	int nType;			//しゅるい
	bool bUse;			//使ってるかどうか
} TRAP;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitTrap(void);
void UninitTrap(void);
void UpdateTrap(void);
void DrawTrap(void);
void SetTrap(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexwidth, float fTexheight, int nType);	//位置、移動量、横幅、高さ、テクスチャの幅、テクスチャの高さ、種類
TRAP *GetTrap(void);
#endif 