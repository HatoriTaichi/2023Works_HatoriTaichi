//---------------------------
//インクルードファイル
//---------------------------
#include "block.h"
#include "player.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_BLOCK_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;					//頂点バッファへのポインタ
BLOCK					g_block[MAX_BLOCK];						//ブロックの構造体

//---------------------------
//初期化処理
//---------------------------
HRESULT InitBlock(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ

	pDevice = GetDevice();			//デバイスの取得

	//ブロックの数ループ
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_block[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//ブロックの位置
		g_block[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//ブロックの移動量
		g_block[nCntBlock].fWidth = 0.0f;						//ブロックの横幅
		g_block[nCntBlock].fHeight = 0.0f;						//ブロックの縦幅
		g_block[nCntBlock].nType = 0;							//ブロックの種類
		g_block[nCntBlock].bUse = false;						//ブロックの状態
		g_block[nCntBlock].bPuse = false;						//透明ぶろっく

	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/marble00.jpeg",	//テクスチャ
								&g_pTextureBlock[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/marble01.jpg",	//テクスチャ
								&g_pTextureBlock[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/marble02.jpg",		//テクスチャ
								&g_pTextureBlock[2]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBlock,
									NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの数ループ
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

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
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitBlock(void)
{
	//テクスチャの数ループ
	for ( int nCntBlock = 0; nCntBlock < MAX_BLOCK_TEX; nCntBlock++)
	{
		//テクスチャの破棄
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	PLAYER    *pPlayer;	//プレイヤー構造体へのポインタ

	pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの数ループ
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//使ってたら
		if (g_block[nCntBlock].bUse == true)
		{
			if (g_block[nCntBlock].nType == 0)
			{
				
			}
			if (g_block[nCntBlock].nType == 1)
			{
				if (GetMode() == MODE_HOME)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//移動量を+
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//半分の高さになったら
					if (g_block[nCntBlock].pos.y <= SCREEN_HEIGHT / 2)
					{
						g_block[nCntBlock].move *= -1;	//反転
					}
					//下に来たら
					else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - BLOCK_Y_SIZE * 3 + 2.0f)
					{
						g_block[nCntBlock].move *= -1;	//反転
					}
				}
				else if (GetMode() == MODE_ES_STAGE01)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//移動量を+
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//半分の高さになったら
					if (g_block[nCntBlock].pos.y <= 250)
					{
						g_block[nCntBlock].move *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
					//下に来たら
					else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - BLOCK_Y_SIZE * 3.5)
					{
						g_block[nCntBlock].move *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
				}
				else if (GetMode() == MODE_ES_STAGE02)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//移動量を+
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//半分の高さになったら
					if (g_block[nCntBlock].pos.y <= 250)
					{
						g_block[nCntBlock].move *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
					//下に来たら
					else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT)
					{
						g_block[nCntBlock].move *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
				}
				else if (GetMode() == MODE_ES_STAGE03)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//移動量を+
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//半分の高さになったら
					if (g_block[nCntBlock].pos.y <= 120)
					{
						g_block[nCntBlock].move *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
					//下に来たら
					else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - 150.0f)
					{
						g_block[nCntBlock].move *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
				}
				else if (GetMode() == MODE_NO_STAGE01)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					if (g_block[nCntBlock].move.x >= 0.0f && g_block[nCntBlock].move.y == 0.0f ||
						g_block[nCntBlock].move.x <= 0.0f && g_block[nCntBlock].move.y == 0.0f)
					{
						//移動
						g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

						//半分の高さになったら
						if (g_block[nCntBlock].pos.x <= 350)
						{
							g_block[nCntBlock].move.x *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
						//下に来たら
						else if (g_block[nCntBlock].pos.x >= SCREEN_WIDTH / 2)
						{
							g_block[nCntBlock].move.x *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
					}
					else if (g_block[nCntBlock].move.y <= 0.0f && g_block[nCntBlock].move.x == 0.0f ||
							 g_block[nCntBlock].move.y >= 0.0f && g_block[nCntBlock].move.x == 0.0f)
					{
						//移動
						g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;
						//半分の高さになったら
						if (g_block[nCntBlock].pos.y <= 180)
						{
							g_block[nCntBlock].move.y *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
						//下に来たら
						else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - 50.0f)
						{
							g_block[nCntBlock].move.y *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
					}
				}
				else if (GetMode() == MODE_NO_STAGE02)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//移動
					g_block[nCntBlock].pos += g_block[nCntBlock].move;

					//半分の高さになったら
					if (g_block[nCntBlock].pos.x >= SCREEN_WIDTH - 280.0f)
					{
						g_block[nCntBlock].move.x *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
					else if (g_block[nCntBlock].pos.x <= 330.0f)
					{
						g_block[nCntBlock].move.x *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
				}
				else if (GetMode() == MODE_NO_STAGE03)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					if (g_block[nCntBlock].move.x >= 0.0f && g_block[nCntBlock].move.y == 0.0f ||
						g_block[nCntBlock].move.x <= 0.0f && g_block[nCntBlock].move.y == 0.0f)
					{
						//移動
						g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

						//半分の高さになったら
						if (g_block[nCntBlock].pos.x <= 350)
						{
							g_block[nCntBlock].move.x *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
						//下に来たら
						else if (g_block[nCntBlock].pos.x >= SCREEN_WIDTH / 2)
						{
							g_block[nCntBlock].move.x *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
					}
					else if (g_block[nCntBlock].move.y <= 0.0f && g_block[nCntBlock].move.x == 0.0f ||
						g_block[nCntBlock].move.y >= 0.0f && g_block[nCntBlock].move.x == 0.0f)
					{
						//移動
						g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;
						//半分の高さになったら
						if (g_block[nCntBlock].pos.y <= 180)
						{
							g_block[nCntBlock].move.y *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
						//下に来たら
						else if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - 50.0f)
						{
							g_block[nCntBlock].move.y *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
					}
				}
				else if (GetMode() == MODE_NO_STAGE04)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//移動
					g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

					//半分の高さになったら
					if (g_block[nCntBlock].pos.x >= SCREEN_WIDTH - 600.0f)
					{
						g_block[nCntBlock].move.x *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
					else if (g_block[nCntBlock].pos.x <= 150.0f)
					{
						g_block[nCntBlock].move.x *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
				}
				else if (GetMode() == MODE_HD_STAGE02)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					if (g_block[nCntBlock].move.x >= 0.0f && g_block[nCntBlock].move.y == 0.0f ||
						g_block[nCntBlock].move.x <= 0.0f && g_block[nCntBlock].move.y == 0.0f)
					{
						//移動
						g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

						//半分の高さになったら
						if (g_block[nCntBlock].pos.x <= 650)
						{
							g_block[nCntBlock].move.x *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
						//下に来たら
						else if (g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth >= 1080)
						{
							g_block[nCntBlock].move.x *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
					}
					else if (g_block[nCntBlock].move.y <= 0.0f && g_block[nCntBlock].move.x == 0.0f ||
						g_block[nCntBlock].move.y >= 0.0f && g_block[nCntBlock].move.x == 0.0f)
					{
						//移動
						g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;
						//半分の高さになったら
						if (g_block[nCntBlock].pos.y <= 100.0f)
						{
							g_block[nCntBlock].move.y *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
						//下に来たら
						else if (g_block[nCntBlock].pos.y >= 670)
						{
							g_block[nCntBlock].move.y *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
					}
				}
				else if (GetMode() == MODE_HD_STAGE03)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					if (g_block[nCntBlock].move.x >= 0.0f && g_block[nCntBlock].move.y == 0.0f ||
						g_block[nCntBlock].move.x <= 0.0f && g_block[nCntBlock].move.y == 0.0f)
					{
						//移動
						g_block[nCntBlock].pos.x += g_block[nCntBlock].move.x;

						//半分の高さになったら
						if (g_block[nCntBlock].pos.x <= 250)
						{
							g_block[nCntBlock].move.x *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
						//下に来たら
						else if (g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth >= 1080)
						{
							g_block[nCntBlock].move.x *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
					}
					else if (g_block[nCntBlock].move.y <= 0.0f && g_block[nCntBlock].move.x == 0.0f ||
						g_block[nCntBlock].move.y >= 0.0f && g_block[nCntBlock].move.x == 0.0f)
					{
						//移動
						g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;
						//半分の高さになったら
						if (g_block[nCntBlock].pos.y <= 150.0f)
						{
							g_block[nCntBlock].move.y *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
						//下に来たら
						else if (g_block[nCntBlock].pos.y >= 650)
						{
							g_block[nCntBlock].move.y *= -1;							//反転
							g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
						}
					}
				}
				else if (GetMode() == MODE_HD_STAGE04)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//移動
					g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;

					//半分の高さになったら
					if (g_block[nCntBlock].pos.y >= SCREEN_HEIGHT - 100.0f)
					{
						g_block[nCntBlock].move.y *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
					else if (g_block[nCntBlock].pos.y <= 300.0f)
					{
						g_block[nCntBlock].move.y *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
				}
				else if (GetMode() == MODE_HD_STAGE05)
				{
					//頂点座標の更新
					pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

					//移動
					g_block[nCntBlock].pos.y += g_block[nCntBlock].move.y;

					//半分の高さになったら
					if (g_block[nCntBlock].pos.y >= (SCREEN_HEIGHT - 10.0f) - 100.0f)
					{
						g_block[nCntBlock].move.y *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
					else if (g_block[nCntBlock].pos.y <= 200.0f)
					{
						g_block[nCntBlock].move.y *= -1;							//反転
						g_block[nCntBlock].nowmove = g_block[nCntBlock].move;	//現在の移動量を保存
					}
				}
			}
			if (g_block[nCntBlock].nType == 2)
			{
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//---------------------------
//描画処理
//---------------------------
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ

	pDevice = GetDevice();		//デバイスを取得する

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffBlock,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	//ブロックの数ループ
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//使ってたら
		if (g_block[nCntBlock].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBlock[g_block[nCntBlock].nType]);		//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntBlock * 4,
									2);
		}
	}
}

//---------------------------
//ブロックのセット
//---------------------------

void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, float fTexwidth, float fTexheight, int nType)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ
	
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの数ループ
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//使ってなかったら
		if (g_block[nCntBlock].bUse == false)
		{
			g_block[nCntBlock].pos = pos;				//持ってきた位置を代入
			g_block[nCntBlock].move = move;				//持ってきた移動量を代入
			g_block[nCntBlock].fWidth = fWidth;			//持ってきた横幅を代入
			g_block[nCntBlock].fHeight = fHeight;		//持ってきた縦幅を代入
			g_block[nCntBlock].nType = nType;			//持ってきた種類を代入
			g_block[nCntBlock].fTexwidth = fTexwidth;	//持ってきたテクスチャの横幅を代入
			g_block[nCntBlock].fTexheigth = fTexheight;	//持ってきたテクスチャの縦幅を代入

			//頂点座標の更新
			pVtx[0].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y, g_block[nCntBlock].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_block[nCntBlock].pos.x + g_block[nCntBlock].fWidth, g_block[nCntBlock].pos.y + g_block[nCntBlock].fHeight, g_block[nCntBlock].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//ブロックタイプが2だったら2
			if (g_block[nCntBlock].nType == 2)
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			}
			//それ以外
			else
			{
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}

			pVtx[0].tex = D3DXVECTOR2(0.0f							, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_block[nCntBlock].fTexwidth	, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f							, g_block[nCntBlock].fTexheigth);
			pVtx[3].tex = D3DXVECTOR2(g_block[nCntBlock].fTexwidth	, g_block[nCntBlock].fTexheigth);

			g_block[nCntBlock].bUse = true;	//使ってる状態
			break;
		}
		pVtx += 4;	//頂点を進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//---------------------------
//ブロックとの当たり判定
//---------------------------

bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float fWidth, float fHeight, int nType)
{
	BLOCK *pBlock;			//ブロックへのポインタ
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	bool bLand = false;		//地面についてるか
	pBlock = &g_block[0];	//ブロックの情報を取得

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	//ブロックの数分ループ
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		//使ってたら
		if (pBlock->bUse == true)
		{
			if (pBlock->nType == 2 && pBlock->bPuse == false)
			{
				//ブロックの横の範囲内
				if (pPos->x + fWidth / 2 >= pBlock->pos.x &&
					pPos->x - fWidth / 2 <= pBlock->pos.x + pBlock->fWidth)
				{
					if (pPosold->y - fHeight >= pBlock->pos.y + pBlock->fHeight &&
						pPos->y - fHeight <= pBlock->pos.y + pBlock->fHeight)
					{
						pMove->y = 0.0f;										//重力を0に
						pPos->y = pBlock->pos.y + pBlock->fHeight + fHeight;	//ブロック外に戻す
						if (nType == 0)
						{
							pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
							pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

							pBlock->bPuse = true;
						}
					}
				}
			}
			else if(pBlock->nType != 2 || pBlock->bPuse == true)
			{
				//ブロックの横の範囲内
				if (pPos->x + fWidth / 2 >= pBlock->pos.x &&
					pPos->x - fWidth / 2 <= pBlock->pos.x + pBlock->fWidth)
				{
					//ブロックに上からめり込んでたら
					if (pPosold->y <= pBlock->pos.y &&
						pPos->y >= pBlock->pos.y)
					{
						//タイプ4だったら
						if (nType == 4)
						{
							bLand = true;
							if (GetMode() == MODE_NO_STAGE04)
							{
								pMove->y *= -1;		//反転
								pMove->x = 0.0f;
							}
							else if (GetMode() == MODE_HD_STAGE05)
							{
								pMove->y *= -1;
							}
							else if (GetMode() == MODE_ES_STAGE03)
							{
								pMove->y *= -1;		//反転
							}
						}
						else if (nType == 3)
						{
							bLand = true;
						}
						else
						{
							pMove->y = 0.0f;				//重力を0に
							pPos->y = pBlock->pos.y;		//ブロック外に戻る
							pPos->y += pBlock->move.y;		//移動量+
							pPos->x += pBlock->move.x;		//移動量+
							bLand = true;					//地面についてる
						}
						//左から落ちそう
						if (pPosold->x - fWidth / 2 >= pBlock->pos.x &&
							pPos->x - fWidth / 2 <= pBlock->pos.x)
						{
							//タイプ0だったら
							if (nType == 0)
							{
								bLand = false;			//地面についてない
							}
							//タイプ1だったら
							if (nType == 2)
							{
								
							}
						}
						//右から落ちそう
						else if (pPosold->x + fWidth / 2 <= pBlock->pos.x + pBlock->fWidth &&
							pPos->x + fWidth / 2 >= pBlock->pos.x + pBlock->fWidth)
						{
							//タイプ0だったら
							if (nType == 0)
							{
								bLand = false;			//地面についてない
							}
							//タイプ1だったら
							if (nType == 2)
							{
								
							}
						}
					}
					//ブロックに頭がぶつかったら
					else if (pPosold->y - fHeight >= pBlock->pos.y + pBlock->fHeight &&
							pPos->y - fHeight <= pBlock->pos.y + pBlock->fHeight)
					{
						//タイプ0だったら
						if (nType == 0)
						{
							bLand = false;			//地面についてない
						}
						//タイプ4だったら
						if (nType == 4)
						{
							bLand = true;
							if (GetMode() == MODE_NO_STAGE04)
							{
								pMove->y *= -1;		//反転
								pMove->x = 2.0f;
							}
							else if (GetMode() == MODE_HD_STAGE05)
							{
								pMove->y *= -1;
							}
							else if (GetMode() == MODE_ES_STAGE03)
							{
								pMove->y *= -1;		//反転
							}
						}
						//タイプ3だったら
						else if (nType == 3)
						{
							bLand = true;		//かべにぶつかってる
						}
						else
						{
							pMove->y = 0.0f;										//重力を0に
							pPos->y = pBlock->pos.y + pBlock->fHeight + fHeight;	//ブロック外に戻す
						}
					}
				}
				//ブロックの縦の範囲内だったら
				if (pPos->y - fHeight <= pBlock->pos.y + pBlock->fHeight&&
					pPos->y >= pBlock->pos.y)
				{
					//右からめり込んでたら
					if (pPosold->x + fWidth / 2 <= pBlock->pos.x &&
						pPos->x + fWidth / 2 >= pBlock->pos.x)
					{
						//ブロック外に戻す
						pPos->x = pBlock->pos.x - fWidth / 2;
						//タイプ0だったら
						if (nType == 0)
						{
							bLand = false;		//地面についてない
						}
						//タイプ1だったら
						if (nType == 1)
						{
							pMove->x *= -1;		//反転
						}
						//タイプ2だったら
						if (nType == 2)
						{
							pMove->x *= -1;		//反転
						}
						//タイプ3だったら
						if (nType == 3)
						{
							bLand = true;		//かべにぶつかってる
						}
						//タイプ4
						if (nType == 4)
						{
							bLand = true;
							if (GetMode() == MODE_HD_STAGE05)
							{
								pMove->x *= -1;
							}
							else
							{
								pMove->x *= -1;		//反転
							}
						}
					}
					//左からめり込んでたら
					else if (pPosold->x - fWidth / 2 >= pBlock->pos.x + pBlock->fWidth &&
						pPos->x - fWidth / 2 <= pBlock->pos.x + pBlock->fWidth)
					{
						//ブロック外に戻す
						pPos->x = pBlock->pos.x + pBlock->fWidth + fWidth / 2;
						//タイプ0だったら
						if (nType == 0)
						{
							bLand = false;		//地面についてない
						}
						//タイプ1だったら
						if (nType == 1)
						{
							pMove->x *= -1;		//反転
						}
						//タイプ2だったら
						if (nType == 2)
						{
							pMove->x *= -1;		//反転
						}
						//タイプ3だったら
						if (nType == 3)
						{
							bLand = true;		//かべにぶつかってる
						}
					}
				}
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

	return bLand;	//ブロックに着地してるかを返す
}
//---------------------------
//ブロックの状態を入手
//---------------------------

BLOCK *GetBlock(void)
{
	return &g_block[0];
}
