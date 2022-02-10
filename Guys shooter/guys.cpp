//---------------------------
//インクルードファイル
//---------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guys.h"
#include "shadow.h"
#include "stage.h"
#include "player.h"
#include "bullet.h"
#include "effect.h"
#include "gunmodel.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
Guys					g_aGuys[MAX_GUYS];	//guys
int						g_nCntDeth;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitGuys(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntModel = 0; nCntModel < MAX_GUYS; nCntModel++)
	{
		//---------------------------
		//Xファイルの読み込み
		//---------------------------
		D3DXLoadMeshFromX(	"data/Model/guys/guys1.4_body.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aGuys[nCntModel].aModel[0].pBuffMat,
							NULL,
							&g_aGuys[nCntModel].aModel[0].pnNumMat,
							&g_aGuys[nCntModel].aModel[0].pMesh);
		D3DXLoadMeshFromX(	"data/Model/guys/guys1.4_rigthhand.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aGuys[nCntModel].aModel[1].pBuffMat,
							NULL,
							&g_aGuys[nCntModel].aModel[1].pnNumMat,
							&g_aGuys[nCntModel].aModel[1].pMesh);
		D3DXLoadMeshFromX(	"data/Model/guys/guys1.4_rigthhand_up.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aGuys[nCntModel].aModel[2].pBuffMat,
							NULL,
							&g_aGuys[nCntModel].aModel[2].pnNumMat,
							&g_aGuys[nCntModel].aModel[2].pMesh);
		D3DXLoadMeshFromX(	"data/Model/guys/guys1.4_lefthand.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aGuys[nCntModel].aModel[3].pBuffMat,
							NULL,
							&g_aGuys[nCntModel].aModel[3].pnNumMat,
							&g_aGuys[nCntModel].aModel[3].pMesh);
		D3DXLoadMeshFromX(	"data/Model/guys/guys1.4_lefthand_up.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aGuys[nCntModel].aModel[4].pBuffMat,
							NULL,
							&g_aGuys[nCntModel].aModel[4].pnNumMat,
							&g_aGuys[nCntModel].aModel[4].pMesh);
		D3DXLoadMeshFromX(	"data/Model/guys/guys1.4_rigthleg.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aGuys[nCntModel].aModel[5].pBuffMat,
							NULL,
							&g_aGuys[nCntModel].aModel[5].pnNumMat,
							&g_aGuys[nCntModel].aModel[5].pMesh);
		D3DXLoadMeshFromX(	"data/Model/guys/guys1.4_rigthleg_down.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aGuys[nCntModel].aModel[6].pBuffMat,
							NULL,
							&g_aGuys[nCntModel].aModel[6].pnNumMat,
							&g_aGuys[nCntModel].aModel[6].pMesh);
		D3DXLoadMeshFromX(	"data/Model/guys/guys1.4_leftleg.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aGuys[nCntModel].aModel[7].pBuffMat,
							NULL,
							&g_aGuys[nCntModel].aModel[7].pnNumMat,
							&g_aGuys[nCntModel].aModel[7].pMesh);
		D3DXLoadMeshFromX(	"data/Model/guys/guys1.4_leftleg_down.x",
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&g_aGuys[nCntModel].aModel[8].pBuffMat,
							NULL,
							&g_aGuys[nCntModel].aModel[8].pnNumMat,
							&g_aGuys[nCntModel].aModel[8].pMesh);

		//---------------------------
		//パーツの階層構造
		//---------------------------
		FILE *pFile = fopen("data/Motion/guys.txt", "r");
		char string[256][256];
		char INDEX[] = "INDEX";
		char MOSIONSET[] = "MOTIONSET";
		char KEYSET[] = "KEYSET";
		char END_KEYSET[] = "END_KEYSET";
		char KEY[] = "KEY";
		char END_MOTIONSET[] = "END_MOTIONSET";

		for (int nCntParts = 0; nCntParts < g_aGuys[nCntParts].nNumModel; nCntParts++)
		{
			while (fgets(string[0], 256, pFile) != NULL)
			{
				if (strstr(string[0], INDEX))
				{
					fscanf(pFile, "%s%s%d%*s%*s", string[1], string[2], &g_aGuys[nCntModel].aModel[nCntParts].nIdx);
					fscanf(pFile, "%s%s%f%f%f", string[3], string[4], &g_aGuys[nCntModel].aModel[nCntParts].PosModel.x, &g_aGuys[nCntModel].aModel[nCntParts].PosModel.y, &g_aGuys[nCntModel].aModel[nCntParts].PosModel.z);
					fscanf(pFile, "%s%s%f%f%f", string[5], string[6], &g_aGuys[nCntModel].aModel[nCntParts].RotModel.x, &g_aGuys[nCntModel].aModel[nCntParts].RotModel.y, &g_aGuys[nCntModel].aModel[nCntParts].RotModel.z);
					break;
				}
			}
			g_aGuys[nCntModel].aModel[nCntParts].vtxMax = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);
			g_aGuys[nCntModel].aModel[nCntParts].vtxMin = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);
		}
		//---------------------------
		//モーション
		//---------------------------
		for (int nCntMosion = 0; nCntMosion < GUYS_STATE_MAX; nCntMosion++)
		{
			while (fgets(string[0], 256, pFile) != NULL)
			{
				if (strstr(string[0], MOSIONSET))
				{
					fscanf(pFile, "%s%s%d%*s%*s%*s%*s", string[1], string[2], &g_aGuys[nCntModel].aMotioninfo[nCntMosion].bLoop);
					fscanf(pFile, "%s%s%d", string[3], string[4], &g_aGuys[nCntModel].aMotioninfo[nCntMosion].nNumKey);
					break;
				}
			}

			for (int nCntKey = 0; nCntKey < g_aGuys[nCntModel].aMotioninfo[nCntMosion].nNumKey; nCntKey++)
			{
				while (fgets(string[0], 256, pFile) != NULL)
				{
					if (strstr(string[0], KEYSET))
					{
						fscanf(pFile, "%s%s%f", string[1], string[2], &g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].nFrame);
						break;
					}
				}

				for (int nCntParts = 0; nCntParts < g_aGuys[nCntParts].nNumModel; nCntParts++)
				{
					while (fgets(string[0], 256, pFile) != NULL)
					{
						if (strstr(string[0], KEY))
						{
							fscanf(pFile, "%s%s%f%f%f", string[1], string[2], &g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosX, &g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosY, &g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ);
							fscanf(pFile, "%s%s%f%f%f%*s", string[3], string[4], &g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotX, &g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotY, &g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotZ);
							break;
						}
					}
				}
				while (fgets(string[0], 256, pFile) != NULL)
				{
					if (strstr(string[0], END_KEYSET))
					{
						break;
					}
				}
			}

			while (fgets(string[0], 256, pFile) != NULL)
			{
				if (strstr(string[0], END_MOTIONSET))
				{
					break;
				}
			}
		}

		fclose(pFile);

		for (int nCntMosion = 0; nCntMosion < GUYS_STATE_MAX; nCntMosion++)
		{
			for (int nCntKey = 0; nCntKey < g_aGuys[nCntModel].aMotioninfo[nCntMosion].nNumKey; nCntKey++)
			{
				for (int nCntParts = 0; nCntParts < g_aGuys[nCntParts].nNumModel; nCntParts++)
				{
					g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosX = g_aGuys[nCntModel].aModel[nCntParts].PosModel.x + g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosX;
					g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosY = g_aGuys[nCntModel].aModel[nCntParts].PosModel.y + g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosY;
					g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ = g_aGuys[nCntModel].aModel[nCntParts].PosModel.z + g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fPosZ;

					g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotX = g_aGuys[nCntModel].aModel[nCntParts].RotModel.x + g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotX;
					g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotY = g_aGuys[nCntModel].aModel[nCntParts].RotModel.y + g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotY;
					g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotZ = g_aGuys[nCntModel].aModel[nCntParts].RotModel.z + g_aGuys[nCntModel].aMotioninfo[nCntMosion].aKeyinfo[nCntKey].aKey[nCntParts].fRotZ;
				}
			}
		}

		//---------------------------
		//プレイヤー(原点)の設定
		//---------------------------
		g_aGuys[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGuys[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGuys[nCntModel].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aGuys[nCntModel].aState = GUYS_STATE_WORK;
		g_aGuys[nCntModel].nKey = 0;
		g_aGuys[nCntModel].fMotion = 0.0f;
		g_aGuys[nCntModel].nIdex = 0;
		g_aGuys[nCntModel].bUse = false;

		//---------------------------
		//頂点座標の抜き出し
		//---------------------------
		int nNumVtx;	//頂点数
		DWORD sizeFVF;	//頂点フォーマットのサイズ
		BYTE *pVtxBuff;	//頂点バッファのポインタ

		for (int nCntParts = 0; nCntParts < g_aGuys[nCntModel].nNumModel; nCntParts++)
		{
			//頂点数を取得
			nNumVtx = g_aGuys[nCntModel].aModel[nCntParts].pMesh->GetNumVertices();

			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_aGuys[nCntModel].aModel[nCntParts].pMesh->GetFVF());

			//頂点バッファのロック
			g_aGuys[nCntModel].aModel[nCntParts].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

				//頂点数を比較して最小値、最大値を抜く
				//X
				if (g_aGuys[nCntModel].aModel[nCntParts].vtxMax.x <= vtx.x)
				{
					g_aGuys[nCntModel].aModel[nCntParts].vtxMax.x = vtx.x;
				}
				if (g_aGuys[nCntModel].aModel[nCntParts].vtxMin.x >= vtx.x)
				{
					g_aGuys[nCntModel].aModel[nCntParts].vtxMin.x = vtx.x;
				}
				//Y
				if (g_aGuys[nCntModel].aModel[nCntParts].vtxMax.y <= vtx.y)
				{
					g_aGuys[nCntModel].aModel[nCntParts].vtxMax.y = vtx.y;
				}
				if (g_aGuys[nCntModel].aModel[nCntParts].vtxMin.y >= vtx.y)
				{
					g_aGuys[nCntModel].aModel[nCntParts].vtxMin.y = vtx.y;
				}
				//Z
				if (g_aGuys[nCntModel].aModel[nCntParts].vtxMax.z <= vtx.z)
				{
					g_aGuys[nCntModel].aModel[nCntParts].vtxMax.z = vtx.z;
				}
				if (g_aGuys[nCntModel].aModel[nCntParts].vtxMin.z >= vtx.z)
				{
					g_aGuys[nCntModel].aModel[nCntParts].vtxMin.z = vtx.z;
				}

				pVtxBuff += sizeFVF;	//頂点を進める
			}
			//頂点バッファをアンロック
			g_aGuys[nCntModel].aModel[nCntParts].pMesh->UnlockVertexBuffer();
		}
	}

	return S_OK;
}
//---------------------------
//終了処理
//---------------------------
void UninitGuys(void)
{
	for (int nCntModel = 0; nCntModel < MAX_GUYS; nCntModel++)
	{
		for (int nCntModelNum = 0; nCntModelNum < g_aGuys[nCntModel].nNumModel; nCntModelNum++)
		{
			//---------------------------
			//メッシュ破棄
			//---------------------------
			if (g_aGuys[nCntModel].aModel[nCntModelNum].pMesh != NULL)
			{
				g_aGuys[nCntModel].aModel[nCntModelNum].pMesh->Release();
				g_aGuys[nCntModel].aModel[nCntModelNum].pMesh = NULL;
			}

			//---------------------------
			//マテリアル破棄
			//---------------------------
			if (g_aGuys[nCntModel].aModel[nCntModelNum].pBuffMat != NULL)
			{
				g_aGuys[nCntModel].aModel[nCntModelNum].pBuffMat->Release();
				g_aGuys[nCntModel].aModel[nCntModelNum].pBuffMat = NULL;
			}
		}
	}
}
//---------------------------
//更新処理
//---------------------------
void UpdateGuys(void)
{
	Player *pPlayer;
	float fPosXAsk[MAX_GUYS][MAX_GUYS_NUM];		//求める値位置X
	float fPosYAsk[MAX_GUYS][MAX_GUYS_NUM];		//求める値位置Y
	float fPosZAsk[MAX_GUYS][MAX_GUYS_NUM];		//求める値位置Z
	float fRotXAsk[MAX_GUYS][MAX_GUYS_NUM];		//求める値向きX
	float fRotYAsk[MAX_GUYS][MAX_GUYS_NUM];		//求める値向きY
	float fRotZAsk[MAX_GUYS][MAX_GUYS_NUM];		//求める値向きZ
	float PosXDifference[MAX_GUYS][MAX_GUYS_NUM];	//位置の差分X
	float PosYDifference[MAX_GUYS][MAX_GUYS_NUM];	//位置の差分Y
	float PosZDifference[MAX_GUYS][MAX_GUYS_NUM];	//位置の差分Z
	float RotXDifference[MAX_GUYS][MAX_GUYS_NUM];	//向きの差分X
	float RotYDifference[MAX_GUYS][MAX_GUYS_NUM];	//向きの差分Y
	float RotZDifference[MAX_GUYS][MAX_GUYS_NUM];	//向きの差分Z

	pPlayer = GetPlayer();

	for (int nCntModel = 0; nCntModel < MAX_GUYS; nCntModel++)
	{
		//前回の位置
		g_aGuys[nCntModel].posold = g_aGuys[nCntModel].pos;
		if (g_aGuys[nCntModel].bUse == true)
		{
			//重力の力
			g_aGuys[nCntModel].move.y += G_GPOW;

			//重力を加える
			g_aGuys[nCntModel].pos.y += g_aGuys[nCntModel].move.y;

			//guysとプレイヤーの差分を入手
			g_aGuys[nCntModel].posdfrc = pPlayer->posold - g_aGuys[nCntModel].pos;

			if (g_aGuys[nCntModel].posdfrc.x >= 0.0f)
			{
				g_aGuys[nCntModel].move.x = g_aGuys[nCntModel].fMoveSpeed;
			}
			else if (g_aGuys[nCntModel].posdfrc.x <= 0.0f)
			{
				g_aGuys[nCntModel].move.x = -g_aGuys[nCntModel].fMoveSpeed;
			}
			if (g_aGuys[nCntModel].posdfrc.z >= 0.0f)
			{
				g_aGuys[nCntModel].move.z = g_aGuys[nCntModel].fMoveSpeed;
			}
			else if (g_aGuys[nCntModel].posdfrc.z <= 0.0f)
			{
				g_aGuys[nCntModel].move.z = -g_aGuys[nCntModel].fMoveSpeed;
			}

			if (GetMode() == MODE_GAME)
			{
				g_aGuys[nCntModel].pos.x += g_aGuys[nCntModel].move.x;
				g_aGuys[nCntModel].pos.z += g_aGuys[nCntModel].move.z;
			}

			if (CollisionStage(&g_aGuys[nCntModel].pos, &g_aGuys[nCntModel].posold, &g_aGuys[nCntModel].move, g_aGuys[nCntModel].fWidth, g_aGuys[nCntModel].fHight, g_aGuys[nCntModel].fDepth, 1) == true)
			{

			}

			//下に落ちたら
			if (g_aGuys[nCntModel].pos.y <= -2000.0f)
			{
				g_aGuys[nCntModel].bUse = false;
				g_nCntDeth++;
			}
			if (g_aGuys[nCntModel].posold.z <= 150.0f && g_aGuys[nCntModel].pos.z >= 150.0f)
			{
				g_aGuys[nCntModel].pos.z = 150.0f - g_aGuys[nCntModel].fDepth / 2;
			}
			else if (g_aGuys[nCntModel].posold.z >= 550.0f && g_aGuys[nCntModel].pos.z <= 550.0f)
			{
				g_aGuys[nCntModel].pos.z = 550.0f + g_aGuys[nCntModel].fDepth / 2;
			}

			//---------------------------
			//モーション
			//---------------------------
			if (g_aGuys[nCntModel].aState == GUYS_STATE_NEUTRAL)
			{
				if (g_aGuys[nCntModel].nKey == 0)
				{
					for (int nCntParts = 0; nCntParts < MAX_GUYS_NUM; nCntParts++)
					{
						PosXDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fPosX - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosX;
						PosYDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fPosY - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosY;
						PosZDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fPosZ - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosZ;

						RotXDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fRotX - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotX;
						RotYDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fRotY - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotY;
						RotZDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fRotZ - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotZ;

						fPosXAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosX + PosXDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fPosYAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosY + PosYDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fPosZAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosZ + PosZDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);

						fRotXAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotX + RotXDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fRotYAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotY + RotYDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fRotZAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotZ + RotZDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);

						g_aGuys[nCntModel].aModel[nCntParts].PosModel.x = fPosXAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].PosModel.y = fPosYAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].PosModel.z = fPosZAsk[nCntModel][nCntParts];

						g_aGuys[nCntModel].aModel[nCntParts].RotModel.x = fRotXAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].RotModel.y = fRotYAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].RotModel.z = fRotZAsk[nCntModel][nCntParts];
					}
					g_aGuys[nCntModel].fMotion += 1.0f;
					//モーションカウンタがフレーム数を超えたら
					if (g_aGuys[nCntModel].fMotion >= g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame)
					{
						//次のキー
						g_aGuys[nCntModel].nKey++;
						//モーションカウンタ初期化
						g_aGuys[nCntModel].fMotion = 0.0f;
					}
				}
				else if (g_aGuys[nCntModel].nKey == 1)
				{
					for (int nCntParts = 0; nCntParts < MAX_GUYS_NUM; nCntParts++)
					{
						PosXDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[0].aKey[nCntParts].fPosX - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosX;
						PosYDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[0].aKey[nCntParts].fPosY - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosY;
						PosZDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[0].aKey[nCntParts].fPosZ - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosZ;

						RotXDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[0].aKey[nCntParts].fRotX - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotX;
						RotYDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[0].aKey[nCntParts].fRotY - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotY;
						RotZDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[0].aKey[nCntParts].fRotZ - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotZ;

						fPosXAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosX + PosXDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fPosYAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosY + PosYDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fPosZAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosZ + PosZDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);

						fRotXAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotX + RotXDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fRotYAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotY + RotYDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fRotZAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotZ + RotZDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);

						g_aGuys[nCntModel].aModel[nCntParts].PosModel.x = fPosXAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].PosModel.y = fPosYAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].PosModel.z = fPosZAsk[nCntModel][nCntParts];

						g_aGuys[nCntModel].aModel[nCntParts].RotModel.x = fRotXAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].RotModel.y = fRotYAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].RotModel.z = fRotZAsk[nCntModel][nCntParts];
					}
					g_aGuys[nCntModel].fMotion += 1.0f;
					if (g_aGuys[nCntModel].fMotion >= g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame)
					{
						if (g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].bLoop == true)
						{
							g_aGuys[nCntModel].nKey = 0;
						}
						else if (g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_NEUTRAL].bLoop == false)
						{
							g_aGuys[nCntModel].nKey = 2;
						}
						g_aGuys[nCntModel].fMotion = 0.0f;
					}
				}
			}
			else if (g_aGuys[nCntModel].aState == GUYS_STATE_WORK)
			{
				if (g_aGuys[nCntModel].nKey == 0)
				{
					for (int nCntParts = 0; nCntParts < MAX_GUYS_NUM; nCntParts++)
					{
						PosXDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fPosX - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosX;
						PosYDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fPosY - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosY;
						PosZDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fPosZ - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosZ;

						RotXDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fRotX - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotX;
						RotYDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fRotY - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotY;
						RotZDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey + 1].aKey[nCntParts].fRotZ - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotZ;

						fPosXAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosX + PosXDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fPosYAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosY + PosYDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fPosZAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosZ + PosZDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);

						fRotXAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotX + RotXDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fRotYAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotY + RotYDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fRotZAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotZ + RotZDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);

						g_aGuys[nCntModel].aModel[nCntParts].PosModel.x = fPosXAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].PosModel.y = fPosYAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].PosModel.z = fPosZAsk[nCntModel][nCntParts];

						g_aGuys[nCntModel].aModel[nCntParts].RotModel.x = fRotXAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].RotModel.y = fRotYAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].RotModel.z = fRotZAsk[nCntModel][nCntParts];
					}
					g_aGuys[nCntModel].fMotion += 1.0f;
					//モーションカウンタがフレーム数を超えたら
					if (g_aGuys[nCntModel].fMotion >= g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame)
					{
						g_aGuys[nCntModel].nKey++;
						//モーションカウンタ初期化
						g_aGuys[nCntModel].fMotion = 0.0f;
					}
				}
				else if (g_aGuys[nCntModel].nKey == 1)
				{
					for (int nCntParts = 0; nCntParts < MAX_GUYS_NUM; nCntParts++)
					{
						PosXDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[0].aKey[nCntParts].fPosX - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosX;
						PosYDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[0].aKey[nCntParts].fPosY - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosY;
						PosZDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[0].aKey[nCntParts].fPosZ - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosZ;

						RotXDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[0].aKey[nCntParts].fRotX - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotX;
						RotYDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[0].aKey[nCntParts].fRotY - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotY;
						RotZDifference[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[0].aKey[nCntParts].fRotZ - g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotZ;

						fPosXAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosX + PosXDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fPosYAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosY + PosYDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fPosZAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fPosZ + PosZDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);

						fRotXAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotX + RotXDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fRotYAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotY + RotYDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);
						fRotZAsk[nCntModel][nCntParts] = g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].aKey[nCntParts].fRotZ + RotZDifference[nCntModel][nCntParts] * (g_aGuys[nCntModel].fMotion / g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame);

						g_aGuys[nCntModel].aModel[nCntParts].PosModel.x = fPosXAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].PosModel.y = fPosYAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].PosModel.z = fPosZAsk[nCntModel][nCntParts];

						g_aGuys[nCntModel].aModel[nCntParts].RotModel.x = fRotXAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].RotModel.y = fRotYAsk[nCntModel][nCntParts];
						g_aGuys[nCntModel].aModel[nCntParts].RotModel.z = fRotZAsk[nCntModel][nCntParts];
					}
					g_aGuys[nCntModel].fMotion += 1.0f;
					if (g_aGuys[nCntModel].fMotion >= g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].aKeyinfo[g_aGuys[nCntModel].nKey].nFrame)
					{
						if (g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].bLoop == true)
						{
							g_aGuys[nCntModel].nKey = 0;
						}
						else if (g_aGuys[nCntModel].aMotioninfo[GUYS_STATE_WORK].bLoop == false)
						{
							g_aGuys[nCntModel].nKey = 2;
						}
						g_aGuys[nCntModel].fMotion = 0.0f;
					}
				}
			}

			SetPointShadow(g_aGuys[nCntModel].nIdex, g_aGuys[nCntModel].pos, 25.0f, 25.0f, g_aGuys[nCntModel].bUse);
		}
	}
}
//---------------------------
//描画処理
//---------------------------
void DrawGuys(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//--------------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//--------------------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntModel = 0; nCntModel < MAX_GUYS_NUM; nCntModel++)
	{
		if (g_aGuys[nCntModel].bUse == true)
		{
			D3DXMatrixIdentity(&g_aGuys[nCntModel].mtxWold);	//マトリックス初期化

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aGuys[nCntModel].rot.y,
											g_aGuys[nCntModel].rot.x,
											g_aGuys[nCntModel].rot.z);

			D3DXMatrixMultiply(	&g_aGuys[nCntModel].mtxWold,
								&g_aGuys[nCntModel].mtxWold,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aGuys[nCntModel].pos.x,
									g_aGuys[nCntModel].pos.y,
									g_aGuys[nCntModel].pos.z);

			D3DXMatrixMultiply(	&g_aGuys[nCntModel].mtxWold,
								&g_aGuys[nCntModel].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aGuys[nCntModel].mtxWold);

			//---------------------------------
			//モデルパーツのマトリックスの設定
			//---------------------------------
			for (int nCntParts = 0; nCntParts < g_aGuys[nCntModel].nNumModel; nCntParts++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用マトリックス
				D3DXMATRIX mtxParent;					//親のマトリックス

				D3DXMatrixIdentity(&g_aGuys[nCntModel].aModel[nCntParts].mtxWold);	//マトリックス初期化

				//カメラの向きを取得
				pDevice->GetTransform(	D3DTS_VIEW,
										&g_aGuys[nCntModel].mtxView);

				//カメラの情報を入れて、スケールを反映
				g_aGuys[nCntModel].mtxWold._11 = g_aGuys[nCntModel].mtxView._11;
				g_aGuys[nCntModel].mtxWold._12 = g_aGuys[nCntModel].mtxView._21;
				g_aGuys[nCntModel].mtxWold._13 = g_aGuys[nCntModel].mtxView._31;
				g_aGuys[nCntModel].mtxWold._31 = g_aGuys[nCntModel].mtxView._13;
				g_aGuys[nCntModel].mtxWold._32 = g_aGuys[nCntModel].mtxView._23;
				g_aGuys[nCntModel].mtxWold._33 = g_aGuys[nCntModel].mtxView._33;

				//向きの設定
				D3DXMatrixRotationYawPitchRoll(	&mtxRotModel,
												g_aGuys[nCntModel].aModel[nCntParts].RotModel.y,
												g_aGuys[nCntModel].aModel[nCntParts].RotModel.x,
												g_aGuys[nCntModel].aModel[nCntParts].RotModel.z);

				D3DXMatrixMultiply(	&g_aGuys[nCntModel].aModel[nCntParts].mtxWold,
									&g_aGuys[nCntModel].aModel[nCntParts].mtxWold,
									&mtxRotModel);
				//位置
				D3DXMatrixTranslation(	&mtxTransModel,
										g_aGuys[nCntModel].aModel[nCntParts].PosModel.x,
										g_aGuys[nCntModel].aModel[nCntParts].PosModel.y,
										g_aGuys[nCntModel].aModel[nCntParts].PosModel.z);

				D3DXMatrixMultiply(	&g_aGuys[nCntModel].aModel[nCntParts].mtxWold,
									&g_aGuys[nCntModel].aModel[nCntParts].mtxWold,
									&mtxTransModel);

				//パーツの親のマトリックスを設定
				//もし親がいたら
				if (g_aGuys[nCntModel].aModel[nCntParts].nIdx != -1)
				{
					mtxParent = g_aGuys[nCntModel].aModel[g_aGuys[nCntModel].aModel[nCntParts].nIdx].mtxWold;
				}
				else
				{
					mtxParent = g_aGuys[nCntModel].mtxWold;
				}

				//パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
				D3DXMatrixMultiply(	&g_aGuys[nCntModel].aModel[nCntParts].mtxWold,
									&g_aGuys[nCntModel].aModel[nCntParts].mtxWold,
									&mtxParent);

				//マトリックスの設定
				pDevice->SetTransform(	D3DTS_WORLD,
										&g_aGuys[nCntModel].aModel[nCntParts].mtxWold);

				//---------------------------
				//描画処理
				//---------------------------
				D3DMATERIAL9		matDef;				//マテリアルの一時保存
				D3DXMATERIAL		*pMat;				//マテリアルデータのポインタ

				//現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				//マテリアルデータのポインタ
				pMat = (D3DXMATERIAL*)g_aGuys[nCntModel].aModel[nCntParts].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aGuys[nCntModel].aModel[nCntParts].pnNumMat; nCntMat++)
				{
					//マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//テクスチャの設定
					pDevice->SetTexture(	0,
											NULL);

					//モデルパーツの描画
					g_aGuys[nCntModel].aModel[nCntParts].pMesh->DrawSubset(nCntMat);
				}
				//一時保存してたやつをもどす
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}

//---------------------------
//セット
//---------------------------
void SetGuys(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, float fMoveSpeed)
{
	for (int nCntModel = 0; nCntModel < MAX_GUYS; nCntModel++)
	{
		if (g_aGuys[nCntModel].bUse == false)
		{
			g_aGuys[nCntModel].pos = pos;	//位置代入
			g_aGuys[nCntModel].rot = rot;	//向き代入
			g_aGuys[nCntModel].nLife = nLife;
			g_aGuys[nCntModel].fMoveSpeed = fMoveSpeed;

			//影
			g_aGuys[nCntModel].nIdex = SetShadow(g_aGuys[nCntModel].pos, 25.0f, 25.0f);
			g_aGuys[nCntModel].bUse = true;
			break;
		}
	}
}

bool CollisionGuys(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, CollisionType nType)
{
	bool bCollision = false;
	D3DXVECTOR3 posdfrc;
	D3DXVECTOR3 efectmove;
	float fAngle;
	float fSpeed = 2.5f;
	float nGuysR = 15.0f;
	float fposdfrcX;

	posdfrc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntGuys = 0; nCntGuys < MAX_GUYS; nCntGuys++)
	{
		if (g_aGuys[nCntGuys].bUse == true)
		{
			posdfrc.x = g_aGuys[nCntGuys].pos.x - pos->x;
			posdfrc.z = g_aGuys[nCntGuys].pos.z - pos->z;

			posdfrc.x = posdfrc.x * posdfrc.x;
			posdfrc.z = posdfrc.z * posdfrc.z;

			fposdfrcX = posdfrc.x + posdfrc.z;

			fposdfrcX = sqrtf(fposdfrcX);

			if (g_aGuys[nCntGuys].pos.y <= pos->y + fHeight / 2 &&
				g_aGuys[nCntGuys].pos.y + g_aGuys[nCntGuys].fHight >= pos->y - fHeight / 2 &&
				fposdfrcX < nGuysR)
			{
				if (nType == COLLISION_PLAYER)
				{

				}
				else if (nType == COLLISION_BULLET)
				{
					g_aGuys[nCntGuys].nLife--;
					if (g_aGuys[nCntGuys].nLife <= 0)
					{
						PlaySound(SOUND_EXPOSION);
						int nGunType = rand() % 2;
						Guntype aType;
						if (nGunType == 0)
						{
							aType = HANDGUN;
						}
						else if (nGunType == 1)
						{
							aType = ASULTRIFLE;
						}
						SetGunModel(g_aGuys[nCntGuys].pos, g_aGuys[nCntGuys].rot, aType);
						g_aGuys[nCntGuys].bUse = false;
						g_nCntDeth++;
						for (int nCntEffect = 0; nCntEffect < 10; nCntEffect++)
						{
							fAngle = (rand() % 314 / 100.0f) * (rand() % 2) *-1;
							efectmove = D3DXVECTOR3(sinf(fAngle) * fSpeed, cosf(fAngle) * fSpeed, sinf(fAngle) * fSpeed);
							SetEffect(g_aGuys[nCntGuys].pos, efectmove, 50.0f, 50.0f, EFFECT_DETH, EFFECT_TEX_DETH, 50.f);
							SetEffect(g_aGuys[nCntGuys].pos, efectmove, 50.0f, 50.0f, EFFECT_DETH, EFFECT_TEX_DETH, 50.f);
							SetEffect(g_aGuys[nCntGuys].pos, efectmove, 50.0f, 50.0f, EFFECT_DETH, EFFECT_TEX_DETH, 50.f);
							SetEffect(g_aGuys[nCntGuys].pos, efectmove, 50.0f, 50.0f, EFFECT_DETH, EFFECT_TEX_DETH, 50.f);
							SetEffect(g_aGuys[nCntGuys].pos, efectmove, 50.0f, 50.0f, EFFECT_DETH, EFFECT_TEX_DETH, 50.f);
							SetEffect(g_aGuys[nCntGuys].pos, efectmove, 50.0f, 50.0f, EFFECT_DETH, EFFECT_TEX_DETH, 50.f);

						}
					}
				}
				bCollision = true;
			}
			//影
			SetPointShadow(g_aGuys[nCntGuys].nIdex, g_aGuys[nCntGuys].pos, 30.0f, 30.0f, g_aGuys[nCntGuys].bUse);
		}
	}
	return bCollision;
}

//---------------------------
//Dethカウントのゲット
//---------------------------
int GetDeth(void)
{
	return g_nCntDeth;
}

//---------------------------
//Dethカウントリセット
//---------------------------
void ResetsDeth(void)
{
	g_nCntDeth = 0;
}

//---------------------------
//情報入手
//---------------------------
Guys *GetGuys(void)
{
	return &g_aGuys[0];
}