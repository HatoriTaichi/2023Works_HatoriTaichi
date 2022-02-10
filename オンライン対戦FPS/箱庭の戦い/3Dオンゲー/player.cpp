//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include "model.h"
#include "tcp_client.h"
#include "renderer.h"
#include "manager.h"
#include "motion.h"
#include "texture.h"
#include "keyinput.h"
#include "mouseinput.h"
#include "playerbullet.h"
#include "camera.h"
#include "singlemodel.h"
#include "manager.h"
#include "game.h"
#include "textureobj.h"
#include "counter.h"
#include "gunfire.h"
#include "sound.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CPlayer::CPlayer(LAYER_TYPE Layer) : CScene(Layer)
{
	m_Boold.push_back(CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "BLOOD_00"));
	m_Boold.push_back(CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "BLOOD_01"));
	m_Boold.push_back(CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "BLOODMASK"));
	m_Boold[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_Boold[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	D3DXVECTOR3 m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_PosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_nParts = 0;
	int m_nDamageTime = 0;
	int m_nStock = MAX_STOCK;
	int m_nRateTime = 0;
	int m_nReloadCnt = 0;
	float m_fMoveSpeed = 0;
	float m_fLife = MAX_LIFE;
	bool m_bRespawn = false;
	bool m_bDamageTime = false;
	bool m_bHitDamage = false;
	bool m_bAttack = false;
	bool m_bEndBattle = false;
	bool m_bShoot = true;
	bool m_bReload = false;
}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// モデルの初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	FILE *pFile;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Rot;
	char aFile[128];
	vector<int> Parent;
	int nKey = 0;
	int nCntKey = 0;
	int nFrame = 0;
	int nCntModel = 0;
	int nCntMosion = 0;
	bool bLoop;
	pFile = fopen("data/Txtdata/player.txt", "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "NUM_MODEL") == 0) // NUM_MODELの文字列を見つけたら
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nParts);
				for (int nCnt = 0; nCnt < m_nParts; nCnt++)
				{
					Parent.push_back(0);
				}
				break;
			}
		}
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			m_pModel.push_back(CModel::Create((CModel::TYPE)nCnt, D3DXVECTOR3(1.0f, 1.0f, 1.0f), &Parent[nCnt], pFile));
		}
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			if (Parent[nCnt] == -1)
			{
				m_pModel[nCnt]->SetPrent(NULL);
			}
			else
			{
				m_pModel[nCnt]->SetPrent(m_pModel[Parent[nCnt]]);
			}
		}
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "MOTIONSET") == 0) // MOTIONSETの文字列を見つけたら
			{
				int nLoop;
				fscanf(pFile, "%*s%*s%d", &nLoop);
				fscanf(pFile, "%*s%*s%*s%*s");
				fscanf(pFile, "%*s%*s%d", &nKey);
				bLoop = nLoop;

				for (int nCnt = 0; nCnt < m_nParts; nCnt++)
				{
					CModel::MOTIONINFO *pMosion = m_pModel[nCnt]->GetMotion(nCntMosion);
					for (int nCntKey = 0; nCntKey < nKey; nCntKey++)
					{
						pMosion->aKeyinfo.push_back(new CModel::KEYINFO);
					}
				}
			}
			if (strcmp(&aFile[0], "KEYSET") == 0) // KEYSETの文字列を見つけたら
			{
				fscanf(pFile, "%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s");
				fscanf(pFile, "%*s%*s%d", &nFrame);
				while (true)
				{
					fscanf(pFile, "%s", &aFile[0]);
					if (strcmp(&aFile[0], "KEY") == 0) // KEYの文字列を見つけたら
					{
						fscanf(pFile, "%*s%*s%*s%*s%*s%*s");
						fscanf(pFile, "%*s%*s%f%f%f", &Pos.x, &Pos.y, &Pos.z);
						fscanf(pFile, "%*s%*s%f%f%f", &Rot.x, &Rot.y, &Rot.z);
					}
					if (strcmp(&aFile[0], "END_KEY") == 0) // END_KEYの文字列を見つけたら
					{
						CModel::MOTIONINFO *pMosion = m_pModel[nCntModel]->GetMotion(nCntMosion);

						pMosion->bLoop = bLoop;
						pMosion->nNumKey = nKey;
						pMosion->aKeyinfo[nCntKey]->fFrame = nFrame;

						pMosion->aKeyinfo[nCntKey]->aKey.fPosX = m_pModel[nCntModel]->GetPos().x + Pos.x;
						pMosion->aKeyinfo[nCntKey]->aKey.fPosY = m_pModel[nCntModel]->GetPos().y + Pos.y;
						pMosion->aKeyinfo[nCntKey]->aKey.fPosZ = m_pModel[nCntModel]->GetPos().z + Pos.z;

						pMosion->aKeyinfo[nCntKey]->aKey.fRotX = m_pModel[nCntModel]->GetRot().x + Rot.x;
						pMosion->aKeyinfo[nCntKey]->aKey.fRotY = m_pModel[nCntModel]->GetRot().y + Rot.y;
						pMosion->aKeyinfo[nCntKey]->aKey.fRotZ = m_pModel[nCntModel]->GetRot().z + Rot.z;

						nCntModel++;
					}
					if (strcmp(&aFile[0], "END_KEYSET") == 0) // END_KEYSETの文字列を見つけたら
					{
						nCntModel = 0;
						nCntKey++;
						break;
					}
				}
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0) // END_MOTIONSETの文字列を見つけたら
			{
				nCntModel = 0;
				nCntKey = 0;
				nCntMosion++;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) // END_SCRIPTの文字列を見つけたら
			{
				break;
			}
		}
	}
	else
	{
		printf("モデルデータが読み取れませんでした。");
	}

	fclose(pFile);

	return S_OK;
}

