#pragma once
#ifndef _BULLET_H
#define _BULLET_H
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define BULLET_MOVE_SPEED (50.0f)	//弾の速さ
#define BULlET_SCALE_X (5.0f)	//スケールサイズ
#define BULLET_SCALE_Y (5.0f)	//スケールサイズ
#define BULLET_X (1.0f)	//玉サイズX半径
#define BULLET_Y (1.0f)	//玉サイズY半径
#define MAX_BULLET (256)			//玉の最大数
#define MAX_BULLET_TEX (1)			//テクスチャの最大数
#define BULLET_SPAN (10)			//弾のクールタイム

//---------------------------
//列挙型
//---------------------------
typedef enum
{
	BULLET_ASULT = 0,	//アサルトライフルの弾
	BULLET_MAX,			//リストの数
} Bullettype;

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 apos[4];	//
	D3DXVECTOR3 avec[4];	//
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	D3DXMATRIX mtxView;		//カメラの向き
	Bullettype aType;		//種類
	float fWidth;			//幅
	float fHeight;			//高さ
	int nIdex;				//影の番号	
	bool bUse;				//使ってるか
} Bullet;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, float fWidth, float fHeight, Bullettype aType);	//位置、向き、移動量、幅、高さ、種類
Bullet *GetBullet(void);
#endif