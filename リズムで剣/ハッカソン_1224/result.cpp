//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 羽鳥太一
//
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "result.h"
#include "manager.h"
#include "textureobj.h"
#include "sound.h"
#include "keyinput.h"
#include "fade.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CResult::CResult()
{

}

//=============================================================================
// デフォルトデストラクタ
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CResult::Init(void)
{
	CUiObj::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), "RESULTBG");

	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CResult::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	CKeyboard *pKey = CManager::GetKeyboard();
	CFade *pFade = CManager::GetFade();

	if (pKey->GetTrigger(pKey->ENTER) == true && pFade->GetFade() == CFade::FADE_NONE)
	{
		pFade->SetFade(CManager::MODE::TITLE);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{

}