//=============================================================================
//
// キーボード入力処理 [keyinput.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "gamepad.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGamepad::CGamepad()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CGamepad::~CGamepad()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	m_pInput->EnumDevices(	DI8DEVCLASS_GAMECTRL, 
							EnumJoysticksCallback,
							NULL,
							DIEDFL_ATTACHEDONLY);

	if (m_pJoystick != NULL)
	{
		// 協調モードを設定
		if (FAILED(m_pJoystick->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}

		m_pJoystick->GetCapabilities(&m_diDevCaps);

		m_pJoystick->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS);

		m_pJoystick->Poll();

		// アクセス権を獲得(入力制御開始)
		m_pJoystick->Acquire();
	}

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CGamepad::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CGamepad::Update(void)
{
	DIJOYSTATE state;

	if (m_pJoystick != NULL)
	{
		//入力デバイスからデータ取得
		if (SUCCEEDED(m_pJoystick->GetDeviceState(sizeof(state), &state)))
		{
			for (int nCntKey = 0; nCntKey < BUTTON_MAX; nCntKey++)
			{
				m_aStateTrigger.rgbButtons[nCntKey] = (m_aState.rgbButtons[nCntKey] ^ state.rgbButtons[nCntKey]) & state.rgbButtons[nCntKey];
				m_aStateRelease.rgbButtons[nCntKey] = (m_aState.rgbButtons[nCntKey] ^ state.rgbButtons[nCntKey]) & ~state.rgbButtons[nCntKey];
			}
			m_aState = state;
		}
		else
		{
			m_pJoystick->Acquire();
		}
	}
}

//=============================================================================
// ボタン情報の取得
//=============================================================================
bool CGamepad::GetPress(int Botton_Type)
{
	return (m_aState.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CGamepad::GetTrigger(int Botton_Type)
{
	return (m_aStateTrigger.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

bool CGamepad::GetRelease(int Botton_Type)
{
	return (m_aStateRelease.rgbButtons[Botton_Type] & 0x80) ? true : false;
}

DIJOYSTATE CGamepad::GetGamepad(void)
{
	return m_aState;
}

//=============================================================================
// コールバック関数
//=============================================================================
BOOL CALLBACK CGamepad::EnumJoysticksCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	// ジョイスティックデバイスの作成
	HRESULT ret = m_pInput->CreateDevice(lpddi->guidInstance, &m_pJoystick, NULL);
	if (FAILED(ret)) 
	{
		return DIENUM_STOP;
	}

	// 入力データ形式のセット
	ret = m_pJoystick->SetDataFormat(&c_dfDIJoystick);
	if (FAILED(ret)) 
	{
		m_pJoystick->Release();
		return DIENUM_STOP;
	}

	return DIENUM_STOP;
}

BOOL CALLBACK CGamepad::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = -STICK_POW;
	diprg.lMax = STICK_POW;

	if (FAILED(m_pJoystick->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}