//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "rule.h"
#include "manager.h"
#include "textureobj.h"

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CRule::CRule()
{

}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CRule::~CRule()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CRule::Init(void)
{
	FILE *pFile;
	string FileString;
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Size;
	char aFile[1][128];

	pFile = fopen("data/Txtdata/ruledata.txt", "r");

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
						m_Ui.push_back(CUiObj::Create(Pos, Size, m_Type[nCnt]));
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

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CRule::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRule::Update(void)
{
	SelectInfo();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRule::Draw(void)
{

}

//=============================================================================
// �I������
//=============================================================================
void CRule::SelectInfo(void)
{
	for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
	{
		string Type = m_Ui[nCntUi]->GetType();
		POINT MousePos;
		D3DXVECTOR3 Pos = m_Ui[nCntUi]->GetPos();
		D3DXVECTOR2 Size = m_Ui[nCntUi]->GetSize();
		bool bSelect = m_Ui[nCntUi]->GetSelect();
		GetCursorPos(&MousePos);
		ScreenToClient(CManager::GetHandle(), &MousePos);

		if (Type == "MANUAL")
		{
			if (bSelect == true)
			{
				for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
				{
					string UseType = m_Ui[nCntUi]->GetType();
					if (UseType == "OPERATIONMANUAL" || UseType == "DESCRIPTION")
					{
						m_Ui[nCntUi]->SetAlpha(0.0f);
					}
					else
					{
						m_Ui[nCntUi]->SetAlpha(1.0f);
					}
				}
			}
		}
		else if (Type == "WEAPON_LETTER")
		{
			if (bSelect == true)
			{
				for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
				{
					string UseType = m_Ui[nCntUi]->GetType();
					if (UseType == "WEAPONMANUAL" || UseType == "DESCRIPTION")
					{
						m_Ui[nCntUi]->SetAlpha(0.0f);
					}
					else
					{
						m_Ui[nCntUi]->SetAlpha(1.0f);
					}
				}
			}
		}
		else if (Type == "WINCONDITION")
		{
			if (bSelect == true)
			{
				for (int nCntUi = 0; nCntUi < m_nUiNum; nCntUi++)
				{
					string UseType = m_Ui[nCntUi]->GetType();
					if (UseType == "WEAPONMANUAL" || UseType == "OPERATIONMANUAL")
					{
						m_Ui[nCntUi]->SetAlpha(0.0f);
					}
					else
					{
						m_Ui[nCntUi]->SetAlpha(1.0f);
					}
				}
			}
		}
	}
}