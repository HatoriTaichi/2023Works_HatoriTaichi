//---------------------------
//インクルードファイル
//---------------------------
#include "guninfo.h"
#include "keyinput.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureGuninfo = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGuninfo = NULL;			//頂点バッファへのポインタ
Guninfo					g_aGuninfo[MAX_GUNDIGIT];			//BGの構造体
GUNINFO_TYPE			g_aType;
int						g_nGunRemaining;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitGuninfo(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ
	int			aNumber[MAX_GUNDIGIT];	//スコア計算

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntGun = 0; nCntGun < MAX_GUNDIGIT; nCntGun++)
	{
		g_aGuninfo[nCntGun].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	}

	//スコア計算
	aNumber[0] = g_nGunRemaining % 100 / 10;
	aNumber[1] = g_nGunRemaining % 10 / 1;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/guninfo_00.png",			//テクスチャ
								&g_pTextureGuninfo);
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_GUNDIGIT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffGuninfo,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffGuninfo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGun = 0; nCntGun < MAX_GUNDIGIT; nCntGun++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun - GUN_X, g_aGuninfo[nCntGun].pos.y - GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun + GUN_X, g_aGuninfo[nCntGun].pos.y - GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun - GUN_X, g_aGuninfo[nCntGun].pos.y + GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun + GUN_X, g_aGuninfo[nCntGun].pos.y + GUN_Y, g_aGuninfo[nCntGun].pos.z);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGuninfo->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitGuninfo(void)
{
	//テクスチャの破棄
	if (g_pTextureGuninfo != NULL)
	{
		g_pTextureGuninfo->Release();
		g_pTextureGuninfo = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffGuninfo != NULL)
	{
		g_pVtxBuffGuninfo->Release();
		g_pVtxBuffGuninfo = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateGuninfo(void)
{
	VERTEX_2D	*pVtx;		//頂点情報へのポインタ
	int			aNumber[MAX_GUNDIGIT];	//スコア計算
	int			nHeith = 0;	//差分
	static int			nCntReloadeng;

	//スコア計算
	aNumber[0] = g_nGunRemaining % 100 / 10;
	aNumber[1] = g_nGunRemaining % 10 / 1;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffGuninfo->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntGun = 0; nCntGun < MAX_GUNDIGIT; nCntGun++, nHeith + 10.0f)
	{
		g_aGuninfo[nCntGun].pos = D3DXVECTOR3(SCREEN_WIDTH - (GUN_X * 4.5), SCREEN_HEIGHT - (GUN_Y / 0.5), 0.0f);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun - GUN_X, g_aGuninfo[nCntGun].pos.y - GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun + GUN_X, g_aGuninfo[nCntGun].pos.y - GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun - GUN_X, g_aGuninfo[nCntGun].pos.y + GUN_Y, g_aGuninfo[nCntGun].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aGuninfo[nCntGun].pos.x + GUN_X * 2 * nCntGun + GUN_X, g_aGuninfo[nCntGun].pos.y + GUN_Y, g_aGuninfo[nCntGun].pos.z);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((aNumber[nCntGun] * 0.1f) + 0.1f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffGuninfo->Unlock();

	if (g_nGunRemaining <= 0)
	{
		PlaySound(SOUND_RELOAD_00);
		nCntReloadeng++;
		if (g_aType == GUNINFO_TYPE_00)
		{
			if (nCntReloadeng > 144)
			{
				g_nGunRemaining = 10;
				nCntReloadeng = 0;
			}
		}
		else if (g_aType == GUNINFO_TYPE_01)
		{
			if (nCntReloadeng > 288)
			{
				g_nGunRemaining = 30;
				nCntReloadeng = 0;
			}
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawGuninfo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffGuninfo,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	for (int nCntGun = 0; nCntGun < MAX_GUNDIGIT; nCntGun++)
	{
		pDevice->SetTexture(0, g_pTextureGuninfo);		//テクスチャの設定

		//ポリゴンの描画
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
								nCntGun * 4,
								2);
	}
}

//---------------------------
//残段数計算
//---------------------------
void AddRemaining(int nShoot)
{
	//スコア換算
	g_nGunRemaining += nShoot;
}

//---------------------------
//残段数計算
//---------------------------
void SetGunType(GUNINFO_TYPE aType)
{
	g_aType = aType;

	if (g_aType == GUNINFO_TYPE_00)
	{
		g_nGunRemaining = 10;
	}
	else if (g_aType == GUNINFO_TYPE_01)
	{
		g_nGunRemaining = 30;
	}
}

//---------------------------
//残段数計算
//---------------------------
int GetRemaining(void)
{
	return g_nGunRemaining;
}