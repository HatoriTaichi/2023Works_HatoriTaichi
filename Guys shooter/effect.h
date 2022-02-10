#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_EFFECT (10000)	//影の最大数
#define MAX_EFFECT_TEX (EFFECT_TEX_MAX)
#define EFFECT_X (0.5f)		//影のX
#define EFFECT_Z (0.5f)		//影のY

//---------------------------
//列挙型.モードの種類
//---------------------------
typedef enum
{
	EFFECT_GUN = 0,		//銃
	EFFECT_DETH,		//死んだとき
	EFFECT_MAX			//リストの数
} EffectType;

typedef enum
{
	EFFECT_TEX_GUN = 0,		//銃
	EFFECT_TEX_DETH,		//死んだとき
	EFFECT_TEX_MAX			//リストの数
} Effecttextype;

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXMATRIX mtxView;		//ビルボード
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	float fWhith;			//幅
	float fHeiht;			//高さ
	float fDepht;			//奥行
	float fAlpha;			//α
	EffectType aType;		//種類
	Effecttextype aTex;		//テクスチャ種類
	int nLife;				//消滅カウント
	bool bUse;				//使ってるかどうか
} Effect;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWhith, float fHeight, EffectType aType, Effecttextype aTex, int nLife);	//位置、幅、高さ
#endif