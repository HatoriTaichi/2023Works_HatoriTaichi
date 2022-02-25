#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H
//---------------------------
//インクルードファイル
//---------------------------
#include "main.h"

//---------------------------
//マクロ定義
//---------------------------
#define MAX_PLAYER_MODEL (1)		//プレイヤーモデルの最大数
#define MAX_PLAYER_TEX (128)		//プレイヤーモデルのパーツのテクスチャの最大数
#define MAX_PLAYER_PARTS_NUM (1)	//プレイヤーモデルのパーツの最大数
#define MAX_PLAYER_KEY (8)			//プレイヤーモデルキーの最大数
#define G_PPOW (-0.1f)				//重力の力
#define JUMP_POW (3.5f)			//ジャンプ力

//---------------------------
//列挙型.モードの種類
//---------------------------
typedef enum
{
	PLAYER_STATE_NEUTRAL = 0,	//ニュートラル
	PLAYER_STATE_WALK,			//歩く
	PLAYER_STATE_ATTACK,		//攻撃
	PLAYER_STATE_MAX			//リストの数
} Playermodelstate;

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
} Playerkey;

typedef struct
{
	float nFrame;							//再生フレーム
	Playerkey aKey[MAX_PLAYER_PARTS_NUM];	//モデル毎のキー要素
} Playerkeyinfo;

typedef struct
{
	bool bLoop;								//ループするか
	int nNumKey;							//キーの総数
	Playerkeyinfo aKeyinfo[MAX_PLAYER_KEY];	//キーの情報(キーの総数分)
} Playermotioninfo;

typedef struct
{
	LPD3DXMESH pMesh;		//メッシュのポインタ
	LPD3DXBUFFER pBuffMat;	//マテリアルのポインタ
	DWORD pnNumMat;			//マテリアルの数
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 vtxMin, vtxMax;	//頂点の端情報
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	int nIdx;				//親モデルのインデックス
} Playermodel;


typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posold;		//前回の位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 apos[4];	//
	D3DXVECTOR3 avec[4];	//
	D3DXMATRIX mtxWold;		//ワールドマトリックス
	int nIdex;				//影の番号
	bool bLand;				//地面についてるか
	Playermodel aModel[MAX_PLAYER_PARTS_NUM];	//モデルのパーツ
	int nNumModel = MAX_PLAYER_PARTS_NUM;		//モデルのパーツ数
	Playermotioninfo aMotioninfo[PLAYER_STATE_MAX];	//モーション情報
	int nNumnMotion;		//モーション数
	bool bLoopMotion;		//ループするか
	int	nNumKey;			//キー数
	int nKey;				//キーNo
	float nMotion;			//モーションのカウント
	Playermodelstate aState;//モーション種類
	float fWidth = 25.0f;	//直径X
	float fHight = 50.0f;	//直径Y
	float fDepth = 25.0f;	//直径Z
	int nGun;
	bool bJump;				//ジャンプ
	bool bUse;				//使ってるか
} Player;

//---------------------------
//プロトタイプ宣言
//---------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Player *GetPlayer(void);
#endif