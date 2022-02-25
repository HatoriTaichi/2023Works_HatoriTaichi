//---------------------------
//インクルードファイル
//---------------------------
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "life.h"
#include "player.h"
#include "block.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "timer.h"
#include "trap.h"
#include "bg.h"
#include "esystage01.h"
#include "sound.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTexturePause[MAX_PAUSE_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;					//頂点バッファへのポインタ
PAUSE					g_pause[MAX_PAUSE];						//BGの構造体
bool					g_bPuse = false;

//---------------------------
//初期化処理
//---------------------------
HRESULT InitPause(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ
	int					nHeight = 0;	

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		g_pause[nCntPause].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / (3 + 1)) + ((SCREEN_HEIGHT / (3 + 1)) * nCntPause), 0.0f);
		g_pause[nCntPause].nType = nCntPause;
		g_pause[nCntPause].bUse = true;
	}
	if (g_pause[0].bUse == true)
	{
		g_pause[1].bUse = false;
		g_pause[2].bUse = false;
	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/gamemenyu00.png",	//テクスチャ
								&g_pTexturePause[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/gamemenyu01.png",	//テクスチャ
								&g_pTexturePause[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/gamemenyu02.png",	//テクスチャ
								&g_pTexturePause[2]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffPause,
									NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの数ループ
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x - PAUSE_X, g_pause[nCntPause].pos.y - PAUSE_Y, g_pause[nCntPause].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x + PAUSE_X, g_pause[nCntPause].pos.y - PAUSE_Y, g_pause[nCntPause].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x - PAUSE_X, g_pause[nCntPause].pos.y + PAUSE_Y, g_pause[nCntPause].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_pause[nCntPause].pos.x + PAUSE_X, g_pause[nCntPause].pos.y + PAUSE_Y, g_pause[nCntPause].pos.z);

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
	g_pVtxBuffPause->Unlock();


	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitPause(void)
{
	for (int nCntTex = 0; nCntTex < MAX_PAUSE_TEX; nCntTex++)
	{
		//テクスチャの破棄
		if (g_pTexturePause[nCntTex] != NULL)
		{
			g_pTexturePause[nCntTex]->Release();
			g_pTexturePause[nCntTex] = NULL;
		}

	}
	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
bool UpdatePause(void)
{
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ
	PLAYER				*pPlayer;	//プレイヤーの構造体

	pPlayer = GetPlayer();			//プレイヤーの情報を取得

	g_bPuse = false;				//ポーズか

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_DOWN) == true)
	{
		if (g_pause[0].bUse == true)
		{
			g_pause[0].bUse = false;
			g_pause[1].bUse = true;
		}
		else if (g_pause[1].bUse == true)
		{
			g_pause[1].bUse = false;
			g_pause[2].bUse = true;
		}
		else if (g_pause[2].bUse == true)
		{
			g_pause[2].bUse = false;
			g_pause[0].bUse = true;
		}
	}
	else if (GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_UP) == true)
	{
		if (g_pause[0].bUse == true)
		{
			g_pause[0].bUse = false;
			g_pause[2].bUse = true;
		}
		else if (g_pause[1].bUse == true)
		{
			g_pause[1].bUse = false;
			g_pause[0].bUse = true;
		}
		else if (g_pause[2].bUse == true)
		{
			g_pause[2].bUse = false;
			g_pause[1].bUse = true;
		}
	}

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		if (g_pause[nCntPause].bUse == true)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else if (g_pause[nCntPause].bUse == false)
		{
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 150);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 150);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 150);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 150);
		}
		if (GetKeyboardPress(DIK_Z) == true || GetKeyboardPress(DIK_LSHIFT) == true)
		{
			PlaySound(SOUND_LABEL_SE000);
			if (g_pause[nCntPause].nType == 0 && g_pause[nCntPause].bUse == true)
			{
				g_bPuse = true;
			}
			else if (g_pause[nCntPause].nType == 1 && g_pause[nCntPause].bUse == true)
			{
				g_bPuse = true;
				pPlayer->bUse = false;
				AddLife(-1);
				if (GetMode() == MODE_ES_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_ES_STAGE02)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 290.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_ES_STAGE03)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 300.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE02)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 400.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE03)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 650.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_NO_STAGE04)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, SCREEN_HEIGHT - 10.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
				else if (GetMode() == MODE_HD_STAGE01)
				{
					SetPlayer(D3DXVECTOR3(0.0f + PLAYER_X_SIZE / 2 * 1.1f, 250.0f, 0.0f), PLAYER_X_SIZE, PLAYER_Y_SIZE);
				}
			}
			else if (g_pause[nCntPause].nType == 2 && g_pause[nCntPause].bUse == true && GetFade() == FADE_NONE)
			{
				UninitScore();

				UninitTimer();

				UninitLife();
				
				SetFade(MODE_HOME);
			}
		}
		pVtx += 4;	//頂点を進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	return g_bPuse;
}

//---------------------------
//描画処理
//---------------------------
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffPause,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

									//ブロックの数ループ
	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		pDevice->SetTexture(0, g_pTexturePause[g_pause[nCntPause].nType]);		//テクスチャの設定
		//ポリゴンの描画
		pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
								nCntPause * 4,
								2);
	}
}