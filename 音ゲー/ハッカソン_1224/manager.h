//=============================================================================
//
// マネージャー管理処理 [namager.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "main.h"

#pragma comment(lib, "ws2_32.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIGHT (3)	//ライトの数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CTexture;
class CKeyboard;
class CMouse;
class CFade;
class CTitle;
class CGame;
class CManual;
class CResult;
class CSound;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CManager
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class MODE
	{
		TITLE = 0,	// タイトルシーン
		MANUAL,
		GAME,	// ゲーム
		RESULT,
		MAX,	// 全体数
	};

	CManager();	// デフォルトコンストラクタ
	~CManager();// デフォルトデストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	// スクリーンの初期化
	void Uninit(void);	// スクリーンの終了
	void Update(void);	// スクリーンの更新
	void Draw(void);	// スクリーンの描画
	static void SetMode(MODE mode);	// モードチェンジ
	static MODE GetMode(void) { return m_Mode; }	// モード入手
	static MODE GetModeOld(void) { return m_ModeOld; }	// 前回のモード入手
	static CRenderer *GetRenderer(void) { return m_pRenderer; }	// レンダリングクラスの取得
	static CTexture *GetTexture(void) { return m_pTexture; }	// テクスチャクラスの取得
	static CKeyboard *GetKeyboard(void) { return m_pKeyboard; }	// キーボードクラスの取得
	static CMouse *GetMouse(void) { return m_pMouse; }	// マウスクラスの取得
	static CFade *GetFade(void) { return m_pFade; }	// フェードクラス
	static CTitle *GetTitle(void) { return m_pTitle; }	// タイトルクラス
	static CGame *GetGame(void) { return m_pGame; }	// ゲームクラス
	static HWND GetHandle(void) { return m_hwnd; }	// ハンドル
	static CSound *GetSound()	{ return m_pSound; }

private:
	static MODE				m_Mode;		// シーンモード
	static MODE				m_ModeOld;	// シーンモード
	static CRenderer		*m_pRenderer;	// レンダリングクラス
	static CTexture			*m_pTexture;	// テクスチャクラス
	static CKeyboard		*m_pKeyboard;	// キーボードクラス
	static CMouse			*m_pMouse;		// マウスクラス
	static CFade			*m_pFade;	// フェード
	static CTitle			*m_pTitle;	// タイトルクラス
	static CManual			*m_pManual;
	static CGame			*m_pGame;	// ゲームクラス
	static CResult			*m_pResult;
	static CSound			*m_pSound;	// サウンドクラス
	static HWND				m_hwnd;	// ウィンドウハンドル
};

#endif