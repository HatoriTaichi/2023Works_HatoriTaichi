//=============================================================================
//
// オブジェクト処理 [scene.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "texture.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CScene
{
public:
	//---------------------------
	// 列挙型
	//---------------------------
	enum class LAYER_TYPE
	{
		LAYER_00 = 0,	// レイヤー(0)
		LAYER_01,		// レイヤー(1)
		LAYER_02,		// レイヤー(2)
		LAYER_03,		// レイヤー(3)
		LAYER_04,		// レイヤー(4)
		LAYER_05,		// レイヤー(5)
		MAX_LAYER,		// レイヤー総数
	};
	CScene(LAYER_TYPE Layer = LAYER_TYPE::LAYER_00);	// デフォルトコンストラクタ
	virtual ~CScene();	// デフォルトデストラクタ
	virtual HRESULT Init(void) = 0;	// ポリゴンの初期化
	virtual void Uninit(void) = 0;	// ポリゴンの終了
	virtual void Update(void) = 0;	// ポリゴンの更新
	virtual void Draw(void) = 0;	// ポリゴンの描画
	static void ReleaseAll(void);	// オブジェクトの破棄
	static void UpdateAll(void);	// オブジェクトの更新処理
	static void DrawAll(void);		// オブジェクトの描画
	D3DXVECTOR3 GetPos(void) { return m_Pos; }			// 位置ゲッダー
	D3DXVECTOR3 GetSize(void) { return m_Size; }		// サイズゲッダー
	bool GetDeath(void) { return m_bDeth; }	// 死亡フラグのゲッダー
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }		// 位置セッター
	void SetSize(D3DXVECTOR3 size) { m_Size = size; }	// サイズセッター
private:
	static vector<CScene*> m_pObjet[(int)LAYER_TYPE::MAX_LAYER];	// 先頭
	D3DXVECTOR3	m_Pos;		// ポス
	D3DXVECTOR3 m_Size;		// サイズ
	int m_nPriority;	// 描画順
	bool m_bDeth;	// 死亡フラグ
protected:
	void Release(void) { m_bDeth = true; }		// 死亡フラグ立てる
};

#endif