//=============================================================================
// モデルの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		m_pModel[nCnt]->Uninit();
		delete m_pModel[nCnt];
		m_pModel[nCnt] = NULL;
	}
}

//=============================================================================
// モデルの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	CTcpClient *pTcp = CManager::GetTcpClient();
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();
	int nMaxModel = CManager::GetGame()->GetMaxModel();

	m_PosOld = m_Pos;
	Move();
	Motion();
	Damage();
	CntStock();
	Attack();

	if (m_bRespawn == false)
	{
		for (int nCnt = 0; nCnt < nMaxModel; nCnt++)
		{
			CModel *pModel = CManager::GetGame()->GetModel(nCnt)->GetModel();
			pModel->BoxCollision(&m_Pos, m_PosOld);
		}
	}
	else
	{
		m_bRespawn = false;
	}

	pTcp->Send((char*)pData, sizeof(CCommunicationData::COMMUNICATION_DATA));
	pData->Player.bPushKey = false;
}

//=============================================================================
// モデルの描画処理
//=============================================================================
void CPlayer::Draw(void)
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
	for (int nCnt = 0; nCnt < m_nParts; nCnt++)
	{
		m_pModel[nCnt]->Draw();
	}
}

//=============================================================================
// 弾との当たり判定
//=============================================================================
bool CPlayer::ToBulletCollision(D3DXVECTOR3 pos, float fwigth, float fheight)
{
	D3DXVECTOR3 posdfrc;
	int nMyR = PLAYER_RADIUS;
	float fposdfrcX;
	bool bHit = false;

	posdfrc.x = m_Pos.x - pos.x;
	posdfrc.z = m_Pos.z - pos.z;

	posdfrc.x = posdfrc.x * posdfrc.x;

	fposdfrcX = posdfrc.x + posdfrc.z;

	fposdfrcX = sqrtf(fposdfrcX);

	if (m_Pos.y <= pos.y + fheight / 2 &&
		m_Pos.y + PLAYER_HEIGHT >= pos.y - fheight / 2 &&
		fposdfrcX < nMyR)
	{
		if (m_bInvincible == false)
		{
			m_fLife -= 3.0f;
			m_nDamageTime = 0;
			m_bDamageTime = true;
			m_bHitDamage = true;
			bHit = true;
		}
	}
	return bHit;
}

//=============================================================================
// モデルの生成
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = NULL;
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
	}

	pPlayer->m_Pos = pos;
	pPlayer->m_Rot = rot;

	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}
	return pPlayer;
}

