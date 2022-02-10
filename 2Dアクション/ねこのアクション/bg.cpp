//---------------------------
//インクルードファイル
//---------------------------
#include "bg.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureBg[MAX_BG_TEX] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;				//頂点バッファへのポインタ
BG						g_bg[MAX_BG];						//BGの構造体
static float			g_fCol = 255.0f;					//点滅

//---------------------------
//初期化処理
//---------------------------
HRESULT InitBg(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ
	VERTEX_2D			*pVtx;		//頂点情報へのポインタ

	pDevice = GetDevice();			//デバイスの取得

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		g_bg[nCntBg].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
		g_bg[nCntBg].nType = 0;			//種類
		g_bg[nCntBg].bUse = false;		//使ってるかどうか
	}
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,	
								"data/Texture/bg.00.png",				//テクスチャ
								&g_pTextureBg[0]);	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/worter.jpg",				//テクスチャ
								&g_pTextureBg[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/title.png",				//テクスチャ
								&g_pTextureBg[2]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/description.png",			//テクスチャ
								&g_pTextureBg[3]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/result.png",				//テクスチャ
								&g_pTextureBg[4]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/push to neter 00.png",	//テクスチャ
								&g_pTextureBg[5]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/gameover.png",			//テクスチャ
								&g_pTextureBg[6]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/1st.png",					//テクスチャ
								&g_pTextureBg[7]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/2nd.png",					//テクスチャ
								&g_pTextureBg[8]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/3rd.png",					//テクスチャ
								&g_pTextureBg[9]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/you.png",					//テクスチャ
								&g_pTextureBg[10]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/cat01.png",				//テクスチャ
								&g_pTextureBg[11]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4 * MAX_BG,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBg,
									NULL);
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
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
	g_pVtxBuffBg->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitBg(void)
{
	for (int nCnTex = 0; nCnTex < MAX_BG_TEX; nCnTex++)
	{
		//テクスチャの破棄
		if (g_pTextureBg[nCnTex] != NULL)
		{
			g_pTextureBg[nCnTex]->Release();
			g_pTextureBg[nCnTex] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateBg(void)
{
	VERTEX_2D *pVtx;	//頂点情報へのポインタ
	static int nCnt;

	nCnt++;
	//一秒たったら
	if (nCnt >= 144)
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
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntP = 0; nCntP < MAX_BG; nCntP++)
	{
		if (g_bg[nCntP].bUse == true)
		{
			if (g_bg[nCntP].nType == 5)
			{
				pVtx[0].col = D3DXCOLOR(255, 255, 255, g_fCol);
				pVtx[1].col = D3DXCOLOR(255, 255, 255, g_fCol);
				pVtx[2].col = D3DXCOLOR(255, 255, 255, g_fCol);
				pVtx[3].col = D3DXCOLOR(255, 255, 255, g_fCol);
			}
		}
		pVtx += 4;	//頂点を進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();
}

//---------------------------
//描画処理
//---------------------------
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	pDevice = GetDevice();		//デバイスを取得する
								//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffBg,
								0,
								sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);	//頂点フォーマットの設定

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		if (g_bg[nCntBg].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureBg[g_bg[nCntBg].nType]);		//テクスチャの設定
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntBg * 4,
									2);
		}
	}
}

//---------------------------
//BGのセット
//---------------------------
void SetBg(D3DXVECTOR3 pos, float fWigth, float fHeight, int nType)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		if (g_bg[nCntBg].bUse == false)
		{
			g_bg[nCntBg].pos = pos;				//持ってきた位置を代入
			g_bg[nCntBg].fWidth = fWigth;		//持ってきた幅
			g_bg[nCntBg].fHeight = fHeight;		//持ってきた高さ
			g_bg[nCntBg].nType = nType;			//持ってきた種類

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_bg[nCntBg].pos.x, g_bg[nCntBg].pos.y, g_bg[nCntBg].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_bg[nCntBg].pos.x + g_bg[nCntBg].fWidth, g_bg[nCntBg].pos.y, g_bg[nCntBg].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_bg[nCntBg].pos.x, g_bg[nCntBg].pos.y + g_bg[nCntBg].fHeight, g_bg[nCntBg].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_bg[nCntBg].pos.x + g_bg[nCntBg].fWidth, g_bg[nCntBg].pos.y + g_bg[nCntBg].fHeight, g_bg[nCntBg].pos.z);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			if (nType == 1)
			{
				//イージー
				if (GetMode() == MODE_ES_STAGE01 || GetMode() == MODE_ES_STAGE02 || GetMode() == MODE_ES_STAGE03)
				{
					pVtx[0].col = D3DXCOLOR(200, 200, 200, 255);
					pVtx[1].col = D3DXCOLOR(200, 200, 200, 255);
					pVtx[2].col = D3DXCOLOR(200, 200, 200, 255);
					pVtx[3].col = D3DXCOLOR(200, 200, 200, 255);
				}
				//ノーマル
				else if (GetMode() == MODE_NO_STAGE01 || GetMode() == MODE_NO_STAGE02 || GetMode() == MODE_NO_STAGE03 || GetMode() == MODE_NO_STAGE04)
				{
					pVtx[0].col = D3DXCOLOR(255, 200, 200, 255);
					pVtx[1].col = D3DXCOLOR(255, 200, 200, 255);
					pVtx[2].col = D3DXCOLOR(255, 200, 200, 255);
					pVtx[3].col = D3DXCOLOR(255, 200, 200, 255);
				}
				//ハード
				else if (GetMode() == MODE_HD_STAGE01 || GetMode() == MODE_HD_STAGE02 || GetMode() == MODE_HD_STAGE03 || GetMode() == MODE_HD_STAGE04 || GetMode() == MODE_HD_STAGE05)
				{
					pVtx[0].col = D3DXCOLOR(255, 100, 100, 255);
					pVtx[1].col = D3DXCOLOR(255, 100, 100, 255);
					pVtx[2].col = D3DXCOLOR(255, 100, 100, 255);
					pVtx[3].col = D3DXCOLOR(255, 100, 100, 255);
				}
			}
			//それ以外
			else
			{
				pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
				pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);
			}

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_bg[nCntBg].bUse = true;
			break;
		}
		pVtx += 4;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();
}