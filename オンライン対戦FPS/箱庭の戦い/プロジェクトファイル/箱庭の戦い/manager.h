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
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIGHT (3)	//ライトの数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CCamera;
class CLight;
class CTexture;
class CKeyboard;
class CMouse;
class CGamepad;
class CSound;
class CTcpClient;
class CGame;
class CTitle;
class CRule;
class CMatching;
class CFade;

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
		RULE,	// ルール画面
		MATCHING,	// マッチング中
		GAME,	// ゲーム
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
	static CCamera *GetCamera(void) { return m_pCamera; }	// カメラクラスの取得
	static CLight *GetLight(int nLightNum) { return m_pLight[nLightNum]; }	// ライトクラスの取得
	static CTexture *GetTexture(void) { return m_pTexture; }	// テクスチャクラスの取得
	static CKeyboard *GetKeyboard(void) { return m_pKeyboard; }	// キーボードクラスの取得
	static CMouse *GetMouse(void) { return m_pMouse; }	// マウスクラスの取得
	static CGamepad *GetGemepad(void) { return m_pGamepad; }	// パッドクラスの取得
	static CSound  *GetSound(void) { return m_pSound; }	// サウンドクラスの取得
	static CTcpClient *GetTcpClient(void) { return m_pTcpClient; }	// 通信クラスの取得
	static CFade *GetFade(void) { return m_pFade; }	// フェードクラス
	static CTitle *GetTitle(void) { return m_pTitle; }	// タイトルクラス
	static CRule *GetRule(void) { return m_pRule; }	// ルールクラス
	static CMatching *GetMatching(void) { return m_pMatchibg; }	// マッチングクラス
	static CGame *GetGame(void) { return m_pGame; }	// ゲームクラス
	static HWND GetHandle(void) { return m_hwnd; }	// ハンドル
private:
	static MODE				m_Mode;		// シーンモード
	static MODE				m_ModeOld;	// シーンモード
	static CRenderer		*m_pRenderer;	// レンダリングクラス
	static CCamera			*m_pCamera;	// カメラクラス
	static CLight			*m_pLight[MAX_LIGHT];	// ライトクラス
	static CTexture			*m_pTexture;	// テクスチャクラス
	static CKeyboard		*m_pKeyboard;	// キーボードクラス
	static CMouse			*m_pMouse;		// マウスクラス
	static CGamepad			*m_pGamepad;	// パッドクラス
	static CSound			*m_pSound;	// サウンドクラス
	static CTcpClient		*m_pTcpClient;	// 通信クラス
	static CFade			*m_pFade;	// フェード
	static CTitle			*m_pTitle;	// タイトルクラス
	static CRule			*m_pRule;	// ルールクラス
	static CMatching		*m_pMatchibg;	// マッチングクラス
	static CGame			*m_pGame;		// ゲームクラス
	static HWND				m_hwnd;	// ウィンドウハンドル
};

#endif