//=============================================================================
// 移動
//=============================================================================
void CPlayer::Move(void)
{
	CCamera *pCamera = CManager::GetCamera();
	CKeyboard *pKey = CManager::GetKeyboard();
	CMouse *pMouse = CManager::GetMouse();
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();
	D3DXVECTOR3 Rot = pCamera->GetRot();
	float fLong = pCamera->GetDestance();
	float fMoveRot;
	m_Rot.y = Rot.x;
	m_Rot.y += D3DXToRadian(180.0f);
	fMoveRot = m_Rot.y - D3DXToRadian(180.0f);

	if (m_bEndBattle == false)
	{
#if _DEBUG
		if (pKey->GetPress(pKey->LSHIFT) == true)
		{
			m_fMoveSpeed = DUSH_SPEED;
			m_Pos.y -= 1.0f;
		}
		else if (pKey->GetPress(pKey->LSHIFT) == false)
		{
			m_fMoveSpeed = NORMAL_SPEED;
		}
#endif
		if (pKey->GetPress(pKey->W) == true)
		{
			m_Pos.x = m_Pos.x + sinf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z + cosf(fMoveRot) * m_fMoveSpeed;
		}
		else if (pKey->GetPress(pKey->S) == true)
		{
			m_Pos.x = m_Pos.x - sinf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z - cosf(fMoveRot) * m_fMoveSpeed;
		}
		if (pKey->GetPress(pKey->A) == true)
		{
			m_Pos.x = m_Pos.x - cosf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z + sinf(fMoveRot) * m_fMoveSpeed;
		}
		else if (pKey->GetPress(pKey->D) == true)
		{
			m_Pos.x = m_Pos.x + cosf(fMoveRot) * m_fMoveSpeed;
			m_Pos.z = m_Pos.z - sinf(fMoveRot) * m_fMoveSpeed;
		}
		m_Pos.y -= 1.0f;
		if (m_Pos.y <= -50.0f)
		{
			m_bRespawn = true;
			m_nStock -= 1;
			if (pData->Player.nNumber == 1)
			{
				m_Pos = D3DXVECTOR3(-650.0f, 100.0f, -600.0f);
			}
			else
			{
				m_Pos = D3DXVECTOR3(650.0f, 100.0f, 600.0f);
			}
		}
	}

	pData->Player.Pos = m_Pos;
	pData->Player.Rot = m_Rot;
}

//=============================================================================
// 攻撃
//=============================================================================
void CPlayer::Attack(void)
{
	CSound *pSound = CManager::GetSound();
	CKeyboard *pKey = CManager::GetKeyboard();
	CMouse *pMouse = CManager::GetMouse();
	CCamera *pCamera = CManager::GetCamera();
	CCounter *pCounter = CManager::GetGame()->GetAmmo();
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();
	D3DXVECTOR3 Rot = pCamera->GetRot();
	D3DXMATRIX WorldPos = m_pModel[11]->GetMatrix();
	float fNorRot = m_Rot.y - D3DXToRadian(180.0f);

	if (m_bEndBattle == false)
	{
		for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
		{
			if (pMouse->GetPress(pMouse->LEFT_BOTTON) == true && pData->Bullet[nCnt].bUse == false && pCounter->GetCounterNum() != 0)
			{
				if (m_bShoot == true)
				{
					pSound->PlaySound(CSound::X2SOUND_LABEL::SHOOT);
					Rot.y = Rot.y - 0.01f;
					pCamera->SetRot(Rot);
					pCounter->AddCounter(-1);
					m_bAttack = true;
					CPlayerBullet::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), Rot, D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "BULLET", 1.0f);
					CGunFire::Create(D3DXVECTOR3(WorldPos._41, WorldPos._42, WorldPos._43), D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), "MASLE_FLASH");
					pData->Bullet[nCnt].Rot = Rot;
					m_bShoot = false;
					if (pData->Bullet[nCnt].bUse == false)
					{
						pData->Bullet[nCnt].bUse = true;
						break;
					}
				}
			}
		}
	}
	if (m_bShoot == false)
	{
		m_nRateTime++;
	}
	if (m_nRateTime >= (FPS / 15))
	{
		m_bShoot = true;
		m_nRateTime = 0;
	}
	if (pKey->GetTrigger(pKey->R) == true)
	{
		pSound->PlaySound(CSound::X2SOUND_LABEL::RELOAD);
		m_bReload = true;
	}
	if (m_bReload == true)
	{
		m_nReloadCnt++;
		if (m_nReloadCnt >= (FPS * 1.5f))
		{
			pCounter->SetCounterNum(30);
			for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
			{
				pData->Bullet[nCnt].bUse = false;
			}
			m_bReload = false;
			m_nReloadCnt = 0;
		}
	}
	if (pMouse->GetPress(pMouse->LEFT_BOTTON) == false)
	{
		pData->Player.bPushKey = false;
	}
	else if (pMouse->GetPress(pMouse->LEFT_BOTTON) == true)
	{
		pData->Player.bPushKey = true;
	}
#if _DEBUG
	if (pKey->GetTrigger(pKey->J) == true)
	{
		m_nStock -= 1;
	}
#endif // _DEBUG

}

