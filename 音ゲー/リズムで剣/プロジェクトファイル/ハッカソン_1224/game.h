//=============================================================================
//
// タイトル [title.h]
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
// 前方宣言
//*****************************************************************************
class CUiObj;
class CCounter;

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
	CCounter *GetCombo(void) { return m_pCombo; }
	CCounter *GetScore(void) { return m_pScore; }
private:
	vector<string> m_Type;	// テクスチャタイプ
	vector<string> m_NotesType;	// テクスチャタイプ
	vector<float> m_nSecond;	// 秒数
	CCounter *m_pCombo;
	CCounter *m_pScore;
	int m_nUiNum;	// UI数
	int m_nNotesNum;	// ノーツ数
	int m_nNotes;	// どのノーツ
	int m_nTimer;
	float m_nLimit;	// 時間
	bool m_bFade = false;	// フェード
};

#endif