//---------------------------
//インクルードファイル
//---------------------------
#include "stage.h"
#include "shadow.h"
#include "camara.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9	g_apTextureStage[MAX_STAGE_MODEL][MAX_STAGE_TEX] = {};	//テクスチャのポインタ
Stage				g_aStage[MAX_STAGE_MODEL];	//自分の構造体
int					g_nModel;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitStage(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntStageModel = 0; nCntStageModel < MAX_STAGE_MODEL; nCntStageModel++)
	{
		//位置向き初期化
		g_aStage[nCntStageModel].pos = (D3DXVECTOR3(-500.0f, 0.0f, 0.0f));
		g_aStage[nCntStageModel].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aStage[nCntStageModel].move = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aStage[nCntStageModel].vtxMaxModel = (D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f));
		g_aStage[nCntStageModel].vtxMinModel = (D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f));
		g_aStage[nCntStageModel].pMesh = {};
		g_aStage[nCntStageModel].pBuffMat = {};
		g_aStage[nCntStageModel].nIdex = 0;
		g_aStage[nCntStageModel].bUse = false;
	}
	g_nModel = 0;

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitStage(void)
{
	for (int nCntStageModel = 0; nCntStageModel < MAX_STAGE_MODEL; nCntStageModel++)
	{
		//---------------------------
		//メッシュ破棄
		//---------------------------
		if (g_aStage[nCntStageModel].pMesh != NULL)
		{
			g_aStage[nCntStageModel].pMesh->Release();
			g_aStage[nCntStageModel].pMesh = NULL;
		}

		//---------------------------
		//マテリアル破棄
		//---------------------------
		if (g_aStage[nCntStageModel].pBuffMat != NULL)
		{
			g_aStage[nCntStageModel].pBuffMat->Release();
			g_aStage[nCntStageModel].pBuffMat = NULL;
		}
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateStage(void)
{
	for (int nCntStage = 0; nCntStage < MAX_STAGE_MODEL; nCntStage++)
	{
		if (g_aStage[nCntStage].bUse == true)
		{
			if (g_aStage[nCntStage].aType == STAGE_MOVEFLOO_00)
			{
				g_aStage[nCntStage].pos += g_aStage[nCntStage].move;
				if (g_aStage[nCntStage].pos.z >= 490.0f)
				{
					g_aStage[nCntStage].move *= -1;
				}
				else if (g_aStage[nCntStage].pos.z <= 210.0f)
				{
					g_aStage[nCntStage].move *= -1;
				}
			}
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawStage(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntStageModel = 0; nCntStageModel < MAX_STAGE_MODEL; nCntStageModel++)
	{
		if (g_aStage[nCntStageModel].bUse == true)
		{
			//カリング有り
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			D3DXMatrixIdentity(&g_aStage[nCntStageModel].mtxWold);	//マトリックス初期化

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,	
											g_aStage[nCntStageModel].rot.y,
											g_aStage[nCntStageModel].rot.x,
											g_aStage[nCntStageModel].rot.z);

			D3DXMatrixMultiply(	&g_aStage[nCntStageModel].mtxWold,
								&g_aStage[nCntStageModel].mtxWold,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aStage[nCntStageModel].pos.x,
									g_aStage[nCntStageModel].pos.y,
									g_aStage[nCntStageModel].pos.z);

			D3DXMatrixMultiply(	&g_aStage[nCntStageModel].mtxWold,
								&g_aStage[nCntStageModel].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aStage[nCntStageModel].mtxWold);
			//---------------------------
			//描画処理
			//---------------------------
			D3DMATERIAL9		matDef;				//マテリアルの一時保存
			D3DXMATERIAL		*pMat;				//マテリアルデータのポインタ

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータのポインタ
			pMat = (D3DXMATERIAL*)g_aStage[nCntStageModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aStage[nCntStageModel].pnNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(	0,
										g_apTextureStage[nCntStageModel][nCntMat]);

				//モデルパーツの描画
				g_aStage[nCntStageModel].pMesh->DrawSubset(nCntMat);
			}
			//一時保存してたやつをもどす
			pDevice->SetMaterial(&matDef);
		}
	}
}

//---------------------------
//セット
//---------------------------
void SetStage(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, MODEL_TYPE Type)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntStageModel = 0; nCntStageModel < MAX_STAGE_MODEL; nCntStageModel++)
	{
		if (g_aStage[nCntStageModel].bUse == false)
		{
			g_aStage[nCntStageModel].pos = pos;		//位置の代入
			g_aStage[nCntStageModel].rot = rot;		//向きの代入
			g_aStage[nCntStageModel].aType = Type;	//種類の代入
			g_aStage[nCntStageModel].move = move;	//移動量の代入

			if (g_aStage[nCntStageModel].aType == STAGE_FLOO_00 || g_aStage[nCntStageModel].aType == STAGE_MOVEFLOO_00)
			{
				//---------------------------
				//Xファイルの読み込み
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Stage/stage_floo_00.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aStage[nCntStageModel].pBuffMat,
									NULL,
									&g_aStage[nCntStageModel].pnNumMat,
									&g_aStage[nCntStageModel].pMesh);
			}
			else if (g_aStage[nCntStageModel].aType == STAGE_FENCE_00)
			{
				//---------------------------
				//Xファイルの読み込み
				//---------------------------
				D3DXLoadMeshFromX(	"data/Model/Stage/stage_fence_01.x",
									D3DXMESH_SYSTEMMEM,
									pDevice,
									NULL,
									&g_aStage[nCntStageModel].pBuffMat,
									NULL,
									&g_aStage[nCntStageModel].pnNumMat,
									&g_aStage[nCntStageModel].pMesh);
			}
			//---------------------------
			//テクスチャの抜き出し
			//---------------------------
			D3DXMATERIAL *pMat;	//マテリアルのポインタ

			//マテリアル情報のポインタ
			pMat = (D3DXMATERIAL*)g_aStage[nCntStageModel].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aStage[nCntStageModel].pnNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(	pDevice,
												pMat[nCntMat].pTextureFilename,			//テクスチャ
												&g_apTextureStage[nCntStageModel][nCntMat]);
				}
			}

			//頂点バッファをアンロック
			g_aStage[nCntStageModel].pMesh->UnlockVertexBuffer();
			g_aStage[nCntStageModel].bUse = true;	//使ってんぜ
			break;
		}
	}
	//---------------------------
	//頂点座標の抜き出し
	//---------------------------
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファのポインタ

	//頂点数を取得
	nNumVtx = g_aStage[g_nModel].pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_aStage[g_nModel].pMesh->GetFVF());

	//頂点バッファのロック
	g_aStage[g_nModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

		//頂点数を比較して最小値、最大値を抜く
		//X
		if (g_aStage[g_nModel].vtxMaxModel.x <= vtx.x)
		{
			g_aStage[g_nModel].vtxMaxModel.x = vtx.x;
		}
		if (g_aStage[g_nModel].vtxMinModel.x >= vtx.x)
		{
			g_aStage[g_nModel].vtxMinModel.x = vtx.x;
		}
		//Y
		if (g_aStage[g_nModel].vtxMaxModel.y <= vtx.y)
		{
			g_aStage[g_nModel].vtxMaxModel.y = vtx.y;
		}
		if (g_aStage[g_nModel].vtxMinModel.y >= vtx.y)
		{
			g_aStage[g_nModel].vtxMinModel.y = vtx.y;
		}
		//Z
		if (g_aStage[g_nModel].vtxMaxModel.z <= vtx.z)
		{
			g_aStage[g_nModel].vtxMaxModel.z = vtx.z;
		}
		if (g_aStage[g_nModel].vtxMinModel.z >= vtx.z)
		{
			g_aStage[g_nModel].vtxMinModel.z = vtx.z;
		}
		pVtxBuff += sizeFVF;	//頂点を進める
	}

	//頂点バッファをアンロック
	g_aStage[g_nModel].pMesh->UnlockVertexBuffer();

	//直径を出す
	g_aStage[g_nModel].fWidth = g_aStage[g_nModel].vtxMaxModel.x - g_aStage[g_nModel].vtxMinModel.x;
	g_aStage[g_nModel].fHight = g_aStage[g_nModel].vtxMaxModel.y - g_aStage[g_nModel].vtxMinModel.y;
	g_aStage[g_nModel].fDepth = g_aStage[g_nModel].vtxMaxModel.z - g_aStage[g_nModel].vtxMinModel.z;

	g_nModel++;
}

