//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "mouseinput.h"
#include "keyinput.h"
#include "player.h"
#include "game.h"
#include "gamepad.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_fLong = CAMERA_DESTAANCE;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot)
{
	m_PosV = PosV;
	m_PosR = PosR;
	m_Rot = Rot;
	m_VecU = (D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	CMouse *pMouse = CManager::GetMouse();
	CKeyboard *pKey = CManager::GetKeyboard();
	CManager::MODE Snece = CManager::GetMode();
	D3DXVECTOR3 Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bool bEndBattle = true;
	if (Snece == CManager::MODE::GAME)
	{
		CPlayer *pPlayer = CManager::GetGame()->GetPlayer();
		Pos = pPlayer->GetPos();
		bEndBattle = pPlayer->GetEndBattle();
	}

	m_PosV.x = Pos.x;
	m_PosV.y = Pos.y + 50.0f;
	m_PosV.z = Pos.z;

	if (bEndBattle == false)
	{
		m_Rot.x += pMouse->GetMousePos().lX * 0.01f;
		m_Rot.y += pMouse->GetMousePos().lY * 0.01f;
	}

	if (m_Rot.y >= D3DX_PI - 0.1f)
	{
		m_Rot.y = D3DX_PI - 0.1f;
	}
	else if (m_Rot.y <= -0.0f + 0.1f)
	{
		m_Rot.y = -0.0f + 0.1f;
	}
#if _DEBUG
	if (pMouse->GetPress(pMouse->RIGHT_BOTTON) == true)
	{
		m_fZoom = CAMERA_ZOOM_MAX;
	}
	else if (pMouse->GetPress(pMouse->RIGHT_BOTTON) == false)
	{
		m_fZoom = CAMERA_ZOOM_NORMAL;
	}
#endif
	if (bEndBattle == false)
	{
		m_PosR.x = m_PosV.x + (sinf(m_Rot.y) * sinf(m_Rot.x)) * m_fLong;
		m_PosR.y = m_PosV.y +	cosf(m_Rot.y)				  * m_fLong;
		m_PosR.z = m_PosV.z + (sinf(m_Rot.y) * cosf(m_Rot.x)) * m_fLong;
	}
}

//=============================================================================
// セット処理
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();		//デバイスを取得する
	//---------------------------
	//マトリックスの設定
	//---------------------------
	D3DXMatrixIdentity(&m_mtxProjection);	//マトリックス初期化

	//マトリックスの作成
	D3DXMatrixPerspectiveFovLH(	&m_mtxProjection,
								D3DXToRadian(m_fZoom),	//視野角
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f,		//カメラの最小描画距離
								30000.0f);	//カメラの最大描画距離

	//プロジェクションマトリックス設定
	pDevice->SetTransform(	D3DTS_PROJECTION,
							&m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(	&m_mtxView,
						&m_PosV,
						&m_PosR,
						&m_VecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(	D3DTS_VIEW,
							&m_mtxView);
}

//=============================================================================
// 生成処理
//=============================================================================
CCamera *CCamera::Create(D3DXVECTOR3 PosV, D3DXVECTOR3 PosR, D3DXVECTOR3 Rot)
{
	CCamera *pCamera = NULL;
	if (pCamera == NULL)
	{
		pCamera = new CCamera;
	}

	if (pCamera)
	{
		pCamera->Init(PosV, PosR, Rot);
	}
	return pCamera;
}