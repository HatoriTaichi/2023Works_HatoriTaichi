//=============================================================================
//
// 3D�I�u�W�F�N�g���� [scene3D.h]
// Author : �H������
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3D�̏_��Ȓ��_�t�H�[�}�b�g

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
} VERTEX_3D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBilboard : public CScene
{
public:
	CBilboard(LAYER_TYPE Layer = LAYER_TYPE::LAYER_02);		// �f�t�H���g�R���X�g���N�^
	~CBilboard();	// �f�X�g���N�^
	virtual HRESULT Init(void);	// ����������
	virtual void Uninit(void);	// �I������
	virtual void Update(void);	// �X�V����
	virtual void Draw(void);	// �`�揈��
	static CBilboard* Create(void);	// �Z�b�^�[
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	// �Z�b�^�[
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }	// �Z�b�^�[
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }	// �Z�b�^�[
	void SetMatrix(D3DXMATRIX mtx) { m_mtxWorld = mtx; }	// �Z�b�^�[
	void SetNumVtx(int nNumVtx) { m_nNumVtx = nNumVtx; }	// �Z�b�^�[
	void SetNumIdx(int nNumIdx) { m_nNumIdx = nNumIdx; }	// �Z�b�^�[
	void SetTexture(string type) { m_pTexture = CTexture::GetTexture(type); }
	D3DXVECTOR3 GetPos(void) { return m_Pos; }		// �Q�b�^�[
	D3DXVECTOR3 GetRot(void) { return m_Rot; }		// �Q�b�^�[
	D3DXVECTOR3 GetScale(void) { return m_Scale; }	// �Q�b�_�[
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }	// �Q�b�_�[ 
	LPDIRECT3DVERTEXBUFFER9* GetVtxBuff(void) { return &m_pVtxBuff; }	// �Q�b�^�[
	LPDIRECT3DINDEXBUFFER9* GetIdxBuff(void) { return &m_pIdxBuff; }	// �Q�b�^�[
	int GetNumVtx(void) { return m_nNumVtx; }			// �Q�b�^�[
	int GetNumIdx(void) { return m_nNumIdx; }			// �Q�b�^�[

private:
	D3DXVECTOR3	m_Pos;	// �ʒu
	D3DXVECTOR3 m_Rot;	// �|���S���̊p�x
	D3DXVECTOR3 m_Scale;	// �X�P�[��
	D3DXMATRIX m_mtxView;	// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxWorld;// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff; // �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int m_nNumVtx;	// ���_��
	int m_nNumIdx;	// �C���f�b�N�X��
};

#endif // !_SCENE3D_H_