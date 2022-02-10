//---------------------------
//インクルードファイル
//---------------------------
#include "floo.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureField[MAX_FLOO_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFloo = NULL;				//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffFloo = NULL;				//インデックスバッファへのポインタ
Field					g_Floo[MAX_FLOO];					//メッシュフィールドの構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitFloo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	for (int nCntFloo = 0; nCntFloo < MAX_FLOO; nCntFloo++)
	{
		g_Floo[nCntFloo].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Floo[nCntFloo].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Floo[nCntFloo].fWidth = 0.5f;
		g_Floo[nCntFloo].fDepht = 0.5f;
		g_Floo[nCntFloo].nTex = 0;
		g_Floo[nCntFloo].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet_00.png",			//テクスチャ
								&g_pTextureField[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * FLOO_VTX_NUM_MAX * MAX_FLOO,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffFloo,
									NULL);
	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(	sizeof(WORD) * FLOO_IDX_NUM_MAX * MAX_FLOO,
								D3DUSAGE_WRITEONLY,
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED,
								&g_pIdxBuffFloo,
								NULL);
	//---------------------------
	//頂点情報
	//---------------------------
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFloo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntField = 0; nCntField < MAX_FLOO; nCntField++)
	{
		int nVtxNum = 0;
		for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z + 1; nCntZ++)
		{
			for (int nCntX = 0; nCntX < FLOO_MAX_VTX_X + 1; nCntX++, nVtxNum++)
			{
				pVtx[nVtxNum].pos = D3DXVECTOR3(-MS_X + (((MS_X * 2) / FLOO_MAX_VTX_X) * nCntX), 0.0f, MS_Z - (((MS_Z * 2) / FLOO_MAX_VTX_Z) * nCntZ));
				pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[nVtxNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
			}
		}
		nVtxNum = 0;
		pVtx += FLOO_VTX_NUM_MAX;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFloo->Unlock();

	//---------------------------
	//インデックス情報
	//---------------------------
	WORD *pIdx;		//インデックス情報へのポインタ

	//インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffFloo->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntField = 0; nCntField < MAX_FLOO; nCntField++)
	{
		//角被さり以外の頂点
		for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z; nCntZ++)
		{
			for (int nCntX = 0; nCntX < FLOO_MAX_VTX_X + 1; nCntX++)
			{
				pIdx[(nCntX * 2) + 0 + ((FLOO_MAX_VTX_X + 2) * 2) * nCntZ] = ((FLOO_MAX_VTX_X + 1) + nCntX) + ((FLOO_MAX_VTX_X + 1) * nCntZ);
				pIdx[(nCntX * 2) + 1 + ((FLOO_MAX_VTX_X + 2) * 2) * nCntZ] = (0 + nCntX) + ((FLOO_MAX_VTX_X + 1) * nCntZ);
			}
		}
		//角被さりの頂点
		for (int nCntZ = 0; nCntZ < FLOO_MAX_VTX_Z - 1; nCntZ++)
		{
			pIdx[(((FLOO_MAX_VTX_X + 1) * 2 + 0) * (nCntZ + 1)) + (2 * nCntZ)] = FLOO_MAX_VTX_X + ((FLOO_MAX_VTX_X + 1) * nCntZ);
			pIdx[(((FLOO_MAX_VTX_X + 1) * 2 + 1) * (nCntZ + 1)) + (1 * nCntZ)] = (FLOO_MAX_VTX_X * 2 + 2) + ((FLOO_MAX_VTX_X + 1) * nCntZ);
		}
		pIdx += FLOO_IDX_NUM_MAX;	//インデックスを進める
	}

	//インデックスバッファをアンロックする
	g_pIdxBuffFloo->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitFloo(void)
{
	//---------------------------
	//テクスチャ破棄
	//---------------------------
	for (int nCntTex = 0; nCntTex < MAX_FLOO_TEX; nCntTex++)
	{
		if (g_pTextureField[nCntTex] != NULL)
		{
			g_pTextureField[nCntTex]->Release();
			g_pTextureField[nCntTex] = NULL;
		}
	}

	//---------------------------
	//バッファ破棄
	//---------------------------
	if (g_pVtxBuffFloo != NULL)
	{
		g_pVtxBuffFloo->Release();
		g_pVtxBuffFloo = NULL;
	}

	//---------------------------
	//インデックスバッファ破棄
	//---------------------------
	if (g_pIdxBuffFloo != NULL)
	{
		g_pIdxBuffFloo->Release();
		g_pIdxBuffFloo = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateFloo(void)
{

}

//---------------------------
//描画処理
//---------------------------
void DrawFloo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntFloo = 0; nCntFloo < MAX_FLOO; nCntFloo++)
	{
		if (g_Floo[nCntFloo].bUse == true)
		{
			//カリング有
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_Floo[nCntFloo].mtxWold);	//マトリックス初期化

			//スケール
			g_Floo[nCntFloo].mtxWold._11 = g_Floo[nCntFloo].fWidth;
			g_Floo[nCntFloo].mtxWold._33 = g_Floo[nCntFloo].fDepht;

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_Floo[nCntFloo].rot.y,
											g_Floo[nCntFloo].rot.x,
											g_Floo[nCntFloo].rot.z);

			D3DXMatrixMultiply(	&g_Floo[nCntFloo].mtxWold,
								&g_Floo[nCntFloo].mtxWold,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_Floo[nCntFloo].pos.x,
									g_Floo[nCntFloo].pos.y,
									g_Floo[nCntFloo].pos.z);

			D3DXMatrixMultiply(	&g_Floo[nCntFloo].mtxWold,
								&g_Floo[nCntFloo].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_Floo[nCntFloo].mtxWold);
			//---------------------------
			//描画処理
			//---------------------------
			//バッファの設定をデータストリームに設定
			pDevice->SetStreamSource(	0,
										g_pVtxBuffFloo,
										0,
										sizeof(VERTEX_3D));
			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffFloo);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_pTextureField[g_Floo[nCntFloo].nTex]);
			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,			//プリミティブの種類
											0,								//インデックス バッファの開始地点から最初のインデックスまでのオフセット
											nCntFloo * FLOO_VTX_NUM_MAX,	//描画で使用される最小の頂点番号
											FLOO_IDX_NUM_MAX,				//頂点の数
											nCntFloo * FLOO_IDX_NUM_MAX,	//インデックス配列の読み取りを開始する位置
											FLOO_POLY_NUM_MAX;				//△の数
			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//床のセット
//---------------------------
void SetFloo(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fDepht, int nTex)
{
	for (int nCntFloo = 0; nCntFloo < MAX_FLOO; nCntFloo++)
	{
		if (g_Floo[nCntFloo].bUse == false)
		{
			g_Floo[nCntFloo].pos = pos;			//位置を入れる
			g_Floo[nCntFloo].rot = rot;			//向きを入れる
			g_Floo[nCntFloo].fWidth = fWidth;	//幅を入れる
			g_Floo[nCntFloo].fDepht = fDepht;	//奥行を入れる
			g_Floo[nCntFloo].nTex = nTex;		//テクスチャの種類

			g_Floo[nCntFloo].bUse = true;		//使ってる
			break;
		}
	}
}