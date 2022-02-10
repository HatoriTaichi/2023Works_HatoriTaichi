//=============================================================================
//
// �e�N�X�`������ [texture.cpp]
// Author : �H������
//
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
vector<LPDIRECT3DTEXTURE9>	CTexture::m_pTexture;	//�e�N�X�`��
int CTexture::m_nTextureMax;	// �ǂݍ��ރe�N�X�`���̍ő吔
vector<string> CTexture::m_FilePas;	// �t�@�C���̃p�X
vector<string> CTexture::m_Enum;	// ������̕ۑ�
map<string, int> CTexture::m_TexType;	// �������int��map

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	m_nTextureMax = NULL;
	m_TexType.clear();
}

//=============================================================================
// �f�t�H���g�f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X���擾����
	FILE *pFile;
	char aFile[64];

	pFile = fopen("data/Txtdata/texturedata.txt", "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "TEX_NUM") == 0) // TEX_NUM�̕��������������
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nTextureMax);
			}
			else if (strcmp(&aFile[0], "ENUM_NAME") == 0) // ENUM_NAME�̕��������������
			{
				for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
				{
					int nNumber;
					char aEnumBuf[1][64];
					string Enum;

					fscanf(pFile, "%s%s%d", aEnumBuf[0], &aFile[0], &nNumber);
					Enum = aEnumBuf[0];
					m_Enum.push_back(Enum);
					m_TexType[Enum] = nNumber;
				}
			}
			else if (strcmp(&aFile[0], "TEXTURE_PAS") == 0) // TEXTURE_PAS�̕��������������
			{
				for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
				{
					char aPasBuf[1][64];
					string Pas;

					fscanf(pFile, "%s", aPasBuf[0]);

					Pas = aPasBuf[0];
					m_FilePas.push_back(Pas);
				}
			}
			else if (strcmp(&aFile[0], "END") == 0) //END�̕��������������
			{
				break;
			}
		}
	}
	else
	{
		printf("�e�N�X�`���f�[�^���ǂݎ��܂���ł����B");
	}

	fclose(pFile);

	for (int nCnt = 0; nCnt < m_nTextureMax; nCnt++)
	{
		LPDIRECT3DTEXTURE9 pTex = NULL;
		D3DXCreateTextureFromFile(	pDevice,
									m_FilePas[nCnt].c_str(),	// �e�N�X�`���p�X
									&pTex);
		m_pTexture.push_back(pTex);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CTexture::Uniinit(void)
{
	for (int nCntTexture = 0; nCntTexture < m_nTextureMax; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}