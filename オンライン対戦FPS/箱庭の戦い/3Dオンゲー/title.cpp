//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "title.h"
#include "manager.h"
#include "textureobj.h"
#include "sound.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CTitle::Init(void)
{
	CSound *pSound = CManager::GetSound();
	FILE *pFile;
	string FileString;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	char aFile[1][128];

	pFile = fopen("data/Txtdata/titledata.txt", "r");

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

	pSound->PlaySound(CSound::X2SOUND_LABEL::TITLE);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CTitle::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{

}