#pragma once
#ifndef _GUYS_H_
#define _GUYS_H_
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_GUYS (30)
#define MAX_GUYS_NUM (9)
#define G_GPOW (-0.5f)

//---------------------------
//列挙型.モードの種類
//---------------------------
typedef enum
{
	GUYS_STATE_NEUTRAL = 0,	//ニュートラルモーション
	GUYS_STATE_WORK,			//歩く
	GUYS_STATE_MAX			//リストの数
} Guysstate;

typedef enum
{
	COLLISION_PLAYER = 0,
	COLLISION_BULLET,
	COLLISION_MAX
} CollisionType;

//---------------------------
//構造体
//---------------------------
typedef struct
{
	float fPosX;	//位置X
	float fPosY;	//位置Y
	float fPosZ;	//位置Z
	float fRotX;	//向きX
	float fRotY;	//向きY
	float fRotZ;	//向きZ
} Key;

typedef struct
{
	float nFrame;					//再生フレーム
	Key aKey[MAX_GUYS_NUM];	//モデル毎のキー要素
} Keyinfo;

typedef struct
{
	bool bLoop;				//ループするか
	int nNumKey;			//キーの総数
	Keyinfo aKeyinfo[8];	//キーの情報(キーの総数分)
} Motioninfo;

typedef struct
{
	LPD3DXMESH pMesh;			//メッシュのポインタ
	LPD3DXBUFFER pBuffMat;		//マテリアルのポインタ
	DWORD pnNumMat;				//マテリアルの数
	D3DXVECTOR3 PosModel;		//位置
	D3DXVECTOR3 RotModel;		//向き
	D3DXVECTOR3 vtxMin, vtxMax;	//頂点の端情報
	D3DXMATRIX mtxWold;			//ワールドマトリックス
	int nIdx;					//親モデルのインデックス
} Guysmodel;

typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 posold;						//前回の位置
	D3DXVECTOR3 move;						//移動量
	D3DXVECTOR3 posdfrc;					//差分
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 apos[4];					//
	D3DXVECTOR3 avec[4];					//
	D3DXMATRIX mtxWold;						//ワールドマトリックス
	D3DXMATRIX mtxView;						//カメラの向き
	int nIdex;								//影の番号
	bool bLand;								//地面についてるか
	Guysmodel aModel[MAX_GUYS_NUM];			//モデルのパーツ
	int nNumModel = MAX_GUYS_NUM;			//モデルのパーツ数
	Motioninfo aMotioninfo[GUYS_STATE_MAX];	//モーション情報
	int nNumnMotion;						//モーション数
	bool bLoopMotion;						//ループするか
	int	nNumKey;							//キー数
	int nKey;								//キーNo
	int nLife;								//体力
	float fMoveSpeed;
	float fWidth = 25.0f;					//直径X
	float fHight = 25.0f;					//直径Y
	float fDepth = 25.0f;					//直径Z
	float fMotion;							//モーションのカウント
	Guysstate aState;						//モーション種類
	bool bUse;								//使ってるか
} Guys;
//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitGuys(void);
void UninitGuys(void);
void UpdateGuys(void);
void DrawGuys(void);
void SetGuys(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, float fMoveSpeed);
bool CollisionGuys(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, CollisionType nType);
int GetDeth(void);
void ResetsDeth(void);
Guys *GetGuys(void);
#endif