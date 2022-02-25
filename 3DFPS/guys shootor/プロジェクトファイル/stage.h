#pragma once
#ifndef _STAGE_H
#define _STAGE_H
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_STAGE_MODEL (64)		//プレイヤーモデルの最大数
#define MAX_STAGE_TEX (128)		//プレイヤーモデルのパーツのテクスチャの最大数

//---------------------------
//列挙型
//---------------------------
typedef enum
{
	STAGE_FLOO_00 = 0,	//床0
	STAGE_FENCE_00,		//柵0
	STAGE_MOVEFLOO_00,	//移動床
	STAGE_MODEL_MAX			//リストの数
} MODEL_TYPE;

//---------------------------
//構造体
//---------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 apos[4];	//
	D3DXVECTOR3 avec[4];	//
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	D3DXVECTOR3 vtxMinModel, vtxMaxModel;	//頂点の端情報
	DWORD pnNumMat;			//マテリアルの数
	LPD3DXMESH pMesh;		//メッシュのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアルのポインタ
	MODEL_TYPE aType;		//種類
	float fWidth;			//
	float fHight;			//
	float fDepth;			//
	int nIdex;				//影の番号
	bool bUse;				//使ってるか
} Stage;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);
void SetStage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, MODEL_TYPE Type);	//位置、向き、種類
bool CollisionStage(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType);
Stage *GetStage(void);
#endif