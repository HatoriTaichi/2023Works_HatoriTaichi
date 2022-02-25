//=============================================================================
//
// キーボード処理 [keyinput.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _KEYINPUT_H_
#define _KEYINPUT_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX (256)//キーの最大数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CKeyboard : public CInput
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	typedef enum
	{
		UP,		// ue
		LEFT,	// hidari
		DOWN,	// sita
		RIGHT,	// migi
		ENTER,
		KEYBINDMAX,
	} KEYBIND;

	CKeyboard();	// デフォルトコンストラクタ
	~CKeyboard();	// デフォルトデストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void GetAllKeyUpdate(KEYBIND key);	// どのキーが押されたか
	void BindKey(KEYBIND key, int keycode);	// キーバインド
	bool GetPress(KEYBIND nKey);	// 押す
	bool GetTrigger(KEYBIND nKey);	// 一回押す
	bool GetRelease(KEYBIND nKey);	// 離した
private:
	BYTE	m_aState[NUM_KEY_MAX];				//キーボードの入力情報（プレス情報）
	BYTE	m_aStateTrigger[NUM_KEY_MAX];		//キーボードの入力情報 (トリガー)
	BYTE	m_aStateRelease[NUM_KEY_MAX];		//キーボードの入力情報 (リリース)
	int Bind[KEYBINDMAX];// キーバインド情報
};

#endif