//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "matching.h"
#include "manager.h"
#include "textureobj.h"
#include "tcp_client.h"
#include "fade.h"
#include "communicationdata.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
bool CMatching::m_bConnect = false;
bool CMatching::m_bEnemyConnect = false;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CMatching::CMatching()
{
	m_bEnemyConnect = false;
	m_bConnect = false;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CMatching::~CMatching()
{
	
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CMatching::Init(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();
	if (pClient != NULL)
	{
		pClient->Init();
	}

	thread th(ConnectTh);

	th.detach();

	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(250.0f, 50.0f, 0.0f), "MATCHING");

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CMatching::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	CScene::ReleaseAll();
	pSound->StopSound(CSound::X2SOUND_LABEL::TITLE);
}

//=============================================================================
// 更新処理
//=============================================================================
void CMatching::Update(void)
{
	CFade *pFade = CManager::GetFade();
	if (m_bEnemyConnect == true && pFade->GetFade() == CFade::FADE::FADE_NONE)
	{
		pFade->SetFade(CManager::MODE::GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CMatching::Draw(void)
{

}

//=============================================================================
// 通信スレッド
//=============================================================================
void CMatching::ConnectTh(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();
	char aRecvData[MAX_CHARDATA];

	while (!m_bConnect)
	{
		m_bConnect = pClient->Connect();
	}
	while (!m_bEnemyConnect)
	{
		pClient->Recv(&aRecvData[0], sizeof(bool));
		memcpy(&m_bEnemyConnect, &aRecvData[0], sizeof(bool));
	}
}