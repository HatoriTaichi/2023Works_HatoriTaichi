//---------------------------
//インクルードファイル
//---------------------------
#include "picture.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTexturePicture[MAX_PICTURE_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPicture = NULL;			//頂点バッファへのポインタ
Picture					g_aPicture[MAX_PICTURE];			//BGの構造体
static float			g_fCol = 255.0f;					//点滅

//---------------------------
//初期化処理
//---------------------------
HRESULT InitPicture(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		g_aPicture[nCntPicture].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_aPicture[nCntPicture].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_aPicture[nCntPicture].aType = PICTURE_TYPE_TITLE;				//種類
		g_aPicture[nCntPicture].bUse = false;		//使ってるかどうか
	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,	
								"data/Texture/title_00.png",			//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_TITLE]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/push to enter_00.png",	//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_ENTER]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/guys_00.png",				//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_GUYS_00]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/guys_01.png",				//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_GUYS_01]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/guys_02.png",				//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_GUYS_02]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/guys_03.png",				//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_GUYS_03]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/guninfo_line_00.png",		//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_GUNLINE_00]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/gun_remaining_00.png",	//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_GUNREMAINING_00]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/test_result.png",			//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_RESULT]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/round_00.png",			//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_ROUND]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/reticle_00.png",			//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_RETICLE_00]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/1st.png",					//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_1ST]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/2nd.png",					//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_2ND]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/3rd.png",					//テクスチャ
								&g_pTexturePicture[PICTURE_TYPE_3RD]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_PICTURE,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffPicture,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPicture->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPicture->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitPicture(void)
{
	for (int nCnTex = 0; nCnTex < MAX_PICTURE_TEX; nCnTex++)
	{
		//テクスチャの破棄
		if (g_pTexturePicture[nCnTex] != NULL)
		{
			g_pTexturePicture[nCnTex]->Release();
			g_pTexturePicture[nCnTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPicture != NULL)
	{
		g_pVtxBuffPicture->Release();
		g_pVtxBuffPicture = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
bool UpdatePicture(void)
{
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	static int nCnt;
	int nNum = 0; 

	nCnt++;
	//一秒たったら
	if (nCnt >= 72)
	{
		//透明度0
		if (g_fCol == 0.0f)
		{
			//透明度255
			g_fCol = 255.0f;
		}
		//透明度255
		else if (g_fCol == 255.0f)
		{
			//透明度0
			g_fCol = 0.0f;
		}
		nCnt = 0;
	}

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPicture->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		if (g_aPicture[nCntPicture].bUse == true)
		{
			nNum = nCntPicture;
			if (g_aPicture[nCntPicture].aType == PICTURE_TYPE_ENTER)
			{
				pVtx[0].col = D3DXCOLOR(255, 255, 255, g_fCol);
				pVtx[1].col = D3DXCOLOR(255, 255, 255, g_fCol);
				pVtx[2].col = D3DXCOLOR(255, 255, 255, g_fCol);
				pVtx[3].col = D3DXCOLOR(255, 255, 255, g_fCol);
			}
			else if (g_aPicture[nCntPicture].aType == PICTURE_TYPE_GUYS_00)
			{
				g_aPicture[nCntPicture].pos += g_aPicture[nCntPicture].move;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);

				if (g_aPicture[nCntPicture].pos.y <= 720 + 200.0f)
				{
					g_aPicture[nCntPicture].move.y *= -1;
				}
				if (g_aPicture[nCntPicture].pos.y >= SCREEN_HEIGHT + 260.0f)
				{
					g_aPicture[nCntPicture].bUse = false;
				}
			}
			else if (g_aPicture[nCntPicture].aType == PICTURE_TYPE_GUYS_01)
			{
				g_aPicture[nCntPicture].pos += g_aPicture[nCntPicture].move;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);

				if (g_aPicture[nCntPicture].pos.y >= 360 - 300.0f)
				{
					g_aPicture[nCntPicture].move.y *= -1;
				}
				if (g_aPicture[nCntPicture].pos.y <= 0 - 260.0f)
				{
					g_aPicture[nCntPicture].bUse = false;
				}
			}
			else if (g_aPicture[nCntPicture].aType == PICTURE_TYPE_GUYS_02)
			{
				g_aPicture[nCntPicture].pos += g_aPicture[nCntPicture].move;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);

				if (g_aPicture[nCntPicture].pos.x <= 1280.0 + 300.0f)
				{
					g_aPicture[nCntPicture].move.x *= -1;
				}
				if (g_aPicture[nCntPicture].pos.x >= SCREEN_WIDTH + 260.0f)
				{
					g_aPicture[nCntPicture].bUse = false;
				}
			}
			else if (g_aPicture[nCntPicture].aType == PICTURE_TYPE_GUYS_03)
			{
				g_aPicture[nCntPicture].pos += g_aPicture[nCntPicture].move;

				//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);

				if (g_aPicture[nCntPicture].pos.x >= 320.0f)
				{
					g_aPicture[nCntPicture].move.x *= -1;
				}
				if (g_aPicture[nCntPicture].pos.x <= 0 - 260.0f)
				{
					g_aPicture[nCntPicture].bUse = false;
				}
			}
		}
		pVtx += 4;	//頂点を進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPicture->Unlock();

	return g_aPicture[nNum].bUse;
}

//---------------------------
//描画処理
//---------------------------
void DrawPicture(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffPicture,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		if (g_aPicture[nCntPicture].bUse == true)
		{
			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 130);

			pDevice->SetTexture(0, g_pTexturePicture[g_aPicture[nCntPicture].aType]);		//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntPicture * 4,
									2);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//BGのセット
//---------------------------
bool SetPicture(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWigth, float fHeight, PICTURE_TYPE aType)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ
	int nNum = 0;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffPicture->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPicture = 0; nCntPicture < MAX_PICTURE; nCntPicture++)
	{
		if (g_aPicture[nCntPicture].bUse == false)
		{
			nNum = nCntPicture;
			g_aPicture[nCntPicture].pos = pos;				//持ってきた位置を代入
			g_aPicture[nCntPicture].move = move;			//持ってきた移動量を代入
			g_aPicture[nCntPicture].fWidth = fWigth;		//持ってきた幅
			g_aPicture[nCntPicture].fHeight = fHeight;		//持ってきた高さ
			g_aPicture[nCntPicture].aType = aType;			//持ってきた種類

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y - g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x - g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aPicture[nCntPicture].pos.x + g_aPicture[nCntPicture].fWidth / 2, g_aPicture[nCntPicture].pos.y + g_aPicture[nCntPicture].fHeight / 2, g_aPicture[nCntPicture].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
			pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
			pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
			pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

			g_aPicture[nCntPicture].bUse = true;
			break;
		}
		pVtx += 4;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPicture->Unlock();

	return g_aPicture[nNum].bUse;
}