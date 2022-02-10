//---------------------------
//インクルードファイル
//---------------------------
#include "shadow.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//頂点バッファへのポインタ
Shadow					g_aShadow[MAX_SHADOW];		//影の構造体			

//---------------------------
//グローバル変数
//---------------------------
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

	//値の初期化
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aShadow[nCntShadow].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aShadow[nCntShadow].fHeiht = 0.0f;
		g_aShadow[nCntShadow].fWhith = SHADOW_X;
		g_aShadow[nCntShadow].fDepht = SHADOW_Z;
		g_aShadow[nCntShadow].fAlpha = 255.0f;
		g_aShadow[nCntShadow].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/shadow000.jpg",			//テクスチャ
								&g_pTextureShadow);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffShadow,
									NULL);
	//---------------------------
	//頂点情報
	//---------------------------
	VERTEX_3D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].fWhith / 2, 0.0f, g_aShadow[nCntShadow].fDepht / 2);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWhith / 2, 0.0f, g_aShadow[nCntShadow].fDepht / 2);
		pVtx[2].pos = D3DXVECTOR3(-g_aShadow[nCntShadow].fWhith / 2, 0.0f, -g_aShadow[nCntShadow].fDepht / 2);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].fWhith / 2, 0.0f, -g_aShadow[nCntShadow].fDepht / 2);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(255, 255, 255, g_aShadow[nCntShadow].fAlpha);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, g_aShadow[nCntShadow].fAlpha);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, g_aShadow[nCntShadow].fAlpha);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, g_aShadow[nCntShadow].fAlpha);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitShadow(void)
{
	//---------------------------
	//テクスチャ破棄
	//---------------------------
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//---------------------------
	//バッファ破棄
	//---------------------------
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateShadow(void)
{
	
}

//---------------------------
//描画処理
//---------------------------
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{
			//カリング有
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

			//減算合成
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			// マトリックス初期化
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			//スケール
			g_aShadow[nCntShadow].mtxWorld._11 = g_aShadow[nCntShadow].fWhith;
			g_aShadow[nCntShadow].mtxWorld._33 = g_aShadow[nCntShadow].fDepht;

			//向きの設定
			D3DXMatrixRotationYawPitchRoll(	&mtxRot,
											g_aShadow[nCntShadow].rot.y,
											g_aShadow[nCntShadow].rot.x,
											g_aShadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(	&g_aShadow[nCntShadow].mtxWorld,
								&g_aShadow[nCntShadow].mtxWorld,
								&mtxRot);
			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aShadow[nCntShadow].pos.x,
									g_aShadow[nCntShadow].pos.y,
									g_aShadow[nCntShadow].pos.z);

			D3DXMatrixMultiply(	&g_aShadow[nCntShadow].mtxWorld,
								&g_aShadow[nCntShadow].mtxWorld,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aShadow[nCntShadow].mtxWorld);

			//---------------------------
			//描画処理
			//---------------------------
			//バッファの設定をデータストリームに設定
			pDevice->SetStreamSource(	0,
										g_pVtxBuffShadow,
										0,
										sizeof(VERTEX_3D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_pTextureShadow);
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntShadow * 4,			//何番目から描画するか
									2);						//△の数
			//通常の設定に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//---------------------------
//影の情報
//---------------------------
int SetShadow(D3DXVECTOR3 pos, float fWhith, float fDepht)
{
	int Index = -1;

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos.x = pos.x;	//位置を代入
			g_aShadow[nCntShadow].pos.z = pos.z;	//位置を代入
			g_aShadow[nCntShadow].fWhith = fWhith;	//幅を代入
			g_aShadow[nCntShadow].fDepht = fDepht;	//高さを代入

			g_aShadow[nCntShadow].bUse = true;
			Index = nCntShadow;
			break;
		}
	}
	return Index;	//使ってる影を渡す
}

//---------------------------
//指定の影をセット
//---------------------------
void SetPointShadow(int nIdx, D3DXVECTOR3 pos, float fWhith, float fDepht, bool bUse)
{
	VERTEX_3D			*pVtx;		//頂点情報へのポインタ

	g_aShadow[nIdx].pos.x = pos.x;	//指定した影が付いてくる
	g_aShadow[nIdx].pos.z = pos.z;	//指定した影が付いてくる

	g_aShadow[nIdx].fWhith = fWhith + (pos.y / 3.0f);
	g_aShadow[nIdx].fDepht = fDepht + (pos.y / 3.0f);
	g_aShadow[nIdx].fAlpha = 1.0f - pos.y / 400.0f;

	if (g_aShadow[nIdx].fAlpha <= 0.0f)
	{
		g_aShadow[nIdx].fAlpha = 0.0f;
	}
	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;	//頂点を進める

	pVtx[0].col = D3DXCOLOR(255, 255, 255, g_aShadow[nIdx].fAlpha);
	pVtx[1].col = D3DXCOLOR(255, 255, 255, g_aShadow[nIdx].fAlpha);
	pVtx[2].col = D3DXCOLOR(255, 255, 255, g_aShadow[nIdx].fAlpha);
	pVtx[3].col = D3DXCOLOR(255, 255, 255, g_aShadow[nIdx].fAlpha);

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	//持ってる影のせいし
	g_aShadow[nIdx].bUse = bUse;
}