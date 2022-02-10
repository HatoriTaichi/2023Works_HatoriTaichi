//---------------------------------
// インクルードファイル
//---------------------------------
#include "fade.h"

//---------------------------------
// グローバル変数
//----------------------------------
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	//頂点バッファへのポインタ
FADE g_fade;									//フェードの状態
MODE g_modeNext;								//次のフェード
D3DXCOLOR g_colorfade;							//フェードの色

//---------------------------------
// 初期化処理
//---------------------------------
void InitFade(MODE modeNext)
{
	g_fade = FADE_IN;
	g_modeNext = g_modeNext;
	g_colorfade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	VERTEX_2D *pVtx;				//頂点情報へのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/brack.png",	//使うテクスチャ
								&g_pTextureFade);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffFade,
									NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);


	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f + FADE_POLYGON_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f + FADE_POLYGON_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f + FADE_POLYGON_WIDTH, 0.0f + FADE_POLYGON_HEIGHT, 0.0f);	
	
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);							
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);							
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);							
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);							
																		
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);										
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);										
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);									
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);								
																					
	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();
}
//---------------------------------
//　終了処理
//---------------------------------
void UninitFade(void)
{
	//テクスチャの破棄
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
//---------------------------------
// 更新処理
//---------------------------------
void UpdateFade(void)
{
	VERTEX_2D *pVtx;

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{
			g_colorfade.a -= 0.01f;		//フェードの速さ
			if (g_colorfade.a <= 0.0f)
			{
				g_colorfade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorfade.a += 0.01f;		//フェードの速さ
			if (g_colorfade.a >= 1.0f)
			{
				g_colorfade.a = 1.0f;
				g_fade = FADE_IN;
				SetMode(g_modeNext);
			}
		}
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].col = g_colorfade;
		pVtx[1].col = g_colorfade;
		pVtx[2].col = g_colorfade;
		pVtx[3].col = g_colorfade;

		g_pVtxBuffFade->Unlock();
	}
}
//---------------------------------
// 描画処理
//---------------------------------
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//デバイスのポインタ
	pDevice = GetDevice();						//デバイスを取得する
	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								g_pVtxBuffFade,
								0,
								sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);					//頂点フォーマットの設定
	pDevice->SetTexture(0, g_pTextureFade);			//テクスチャの設定
	//ポリゴンの描画
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
							0,
							2);
}

//---------------------------------
// フェードのセット
//---------------------------------
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorfade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//---------------------------------
//フェードの情報を取得
//---------------------------------
FADE GetFade(void)
{
	return g_fade;
}