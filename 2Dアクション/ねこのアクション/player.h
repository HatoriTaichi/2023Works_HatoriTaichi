#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define PLAYER_X_SIZE (60.0f)	//ポリゴンのXの半径サイズ
#define PLAYER_Y_SIZE (60.0f)	//ポリゴンのYの半径サイズ
#define G_POW (0.5f)			//重力の力
#define JAMP_POW (-14.0f)		//ジャンプ力
#define JAMP_MOVE_POW (-5.0)	//移動ジャンプ
#define MOVE_SPEED (3.0)		//移動量

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//ポリゴンの位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	float fWidth;			//幅
	float fHeight;			//高さ
	int nLevel;				//レベル解放
	bool bJamp;				//ジャンプの状態
	bool bUse;				//使ってるかどうか
} PLAYER;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetPlayer(D3DXVECTOR3 pos, float fWidth, float fHeight);	//位置、幅、高さ
PLAYER *GetPlayer(void);
#endif 
