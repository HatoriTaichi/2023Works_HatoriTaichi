#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_ENEMY (128)				//敵の最大数
#define MAX_ENEMY_TEX (3)			//テクスチャの最大数
#define ENEMY_X_SIZE (60.0f)		//ポリゴンのXの半径サイズ
#define ENEMY_Y_SIZE (60.0f)		//ポリゴンのYの半径サイズ
#define G_POW (0.5f)				//重力の力
#define ES_BOS_MOVE_SPEED (-10.0f)	//イージーのステージボスの移動量
#define ENEMY_POS_X (0.0f + ENEMY_X_SIZE)	//敵の位置
#define ENEMY_POS_Y (SCREEN_HEIGHT)			//敵の位置

//---------------------------
//構造体の定義
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//ポリゴンの位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	int nLife;				//体力
	float fWidth;			//幅
	float fHeight;			//高さ
	int nType;				//種類
	bool bJump;				//ジャンプの状態
	bool bUse;				//使ってるかどうか
	bool bDamage;			//ダメージ
} ENEMY;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, int nType, int nLife);	//位置、移動量、幅、高さ、種類、体力
ENEMY *GetEnemy(void);
#endif 