//=============================================================================
// モーション
//=============================================================================
void CPlayer::Motion(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();
	CKeyboard *pKey = CManager::GetKeyboard();

	if (m_bAttack == false)
	{
		if (pKey->GetPress(pKey->W) == false &&
			pKey->GetPress(pKey->A) == false &&
			pKey->GetPress(pKey->S) == false &&
			pKey->GetPress(pKey->D) == false)
		{
			m_Motion = CModel::MOSTION::NEUTRAL;
			pData->Player.Motion = CCommunicationData::MOSTION::NEUTRAL;
			for (int nCnt = 0; nCnt < m_nParts; nCnt++)
			{
				CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
				D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
				D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

				CMotion::PlayMotin(Motion, &Pos, &Rot);
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
		}
		else if (pKey->GetPress(pKey->W) == true ||
				 pKey->GetPress(pKey->A) == true ||
				 pKey->GetPress(pKey->D) == true)
		{
			m_Motion = CModel::MOSTION::WORK;
			pData->Player.Motion = CCommunicationData::MOSTION::WORK;
			for (int nCnt = 0; nCnt < m_nParts; nCnt++)
			{
				CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
				D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
				D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

				CMotion::PlayMotin(Motion, &Pos, &Rot);
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
		}
		else if (pKey->GetPress(pKey->S) == true)
		{
			m_Motion = CModel::MOSTION::BUCK_WORK;
			pData->Player.Motion = CCommunicationData::MOSTION::BUCK_WORK;
			for (int nCnt = 0; nCnt < m_nParts; nCnt++)
			{
				CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
				D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
				D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

				CMotion::PlayMotin(Motion, &Pos, &Rot);
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
		}
	}
	else if (m_bShoot == true)
	{
		m_Motion = CModel::MOSTION::ATTACK;
		pData->Player.Motion = CCommunicationData::MOSTION::ATTACK;
		for (int nCnt = 0; nCnt < m_nParts; nCnt++)
		{
			CModel::MOTIONINFO *Motion = m_pModel[nCnt]->GetMotion((int)m_Motion);
			D3DXVECTOR3 Pos = m_pModel[nCnt]->GetPos();
			D3DXVECTOR3 Rot = m_pModel[nCnt]->GetRot();

			if (CMotion::PlayMotin(Motion, &Pos, &Rot) == false)
			{
				m_pModel[nCnt]->SetPos(Pos);
				m_pModel[nCnt]->SetRot(Rot);
			}
			else
			{
				m_bAttack = false;
			}
		}
	}
}

//=============================================================================
// ダメージ
//=============================================================================
void CPlayer::Damage(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();

	if (m_bInvincible == true)
	{
		m_nIvbTime++;
	}
	if (m_nIvbTime >= (FPS * 1.5))
	{
		m_bInvincible = false;
	}

	if (m_fLife < MAX_LIFE && m_bDamageTime == true)
	{
		m_nDamageTime++;
	}

	if (m_nDamageTime >= RECOVERY_TIME)
	{
		m_nDamageTime = 0;
		m_bDamageTime = false;
	}

	if (m_bDamageTime == false)
	{
		m_fLife += 0.1f;
	}

	if (m_fLife >= 80.0f)
	{
		m_Boold[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	}
	if (m_fLife >= MAX_LIFE)
	{
		m_Boold[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (m_fLife >= MAX_LIFE)
	{
		m_fLife = MAX_LIFE;
	}

	if (m_fLife < MAX_LIFE && m_fLife >= 80.0f && m_bHitDamage == true)
	{
		m_Boold[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
		m_bHitDamage = false;
	}
	else if (m_fLife < 80.0f && m_bHitDamage == true)
	{
		m_Boold[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
		m_bHitDamage = false;
	}

	if (m_fLife <= 0.0f)
	{
		m_fLife = MAX_LIFE;
		m_bRespawn = true;
		m_bHitDamage = false;
		m_bDamageTime = false;
		m_bInvincible = true;
		m_nStock -= 1;
		m_Boold[2]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		if (pData->Player.nNumber == 1)
		{
			m_Pos = D3DXVECTOR3(-650.0f, 100.0f, -600.0f);
		}
		else
		{
			m_Pos = D3DXVECTOR3(650.0f, 100.0f, 600.0f);
		}
	}
	pData->Player.nStock = m_nStock;
}

//=============================================================================
// ストックカウンタ
//=============================================================================
void CPlayer::CntStock(void)
{
	CCommunicationData::COMMUNICATION_DATA *pData = m_CommuData.GetCmmuData();
	if (pData->Player.nNumber != 0)
	{
		CCounter *pCounter = CManager::GetGame()->GetCounter(pData->Player.nNumber - 1);
		pCounter->SetCounterNum(m_nStock);
	}
}