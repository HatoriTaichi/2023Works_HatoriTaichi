//=============================================================================
//
// 3Dポリゴン処理 [floo.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _MESHFLOO_H_
#define _MESHFLOO_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"
#include "scene3D.h"
#include "manager.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMeshFloo : public CScene3D
{
public:
	CMeshFloo();		// デフォルトコンストラクタ
	~CMeshFloo();	// デストラクタ
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	static CMeshFloo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyZ, int nRadiusX, int nRadiusZ, string type);	// セッター
private:
	int m_nXPoly;
	int m_nZPoly;
	int m_nXRadius;
	int m_nZRadius;
	int m_nMoveReversCnt;
	bool m_bRevers;
	D3DXMATRIX m_mtxWorld;// ワールドマトリックス
	string m_Type;	// テクスチャ
};

#endif // !_SCENE3D_H_