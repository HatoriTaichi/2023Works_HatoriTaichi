//---------------------------
//インクルードファイル
//---------------------------
#include "effect.h"

//---------------------------
//グローバル変数
//---------------------------
LPDIRECT3DTEXTURE9		g_pTextureEffect[MAX_EFFECT_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファへのポインタ
Effect					g_aEffect[MAX_EFFECT];		//影の構造体			

//---------------------------
//グローバル変数
//---------------------------
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//デバイスへのポインタ

	pDevice = GetDevice();			//デバイスの取得

									//値の初期化
	for (int nCntShadow = 0; nCntShadow < MAX_EFFECT; nCntShadow++)
	{
		g_aEffect[nCntShadow].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aEffect[nCntShadow].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aEffect[nCntShadow].fHeiht = 0.0f;
		g_aEffect[nCntShadow].fWhith = EFFECT_X;
		g_aEffect[nCntShadow].fHeiht = EFFECT_Z;
		g_aEffect[nCntShadow].fDepht = EFFECT_Z;
		g_aEffect[nCntShadow].fAlpha = 255.0f;
		g_aEffect[nCntShadow].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet_00.png",			//テクスチャ
								&g_pTextureEffect[EFFECT_TEX_GUN]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(	pDevice,
								"data/Texture/bullet_01.png",			//テクスチャ
								&g_pTextureEffect[EFFECT_TEX_DETH]);
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEffect,
									NULL);
	//---------------------------
	//頂点情報
	//---------------------------
	VERTEX_3D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_EFFECT; nCntShadow++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntShadow].fWhith / 2, g_aEffect[nCntShadow].fHeiht / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntShadow].fWhith / 2, g_aEffect[nCntShadow].fHeiht / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntShadow].fWhith / 2, -g_aEffect[nCntShadow].fHeiht / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntShadow].fWhith / 2, -g_aEffect[nCntShadow].fHeiht / 2, 0.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = D3DXCOLOR(255, 255, 255, g_aEffect[nCntShadow].fAlpha);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, g_aEffect[nCntShadow].fAlpha);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, g_aEffect[nCntShadow].fAlpha);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, g_aEffect[nCntShadow].fAlpha);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点を進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitEffect(void)
{
	//---------------------------
	//テクスチャ破棄
	//---------------------------
	for (int nTex = 0; nTex < MAX_EFFECT_TEX; nTex++)
	{
		if (g_pTextureEffect[nTex] != NULL)
		{
			g_pTextureEffect[nTex]->Release();
			g_pTextureEffect[nTex] = NULL;
		}
	}

	//---------------------------
	//バッファ破棄
	//---------------------------
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateEffect(void)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			g_aEffect[nCntEffect].nLife--;

			g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;

			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;	
			}
		}
	}
}

//---------------------------
//描画処理
//---------------------------
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9	pDevice;			//デバイスのポインタ

	pDevice = GetDevice();					//デバイスを取得する

	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMATRIX			mtxRot, mtxTrans;	//計算用マトリックス

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//カリング有
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

			//加算合成関係
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			// マトリックス初期化
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

			//カメラの向きを取得
			pDevice->GetTransform(	D3DTS_VIEW,
									&g_aEffect[nCntEffect].mtxView);

			//カメラの情報を入れて、スケールを反映
			g_aEffect[nCntEffect].mtxWorld._11 = g_aEffect[nCntEffect].mtxView._11 * g_aEffect[nCntEffect].fWhith;
			g_aEffect[nCntEffect].mtxWorld._12 = g_aEffect[nCntEffect].mtxView._21 * g_aEffect[nCntEffect].fWhith;
			g_aEffect[nCntEffect].mtxWorld._13 = g_aEffect[nCntEffect].mtxView._31 * g_aEffect[nCntEffect].fWhith;
			g_aEffect[nCntEffect].mtxWorld._21 = g_aEffect[nCntEffect].mtxView._12 * g_aEffect[nCntEffect].fHeiht;
			g_aEffect[nCntEffect].mtxWorld._22 = g_aEffect[nCntEffect].mtxView._22 * g_aEffect[nCntEffect].fHeiht;
			g_aEffect[nCntEffect].mtxWorld._23 = g_aEffect[nCntEffect].mtxView._32 * g_aEffect[nCntEffect].fHeiht;
			g_aEffect[nCntEffect].mtxWorld._31 = g_aEffect[nCntEffect].mtxView._13;
			g_aEffect[nCntEffect].mtxWorld._32 = g_aEffect[nCntEffect].mtxView._23;
			g_aEffect[nCntEffect].mtxWorld._33 = g_aEffect[nCntEffect].mtxView._33;

			//位置
			D3DXMatrixTranslation(	&mtxTrans,
									g_aEffect[nCntEffect].pos.x,
									g_aEffect[nCntEffect].pos.y,
									g_aEffect[nCntEffect].pos.z);

			D3DXMatrixMultiply(	&g_aEffect[nCntEffect].mtxWorld,
								&g_aEffect[nCntEffect].mtxWorld,
								&mtxTrans);
			//マトリックスの設定
			pDevice->SetTransform(	D3DTS_WORLD,
									&g_aEffect[nCntEffect].mtxWorld);

			//---------------------------
			//描画処理
			//---------------------------
			//バッファの設定をデータストリームに設定
			pDevice->SetStreamSource(	0,
										g_pVtxBuffEffect,
										0,
										sizeof(VERTEX_3D));
			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(	0,
									g_pTextureEffect[g_aEffect[nCntEffect].aTex]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP,	//プリミティブの種類
									nCntEffect * 4,			//何番目から描画するか
									2);						//△の数

			//通常合成に戻す(加算合成)
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//αテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
}

//---------------------------
//エフェクトの設定
//---------------------------
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWhith, float fHeight, EffectType aType, Effecttextype aTex, int nLife)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;		//位置を代入
			g_aEffect[nCntEffect].move = move;
			g_aEffect[nCntEffect].fWhith = fWhith;	//幅を代入
			g_aEffect[nCntEffect].fHeiht = fHeight;	//高さを代入
			g_aEffect[nCntEffect].aType = aType;	//種類
			g_aEffect[nCntEffect].aTex = aTex;		//テクスチャ種類
			g_aEffect[nCntEffect].nLife = nLife;	//消滅カウント

			g_aEffect[nCntEffect].bUse = true;
			break;
		}
	}
}