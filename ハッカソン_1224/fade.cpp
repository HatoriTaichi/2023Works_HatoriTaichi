//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 羽鳥太一
//
//=============================================================================
#include "fade.h"
#include "renderer.h"

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFade::CFade()
{
	m_pVtxBuff = NULL;
	m_nextMode = CManager::MODE::TITLE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{

}

//=============================================================================
// フェードの初期化処理
//=============================================================================
HRESULT CFade::Init(void) 
{
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(	sizeof(VERTEX_2D) * 4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&m_pVtxBuff,
									NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// フェードの終了処理
//=============================================================================
void CFade::Uninit(void) 
{
	if (m_pVtxBuff != NULL) 
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// フェードの更新処理
//=============================================================================
void CFade::Update(void) 
{
	if (m_Fade != FADE_NONE)
	{
		if (m_Fade == FADE_IN)
		{
			m_colA -= 0.0035f;		//フェードの速さ
			if (m_colA <= 0.0f)
			{
				m_colA = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)
		{
			m_colA += 0.0035f;		//フェードの速さ
			if (m_colA >= 1.0f)
			{
				m_colA = 1.0f;
				m_Fade = FADE_IN;
				CManager::SetMode(m_nextMode);
			}
		}
		VERTEX_2D *pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点情報を設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colA);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colA);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colA);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, m_colA);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// フェードの描画処理
//=============================================================================
void CFade::Draw(void) 
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);	

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(	0,
								m_pVtxBuff, 
								0,
								sizeof(VERTEX_2D));
	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(	D3DPT_TRIANGLESTRIP, //プリミティブの種類
							0,
							2);
}

//=============================================================================
//フェードの設定
//=============================================================================
void CFade::SetFade(CManager::MODE mode) 
{
	m_Fade = FADE_OUT;
	m_nextMode = mode;
	m_colA = 0.0f;
}