//---------------------------
//インクルードファイル
//---------------------------
#include "timer.h"
#include "fade.h"
#include "score.h"
#include "enemy.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureTimer = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		//頂点バッファへのポインタ
TIMER					g_timer[MAX_TIMER];			//BGの構造体
int						g_nTimer;				//タイマー
int						g_nCntRealT = 0;			//現実時間になるたけ知被ける
bool					g_bPulse = true;			//一回タス

//---------------------------
//初期化処
//---------------------------
HRESULT InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	pDevice = GetDevice();		//デバイスの取得
	//タイマーの初期化
	for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++)
	{
		g_timer[nCnttimer].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_timer[nCnttimer].bUse = false;
	}

	g_nTimer = NO_TIMER_SET;

#ifdef _DEBUG
	g_nTimer = DEBUG_MAXTIMER_SET;		//タイマー
#endif
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/score00.png",
								&g_pTextureTimer);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_TIMER,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffTimer,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer - TIMER_SIZE_X, g_timer[nCnttimer].pos.y - TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer + TIMER_SIZE_X, g_timer[nCnttimer].pos.y - TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer - TIMER_SIZE_X, g_timer[nCnttimer].pos.y + TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer + TIMER_SIZE_X, g_timer[nCnttimer].pos.y + TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitTimer(void)
{
	g_nTimer = 0;
	//テクスチャの破棄
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateTimer(void)
{
	ENEMY		*pEnemy;
	VERTEX_2D	*pVtx;				//頂点情報へのポインタ
	int			nHeith = 0;			//差分
	int			aNumber[MAX_TIMER];	//タイマーの桁数

	pEnemy = GetEnemy();

	g_nCntRealT++;
	if (g_nCntRealT >= 150)
	{
		if (GetMode() != MODE_RESULT || GetMode() == MODE_TITLE)
		{
			//時間を減らす
			g_nTimer += -1;
		}

		//時間の計算
		aNumber[0] = g_nTimer % 1000 / 100;
		aNumber[1] = g_nTimer % 100 / 10;
		aNumber[2] = g_nTimer % 10 / 1;

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ移動
		for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++, nHeith + 50.0f)
		{
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2((aNumber[nCnttimer] * 0.1f) + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((aNumber[nCnttimer] * 0.1f) + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2((aNumber[nCnttimer] * 0.1f) + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((aNumber[nCnttimer] * 0.1f) + 0.1f, 1.0f);

			pVtx += 4;
		}
		//頂点バッファをアンロックする
		g_pVtxBuffTimer->Unlock();

		g_nCntRealT = 0;
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++, nHeith + 50.0f)
	{
		g_timer[nCnttimer].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - TIMER_SIZE_X * 2, 0.0f + 25.0f, 0.0f);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer - TIMER_SIZE_X, g_timer[nCnttimer].pos.y - TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer + TIMER_SIZE_X, g_timer[nCnttimer].pos.y - TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer - TIMER_SIZE_X, g_timer[nCnttimer].pos.y + TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_timer[nCnttimer].pos.x + TIMER_SIZE_X * 2 * nCnttimer + TIMER_SIZE_X, g_timer[nCnttimer].pos.y + TIMER_SIZE_Y, g_timer[nCnttimer].pos.z);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTimer->Unlock();
	//タイマーが0になったら	
	if (g_nTimer <= 0 && GetFade() == FADE_NONE)
	{
		SetFade(MODE_GAMEOVER);
	}
	for (int inCnt = 0; inCnt < MAX_ENEMY; inCnt++)
	{
		//リザルト画面
		if (GetMode() == MODE_ES_STAGE03 && GetMode() == MODE_NO_STAGE04 && GetMode() == MODE_HD_STAGE05 || pEnemy->nLife <= 0)
		{
			//タイマーが残ってたら
			if (g_nTimer >= 0 && g_bPulse == true)
			{
				AddScore(g_nTimer);
				g_bPulse = false;
			}
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffTimer,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //頂点フォーマットの設定

	for (int nCnttimer = 0; nCnttimer < MAX_TIMER; nCnttimer++)
	{
		//テクスチャ
		pDevice->SetTexture(0, g_pTextureTimer);
		//ポリゴンの描画
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //プリミティブの種類
								nCnttimer * 4,
								2);
	}
}