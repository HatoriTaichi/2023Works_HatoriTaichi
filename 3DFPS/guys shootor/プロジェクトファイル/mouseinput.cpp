#include "mouseinput.h"

//---------------------------
//マクロ定義
//---------------------------
#define NUM_BOTTON_MAX (4)	//ボタンの最大数

//---------------------------
//グローバル変数
//---------------------------
LPDIRECTINPUT8 g_pMouseInput = NULL;				//DirectInputオブジェクトのポインタ
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;			//入力デバイス（マウス）へのポインタ
DIMOUSESTATE g_aMouseold;							//前回のマウス
DIMOUSESTATE g_aMouse;								//マウス

//---------------------------
//初期化処理
//---------------------------
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pMouseInput, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pMouseInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//省略
	// データフォーマットを設定
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// マウスへのアクセス権を獲得(入力制御開始)
	g_pDevMouse->Acquire();

	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitMouse(void)
{
	//入力デバイスの開放
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}
	//DirectInputオブジェクトの開放
	if (g_pMouseInput != NULL)
	{
		g_pMouseInput->Release();
		g_pMouseInput = NULL;
	}
}

//---------------------------
//更新処理
//---------------------------
void UpdateMouse(void)
{
	//前回のマウスの状態
	g_aMouseold = g_aMouse;

	// 最新のマウスの状態を更新
	HRESULT	hr = g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_aMouse);
	if (FAILED(hr))
	{
		g_pDevMouse->Acquire();
		hr = g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_aMouse);
	}
}

//---------------------------
//ボタン押した
//---------------------------
bool MouseDowan(int Botton_Type)
{
	return (g_aMouse.rgbButtons[Botton_Type] & 0x80) ? true : false;
}
