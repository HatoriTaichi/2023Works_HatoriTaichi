//---------------------------
//インクルードファイル
//---------------------------
#include "life.h"
#include "fade.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_apTextureLife = NULL;		//テクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;		//頂点バッファへのポインタ
LIFE					g_aLife;					//体力の構造体
int						g_nLife;					//体力

//---------------------------
//初期化処理
//---------------------------
HRESULT InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスへのポインタ
	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_aLife.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nLife = MAX_LIFE;	//体力の最大数
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/life.png",
								&g_apTextureLife);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffLife,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x - LIFE_X, g_aLife.pos.y - LIFE_Y, g_aLife.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + LIFE_X, g_aLife.pos.y - LIFE_Y, g_aLife.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x - LIFE_X, g_aLife.pos.y + LIFE_Y, g_aLife.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + LIFE_X, g_aLife.pos.y + LIFE_Y, g_aLife.pos.z);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	pVtx[1].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	pVtx[2].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	pVtx[3].col = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.1f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.1f);

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitLife(void)
{
	g_nLife = MAX_LIFE;	//体力の最大数
	//テクスチャの破棄
	if (g_apTextureLife != NULL)
	{
		g_apTextureLife->Release();
		g_apTextureLife = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateLife(void)
{
	VERTEX_2D	 *pVtx;
	int			 nCntLife;

	//最大いじょうになったら	
	if (g_nLife >= MAX_LIFE)
	{
		//最大に合わせる
		g_nLife = MAX_LIFE;
	}

	g_aLife.pos = D3DXVECTOR3(0.0f + LIFE_X, 0.0f + LIFE_Y, 0.0f);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x - LIFE_X, g_aLife.pos.y - LIFE_Y, g_aLife.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + LIFE_X, g_aLife.pos.y - LIFE_Y, g_aLife.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x - LIFE_X, g_aLife.pos.y + LIFE_Y, g_aLife.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + LIFE_X, g_aLife.pos.y + LIFE_Y, g_aLife.pos.z);

	//体力が削れたら
	if (g_nLife <= MAX_LIFE)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.1f * g_nLife - 0.1);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.1f * g_nLife - 0.1);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.1f * g_nLife);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.1f * g_nLife);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();

	//体力がなくなったら
	if (g_nLife <= 0 && GetFade() == FADE_NONE)
	{
		g_nLife = 0;
		SetFade(MODE_GAMEOVER);
		if (GetMode() == MODE_ES_STAGE03 || GetMode() == MODE_NO_STAGE04 || GetMode() == MODE_HD_STAGE05)
		{
			StopSound(SOUND_LABEL_BGM004);
		}
		else if (GetMode() != MODE_ES_STAGE03 || GetMode() != MODE_NO_STAGE04 || GetMode() != MODE_HD_STAGE05)
		{
			StopSound(SOUND_LABEL_BGM001);
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffLife,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D); //頂点フォーマットの設定
	//テクスチャ
	pDevice->SetTexture(0, g_apTextureLife);
	//ポリゴンの描画
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //プリミティブの種類
							0,
							2);
}

//---------------------------
//体力計算
//---------------------------
void AddLife(int nMinus)
{
	g_nLife += nMinus;
}