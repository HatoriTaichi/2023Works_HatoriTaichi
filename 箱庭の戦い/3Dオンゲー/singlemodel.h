//=============================================================================
//
// 単体モデル処理 [player.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _SINGLEMODEL_H_
#define _SINGLEMODEL_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "model.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSingleModel : public CScene
{
public:
	CSingleModel(LAYER_TYPE Layer = LAYER_TYPE::LAYER_01);	// デフォルトコンストラクタ
	~CSingleModel();	// デフォルトデストラクタ
	HRESULT Init(void);	// ポリゴンの初期化
	void Uninit(void);	// ポリゴンの終了
	void Update(void);	// ポリゴンの更新
	void Draw(void);	// ポリゴンの描画
	static CSingleModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, CModel::TYPE type);	// 生成
	void SetScale(D3DXVECTOR3 scale) { m_pModel->SetScale(scale); }	// セッター
	D3DXVECTOR3 GetPos(void) { return m_Pos; }	// ゲッダー
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// ゲッダー
	CModel *GetModel(void) { return m_pModel; }	// ゲッダー
private:
	CModel *m_pModel;	// モデル
	CModel::TYPE m_Type;	// 種類
	D3DXVECTOR3 m_Pos;		// 位置
	D3DXVECTOR3 m_Rot;		// 向き
	D3DXVECTOR3 m_Scale;	// スケール
	D3DXMATRIX m_MtxWold;	// ワールドマトリックス
};

#endif