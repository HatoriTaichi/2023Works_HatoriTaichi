//==================================================
//
// メインCPP(main.cpp)
// Author：羽鳥太一
//
//==================================================
//------------------------
// インクルード
//------------------------
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include <iostream>
#include <utility>
#include "main.h"
#include "tcp_listener.h"
#include "communication.h"
#include "communicationdata.h"

//------------------------
// グローバル変数
//------------------------
int g_nRoomCount = 0;

//------------------------
// メイン関数
//------------------------
void main(void)
{
	int n = sizeof(CCommunicationData::COMMUNICATION_DATA);
	//------------------------
	// 初期化
	//------------------------
	WSADATA  wsaData;
	int nErr = WSAStartup(WINSOCK_VERSION, &wsaData);

	if (nErr != 0)
	{
		cout << "初期化に失敗しました" << endl;
	}

	CTcpListener *pListenner = new CTcpListener;

	if (pListenner != NULL && pListenner->Init() == true)
	{
		while (pListenner != NULL)
		{
			CCommunication *pCommunication;

			// 接続待ち
			pCommunication = pListenner->Accept();
			g_nRoomCount++;

			// スレッド生成
			thread th(RoomCreate, pCommunication, pListenner);

			// 部屋を作り終えるまでブロック
			th.join();
		}
	}
	if (pListenner != NULL)
	{
		pListenner->Uninit();
		delete pListenner;
		pListenner = NULL;
	}

	//------------------------
	// 終了
	//------------------------
	cout << "終了します。"<< endl;
	cout << "何かキーを押してください。"<< endl;
	KeyWait();
	WSACleanup();
}

//--------------------------
// 1部屋事のマルチスレッド
//--------------------------
void CommuniCationClient(CCommunication *pSendRecvP1, CCommunication *pSendRecvP2, CTcpListener *pServer)
{
	fd_set fds, readfds;
	SOCKET maxfd, sock[MAX_PLAYER];
	CCommunicationData CommmuData[MAX_PLAYER];
	CCommunicationData::COMMUNICATION_DATA *pCommuData[MAX_PLAYER];
	int nRecv = 1;
	char aRecvData[MAX_COMMUDATA];

	FD_ZERO(&readfds);

	cout << "部屋数 : " << g_nRoomCount << endl;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		pCommuData[nCnt] = CommmuData[nCnt].GetCmmuData();
		pCommuData[nCnt]->bConnect = true;
	}

	// ソケットの入手
	sock[0] = pSendRecvP1->GetSocket();
	sock[1] = pSendRecvP2->GetSocket();

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		 // 監視ソケットの登録
		FD_SET(sock[nCnt], &readfds);
	}
	// 最大ソケットの判定
	if (sock[0] > sock[1])
	{
		maxfd = sock[0];
	}
	else if (sock[1] > sock[0])
	{
		maxfd = sock[1];
	}
	while (nRecv != -1)
	{
		memcpy(&fds, &readfds, sizeof(fd_set));

		// ソケットの監視
		select(maxfd + 1, &fds, NULL, NULL, NULL);

		// プレイヤー1にsendされていたら
		if (FD_ISSET(sock[0], &fds))
		{
			nRecv = pSendRecvP1->Recv(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

			CommmuData[0].SetCmmuData(*(CCommunicationData::COMMUNICATION_DATA*)&aRecvData[0]);

			pSendRecvP2->Send(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
		}
		// プレイヤー2にsendされていたら
		if (FD_ISSET(sock[1], &fds))
		{
			nRecv = pSendRecvP2->Recv(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

			CommmuData[1].SetCmmuData(*(CCommunicationData::COMMUNICATION_DATA*)&aRecvData[0]);

			pSendRecvP1->Send(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
		}
	}
	// 接続フラグの切替
	pCommuData[0]->bConnect = false;
	pCommuData[1]->bConnect = false;

	// 切断されていることをsend
	pSendRecvP1->Send(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));
	pSendRecvP2->Send(&aRecvData[0], sizeof(CCommunicationData::COMMUNICATION_DATA));

	pSendRecvP1->Uninit();
	pSendRecvP2->Uninit();
	delete pSendRecvP1;
	delete pSendRecvP2;

	g_nRoomCount--;
	cout << "部屋が解散されました。" << endl;
	cout << "部屋数 : " << g_nRoomCount << endl;
}

//------------------------
// 部屋を作る
//------------------------
void RoomCreate(CCommunication *pSendRecvP1, CTcpListener *pServer)
{
	CCommunication *pSendRecvP2;
	CCommunicationData::COMMUNICATION_DATA pCommuData[MAX_PLAYER];
	bool bConnect = false;
	char SendData[MAX_COMMUDATA];

	// 接続待ち
	pSendRecvP2 = pServer->Accept();

	bConnect = true;

	// プレイヤー1にsend
	memcpy(&SendData[0], &bConnect, sizeof(bool));
	pSendRecvP1->Send(&SendData[0], sizeof(bool));

	// プレイヤー2にsend
	memcpy(&SendData[0], &bConnect, sizeof(bool));
	pSendRecvP2->Send(&SendData[0], sizeof(bool));

	// プレイヤー番号の設定
	pCommuData[0].Player.nNumber = 1;
	pCommuData[1].Player.nNumber = 2;

	// プレイヤー1にsend
	memcpy(&SendData[0], &pCommuData[0].Player.nNumber, sizeof(int));
	pSendRecvP1->Send(&SendData[0], sizeof(int));

	// プレイヤー2にsend
	memcpy(&SendData[0], &pCommuData[1].Player.nNumber, sizeof(int));
	pSendRecvP2->Send(&SendData[0], sizeof(int));

	// スレッド生成
	thread th(CommuniCationClient, pSendRecvP1, pSendRecvP2, pServer);

	// スレッドを切り離す
	th.detach();
}

//------------------------
// キー入力待ち
//------------------------
void KeyWait(void)
{
	rewind(stdin);
	getchar();
}