//---------------------------
//当たり判定
//---------------------------
bool CollisionStage(D3DXVECTOR3 *pos, D3DXVECTOR3 *posold, D3DXVECTOR3 *move, float fWidth, float fHeight, float fDepht, int nType)
{
	bool bLand = false;	//地面についてるか
	Camera *pCamera;
	Stage *pStage;

	pStage = GetStage();
	pCamera = GetCamera();

	for (int nCntModel = 0; nCntModel < MAX_STAGE_MODEL; nCntModel++, pStage++)
	{
		if (pStage->bUse == true)
		{
			if (nType == 0)
			{
				//回転0か反対
				if (pStage->rot.y == 0.0f || pStage->rot.y == -D3DX_PI)
				{
					//上に載ってたら
					if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
						pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
						pos->z - fDepht / 2.0f < pStage->pos.z + pStage->fDepth / 2.0f &&
						pos->z + fDepht / 2.0f > pStage->pos.z - pStage->fDepth / 2.0f &&
						posold->y >= pStage->pos.y + pStage->vtxMaxModel.y &&
						pos->y <= pStage->pos.y + pStage->vtxMaxModel.y)
					{
						move->y = 0.0f;
						pos->y = pStage->pos.y + pStage->vtxMaxModel.y;	//地面に合わせる
						pCamera->PosV.x += pStage->move.x;	//移動床だったら動く
						pCamera->PosV.z += pStage->move.z;	//移動床だったら動く
						pCamera->PosR.z += pStage->move.z;
						pCamera->PosR.x += pStage->move.x;
						bLand = true;			//地面についてる
					}
					//フェンスだったら
					if (pStage->aType == STAGE_FENCE_00)
					{
						//かいてんが0
						if (pStage->rot.y == 0.0f)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->z > pStage->pos.z - pStage->fDepth * 2)
							{
								pCamera->PosV.z = pStage->pos.z - pStage->fDepth * 2;
								bLand = false;			//地面についてない
							}
						}
						//回転が反対
						else if (pStage->rot.y == -D3DX_PI)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->z < pStage->pos.z + pStage->fDepth * 2)
							{
								pCamera->PosV.z = pStage->pos.z + pStage->fDepth * 2;
								bLand = false;			//地面についてない
							}
						}
					}
				}
				//かいてんが左右
				else if (pStage->rot.y == D3DX_PI / 2 || pStage->rot.y == -D3DX_PI / 2)
				{
					//上に載ってたら
					if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
						pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
						pos->z - fDepht / 2.0f < pStage->pos.z + pStage->fWidth / 2.0f &&
						pos->z + fDepht / 2.0f > pStage->pos.z - pStage->fWidth / 2.0f &&
						posold->y >= pStage->pos.y + pStage->vtxMaxModel.y &&
						pos->y <= pStage->pos.y + pStage->vtxMaxModel.y)
					{
						move->y = 0.0f;
						pos->y = pStage->pos.y + pStage->vtxMaxModel.y;	//地面に合わせる
						pCamera->PosV.x += pStage->move.x;	//移動床だったら動く
						pCamera->PosV.z += pStage->move.z;	//移動床だったら動く
						bLand = true;			//地面についてる
					}
					//フェンスだったら	
					if (pStage->aType == STAGE_FENCE_00)
					{
						//右
						if (pStage->rot.y == D3DX_PI / 2)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->x > pStage->pos.x - pStage->fDepth * 2)
							{
								pCamera->PosV.x = pStage->pos.x - pStage->fDepth * 2;
								bLand = false;			//地面についてない
							}
						}
						//左
						else if (pStage->rot.y == -D3DX_PI / 2)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->x < pStage->pos.x + pStage->fDepth * 2)
							{
								pCamera->PosV.x = pStage->pos.x + pStage->fDepth * 2;
								bLand = false;			//地面についてない
							}
						}
					}
				}
			}
			else if (nType != 0)
			{
				//回転0か反対
				if (pStage->rot.y == 0.0f || pStage->rot.y == -D3DX_PI)
				{
					//上に載ってたら
					if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
						pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
						pos->z - fDepht / 2.0f < pStage->pos.z + pStage->fDepth / 2.0f &&
						pos->z + fDepht / 2.0f > pStage->pos.z - pStage->fDepth / 2.0f &&
						posold->y >= pStage->pos.y + pStage->vtxMaxModel.y &&
						pos->y <= pStage->pos.y + pStage->vtxMaxModel.y)
					{
						move->y = 0.0f;
						pos->y = pStage->pos.y + pStage->vtxMaxModel.y;	//地面に合わせる
						pos->x += pStage->move.x;	//移動床だったら動く
						pos->z += pStage->move.z;	//移動床だったら動く
						bLand = true;			//地面についてる
					}
					//フェンスだったら
					if (pStage->aType == STAGE_FENCE_00)
					{
						//かいてんが0
						if (pStage->rot.y == 0.0f)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->z > pStage->pos.z - pStage->fDepth * 2)
							{
								pos->z = pStage->pos.z - pStage->fDepth * 2;
								if (nType == 1)
								{
									bLand = true;
								}
								else
								{
									bLand = false;			//地面についてない
								}
							}
						}
						//回転が反対
						else if (pStage->rot.y == -D3DX_PI)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fWidth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fWidth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->z < pStage->pos.z + pStage->fDepth * 2)
							{
								pos->z = pStage->pos.z + pStage->fDepth * 2;
								if (nType == 1)
								{
									bLand = true;
								}
								else
								{
									bLand = false;			//地面についてない
								}
							}
						}
					}
				}
				//かいてんが左右
				else if (pStage->rot.y == D3DX_PI / 2 || pStage->rot.y == -D3DX_PI / 2)
				{
					//上に載ってたら
					if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
						pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
						pos->z - fDepht / 2.0f < pStage->pos.z + pStage->fWidth / 2.0f &&
						pos->z + fDepht / 2.0f > pStage->pos.z - pStage->fWidth / 2.0f &&
						posold->y >= pStage->pos.y + pStage->vtxMaxModel.y &&
						pos->y <= pStage->pos.y + pStage->vtxMaxModel.y)
					{
						move->y = 0.0f;
						pos->y = pStage->pos.y + pStage->vtxMaxModel.y;	//地面に合わせる
						pos->x += pStage->move.x;	//移動床だったら動く
						pos->z += pStage->move.z;	//移動床だったら動く
						bLand = true;			//地面についてる
					}
					//フェンスだったら	
					if (pStage->aType == STAGE_FENCE_00)
					{
						//右
						if (pStage->rot.y == D3DX_PI / 2)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->x > pStage->pos.x - pStage->fDepth * 2)
							{
								pos->x = pStage->pos.x - pStage->fDepth * 2;
								if (nType == 1)
								{
									bLand = true;
								}
								else
								{
									bLand = false;			//地面についてない
								}
							}
						}
						//左
						else if (pStage->rot.y == -D3DX_PI / 2)
						{
							if (pos->x - fWidth / 2.0f < pStage->pos.x + pStage->fDepth / 2.0f &&
								pos->x + fWidth / 2.0f > pStage->pos.x - pStage->fDepth / 2.0f &&
								pos->y + fHeight > pStage->pos.y &&
								pos->y < pStage->pos.y + pStage->fHight &&
								posold->x < pStage->pos.x + pStage->fDepth * 2)
							{
								pos->x = pStage->pos.x + pStage->fDepth * 2;
								if (nType == 1)
								{
									bLand = true;
								}
								else
								{
									bLand = false;			//地面についてない
								}
							}
						}
					}
				}
			}
		}
	}
	pStage -= MAX_STAGE_MODEL;

	return bLand;
}

//---------------------------
//当たり判定
//---------------------------
Stage *GetStage(void)
{
	return &g_aStage[0];
}