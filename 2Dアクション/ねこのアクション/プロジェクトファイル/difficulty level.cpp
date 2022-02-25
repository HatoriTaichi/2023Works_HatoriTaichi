//---------------------------
//インクルードファイル
//---------------------------
#include "difficulty level.h"
#include "bullet.h"
#include "fade.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureLetter[MAX_LEVEL] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLetter = NULL;		//頂点バッファへのポインタ
LETTER					g_aLetter[MAX_LEVEL];			//レベル文字の構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitLetter(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ
	pDevice = GetDevice();			//デバイスの取得

	//レベル数分ループ
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		g_aLetter[nCntLevel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//レベル文字の位置
		g_aLetter[nCntLevel].nType = 0;								//レベル文字の種類		
		g_aLetter[nCntLevel].nUse = false;							//使った状態
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/easy.png",	//テクスチャ
								&g_pTextureLetter[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/normal.png",	//テクスチャ
								&g_pTextureLetter[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/hard.png",	//テクスチャ
								&g_pTextureLetter[2]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_LEVEL,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffLetter,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLetter->Lock(0, 0, (void**)&pVtx, 0);

	//レベル分回す
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x - TETTER_X, g_aLetter[nCntLevel].pos.y - TETTER_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x + TETTER_X, g_aLetter[nCntLevel].pos.y - TETTER_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x - TETTER_X, g_aLetter[nCntLevel].pos.y + TETTER_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x + TETTER_X, g_aLetter[nCntLevel].pos.y + TETTER_Y, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;		//頂点えお進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLetter->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitLetter(void)
{
	//レベル分回す
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		//テクスチャの破棄
		if (g_pTextureLetter[nCntLevel] != NULL)
		{
			g_pTextureLetter[nCntLevel]->Release();
			g_pTextureLetter[nCntLevel] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffLetter != NULL)
	{
		g_pVtxBuffLetter->Release();
		g_pVtxBuffLetter = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateLetter(void)
{
	BULLET			*pbullet;

	pbullet = GetBullet();
	//レベル数分ループ
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		//使ってたら
		if (g_aLetter[nCntLevel].nUse == true)
		{
			//タイプ0
			if (g_aLetter[nCntLevel].nType == 0)
			{
				for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pbullet++)
				{
					//当たったら
					if (pbullet->pos.x + BULLET_SIZE_X >= g_aLetter[nCntLevel].pos.x - TETTER_X &&
						pbullet->pos.x - BULLET_SIZE_X <= g_aLetter[nCntLevel].pos.x + TETTER_X &&
						pbullet->pos.y + BULLET_SIZE_Y >= g_aLetter[nCntLevel].pos.y - TETTER_Y &&
						pbullet->pos.y - BULLET_SIZE_Y <= g_aLetter[nCntLevel].pos.y + TETTER_Y &&
						GetFade() == FADE_NONE)
					{
						pbullet->bUse = false;
						g_aLetter[nCntLevel].nUse = false;
						PlaySound(SOUND_LABEL_SE000);
						SetFade(MODE_ES_STAGE01);
					}
				}
				pbullet -= MAX_BULLET;
			}
			//タイプ1
			else if (g_aLetter[nCntLevel].nType == 1)
			{
				for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pbullet++)
				{
					//当たったら
					if (pbullet->pos.x + BULLET_SIZE_X >= g_aLetter[nCntLevel].pos.x - TETTER_X &&
						pbullet->pos.x - BULLET_SIZE_X <= g_aLetter[nCntLevel].pos.x + TETTER_X &&
						pbullet->pos.y + BULLET_SIZE_Y >= g_aLetter[nCntLevel].pos.y - TETTER_Y &&
						pbullet->pos.y - BULLET_SIZE_Y <= g_aLetter[nCntLevel].pos.y + TETTER_Y &&
						GetFade() == FADE_NONE)
					{
						pbullet->bUse = false;
						g_aLetter[nCntLevel].nUse = false;
						PlaySound(SOUND_LABEL_SE000);
						SetFade(MODE_NO_STAGE01);
					}
				}
				pbullet -= MAX_BULLET;
			}
			//タイプ2
			else if (g_aLetter[nCntLevel].nType == 2)
			{
				for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pbullet++)
				{
					//当たったら
					if (pbullet->pos.x + BULLET_SIZE_X >= g_aLetter[nCntLevel].pos.x - TETTER_X &&
						pbullet->pos.x - BULLET_SIZE_X <= g_aLetter[nCntLevel].pos.x + TETTER_X &&
						pbullet->pos.y + BULLET_SIZE_Y >= g_aLetter[nCntLevel].pos.y - TETTER_Y &&
						pbullet->pos.y - BULLET_SIZE_Y <= g_aLetter[nCntLevel].pos.y + TETTER_Y &&
						GetFade() == FADE_NONE)
					{
						pbullet->bUse = false;
						g_aLetter[nCntLevel].nUse = false;
						PlaySound(SOUND_LABEL_SE000);
						SetFade(MODE_HD_STAGE01);
					}
				}
				pbullet -= MAX_BULLET;
			}
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawLetter(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffLetter,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	//レベル数分ループ
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		//使ってたら
		if (g_aLetter[nCntLevel].nUse == true)
		{
			pDevice->SetTexture(0, g_pTextureLetter[g_aLetter[nCntLevel].nType]);		//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntLevel * 4,
									2);
		}
	}
}

//---------------------------
//ブロックのセット
//---------------------------

void SetLetter(D3DXVECTOR3 pos, int nType)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffLetter->Lock(0, 0, (void**)&pVtx, 0);
	//レベル分回す
	for (int nCntLevel = 0; nCntLevel < MAX_LEVEL; nCntLevel++)
	{
		if (g_aLetter[nCntLevel].nUse == false)
		{
			g_aLetter[nCntLevel].pos = pos;			//持ってきた位置を代入
			g_aLetter[nCntLevel].nType = nType;		//持ってきた種類を代入
													//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x - TETTER_X, g_aLetter[nCntLevel].pos.y - TETTER_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x + TETTER_X, g_aLetter[nCntLevel].pos.y - TETTER_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x - TETTER_X, g_aLetter[nCntLevel].pos.y + TETTER_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLetter[nCntLevel].pos.x + TETTER_X, g_aLetter[nCntLevel].pos.y + TETTER_Y, 0.0f);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			
			g_aLetter[nCntLevel].nUse = true;
			break;
		}
		pVtx += 4;	//頂点の数を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffLetter->Unlock();
}

//---------------------------
//ブロックのセット
//---------------------------

LETTER *GetLetter(void)
{
	return &g_aLetter[0];
}