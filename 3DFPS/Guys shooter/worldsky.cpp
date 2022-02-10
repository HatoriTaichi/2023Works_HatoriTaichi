//---------------------------
//インクルードファイル
//---------------------------
#include "worldsky.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureSky[MAX_SKY_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSky = NULL;				//頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffSky = NULL;				//インデックスバッファへのポインタ
Sky					g_Sky[MAX_SKY];					//メッシュフィールドの構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();		//デバイスの取得

	for (int nCntSky = 0; nCntSky < MAX_SKY; nCntSky++)
	{
		g_Sky[nCntSky].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Sky[nCntSky].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Sky[nCntSky].fWidth = 0.5f;
		g_Sky[nCntSky].fDepht = 0.5f;
		g_Sky[nCntSky].nTex = 0;
		g_Sky[nCntSky].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/sky_00.jpg",			//テクスチャ
								&g_pTextureSky[0]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * SKY_VTX_NUM_MAX * MAX_SKY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffSky,
									NULL);
	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(	sizeof(WORD) * SKY_IDX_NUM_MAX * MAX_SKY,
								D3DUSAGE_WRITEONLY,
								D3DFMT_INDEX16,
								D3DPOOL_MANAGED,
								&g_pIdxBuffSky,
								NULL);
	//---------------------------
	//頂点情報
	//---------------------------
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffSky->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntField = 0; nCntField < MAX_SKY; nCntField++)
	{
		int nVtxNum = 0;
		for (int nCntY = 0; nCntY < SKY_MAX_VTX_Y + 1; nCntY++)
		{
			for (int nCntX = 0; nCntX < SKY_MAX_VTX_X + 1; nCntX++, nVtxNum++)
			{
				pVtx[nVtxNum].pos = D3DXVECTOR3(cosf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntX) * sinf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntY + (D3DX_PI / 2)) * SKY_X,
												sinf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntY) * SKY_X,
												sinf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntX) * sinf(D3DX_PI * 2 / SKY_MAX_VTX_X * nCntY + (D3DX_PI / 2)) * SKY_X);
				pVtx[nVtxNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nVtxNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[nVtxNum].tex = D3DXVECTOR2((1.0f / SKY_MAX_VTX_X) * nCntX, (1.0f / SKY_MAX_VTX_Y) * nCntY);
			}
		}
		nVtxNum = 0;
		pVtx += SKY_VTX_NUM_MAX;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffSky->Unlock();

	//---------------------------
	//インデックス情報
	//---------------------------
	WORD *pIdx;		//インデックス情報へのポインタ

					//インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffSky->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntField = 0; nCntField < MAX_SKY; nCntField++)
	{
		//角被さり以外の頂点
		for (int nCntZ = 0; nCntZ < SKY_MAX_VTX_Y; nCntZ++)
		{
			for (int nCntX = 0; nCntX < SKY_MAX_VTX_X + 1; nCntX++)
			{
				pIdx[(nCntX * 2) + 0 + ((SKY_MAX_VTX_X + 2) * 2) * nCntZ] = ((SKY_MAX_VTX_X + 1) + nCntX) + ((SKY_MAX_VTX_X + 1) * nCntZ);
				pIdx[(nCntX * 2) + 1 + ((SKY_MAX_VTX_X + 2) * 2) * nCntZ] = (0 + nCntX) + ((SKY_MAX_VTX_X + 1) * nCntZ);
			}
		}
		//角被さりの頂点
		for (int nCntZ = 0; nCntZ < SKY_MAX_VTX_Y - 1; nCntZ++)
		{
			pIdx[(((SKY_MAX_VTX_X + 1) * 2 + 0) * (nCntZ + 1)) + (2 * nCntZ)] = SKY_MAX_VTX_X + ((SKY_MAX_VTX_X + 1) * nCntZ);
			pIdx[(((SKY_MAX_VTX_X + 1) * 2 + 1) * (nCntZ + 1)) + (1 * nCntZ)] = (SKY_MAX_VTX_X * 2 + 2) + ((SKY_MAX_VTX_X + 1) * nCntZ);
		}
		pIdx += SKY_IDX_NUM_MAX;	//インデックスを進める
	}

	//インデックスバッファをアンロックする
	g_pIdxBuffSky->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitSky(void)
{
	//---------------------------
	//テクスチャ破棄
	//---------------------------
	for (int nCntTex = 0; nCntTex < MAX_SKY_TEX; nCntTex++)
	{
		if (g_pTextureSky[nCntTex] != NULL)
		{
			g_pTextureSky[nCntTex]->Release();
			g_pTextureSky[nCntTex] = NULL;
		}
	}

	//---------------------------
	//バッファ破棄
	//---------------------------
	if (g_pVtxBuffSky != NULL)
	{
		g_pVtxBuffSky->Release();
		g_pVtxBuffSky = NULL;
	}

	//---------------------------
	//インデックスバッファ破棄
	//---------------------------
	if (g_pIdxBuffSky != NULL)
	{
		g_pIdxBuffSky->Release();
		g_pIdxBuffSky = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateSky(void)
{

}

//---------------------------
//描画処理
//---------------------------
void DrawSky(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntSky = 0; nCntSky < MAX_SKY; nCntSky++)
	{
		if (g_Sky[nCntSky].bUse == true)
		{
			//カリング有
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			D3DXMatrixIdentity(&g_Sky[nCntSky].mtxWold);	//マトリックス初期化

			//スケール
			g_Sky[nCntSky].mtxWold._11 = g_Sky[nCntSky].fWidth;
			g_Sky[nCntSky].mtxWold._33 = g_Sky[nCntSky].fDepht;

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_Sky[nCntSky].rot.y,
											g_Sky[nCntSky].rot.x,
											g_Sky[nCntSky].rot.z);

			D3DXMatrixMultiply(	&g_Sky[nCntSky].mtxWold,
								&g_Sky[nCntSky].mtxWold,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_Sky[nCntSky].pos.x,
									g_Sky[nCntSky].pos.y,
									g_Sky[nCntSky].pos.z);

			D3DXMatrixMultiply(	&g_Sky[nCntSky].mtxWold,
								&g_Sky[nCntSky].mtxWold,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_Sky[nCntSky].mtxWold);
			//---------------------------
			//描画処理
			//---------------------------
			//バッファの設定をデータストリームに設定
			pDevice->SetStreamSource(	0,
										g_pVtxBuffSky,
										0,
										sizeof(VERTEX_3D));
			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffSky);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_pTextureSky[g_Sky[nCntSky].nTex]);
			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,			//プリミティブの種類
											0,								//インデックス バッファの開始地点から最初のインデックスまでのオフセット
											nCntSky * SKY_VTX_NUM_MAX,	//描画で使用される最小の頂点番号
											SKY_IDX_NUM_MAX,				//頂点の数
											nCntSky * SKY_IDX_NUM_MAX,	//インデックス配列の読み取りを開始する位置
											SKY_POLY_NUM_MAX;				//△の数

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
void SetSky(D3DXVECTOR3 rot, D3DXVECTOR3 pos, float fWidth, float fDepht, int nTex)
{
	for (int nCntSky = 0; nCntSky < MAX_SKY; nCntSky++)
	{
		if (g_Sky[nCntSky].bUse == false)
		{
			g_Sky[nCntSky].pos = pos;			//位置を入れる
			g_Sky[nCntSky].rot = rot;			//向きを入れる
			g_Sky[nCntSky].fWidth = fWidth;	//幅を入れる
			g_Sky[nCntSky].fDepht = fDepht;	//奥行を入れる
			g_Sky[nCntSky].nTex = nTex;		//テクスチャの種類

			g_Sky[nCntSky].bUse = true;		//使ってる
			break;
		}
	}
}