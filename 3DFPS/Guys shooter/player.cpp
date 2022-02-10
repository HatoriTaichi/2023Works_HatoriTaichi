//---------------------------
//インクルードファイル
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "player.h"
#include "shadow.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "camara.h"
#include "stage.h"
#include "bullet.h"
#include "guninfo.h"
#include "fade.h"
#include "guys.h"
#include "round.h"
#include "gunmodel.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9	g_apTexturePlayer[MAX_PLAYER_PARTS_NUM][MAX_PLAYER_TEX] = {};	//テクスチャのポインタ
Player				g_aPlayer;	//自分の構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	//---------------------------------
	//プレイヤー(パーツ)情報の初期化
	//---------------------------------
	g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aPlayer.nMotion = 0.0f;
	g_aPlayer.nKey = 0;
	g_aPlayer.aState = PLAYER_STATE_NEUTRAL;
	g_aPlayer.nIdex = 0;
	g_aPlayer.bUse = false;
	g_aPlayer.bJump = true;

	for (int nCntParts = 0; nCntParts < MAX_PLAYER_PARTS_NUM; nCntParts++)
	{
		g_aPlayer.aModel[nCntParts].vtxMax = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
		g_aPlayer.aModel[nCntParts].vtxMin = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);
		g_aPlayer.aModel[nCntParts].pBuffMat = {};
		g_aPlayer.aModel[nCntParts].pMesh = {};
	}

	//---------------------------
	//Xファイルの読み込み
	//---------------------------
	D3DXLoadMeshFromX(	"data/Model/Player/guys1.4_body.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_aPlayer.aModel[0].pBuffMat,
						NULL,
						&g_aPlayer.aModel[0].pnNumMat,
						&g_aPlayer.aModel[0].pMesh);

	//---------------------------
	//パーツの階層構造
	//---------------------------
	g_aPlayer.aModel[0].nIdx = -1;								//親モデルのインデックス(親が無い(原点)は-1)
	g_aPlayer.aModel[0].pos = D3DXVECTOR3(0.0f, 2.5f, 0.0f);	//位置(オフセット)
	g_aPlayer.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

	//---------------------------
	//頂点座標の抜き出し
	//---------------------------
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファのポインタ

	for (int nCntModel = 0; nCntModel < g_aPlayer.nNumModel; nCntModel++)
	{
		//頂点数を取得
		nNumVtx = g_aPlayer.aModel[nCntModel].pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aPlayer.aModel[nCntModel].pMesh->GetFVF());

		//頂点バッファのロック
		g_aPlayer.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

			//頂点数を比較して最小値、最大値を抜く
			//X
			if (g_aPlayer.aModel[nCntModel].vtxMax.x <= vtx.x)
			{
				g_aPlayer.aModel[nCntModel].vtxMax.x = vtx.x;
			}
			if (g_aPlayer.aModel[nCntModel].vtxMin.x >= vtx.x)
			{
				g_aPlayer.aModel[nCntModel].vtxMin.x = vtx.x;
			}
			//Y
			if (g_aPlayer.aModel[nCntModel].vtxMax.y <= vtx.y)
			{
				g_aPlayer.aModel[nCntModel].vtxMax.y = vtx.y;
			}
			if (g_aPlayer.aModel[nCntModel].vtxMin.y >= vtx.y)
			{
				g_aPlayer.aModel[nCntModel].vtxMin.y = vtx.y;
			}
			//Z
			if (g_aPlayer.aModel[nCntModel].vtxMax.z <= vtx.z)
			{
				g_aPlayer.aModel[nCntModel].vtxMax.z = vtx.z;
			}
			if (g_aPlayer.aModel[nCntModel].vtxMin.z >= vtx.z)
			{
				g_aPlayer.aModel[nCntModel].vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	//頂点を進める
		}
		//頂点バッファをアンロック
		g_aPlayer.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}
	g_aPlayer.nGun = SetGunModel(g_aPlayer.pos, g_aPlayer.rot, HANDGUN);
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitPlayer(void)
{
	for (int nCntModelNum = 0; nCntModelNum < g_aPlayer.nNumModel; nCntModelNum++)
	{
		//---------------------------
		//メッシュ破棄
		//---------------------------
		if (g_aPlayer.aModel[nCntModelNum].pMesh != NULL)
		{
			g_aPlayer.aModel[nCntModelNum].pMesh->Release();
			g_aPlayer.aModel[nCntModelNum].pMesh = NULL;
		}

		//---------------------------
		//マテリアル破棄
		//---------------------------
		if (g_aPlayer.aModel[nCntModelNum].pBuffMat != NULL)
		{
			g_aPlayer.aModel[nCntModelNum].pBuffMat->Release();
			g_aPlayer.aModel[nCntModelNum].pBuffMat = NULL;
		}
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdatePlayer(void)
{
	Camera	*pCamera;
	static Guntype aGunType;
	int		nRound = GetRound();
	int		nRemaining = GetRemaining();
	static int nBulletSpan;

	nBulletSpan++;

	pCamera = GetCamera();

	//前回の位置を保存
	g_aPlayer.posold = g_aPlayer.pos;

	//カメラの向きに動機
	g_aPlayer.rot.y = pCamera->Rot.y;

	//重力の力
	g_aPlayer.move.y += G_PPOW;

	//重力を加える
	g_aPlayer.pos += g_aPlayer.move;

	if (CollisionStage(&g_aPlayer.pos, &g_aPlayer.posold, &g_aPlayer.move, g_aPlayer.fWidth, g_aPlayer.fHight, g_aPlayer.fDepth, 0) == true)
	{
		g_aPlayer.bJump = true;
	}
	if (MouseDowan(MOUSE_LEFT_BOTTON) == true && nRemaining > 0 && nBulletSpan > 20)
	{
		PlaySound(SOUND_SHOT_00);
		SetBullet(D3DXVECTOR3(g_aPlayer.pos.x, g_aPlayer.pos.y + 25.0f, g_aPlayer.pos.z), pCamera->Rot, D3DXVECTOR3(sinf(pCamera->Rot.y) * BULLET_MOVE_SPEED, sinf(pCamera->Rot.x) * BULLET_MOVE_SPEED, cosf(pCamera->Rot.y) * BULLET_MOVE_SPEED), BULlET_SCALE_X, BULLET_SCALE_Y, BULLET_ASULT);
		AddRemaining(-1);
		nBulletSpan = 0;
	}
	if (GetKeyboardTrigger(DIK_R) == true)
	{
		if (aGunType == HANDGUN)
		{
			PlaySound(SOUND_RELOAD_00);
			SetGunType(GUNINFO_TYPE_00);
		}
		else if (aGunType == ASULTRIFLE)
		{
			PlaySound(SOUND_RELOAD_00);
			SetGunType(GUNINFO_TYPE_01);
		}
	}
	if (GetKeyboardTrigger(DIK_SPACE) == true && g_aPlayer.bJump == true)
	{
		g_aPlayer.move.y = JUMP_POW;
		g_aPlayer.bJump = false;
	}
	if (g_aPlayer.move.y > 0.0f)
	{
		pCamera->PosR.y = pCamera->PosR.y + g_aPlayer.move.y;
	}
	else if (g_aPlayer.move.y < 0.0f)
	{
		pCamera->PosR.y = pCamera->PosR.y + g_aPlayer.move.y;
	}

	if (GetMode() == MODE_GAME)
	{
		//下に落ちたら
		if (g_aPlayer.pos.y <= -2000.0f && GetFade() == FADE_NONE)
		{
			StopSound(SOUND_GAME_BGM);
			SetFade(MODE_RESULT);
		}
		if (CollisionGuys(&g_aPlayer.pos, &g_aPlayer.posold, &g_aPlayer.move, 50.0f, 50.0f, COLLISION_PLAYER) == true && GetFade() == FADE_NONE)
		{
			StopSound(SOUND_GAME_BGM);
			SetFade(MODE_RESULT);
		}
		if (CollisionGunModel(&g_aPlayer.pos, &g_aPlayer.posold, &g_aPlayer.move, 50.0f, 50.0f, &g_aPlayer.nGun) == true)
		{

		}
	}
	if (GetMode() == MODE_OPERATION)
	{
		if (g_aPlayer.pos.y <= -2000.0f && GetFade() == FADE_NONE)
		{
			pCamera->PosV = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
			g_aPlayer.pos = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
		}
	}

#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_aPlayer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
#endif

	//影
	SetPointShadow(g_aPlayer.nIdex, g_aPlayer.pos, 30.0f, 30.0f, g_aPlayer.bUse);
	aGunType = SetPointGunModel(g_aPlayer.pos, pCamera->Rot, g_aPlayer.nGun);
}

//---------------------------
//描画処理
//---------------------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//-------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//-------------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

	D3DXMatrixIdentity(&g_aPlayer.mtxWold);	//マトリックス初期化

	//向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									g_aPlayer.rot.y,
									g_aPlayer.rot.x,
									g_aPlayer.rot.z);

	D3DXMatrixMultiply(	&g_aPlayer.mtxWold,
						&g_aPlayer.mtxWold,
						&mtxRot);
	//位置
	D3DXMatrixTranslation(	&mtxTrans,
							g_aPlayer.pos.x,
							g_aPlayer.pos.y,
							g_aPlayer.pos.z);

	D3DXMatrixMultiply(	&g_aPlayer.mtxWold,
						&g_aPlayer.mtxWold,
						&mtxTrans);
	//マトリックスの設定
	pDevice->SetTransform(	D3DTS_WORLD,
							&g_aPlayer.mtxWold);

	//---------------------------------
	//モデルパーツのマトリックスの設定
	//---------------------------------
	for (int nCntModel = 0; nCntModel < g_aPlayer.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用マトリックス
		D3DXMATRIX mtxParent;					//親のマトリックス

		D3DXMatrixIdentity(&g_aPlayer.aModel[nCntModel].mtxWold);	//マトリックス初期化

		//向きの設定
		D3DXMatrixRotationYawPitchRoll(	&mtxRotModel,
										g_aPlayer.aModel[nCntModel].rot.y,
										g_aPlayer.aModel[nCntModel].rot.x,
										g_aPlayer.aModel[nCntModel].rot.z);

		D3DXMatrixMultiply(	&g_aPlayer.aModel[nCntModel].mtxWold,
							&g_aPlayer.aModel[nCntModel].mtxWold,
							&mtxRotModel);
		//位置
		D3DXMatrixTranslation(	&mtxTransModel,
								g_aPlayer.aModel[nCntModel].pos.x,
								g_aPlayer.aModel[nCntModel].pos.y,
								g_aPlayer.aModel[nCntModel].pos.z);

		D3DXMatrixMultiply(	&g_aPlayer.aModel[nCntModel].mtxWold,
							&g_aPlayer.aModel[nCntModel].mtxWold,
							&mtxTransModel);

		//パーツの親のマトリックスを設定
		//もし親がいたら
		if (g_aPlayer.aModel[nCntModel].nIdx != -1)
		{
			mtxParent = g_aPlayer.aModel[g_aPlayer.aModel[nCntModel].nIdx].mtxWold;
		}
		else
		{
			mtxParent = g_aPlayer.mtxWold;
		}

		//パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
		D3DXMatrixMultiply(	&g_aPlayer.aModel[nCntModel].mtxWold,
							&g_aPlayer.aModel[nCntModel].mtxWold,
							&mtxParent);

		//マトリックスの設定
		pDevice->SetTransform(	D3DTS_WORLD,
								&g_aPlayer.aModel[nCntModel].mtxWold);

		//---------------------------
		//描画処理
		//---------------------------
		D3DMATERIAL9		matDef;				//マテリアルの一時保存
		D3DXMATERIAL		*pMat;				//マテリアルデータのポインタ

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータのポインタ
		pMat = (D3DXMATERIAL*)g_aPlayer.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aPlayer.aModel[nCntModel].pnNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_apTexturePlayer[nCntModel][nCntMat]);

			//モデルパーツの描画
			g_aPlayer.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
		//一時保存してたやつをもどす
		pDevice->SetMaterial(&matDef);
	}
}

//---------------------------
//セット
//---------------------------
void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Camera *pCamera = GetCamera();

	if (g_aPlayer.bUse == false)
	{
		g_aPlayer.pos = pos;
		pCamera->PosV = pos;
		g_aPlayer.rot = rot;

		//影を付ける
		g_aPlayer.nIdex = SetShadow(g_aPlayer.pos, 30.0f, 30.0f);
		g_aPlayer.bUse = true;
	}
}

//---------------------------
//プレイヤー情報
//---------------------------
Player *GetPlayer(void)
{
	return &g_aPlayer;
}
