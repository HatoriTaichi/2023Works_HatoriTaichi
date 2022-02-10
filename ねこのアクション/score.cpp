//---------------------------
//インクルードファイル
//---------------------------
#include "score.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureScore = NULL;	//テクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//頂点バッファへのポインタ
Score					g_aScore[MAX_SCOREDIGIT];	//スコアの構造体
int						g_nScore;					//スコア

//---------------------------
//初期化処理
//---------------------------
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();
	//敵の初期化
	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		g_aScore[nCntScore].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/score00.png",
								&g_apTextureScore);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_SCOREDIGIT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffScore,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[1].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
		pVtx[3].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitScore(void)
{
	g_nScore = 0;
	//テクスチャの破棄
	if (g_apTextureScore != NULL)
	{
		g_apTextureScore->Release();
		g_apTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateScore(void)
{
	VERTEX_2D	*pVtx;		//頂点情報へのポインタ
	int			nHeith = 0;	//差分

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//リザルト意外だったら
	if (GetMode() != MODE_RESULT)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++, nHeith + 50.0f)
		{
			g_aScore[nCntScore].pos = D3DXVECTOR3(1070, 0.0f + 25.0f, 0.0f);

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);

			pVtx += 4;
		}
	}
	//リザルト画面
	if (GetMode() == MODE_RESULT)
	{
		for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++, nHeith + 50.0f)
		{
			g_aScore[nCntScore].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - SCORE_X * 3.5, SCREEN_HEIGHT / 2 + SCORE_Y * 4, 0.0f);

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y - SCORE_Y, g_aScore[nCntScore].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore - SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aScore[nCntScore].pos.x + SCORE_X * 2 * nCntScore + SCORE_X, g_aScore[nCntScore].pos.y + SCORE_Y, g_aScore[nCntScore].pos.z);

			pVtx += 4;
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//---------------------------
//描画処理
//---------------------------
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffScore,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //頂点フォーマットの設定

	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		//テクスチャ
		pDevice->SetTexture(0, g_apTextureScore);
		//ポリゴンの描画
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //プリミティブの種類
								nCntScore * 4,
								2);
	}
}

//---------------------------
//スコア計算
//---------------------------
void AddScore(int nVolue)
{
	VERTEX_2D	*pVtx;						//頂点情報へのポインタ
	int			aNumber[MAX_SCOREDIGIT];	//スコア計算

	//スコア換算
	g_nScore += nVolue;

	//スコア計算
	aNumber[0] = g_nScore % 100000 / 10000;
	aNumber[1] = g_nScore % 10000 / 1000;
	aNumber[2] = g_nScore % 1000 / 100;
	aNumber[3] = g_nScore % 100 / 10;
	aNumber[4] = g_nScore % 10 / 1;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCOREDIGIT; nCntScore++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntScore] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//---------------------------
//スコア入手
//---------------------------
int GetScore(void)
{
	return g_nScore;
}