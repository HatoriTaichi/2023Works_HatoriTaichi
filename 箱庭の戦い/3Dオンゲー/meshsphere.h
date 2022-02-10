//=============================================================================
//
// 3Dポリゴン処理 [floo.h]
// Author : 羽鳥太一
//
//=============================================================================
#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_

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
class CMeshsphere : public CScene3D
{
public:
	CMeshsphere();		// デフォルトコンストラクタ
	~CMeshsphere();	// デストラクタ
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理
	static CMeshsphere *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPolyX, int nPolyY, int nRadius, string type);	// セッター
private:
	int m_nXPoly;
	int m_nYPoly;
	int m_nRadius;
	D3DXMATRIX m_mtxWorld;// ワールドマトリックス
	string m_Type;	// テクスチャ
};

#endif // !_SCENE3D_H_