//=============================================================================
//
// �L�[�{�[�h���� [keyinput.h]
// Author : �H������
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STICK_POW (1000)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGamepad : public CInput
{
public:
	typedef enum
	{
		A = 0,
		B,
		Y,
		X,
		L2,
		R2,
		L,
		R,
		START,
		SELECT,
		L3,
		R3,
		BUTTOM,
		HOME,
		BUTTON_MAX,
	} PADBUTTON;
	CGamepad();	// �f�t�H���g�R���X�g���N�^
	~CGamepad();	// �f�t�H���g�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	bool GetPress(int Botton_Type);	// ����
	bool GetTrigger(int Botton_Type);	// ��񉟂�
	bool GetRelease(int Botton_Type);	// ������
	DIJOYSTATE GetGamepad(void);	// �}�E�X���W
	static BOOL CALLBACK EnumJoysticksCallback(const LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
private:
	DIDEVCAPS m_diDevCaps;
	DIJOYSTATE m_aState;			//�L�[�{�[�h�̓��͏��i�v���X���j
	DIJOYSTATE m_aStateTrigger;		//�L�[�{�[�h�̓��͏�� (�g���K�[)
	DIJOYSTATE m_aStateRelease;		//�L�[�{�[�h�̓��͏�� (�����[�X)
};

#endif