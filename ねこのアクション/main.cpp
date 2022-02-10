//=============================================================================
//
// メイン処理 [main.cpp]
// Author : KAZUTO SAKAI
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "home.h"
#include "fade.h"
#include "esystage01.h"
#include "esystage02.h"
#include "esystage03.h"
#include "title.h"
#include "result.h"
#include "operation.h"
#include "gameover.h"
#include "nostage01.h"
#include "nostage02.h"
#include "nostage03.h"
#include "nostage04.h"
#include "hard01.h"
#include "hard02.h"
#include "herd03.h"
#include "herd04.h"
#include "herd05.h"
#include "sound.h"

#ifdef _DEBUG
#include "score.h"
#include "timer.h"
#include"life.h"
#endif  _DEBUG


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"								// ウインドウのクラス名
#define WINDOW_NAME		"ねこのアクション"	// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
#ifdef _DEBUG
void DrawFPS(void);
#endif

//*****************************************************************************
// グローバル変数宣言
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D オブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;			// フォントへのポインタ
#endif
int					g_nCountFPS;			// FPSカウンタ
MODE				g_mode = MODE_TITLE;	//現在のモード
MODE				g_mode2;

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
	hWnd = CreateWindow(	CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							NULL,
							NULL,
							hInstance,
							NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if (FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒ごとに実行
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 144))
			{// 1/144秒経過
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// 終了処理
	Uninit();

	// 分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;							// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	d3dpp.Windowed = TRUE;								// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

																// デバイスの生成
																// ディスプレイアダプタを表すためのデバイスを作成
																// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングを行わない
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																			// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

																			// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

#ifdef _DEBUG
	// デバッグ情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
#endif

	InitKeyboard(hInstance, hWnd);

	InitSound(hWnd);

#ifdef _DEBUG
	InitScore();

	InitTimer();

	InitLife();
#endif _DEBUG

	SetMode(g_mode);

	InitFade(g_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
#ifdef _DEBUG
	if (g_pFont != NULL)
	{// デバッグ情報表示用フォントを設定
		g_pFont->Release();
		g_pFont = NULL;
	}
#endif
	//省略部分：各種オブジェクトの終了処理
	UninitKeyboard();

	UninitTitle();

	UninitOperation();

	UninitResult();

	UninitGameover();

	UninitHome();

	UninitEsStage01();

	UninitEsStage02();

	UninitEsStage03();

	UninitNoStage01();

	UninitNoStage02();

	UninitNoStage03();

	UninitNoStage04();

	UninitHdStage01();

	UninitHdStage02();

	UninitHdStage03();

	UninitHdStage04();

	UninitHdStage05();

	UninitFade();
	if (g_pD3DDevice != NULL)
	{// デバイスの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	//省略部分：各種オブジェクトの更新処理
	UpdateKeyboard();
	
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_OPERATION:
		UpdateOperation();
		break;
	case MODE_HOME:
		UpdateHome();
		break;
	case MODE_ES_STAGE01:
		UpdateEsStage01();
		break;
	case MODE_ES_STAGE02:
		UpdateEsStage02();
		break;
	case MODE_ES_STAGE03:
		UpdateEsStage03();
		break;
	case MODE_NO_STAGE01:
		UpdateNoStage01();
		break;
	case MODE_NO_STAGE02:
		UpdateNoStage02();
		break;
	case MODE_NO_STAGE03:
		UpdateNoStage03();
		break;
	case MODE_NO_STAGE04:
		UpdateNoStage04();
		break;
	case MODE_HD_STAGE01:
		UpdateHdStage01();
		break;
	case MODE_HD_STAGE02:
		UpdateHdStage02();
		break;
	case MODE_HD_STAGE03:
		UpdateHdStage03();
		break;
	case MODE_HD_STAGE04:
		UpdateHdStage04();
		break;
	case MODE_HD_STAGE05:
		UpdateHdStage05();
		break;
	case MODE_GAMEOVER:
		UpdateGameover();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	}
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		//省略部分：各種オブジェクトの描画処理
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_OPERATION:
			DrawOperation();
			break;
		case MODE_HOME:
			DrawHome();
			break;
		case MODE_ES_STAGE01:
			DrawEsStage01();
			break;
		case MODE_ES_STAGE02:
			DrawEsStage02();
			break;
		case MODE_ES_STAGE03:
			DrawEsStage03();
			break;
		case MODE_NO_STAGE01:
			DrawNoStage01();
			break;
		case MODE_NO_STAGE02:
			DrawNoStage02();
			break;
		case MODE_NO_STAGE03:
			DrawNoStage03();
			break;
		case MODE_NO_STAGE04:
			DrawNoStage04();
			break;
		case MODE_HD_STAGE01:
			DrawHdStage01();
			break;
		case MODE_HD_STAGE02:
			DrawHdStage02();
			break;
		case MODE_HD_STAGE03:
			DrawHdStage03();
			break;
		case MODE_HD_STAGE04:
			DrawHdStage04();
			break;
		case MODE_HD_STAGE05:
			DrawHdStage05();
			break;
		case MODE_GAMEOVER:
			DrawGameover();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		}
		DrawFade();
#ifdef _DEBUG
		DrawFPS();
#endif
		// Direct3Dによる描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイスを取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=============================================================================
// モードの切り替え
//=============================================================================
void SetMode(MODE mode)
{
	g_mode2 = g_mode;

	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_OPERATION:
		UninitOperation();
		break;
	case MODE_HOME:
		UninitHome();
		break;
	case MODE_ES_STAGE01:
		UninitEsStage01();
		break;
	case MODE_ES_STAGE02:
		UninitEsStage02();
		break;
	case MODE_ES_STAGE03:
		UninitEsStage03();
		break;
	case MODE_NO_STAGE01:
		UninitNoStage01();
		break;
	case MODE_NO_STAGE02:
		UninitNoStage02();
		break;
	case MODE_NO_STAGE03:
		UninitNoStage03();
		break;
	case MODE_NO_STAGE04:
		UninitNoStage04();
		break;
	case MODE_HD_STAGE01:
		UninitHdStage01();
		break;
	case MODE_HD_STAGE02:
		UninitHdStage02();
		break;
	case MODE_HD_STAGE03:
		UninitHdStage03();
		break;
	case MODE_HD_STAGE04:
		UninitHdStage04();
		break;
	case MODE_HD_STAGE05:
		UninitHdStage05();
		break;
	case MODE_GAMEOVER:
		UninitGameover();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_OPERATION:
		InitOperation();
		break;
	case MODE_HOME:
		InitHome();
		break;
	case MODE_ES_STAGE01:
		InitEsStage01();
		break;
	case MODE_ES_STAGE02:
		InitEsStage02();
		break;
	case MODE_ES_STAGE03:
		InitEsStage03();
		break;
	case MODE_NO_STAGE01:
		InitNoStage01();
		break;
	case MODE_NO_STAGE02:
		InitNoStage02();
		break;
	case MODE_NO_STAGE03:
		InitNoStage03();
		break;
	case MODE_NO_STAGE04:
		InitNoStage04();
		break;
	case MODE_HD_STAGE01:
		InitHdStage01();
		break;
	case MODE_HD_STAGE02:
		InitHdStage02();
		break;
	case MODE_HD_STAGE03:
		InitHdStage03();
		break;
	case MODE_HD_STAGE04:
		InitHdStage04();
		break;
	case MODE_HD_STAGE05:
		InitHdStage05();
		break;
	case MODE_GAMEOVER:
		InitGameover();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	}

	g_mode = mode;

}

//=============================================================================
// モード情報の取得
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}

//=============================================================================
// 前回のモード情報の取得
//=============================================================================
MODE GetMode2(void)
{
	return g_mode2;
}

//=============================================================================
// FPS表示処理
//=============================================================================
#ifdef _DEBUG
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", g_nCountFPS);

	// テキスト描画
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0x0, 0x0));
}
#endif