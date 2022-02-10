//---------------------------
//インクルードファイル
//---------------------------
#include "round.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureRound = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRound = NULL;	//頂点バッファへのポインタ
Round					g_aRound[MAX_ROUNDDIGIT];	//BGの構造体
int						g_nCntRound;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitRound(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ
	int			aNumber[MAX_ROUNDDIGIT];	//スコア計算

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntRound = 0; nCntRound < MAX_ROUNDDIGIT; nCntRound++)
	{
		g_aRound[nCntRound].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	}

	g_nCntRound = 0;

	//スコア計算
	aNumber[0] = g_nCntRound % 100 / 10;
	aNumber[1] = g_nCntRound % 10 / 1;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/guninfo_00.png",			//テクスチャ
								&g_pTextureRound);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_ROUNDDIGIT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffRound,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRound = 0; nCntRound < MAX_ROUNDDIGIT; nCntRound++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound - ROUND_X, g_aRound[nCntRound].pos.y - ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound + ROUND_X, g_aRound[nCntRound].pos.y - ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound - ROUND_X, g_aRound[nCntRound].pos.y + ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound + ROUND_X, g_aRound[nCntRound].pos.y + ROUND_Y, g_aRound[nCntRound].pos.z);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntRound] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntRound] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntRound] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntRound] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRound->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitRound(void)
{
	//テクスチャの破棄
	if (g_pTextureRound != NULL)
	{
		g_pTextureRound->Release();
		g_pTextureRound = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffRound != NULL)
	{
		g_pVtxBuffRound->Release();
		g_pVtxBuffRound = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateRound(void)
{
	VERTEX_2D	*pVtx;		//頂点情報へのポインタ
	int			nHeith = 0;	//差分

							//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRound = 0; nCntRound < MAX_ROUNDDIGIT; nCntRound++, nHeith + 10.0f)
	{
		g_aRound[nCntRound].pos = D3DXVECTOR3(60 + ROUND_X, SCREEN_HEIGHT - (ROUND_Y / 1.0f), 0.0f);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound - ROUND_X, g_aRound[nCntRound].pos.y - ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound + ROUND_X, g_aRound[nCntRound].pos.y - ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound - ROUND_X, g_aRound[nCntRound].pos.y + ROUND_Y, g_aRound[nCntRound].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aRound[nCntRound].pos.x + ROUND_X * 2 * nCntRound + ROUND_X, g_aRound[nCntRound].pos.y + ROUND_Y, g_aRound[nCntRound].pos.z);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffRound->Unlock();
}

//---------------------------
//描画処理
//---------------------------
void DrawRound(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffRound,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	for (int nCntGun = 0; nCntGun < MAX_ROUNDDIGIT; nCntGun++)
	{
		pDevice->SetTexture(0, g_pTextureRound);		//テクスチャの設定

		//ポリゴンの描画
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
								nCntGun * 4,
								2);
	}
}

//---------------------------
//残段数計算
//---------------------------
void AddRound(int nShoot)
{
	VERTEX_2D	*pVtx;						//頂点情報へのポインタ
	int			aNumber[MAX_ROUNDDIGIT];	//スコア計算

	//スコア換算
	g_nCntRound += nShoot;

	//スコア計算
	aNumber[0] = g_nCntRound % 100 / 10;
	aNumber[1] = g_nCntRound % 10 / 1;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGun = 0; nCntGun < MAX_ROUNDDIGIT; nCntGun++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffRound->Unlock();
}

//---------------------------
//情報のリターン
//---------------------------
int GetRound(void)
{
	return g_nCntRound;
}