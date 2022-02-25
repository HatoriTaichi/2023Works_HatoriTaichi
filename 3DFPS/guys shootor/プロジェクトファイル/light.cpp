//---------------------------
//インクルードファイル
//---------------------------
#include "light.h"
#include "keyinput.h"
#include "camara.h"

//---------------------------
//グローバル変数
//---------------------------
D3DLIGHT9		g_Ligt[MAX_LIGHT];	//ライト

//---------------------------
//初期化処理
//---------------------------
HRESULT InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	D3DXVECTOR3 VecDir[MAX_LIGHT];	//ベクトル

	pDevice = GetDevice(); //デバイスを取得する

	//---------------------------
	//ライトの設定
	//---------------------------

	for (int nCntLihgt = 0; nCntLihgt < MAX_LIGHT; nCntLihgt++)
	{
		//ライトのクリア
		ZeroMemory(	&g_Ligt[nCntLihgt],
					sizeof(D3DLIGHT9));

		if (nCntLihgt == 0)
		{
			//ライトの種類
			g_Ligt[nCntLihgt].Type = D3DLIGHT_DIRECTIONAL;	//種類

			//ライトの拡散光
			g_Ligt[nCntLihgt].Diffuse = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//色

			//ライトの場所
			g_Ligt[nCntLihgt].Position = (D3DXVECTOR3(-1000.0f, 1000.0f, 1000.0f));

			//ライトの方向
			VecDir[nCntLihgt] = (D3DXVECTOR3(0.2f, -0.8f, 0.6f));

			//正規化する
			D3DXVec3Normalize(	&VecDir[nCntLihgt],
								&VecDir[nCntLihgt]);

			//ライトの方向を入れる
			g_Ligt[nCntLihgt].Direction = VecDir[nCntLihgt];

			//ライトの設定
			pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//0番目のライトに設定した設定を入れる

			//ライトを有効にする
			pDevice->LightEnable(nCntLihgt, TRUE);	//0番目のライトを付ける
		}
		else if (nCntLihgt == 1)
		{
			//ライトの種類
			g_Ligt[nCntLihgt].Type = D3DLIGHT_DIRECTIONAL;	//種類

			//ライトの拡散光
			g_Ligt[nCntLihgt].Diffuse = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//色

			//ライトの場所
			g_Ligt[nCntLihgt].Position = (D3DXVECTOR3(0.0f, 1000.0f, 0.0f));

			//ライトの方向
			VecDir[nCntLihgt] = (D3DXVECTOR3(0.0f, -1.0f, 0.0f));

			//正規化する
			D3DXVec3Normalize(	&VecDir[nCntLihgt],
								&VecDir[nCntLihgt]);

			//ライトの方向を入れる
			g_Ligt[nCntLihgt].Direction = VecDir[nCntLihgt];

			//ライトの設定
			pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//1番目のライトに設定した設定を入れる

			//ライトを有効にする
			pDevice->LightEnable(nCntLihgt, TRUE);	//1番目のライトを付ける
		}
		else if (nCntLihgt == 2)
		{
			//ライトの種類
			g_Ligt[nCntLihgt].Type = D3DLIGHT_DIRECTIONAL;	//種類

			//ライトの拡散光
			g_Ligt[nCntLihgt].Diffuse = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//色

			//ライトの場所
			g_Ligt[nCntLihgt].Position = (D3DXVECTOR3(3000.0f, -1000.0f, -3000.0f));

			//ライトの方向
			VecDir[nCntLihgt] = (D3DXVECTOR3(-0.2f, 0.8f, -0.6f));

			//正規化する
			D3DXVec3Normalize(	&VecDir[nCntLihgt],
								&VecDir[nCntLihgt]);

			//ライトの方向を入れる
			g_Ligt[nCntLihgt].Direction = VecDir[nCntLihgt];

			//ライトの設定
			pDevice->SetLight(nCntLihgt, &g_Ligt[nCntLihgt]);	//2番目のライトに設定した設定を入れる

			//ライトを有効にする
			pDevice->LightEnable(nCntLihgt, TRUE);	//2番目のライトを付ける
		}
	}
	return S_OK;
}

//---------------------------
//終了処理
//---------------------------
void UninitLight(void)
{

}

//---------------------------
//更新処理
//---------------------------
void UpdateLight(void)
{

}
