//==================================================
//
// メインヘッダー(main.h)
// Author：羽鳥太一
//
//==================================================
#ifndef _MAIN_H_
#define _MAIN_H_
//------------------------
// インクルード
//------------------------
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <thread>


//------------------------
// 前方宣言
//------------------------
class CCommunication;
class CTcpListener;

//------------------------
// マクロ定義
//------------------------
#define MAX_IP_NUM (16)
#define MAX_PLAYER (2)
#define MAX_COMMUDATA (524)

#pragma comment(lib, "ws2_32.lib")

//------------------------
// プロトタイプ宣言
//------------------------
void CommuniCationClient(CCommunication *pSendRecvP1, CCommunication *pSendRecvP2, CTcpListener *pServer);
void RoomCreate(CCommunication *pSendRecv, CTcpListener *pServer);
void KeyWait(void);

#endif // !_MAIN_H_