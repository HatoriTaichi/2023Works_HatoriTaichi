//=============================================================================
//
// キーボード処理 [keyinput.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STICK_POW (1000)

//*****************************************************************************
// クラス定義
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
	CGamepad();	// デフォルトコンストラクタ
	~CGamepad();	// デフォルトデストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	bool GetPress(int Botton_Type);	// 押す
	bool GetTrigger(int Botton_Type);	// 一回押す
	bool GetRelease(int Botton_Type);	// 離した
	DIJOYSTATE GetGamepad(void);	// マウス座標
	static BOOL CALLBACK EnumJoysticksCallback(const LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);
	static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext);
private:
	DIDEVCAPS m_diDevCaps;
	DIJOYSTATE m_aState;			//キーボードの入力情報（プレス情報）
	DIJOYSTATE m_aStateTrigger;		//キーボードの入力情報 (トリガー)
	DIJOYSTATE m_aStateRelease;		//キーボードの入力情報 (リリース)
};

#endif