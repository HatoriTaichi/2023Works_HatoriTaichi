//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "game.h"
#include "manager.h"
#include "textureobj.h"
#include "notes.h"
#include "enemy.h"
#include "fade.h"
#include "player.h"
#include "sound.h"
#include "counter.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGame::CGame()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CGame::Init(void)
{
	FILE *pFile;
	string FileString;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	char aFile[1][128];

	CSound *pSound;
	pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	pFile = fopen("data/Txtdata/gameuidata.txt", "r");

	if (pFile != NULL)
	{
		int nCnt = 0;
		while (true)
		{
			fscanf(pFile, "%s", aFile[0]);
			if (strcmp(aFile[0], "UI_NUM") == 0) // UI_NUM�̕��������������
			{
				fscanf(pFile, "%*s%d", &m_nUiNum);
			}
			if (strcmp(aFile[0], "SET_UI") == 0) // SET_UI�̕��������������
			{
				while (true)
				{
					fscanf(pFile, "%s", aFile[0]);

					// TEX_TYPE�̕��������������
					if (strcmp(aFile[0], "TEX_TYPE") == 0) // TEX_TYPE�̕��������������
					{
						char aTypeBuf[1][64];
						string Type;
						fscanf(pFile, "%*s%s", aTypeBuf[0]);
						Type = aTypeBuf[0];
						m_Type.push_back(Type);
					}
					// POS�̕��������������
					else if (strcmp(aFile[0], "POS") == 0)
					{
						fscanf(pFile, "%*s%f%f%f", &Pos.x, &Pos.y, &Pos.z);
					}
					// SIZE�̕��������������
					else if (strcmp(aFile[0], "SIZE") == 0)
					{
						fscanf(pFile, "%*s%f%f%f", &Size.x, &Size.y, &Size.z);
					}
					// END_UISET�̕��������������
					else if (strcmp(aFile[0], "END_UISET") == 0)
					{
						CUiObj::Create(Pos, Size, m_Type[nCnt]);
						nCnt++;
						break;
					}
				}
			}
			else if (strcmp(aFile[0], "END") == 0)
			{
				break;
			}
		}
	}
	else
	{
		cout << "�e�L�X�g�t�@�C�����Ђ炯�܂���ł����B";
	}

	fclose(pFile);

	pFile = fopen("data/Txtdata/gamedata.txt", "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", aFile[0]);
			if (strcmp(aFile[0], "NORTS_NUM") == 0) // NORTS_NUM�̕��������������
			{
				fscanf(pFile, "%*s%d", &m_nNotesNum);
			}
			if (strcmp(aFile[0], "SET_NORTS") == 0) // SET_NORTS�̕��������������
			{
				while (true)
				{
					fscanf(pFile, "%s", aFile[0]);

					// TEX_TYPE�̕��������������
					if (strcmp(aFile[0], "TEX_TYPE") == 0) // TEX_TYPE�̕��������������
					{
						char aTypeBuf[1][64];
						string Type;
						fscanf(pFile, "%*s%s", aTypeBuf[0]);
						Type = aTypeBuf[0];
						m_NotesType.push_back(Type);
					}
					// SECOND�̕��������������
					else if (strcmp(aFile[0], "SECOND") == 0)
					{
						float nSecond;
						fscanf(pFile, "%*s%f", &nSecond);
						m_nSecond.push_back(nSecond);
					}
					// END_NOERTSSET�̕��������������
					else if (strcmp(aFile[0], "END_NOERTSSET") == 0)
					{
						break;
					}
				}
			}
			else if (strcmp(aFile[0], "END") == 0)
			{
				break;
			}
		}
	}
	else
	{
		cout << "�e�L�X�g�t�@�C�����Ђ炯�܂���ł����B";
	}

	fclose(pFile);

	CPlayer::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), "PLAYER");
	m_pCombo = CCounter::Create(D3DXVECTOR3(0.0f + 250.0f, 177.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f), 3, "NUMBER");
	m_pScore = CCounter::Create(D3DXVECTOR3(SCREEN_WIDTH - 500.0f, 177.0f, 0.0f), D3DXVECTOR3(25.0f, 50.0f, 0.0f), 8, "NUMBER");

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGame::Uninit(void)
{
	CSound *pSound;
	pSound = CManager::GetSound();
	pSound->Stop();

	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	CFade *pFade = CManager::GetFade();
	m_nLimit++;

	if (m_nTimer >= (FPS * 5) && pFade->GetFade() == CFade::FADE_NONE)
	{
		pFade->SetFade(CManager::MODE::RESULT);
		m_nNotes = 0;
	}

	if (m_nNotes == m_nNotesNum)
	{
		m_bFade = true;
		m_nTimer++;
	}

	if (m_nLimit >= (FPS * m_nSecond[m_nNotes]) && m_bFade == false)
	{
		if (m_NotesType[m_nNotes] == "RIGHT_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), m_NotesType[m_nNotes]);
		}
		else if (m_NotesType[m_nNotes] == "LEFT_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), m_NotesType[m_nNotes]);
		}
		else if (m_NotesType[m_nNotes] == "UP_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), m_NotesType[m_nNotes]);
		}
		else if (m_NotesType[m_nNotes] == "DOWN_ARROW")
		{
			CNotes::Create(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), m_NotesType[m_nNotes]);
		}
		if (m_nNotes <= (m_nNotesNum - 1))
		{
			m_nNotes++;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}