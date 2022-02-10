//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "game.h"
#include "meshfloo.h"
#include "enemy.h"
#include "player.h"
#include "model.h"
#include "tcp_client.h"
#include "singlemodel.h"
#include "sound.h"
#include "meshsphere.h"
#include "camera.h"
#include "manager.h"
#include "counter.h"
#include "textureobj.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGame::CGame()
{
	bool m_bDoOnece = false;
	bool m_bShow = false;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CGame::Init(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();
	FILE *pFile;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Rot;
	D3DXVECTOR3 Scale;
	char aFile[MAX_CHARDATA][MAX_CHARDATA * 2];
	char RecvData[MAX_CHARDATA];
	int nNumber;

	pClient->Recv(&RecvData[0], sizeof(int));
	memcpy(&nNumber, &RecvData[0], sizeof(int));

	pFile = fopen("data/Txtdata/stagedata.txt", "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(aFile[0], "MODEL_NUM") == 0) // MODEL_NUMの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nMaxModel);
			}
			if (strcmp(aFile[0], "SET_MODEL") == 0) // SET_MODELの文字列を見つけたら
			{
				while (true)
				{
					fscanf(pFile, "%s", &aFile[0]);
					if (strcmp(aFile[0], "MODEL_INDX") == 0) // MODEL_INDXの文字列を見つけたら
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_nType);
					}
					else if (strcmp(aFile[0], "POS") == 0) // POSの文字列を見つけたら
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &Pos.x, &Pos.y, &Pos.z);
					}
					else if (strcmp(aFile[0], "ROT") == 0) // ROTの文字列を見つけたら
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &Rot.x, &Rot.y, &Rot.z);
					}
					else if (strcmp(aFile[0], "RSCALE") == 0) // RSCALEの文字列を見つけたら
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f%f%f", &Scale.x, &Scale.y, &Scale.z);
					}
					else if (strcmp(aFile[0], "END_MODELSET") == 0) // END_MODELSETの文字列を見つけたら
					{
						m_pSingleModel.push_back(CSingleModel::Create(Pos, Rot, Scale, (CModel::TYPE)m_nType));
						break;
					}
				}
			}
			else if (strcmp(aFile[0], "END") == 0) //ENDの文字列を見つけたら
			{
				break;
			}
		}
	}
	else
	{
		printf("テクスチャデータが読み取れませんでした。");
	}

	fclose(pFile);

	CMeshsphere::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 32, 8, 3200.0f, "SKY");
	CMeshFloo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 20, 4100.0, 4100.0f, "SEE");
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(250.0f, 175.0f, 0.0f), "PLAYER_DIVIDE");
	CUiObj::Create(D3DXVECTOR3(SCREEN_WIDTH - 150.0f, SCREEN_HEIGHT - 100.0f, 0.0f), D3DXVECTOR3(150.0f, 100.0f, 0.0f), "WEAPONFRAME");
	CUiObj::Create(D3DXVECTOR3((SCREEN_WIDTH - 150.0f), (SCREEN_HEIGHT - 100.0f) - 45.0f, 0.0f), D3DXVECTOR3(100.0f, 45.0f, 0.0f), "WEAPON_VECTOR");
	CUiObj::Create(D3DXVECTOR3((SCREEN_WIDTH - 150.0f) + 50.0f, (SCREEN_HEIGHT - 100.0f) + 50.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "AMMOFRAME");
	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), "BULLET");
	m_pMaxAmmo = CCounter::Create(D3DXVECTOR3(((SCREEN_WIDTH - 150.0f) + 50.0f) + 20.0f, ((SCREEN_HEIGHT - 100.0f) + 50.0f) + 15.0f, 0.0f), D3DXVECTOR3(15.0f, 25.0f, 0.0f), 2, "NUMBER_00");
	m_pMaxAmmo->AddCounter(30);
	m_pAmmo = CCounter::Create(D3DXVECTOR3(((SCREEN_WIDTH - 150.0f) + 50.0f) - 60.0f, ((SCREEN_HEIGHT - 100.0f) + 50.0f) - 15.0f, 0.0f), D3DXVECTOR3(15.0f, 25.0f, 0.0f), 2, "NUMBER_00");
	m_pAmmo->AddCounter(30);
	m_pKiilCount.push_back(CCounter::Create(D3DXVECTOR3(SCREEN_CENTER_X + 70.0f, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(45.0f, 50.0f, 0.0f), 2, "NUMBER_P1"));
	m_pKiilCount.push_back(CCounter::Create(D3DXVECTOR3(SCREEN_CENTER_X - 170.0f, 0.0f + 50.0f, 0.0f), D3DXVECTOR3(45.0f, 50.0f, 0.0f), 2, "NUMBER_P2"));

	if (nNumber == 1)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(-650.0f, 100.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else if (nNumber == 2)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(650.0f, 100.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	m_pPlayer->SetIndex(nNumber);

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CGame::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	MouseProcess();
	UpdateListenter();
	WinOrLoss();
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// リスナーのアップデート
//=============================================================================
void CGame::UpdateListenter(void)
{
	CSound *pSound = CManager::GetSound();
	CCamera *pCamera = CManager::GetCamera();
	VECTOR pos, dir;	// 位置向き
	D3DXVECTOR3 nor;	// 向き(正規化)

	pos.x = pCamera->GetPosV().x;
	pos.y = pCamera->GetPosV().y;
	pos.z = pCamera->GetPosV().z;

	nor = pCamera->GetPosR() - pCamera->GetPosV();
	D3DXVec3Normalize(&nor, &nor);

	dir.x = nor.x;
	dir.y = nor.y;
	dir.z = nor.z;

	pSound->UpdateListener(pos, dir);
}

//=============================================================================
// 勝敗
//=============================================================================
void CGame::WinOrLoss(void)
{
	CSound *pSound = CManager::GetSound();
	CCommunicationData::COMMUNICATION_DATA *pData = m_pEnemy->GetCommuData();
	int nStock[MAX_PLAYER];

	nStock[0] = m_pPlayer->GetStock();
	nStock[1] = m_pEnemy->GetStock();

	if (nStock[0] <= 0 && m_bDoOnece == false)
	{
		pSound->PlaySound(CSound::X2SOUND_LABEL::LOSE);
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 250.0f, 0.0f), D3DXVECTOR3(150.0f, 75.0f, 0.0f), "LOSE");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 475.0f, 0.0f), D3DXVECTOR3(250.0f, 60.0f, 0.0f), "RESTART");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X - 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "YES");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X + 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "NO");
		pData->Player.bPushKey = false;
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			pData->Bullet[nCnt].bUse = false;
		}
		m_pPlayer->SetEndBattle(true);
		m_bDoOnece = true;
	}
	else if (nStock[1] <= 0 && m_bDoOnece == false)
	{
		pSound->PlaySound(CSound::X2SOUND_LABEL::WIN);
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 250.0f, 0.0f), D3DXVECTOR3(150.0f, 75.0f, 0.0f), "WIN");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, 0.0f + 475.0f, 0.0f), D3DXVECTOR3(250.0f, 60.0f, 0.0f), "RESTART");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X - 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "YES");
		CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X + 200.0f, 0.0f + 760.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f), "NO");
		pData->Player.bPushKey = false;
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			pData->Bullet[nCnt].bUse = false;
		}
		m_pPlayer->SetEndBattle(true);
		m_bDoOnece = true;
	}
}

//=============================================================================
// マウス関連
//=============================================================================
void CGame::MouseProcess(void)
{
	CTcpClient *pClient = CManager::GetTcpClient();

	if (m_pPlayer->GetEndBattle() == false)
	{
		//SetCursorPos(SCREEN_CENTER_X, SCREEN_CENTER_Y);
		if (m_bShow == false)
		{
			ShowCursor(FALSE);
			m_bShow = true;
		}
	}
	else
	{
		if (m_bShow == true)
		{
			pClient->Uninit();

			ShowCursor(TRUE);
			m_bShow = false;
		}
	}
}