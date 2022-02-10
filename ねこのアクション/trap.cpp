//---------------------------
//インクルードファイル
//---------------------------
#include "trap.h"
#include "player.h"
#include "life.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureTrap[MAX_TEX_TRAP] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTrap = NULL;			//頂点バッファへのポインタ
TRAP					g_trap[MAX_TRAP];				//ブロックの構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitTrap(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		g_trap[nCntTrap].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
		g_trap[nCntTrap].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//前回の位置
		g_trap[nCntTrap].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量
		g_trap[nCntTrap].fWidth = 0.0f;								//幅
		g_trap[nCntTrap].fHeight = 0.0f;							//高さ
		g_trap[nCntTrap].fTexwidth = 0.0f;							//テクスチャの幅
		g_trap[nCntTrap].fTexheigth = 0.0f;							//テクスチャの高さ
		g_trap[nCntTrap].bUse = false;								//使ってるかどうか
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/trap.png",	//下向きテクスチャ
								&g_pTextureTrap[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/trap01.png",	//右向きテクスチャ
								&g_pTextureTrap[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/trap02.png",	//左向きテクスチャ
								&g_pTextureTrap[2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/trap03.png",	//上向きテクスチャ
								&g_pTextureTrap[3]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_TRAP,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffTrap,
									NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの数ループ
	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

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

		pVtx += 4;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTrap->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitTrap(void)
{
	for (int nCntTex = 0; nCntTex < MAX_TEX_TRAP; nCntTex++)
	{
		//テクスチャの破棄
		if (g_pTextureTrap[nCntTex] != NULL)
		{
			g_pTextureTrap[nCntTex]->Release();
			g_pTextureTrap[nCntTex] = NULL;
		}

	}
	//頂点バッファの破棄
	if (g_pVtxBuffTrap != NULL)
	{
		g_pVtxBuffTrap->Release();
		g_pVtxBuffTrap = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateTrap(void)
{
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ
	PLAYER				*pPlayer;	//プレイヤーの構造体

	pPlayer = GetPlayer();			//プレイヤーの情報を取得

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		if (g_trap[nCntTrap].bUse == true)
		{
			if (GetMode() == MODE_NO_STAGE03)
			{
				g_trap[nCntTrap].pos += g_trap[nCntTrap].move;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

				if (g_trap[nCntTrap].pos.x <= 375)
				{
					g_trap[nCntTrap].bUse = false;
				}
			}
			else if (GetMode() == MODE_HD_STAGE01)
			{
				g_trap[nCntTrap].pos += g_trap[nCntTrap].move;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

				if (pPlayer->pos.y >= 570 &&
					pPlayer->pos.x <= 750 &&
					pPlayer->pos.x >= 550)
				{
					g_trap[nCntTrap].move.x = 7.0f;
				}
			}
			if (GetMode() == MODE_HD_STAGE02)
			{
				g_trap[nCntTrap].pos += g_trap[nCntTrap].move;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

				if (g_trap[nCntTrap].pos.x >= SCREEN_WIDTH)
				{
					g_trap[nCntTrap].bUse = false;
				}
			}
			if (pPlayer->bUse == true)
			{
				//プレイヤーにあ祟ったら
				if (pPlayer->pos.y >= g_trap[nCntTrap].pos.y &&
					pPlayer->pos.y - pPlayer->fHeight <= g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight &&
					pPlayer->pos.x + pPlayer->fWidth / 2 >= g_trap[nCntTrap].pos.x &&
					pPlayer->pos.x - pPlayer->fWidth / 2 <= g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth)
				{
					if (GetMode() == MODE_NO_STAGE01)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 300.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_NO_STAGE02)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 400.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_NO_STAGE03)
					{
						g_trap[nCntTrap].move.x = 0.0f;
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE01)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE02)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 670.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
					else if (GetMode() == MODE_HD_STAGE03)
					{
						pPlayer->bUse = false;
						AddLife(-1);
						SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
					}
				}
			}
			if (g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth <= 0)
			{
				g_trap[nCntTrap].bUse = false;
			}
			else if (g_trap[nCntTrap].pos.x >= SCREEN_WIDTH)
			{
				g_trap[nCntTrap].bUse = false;
			}
		}
		pVtx += 4;	//頂点を進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTrap->Unlock();
}

//---------------------------
//描画処理
//---------------------------
void DrawTrap(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffTrap,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	//ブロックの数ループ
	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		//使ってたら
		if (g_trap[nCntTrap].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureTrap[g_trap[nCntTrap].nType]);		//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntTrap * 4,
									2);
		}
	}
}

//---------------------------
//トラップのセット
//---------------------------
void SetTrap(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexwidth, float fTexheight, int nType)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTrap->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの数ループ
	for (int nCntTrap = 0; nCntTrap < MAX_TRAP; nCntTrap++)
	{
		//使ってなかったら
		if (g_trap[nCntTrap].bUse == false)
		{
			g_trap[nCntTrap].pos = pos;					//持ってきた位置を代入
			g_trap[nCntTrap].move = move;				//持ってきた移動量を代入
			g_trap[nCntTrap].fWidth = fWidth;			//持ってきた横幅を代入
			g_trap[nCntTrap].fHeight = fHeight;			//持ってきた縦幅を代入
			g_trap[nCntTrap].fTexwidth = fTexwidth;		//持ってきたテクスチャの横幅を代入
			g_trap[nCntTrap].fTexheigth = fTexheight;	//持ってきたテクスチャの縦幅を代入
			g_trap[nCntTrap].nType = nType;				//持ってきた移動量を代入

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y, g_trap[nCntTrap].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_trap[nCntTrap].pos.x + g_trap[nCntTrap].fWidth, g_trap[nCntTrap].pos.y + g_trap[nCntTrap].fHeight, g_trap[nCntTrap].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_trap[nCntTrap].fTexwidth, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, g_trap[nCntTrap].fTexheigth);
			pVtx[3].tex = D3DXVECTOR2(g_trap[nCntTrap].fTexwidth, g_trap[nCntTrap].fTexheigth);

			g_trap[nCntTrap].bUse = true;	//使ってる状態
			break;
		}
		pVtx += 4;	//頂点を進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTrap->Unlock();
}

//---------------------------
//トラップの情報を取得
//---------------------------
TRAP *GetTrap(void)
{
	return &g_trap[0];
}