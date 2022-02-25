//=============================================================================
//
// 3Dオブジェクト処理 [scene3D.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#include "bilboard.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CBilboard::CBilboard(LAYER_TYPE Layer) : CScene(Layer)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_nNumVtx = 0;
	m_nNumIdx = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBilboard::~CBilboard()
{

}

//=============================================================================
// 3Dオブジェクトの初期化処理
//=============================================================================
HRESULT CBilboard::Init(void)
{
	return S_OK;
}

//=============================================================================
// 3Dオブジェクトの終了処理
//=============================================================================
void CBilboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//インデックスバッファの破棄
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 3Dオブジェクトの更新処理
//=============================================================================
void CBilboard::Update(void)
{
	
}

//=============================================================================
// 3Dオブジェクトの描画処理
//=============================================================================
void CBilboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する

	// 逆回転カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	D3DXMATRIX mtxScale, mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// スケールの設定
	D3DXMatrixScaling(	&mtxScale,
						m_Scale.x,
						m_Scale.y,
						m_Scale.z);

	D3DXMatrixMultiply(	&m_mtxWorld,
						&m_mtxWorld,
						&mtxScale);

	// カメラの向きを取得
	pDevice->GetTransform(	D3DTS_VIEW,
							&m_mtxView);

	// カメラの情報を入れて、スケールを反映
	m_mtxWorld._11 = m_mtxView._11;
	m_mtxWorld._12 = m_mtxView._21;
	m_mtxWorld._13 = m_mtxView._31;
	m_mtxWorld._21 = m_mtxView._12;
	m_mtxWorld._22 = m_mtxView._22;
	m_mtxWorld._23 = m_mtxView._32;
	m_mtxWorld._31 = m_mtxView._13;
	m_mtxWorld._32 = m_mtxView._23;
	m_mtxWorld._33 = m_mtxView._33;

	// 位置を反映
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x,
							m_Pos.y,
							m_Pos.z);
	D3DXMatrixMultiply(	&m_mtxWorld,
						&m_mtxWorld,
						&mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture); // テクスチャの設定

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(	0,
								m_pVtxBuff,
								0,
								sizeof(VERTEX_3D));
	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_nNumVtx,	// 使用する頂点数
									0,	// ここの値が最初のインデックス
									m_nNumIdx - 2);	// 三角形の数

	// カリングを戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//=============================================================================
// 生成処理
//=============================================================================
CBilboard *CBilboard::Create(void)
{
	CBilboard *pBilboard = NULL;
	if (pBilboard == NULL)
	{
		pBilboard = new CBilboard;
	}

	if (pBilboard != NULL)
	{
		pBilboard->Init();
	}

	return pBilboard;
}