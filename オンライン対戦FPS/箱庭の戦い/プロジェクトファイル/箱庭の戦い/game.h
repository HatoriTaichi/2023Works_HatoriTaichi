//=============================================================================
//
// 入力処理 [input.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYER (2)	// プレイヤーの数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CEnemy;
class CSingleModel;
class CSound;
class CCounter;
class CUiObj;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGame
{
public:
	CGame();	// デフォルトコンストラクタ
	~CGame();	// デフォルトデストラクタ
	HRESULT Init(void);	// 初期化
	void Uninit(void);		// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	CPlayer *GetPlayer(void) { return m_pPlayer; }	// ゲッダー
	CEnemy *GetEnemy(void) { return m_pEnemy; }	// ゲッダー
	CSingleModel *GetModel(int nCnt) {return m_pSingleModel[nCnt]; }	// ゲッダー
	int GetMaxModel(void) { return m_nMaxModel; }	// ゲッター
	CCounter *GetCounter(int nIndex) { return m_pKiilCount[nIndex]; }	// ゲッター
	CCounter *GetAmmo(void) { return m_pAmmo; }	// ゲッター
private:
	void WinOrLoss(void);	// 勝敗
	void MouseProcess(void);	// マウス関連
	vector<CSingleModel*> m_pSingleModel;	// ステージ
	CPlayer *m_pPlayer;	// プレイヤー
	CEnemy *m_pEnemy;	// 敵
	vector<CCounter*> m_pKiilCount;	// キルカウント
	CCounter *m_pMaxAmmo;	// 最大弾数
	CCounter *m_pAmmo;	// 弾数
	int m_nMaxModel;	// モデル最大数
	int m_nType;	// モデルタイプ
	bool m_bDoOnece = false;	// 一回だけ
	bool m_bShow = false;	// マウスの表示
};

#endif