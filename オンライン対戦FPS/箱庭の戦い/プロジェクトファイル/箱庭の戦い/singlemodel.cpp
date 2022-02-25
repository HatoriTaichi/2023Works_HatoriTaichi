//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "singlemodel.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CSingleModel::CSingleModel(LAYER_TYPE Layer) : CScene(Layer)
{
	
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CSingleModel::~CSingleModel()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CSingleModel::Init(void)
{
	m_pModel = CModel::Create(m_Type);
	m_pModel->SetScale(m_Scale);
	m_pModel->SetPrent(NULL);

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CSingleModel::Uninit(void)
{
	m_pModel->Uninit();
	delete m_pModel;
	m_pModel = NULL;
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CSingleModel::Update(void)
{
	m_pModel->Update();
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CSingleModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; // デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスを取得する

	//--------------------------------------
	//プレイヤー(原点)のマトリックスの設定
	//--------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	D3DXMatrixIdentity(&m_MtxWold);	//マトリックス初期化

	//向きの設定
	D3DXMatrixRotationYawPitchRoll(	&mtxRot,
									m_Rot.y,
									m_Rot.x,
									m_Rot.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxRot);
	//位置
	D3DXMatrixTranslation(	&mtxTrans,
							m_Pos.x,
							m_Pos.y,
							m_Pos.z);

	D3DXMatrixMultiply(	&m_MtxWold,
						&m_MtxWold,
						&mtxTrans);
	//マトリックスの設定
	pDevice->SetTransform(	D3DTS_WORLD,
							&m_MtxWold);
	m_pModel->Draw();
}

//=============================================================================
// モデルの生成
//=============================================================================
CSingleModel *CSingleModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, CModel::TYPE type)
{
	CSingleModel *pModel = NULL;
	if (pModel == NULL)
	{
		pModel = new CSingleModel;
	}

	pModel->m_Pos = pos;
	pModel->m_Rot = rot;
	pModel->m_Scale = scale;
	pModel->m_Type = type;

	if (pModel != NULL)
	{
		pModel->Init();
	}
	return pModel;
}