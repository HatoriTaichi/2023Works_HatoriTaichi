//=============================================================================
//
// 2Dポリゴン処理 [scene2D.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CScene2D::CScene2D(LAYER_TYPE Layer) : CScene(Layer)
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init(void)
{
	VERTEX_2D *pVtx;	// 頂点情報
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する

	m_pTexture = CTexture::GetTexture(m_TexType);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_Size.x, m_Pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_Size.x, m_Pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_Size.x, m_Pos.y + m_Size.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();	// 自分の破棄
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスを取得する

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								m_pVtxBuff,
								0,
								sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);	// 頂点フォーマットの設定

	pDevice->SetTexture(0, m_pTexture);	// テクスチャの設定

	// ポリゴンの描画
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, // プリミティブの種類
							0,
							2);
}

//=============================================================================
// オブジェクトの生成
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, string Type)
{
	CScene2D *pScene2D = NULL;
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D;
	}

	pScene2D->m_Pos = pos;
	pScene2D->m_Size = size;
	pScene2D->m_TexType = Type;

	if (pScene2D != NULL)
	{
		pScene2D->Init();
	}
	return pScene2D;
}

//=============================================================================
// セッター
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;	// 頂点情報

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	CScene::SetPos(pos);
	m_Pos = pos;

	VERTEX_2D *pVtx;	// 頂点情報

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_Size.x, pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_Size.x, pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_Size.x, pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_Size.x, pos.y + m_Size.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CScene2D::SetSize(D3DXVECTOR3 size)
{
	CScene::SetSize(size);
	m_Size = size;

	VERTEX_2D *pVtx;	// 頂点情報

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - size.x, m_Pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + size.x, m_Pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - size.x, m_Pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + size.x, m_Pos.y + size.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CScene2D::SetTex(int nPattern, int nAnimMaxX, int nAnimMaxY)
{
	VERTEX_2D *pVtx;	// 頂点情報

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + (float)(nPattern % nAnimMaxX) / nAnimMaxX, 0.0f + (float)(nPattern / nAnimMaxY) / nAnimMaxY);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nAnimMaxX) + (float)(nPattern % nAnimMaxX) / nAnimMaxX, 0.0f + (float)(nPattern / nAnimMaxY) / nAnimMaxY);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (float)(nPattern % nAnimMaxX) / nAnimMaxX, (1.0f / nAnimMaxY) + (float)(nPattern / nAnimMaxY) / nAnimMaxY);
	pVtx[3].tex = D3DXVECTOR2((1.0f / nAnimMaxX) + (float)(nPattern % nAnimMaxX) / nAnimMaxX, (1.0f / nAnimMaxY) + (float)(nPattern / nAnimMaxY) / nAnimMaxY);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CScene2D::SetTex(int nScore)
{
	VERTEX_2D *pVtx;	// 頂点情報

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2((nScore * 0.1f) + 0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nScore * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nScore * 0.1f) + 0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nScore * 0.1f) + 0.1f, 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}