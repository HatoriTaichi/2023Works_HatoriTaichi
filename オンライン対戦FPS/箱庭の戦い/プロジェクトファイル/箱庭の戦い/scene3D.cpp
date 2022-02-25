//=============================================================================
//
// 3Dオブジェクト処理 [scene3D.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CScene3D::CScene3D()
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
CScene3D::~CScene3D()
{

}

//=============================================================================
// 3Dオブジェクトの初期化処理
//=============================================================================
HRESULT CScene3D::Init(void)
{
	return S_OK;
}

//=============================================================================
// 3Dオブジェクトの終了処理
//=============================================================================
void CScene3D::Uninit(void)
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
void CScene3D::Update(void)
{

}

//=============================================================================
// 3Dオブジェクトの描画処理
//=============================================================================
void CScene3D::Draw(void) 
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	// αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(	&mtxRot, 
									m_Rot.y, 
									m_Rot.x, 
									m_Rot.z);
	D3DXMatrixMultiply(	&m_mtxWorld, 
						&m_mtxWorld, 
						&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x, 
							m_Pos.y, 
							m_Pos.z);
	D3DXMatrixMultiply(	&m_mtxWorld, 
						&m_mtxWorld, 
						&mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture); //テクスチャの設定

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(	0, 
								m_pVtxBuff, 
								0, 
								sizeof(VERTEX_3D));
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(	D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_nNumVtx,	// 使用する頂点数
									0,	// ここの値が最初のインデックス
									m_nNumIdx - 2);	// 三角形の数

	// αテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//=============================================================================
// 生成処理
//=============================================================================
CScene3D* CScene3D::Create(void) 
{
	CScene3D* pScene3D = NULL;
	if (pScene3D == NULL)
	{
		pScene3D = new CScene3D;
	}

	if (pScene3D != NULL)
	{
		pScene3D->Init();
	}

	return pScene3D;
}