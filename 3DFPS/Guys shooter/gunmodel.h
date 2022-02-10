#pragma once
#ifndef _GUNMODEL_H_
#define _GUNMODEL_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_GUN_MODEL (32)	//モデルの数
#define MAX_GUN_TEX (128)	//テクスチャの数

//---------------------------
//列挙型
//---------------------------
typedef enum
{
	HANDGUN = 0,	//ハンドガン
	ASULTRIFLE,		//アサルト
	GUN_MODELMAX,	//リストの数
} Guntype;

//---------------------------
//構造体
//---------------------------
typedef struct
{
	DWORD pnNumMat;		//マテリアルの数
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 vtxMin, vtxMax;	//頂点の端情報
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	D3DXMATRIX mtxView;		//カメラの向き
	LPD3DXMESH pMesh;		//メッシュのポインタ
	LPD3DXBUFFER pBuffMat;//マテリアルのポインタ
	Guntype aType;			//種類
	int nCnt;
	bool bUse;					//使ってるか
} Gunmodel;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitGunModel(void);
void UninitGunModel(void);
void UpdateGunModel(void);
void DrawGunModel(void);
int SetGunModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, Guntype Type);
Guntype SetPointGunModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx);
bool CollisionGunModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, int *nIdx);
#endif