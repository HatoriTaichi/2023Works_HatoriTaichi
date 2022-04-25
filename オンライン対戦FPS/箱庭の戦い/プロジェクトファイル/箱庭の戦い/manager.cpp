//=============================================================================
//
// マネージャー管理処理 [manager.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "gamepad.h"
#include "tcp_client.h"
#include "light.h"
#include "camera.h"
#include "model.h"
#include "title.h"
#include "rule.h"
#include "matching.h"
#include "game.h"
#include "fade.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CManager::MODE CManager::m_Mode;
CManager::MODE CManager::m_ModeOld;
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight[MAX_LIGHT];
CTexture *CManager::m_pTexture = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CMouse *CManager::m_pMouse = NULL;
CGamepad *CManager::m_pGamepad = NULL;
CSound *CManager::m_pSound = NULL;
CTcpClient *CManager::m_pTcpClient = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CRule *CManager::m_pRule = NULL;
CMatching *CManager::m_pMatchibg = NULL;
CGame *CManager::m_pGame = NULL;
HWND CManager::m_hwnd = NULL;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CManager::CManager()
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		m_pLight[nCnt] = NULL;
	}
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	m_hwnd = hWnd;
	if (m_pTexture == NULL &&
		m_pRenderer == NULL &&
		m_pKeyboard == NULL &&
		m_pMouse == NULL &&
		m_pGamepad == NULL &&
		m_pSound == NULL &&
		m_pTcpClient == NULL &&
		m_pFade == NULL)
	{
		m_pTexture = new CTexture;
		m_pRenderer = new CRenderer;
		m_pKeyboard = new CKeyboard;
		m_pMouse = new CMouse;
		m_pGamepad = new CGamepad;
		m_pSound = new CSound;
		m_pTcpClient = new CTcpClient;
		m_pFade = new CFade;

		if (m_pTexture != NULL &&
			m_pRenderer != NULL &&
			m_pKeyboard != NULL &&
			m_pMouse != NULL &&
			m_pSound != NULL &&
			m_pTcpClient != NULL &&
			m_pFade != NULL)
		{
			// 初期化
			m_pRenderer->Init(hWnd, bWindow);
			m_pFade->Init();
			m_pKeyboard->Init(hInstance, hWnd);
			m_pMouse->Init(hInstance, hWnd);
			m_pGamepad->Init(hInstance, hWnd);
			m_pSound->InitSound(hWnd);
			m_pKeyboard->BindKey(CKeyboard::NUM_1, DIK_1);
			m_pKeyboard->BindKey(CKeyboard::NUM_2, DIK_2);
			m_pKeyboard->BindKey(CKeyboard::W, DIK_W);
			m_pKeyboard->BindKey(CKeyboard::A, DIK_A);
			m_pKeyboard->BindKey(CKeyboard::S, DIK_S);
			m_pKeyboard->BindKey(CKeyboard::D, DIK_D);
			m_pKeyboard->BindKey(CKeyboard::J, DIK_J);
			m_pKeyboard->BindKey(CKeyboard::R, DIK_R);
			m_pKeyboard->BindKey(CKeyboard::SPACE, DIK_SPACE);
			m_pKeyboard->BindKey(CKeyboard::LSHIFT, DIK_LSHIFT);
			m_pKeyboard->BindKey(CKeyboard::CTRL, DIK_LCONTROL);
			CTexture::Init();
			CModel::Load();
		}
	}

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 25.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pLight[0] = CLight::Create(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(-1000.0f, 1000.0f, 1000.0f), D3DXVECTOR3(0.2f, -0.8f, 0.4f));
	m_pLight[1] = CLight::Create(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1000.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	m_pLight[2] = CLight::Create(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(1000.0f, -1000.0f, -1000.0f), D3DXVECTOR3(-0.2f, 0.8f, -0.4f));

	SetMode(MODE::TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// オブジェクトの全破棄
	CScene::ReleaseAll();
	CTexture::Uniinit();
	CModel::UnLoad();
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		if (m_pLight[nCnt] != NULL)
		{
			m_pLight[nCnt]->Uninit();
			delete m_pLight[nCnt];
			m_pLight[nCnt] = NULL;
		}
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	if (m_pMouse != NULL)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = NULL;
	}
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Uninit();
		delete m_pGamepad;
		m_pGamepad = NULL;
	}
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}
	if (m_pTcpClient != NULL)
	{
		m_pTcpClient->Uninit();
		delete m_pTcpClient;
		m_pTcpClient = NULL;
	}
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	WSACleanup();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	switch (m_Mode)
	{
	case MODE::TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case MODE::RULE:
		if (m_pRule != NULL)
		{
			m_pRule->Update();
		}
		break;
	case MODE::MATCHING:
		if (m_pMatchibg != NULL)
		{
			m_pMatchibg->Update();
		}
		break;
	case MODE::GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	default:
		break;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		if (m_pLight[nCnt] != NULL)
		{
			m_pLight[nCnt]->Update();
		}
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	if (m_pMouse != NULL)
	{
		m_pMouse->Update();
	}
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	switch (m_Mode)
	{
	case MODE::TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Draw();
		}
		break;
	case MODE::RULE:
		if (m_pRule != NULL)
		{
			m_pRule->Draw();
		}
		break;
	case MODE::MATCHING:
		if (m_pMatchibg != NULL)
		{
			m_pMatchibg->Draw();
		}
		break;
	case MODE::GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Draw();
		}
		break;
	default:
		break;
	}
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
	m_pCamera->SetCamera();
}

//=============================================================================
// モードチャンジ
//=============================================================================
void CManager::SetMode(MODE mode)
{
	m_ModeOld = m_Mode;
	m_Mode = mode;
	switch (m_ModeOld)
	{
	case MODE::TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE::RULE:
		if (m_pRule != NULL)
		{
			m_pRule->Uninit();
			m_pRule = NULL;
		}
		break;
	case MODE::MATCHING:
		if (m_pMatchibg != NULL)
		{
			m_pMatchibg->Uninit();
			m_pMatchibg = NULL;
		}
		break;
	case MODE::GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	default:
		break;
	}

	switch (m_Mode)
	{
	case MODE::TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;
			m_pTitle->Init();
		}
		break;
	case MODE::RULE:
		if (m_pRule == NULL)
		{
			m_pRule = new CRule;
			m_pRule->Init();
		}
		break;
	case MODE::MATCHING:
		if (m_pMatchibg == NULL)
		{
			m_pMatchibg = new CMatching;
			m_pMatchibg->Init();
		}
		break;
	case MODE::GAME:
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;
			m_pGame->Init();
		}
		break;
	default:
		break;
	}
}