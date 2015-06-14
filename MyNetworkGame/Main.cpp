#pragma warning(disable: 4996)
#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <ddraw.h>
#include <dsound.h>
#include <stdio.h>

#include "dsutil.h"
#include "ddutil.h"
#include "extern.h"
#include "data.h"
#include "Logic.h"

BOOL LeftButton, RightButton;
HSNDOBJ Sound[];
bool ZokBoClick = false;
int Count; int result;
int myChoice, yourChoice, myFirstPae, mySecondPae, yourFirstPae, yourSecondPae;
int myResult, yourResult;
bool GameStart = false;
int win = 0;
MSG msg;
int turn;
int myMoney = 0;
int yourMoney;
void CommInit(int argc, char **argv);
void CommSend();
void CommRecv(char *recvData);

int mySendData;
int yourSendData;

void checkMoney(){
	if (result == 0){
		myMoney = myMoney + 1;
	}
	else if (result == 3){
		myMoney = myMoney + 2;
	}
	else{
	}
}

void Pae(){

	myFirstPae = random();
	while (myFirstPae == yourFirstPae){
		yourFirstPae = random();
	}
	mySecondPae = random();
	while (mySecondPae == myFirstPae || mySecondPae == yourFirstPae || mySecondPae == yourSecondPae){
		mySecondPae = random();
	}
	myResult = CheckResult(myFirstPae, mySecondPae);

	if (myResult == 70){
		myResult = CheckResult(mySecondPae, myFirstPae);
	}


}

void _GameProc(int FullScreen)
{
	RECT	BackRect = { 0, 0, 1280, 720 };
	RECT    ZokBoSize = { 0, 30, 1280, 700 };
	RECT	ImageSize = { 700, 200, 1000, 600 };
	RECT    TextSize = {40, 30, 430, 72};
	RECT    myGoStopSize, otherGoStopSize;
	RECT    ButtonRect, goStop[20], ZokBo, Number[10], Money[7];
	RECT ButtonLocation;
	RECT TextLocation;

	if (GameStart==false){
		BackScreen->BltFast(0, 0, ResourceImage[10], &BackRect, DDBLTFAST_WAIT);

	}
	else{
		if (turn == 0){
			//�� ó�� ų�� �а� ��ġ�� ���װ� �־ ������ �� �� �� ������ ��
			Pae();
			CommSend();
			turn++;
		}
		if (myMoney > 6){
			win = 2;
		}

		if (yourMoney > 6){
			win = 1;
		}

		if (win == 0){
			// BackGround
			BackScreen->BltFast(0, 0, ResourceImage[9], &BackRect, DDBLTFAST_WAIT);

			// 10�� ��ǳ �罿
			goStop[0].left = 5;
			goStop[0].top = 5;
			goStop[0].right = 50;
			goStop[0].bottom = 75;

			// 10�� ��ǳ û��
			goStop[1].left = 50;
			goStop[1].top = 5;
			goStop[1].right = 95;
			goStop[1].bottom = 75;

			// 9�� ��ȭ ����
			goStop[2].left = 117;
			goStop[2].top = 5;
			goStop[2].right = 162;
			goStop[2].bottom = 75;

			//9�� ��ȭ û��
			goStop[3].left = 162;
			goStop[3].top = 5;
			goStop[3].right = 207;
			goStop[3].bottom = 75;

			//8�� ���� ��
			goStop[4].left = 230;
			goStop[4].top = 5;
			goStop[4].right = 275;
			goStop[4].bottom = 75;

			//8�� ���� ��
			goStop[5].left = 275;
			goStop[5].top = 5;
			goStop[5].right = 320;
			goStop[5].bottom = 75;

			//7�� ȫ�θ� �����
			goStop[6].left = 343;
			goStop[6].top = 5;
			goStop[6].right = 388;
			goStop[6].bottom = 75;

			//7�� ȫ�θ� �ʴ�
			goStop[7].left = 388;
			goStop[7].top = 5;
			goStop[7].right = 433;
			goStop[7].bottom = 75;

			//6�� ��� ����
			goStop[8].left = 5;
			goStop[8].top = 90;
			goStop[8].right = 50;
			goStop[8].bottom = 160;

			//6�� ��� û��
			goStop[9].left = 50;
			goStop[9].top = 90;
			goStop[9].right = 95;
			goStop[9].bottom = 160;

			//5�� ���� �׸�
			goStop[10].left = 117;
			goStop[10].top = 90;
			goStop[10].right = 162;
			goStop[10].bottom = 160;

			//5�� ���� �ʴ�
			goStop[11].left = 164;
			goStop[11].top = 90;
			goStop[11].right = 207;
			goStop[11].bottom = 160;

			//4�� ��θ� ��
			goStop[12].left = 230;
			goStop[12].top = 90;
			goStop[12].right = 274;
			goStop[12].bottom = 160;

			//4�� ��θ� �ʴ�
			goStop[13].left = 276;
			goStop[13].top = 90;
			goStop[13].right = 319;
			goStop[13].bottom = 160;

			//3�� ���� ��
			goStop[14].left = 342;
			goStop[14].top = 90;
			goStop[14].right = 385;
			goStop[14].bottom = 160;

			//3�� ���� ȫ��
			goStop[15].left = 388;
			goStop[15].top = 90;
			goStop[15].right = 431;
			goStop[15].bottom = 160;

			//2�� ��ȭ ��
			goStop[16].left = 6;
			goStop[16].top = 176;
			goStop[16].right = 49;
			goStop[16].bottom = 242;

			//2�� ��ȭ ȫ��
			goStop[17].left = 52;
			goStop[17].top = 176;
			goStop[17].right = 95;
			goStop[17].bottom = 242;

			//1�� �ҳ��� ��
			goStop[18].left = 119;
			goStop[18].top = 176;
			goStop[18].right = 161;
			goStop[18].bottom = 242;

			//1�� �ҳ��� ȫ��
			goStop[19].left = 164;
			goStop[19].top = 176;
			goStop[19].right = 207;
			goStop[19].bottom = 242;

			//0
			Number[0].left = 873;
			Number[0].top = 440;
			Number[0].bottom = 523;
			Number[0].right = 936;
			//1
			Number[1].left = 976;
			Number[1].top = 440;
			Number[1].bottom = 523;
			Number[1].right = 1030;
			//2
			Number[2].left = 1064;
			Number[2].top = 440;
			Number[2].bottom = 523;
			Number[2].right = 1135;
			//3
			Number[3].left = 1165;
			Number[3].top = 440;
			Number[3].bottom = 523;
			Number[3].right = 1228;
			//4
			Number[4].left = 1260;
			Number[4].top = 440;
			Number[4].bottom = 523;
			Number[4].right = 1328;
			//5
			Number[5].left = 873;
			Number[5].top = 564;
			Number[5].bottom = 654;
			Number[5].right = 936;
			//6	
			Number[6].left = 976;
			Number[6].top = 564;
			Number[6].bottom = 654;
			Number[6].right = 1030;
			//7
			Number[7].left = 1064;
			Number[7].top = 564;
			Number[7].bottom = 654;
			Number[7].right = 1135;
			//8
			Number[8].left = 1165;
			Number[8].top = 564;
			Number[8].bottom = 654;
			Number[8].right = 1228;
			//9
			Number[9].left = 1260;
			Number[9].top = 564;
			Number[9].bottom = 654;
			Number[9].right = 1328;

			//1���
			Money[0].left = 9;
			Money[0].top = 7;
			Money[0].right = 79;
			Money[0].bottom = 31;
			//2���
			Money[1].left = 85;
			Money[1].top = 7;
			Money[1].right = 158;
			Money[1].bottom = 31;
			//4���
			Money[2].left = 165;
			Money[2].top = 7;
			Money[2].right = 233;
			Money[2].bottom = 31;
			//8���
			Money[3].left = 245;
			Money[3].top = 7;
			Money[3].right = 313;
			Money[3].bottom = 31;
			//16���
			Money[4].left = 324;
			Money[4].top = 7;
			Money[4].right = 403;
			Money[4].bottom = 31;
			//32���
			Money[5].left = 413;
			Money[5].top = 7;
			Money[5].right = 494;
			Money[5].bottom = 31;
			//64���
			Money[6].left = 504;
			Money[6].top = 7;
			Money[6].right = 652;
			Money[6].bottom = 31;


			//Random���� �� �� �̱�!  ��� ������ �̹� srand���� �� ������! �� ��!
			myGoStopSize.left = 50;
			myGoStopSize.right = myGoStopSize.left + 80;
			myGoStopSize.top = 500;
			myGoStopSize.bottom = myGoStopSize.top + 100;
			BackScreen->Blt(&myGoStopSize, ResourceImage[8], &goStop[myFirstPae], DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			//Random���� �� �� �̱�! ��� ��!
			otherGoStopSize.left = 500;
			otherGoStopSize.right = otherGoStopSize.left + 80;
			otherGoStopSize.top = 500;
			otherGoStopSize.bottom = otherGoStopSize.top + 100;
			BackScreen->Blt(&otherGoStopSize, ResourceImage[8], &goStop[yourFirstPae], DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			myGoStopSize.left = 130;
			myGoStopSize.right = myGoStopSize.left + 80;
			myGoStopSize.top = 500;
			myGoStopSize.bottom = myGoStopSize.top + 100;
			BackScreen->Blt(&myGoStopSize, ResourceImage[8], &goStop[mySecondPae], DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			//2��° �и� �����Z!
			otherGoStopSize.left = 580;
			otherGoStopSize.right = otherGoStopSize.left + 80;
			otherGoStopSize.top = 500;
			otherGoStopSize.bottom = otherGoStopSize.top + 100;
			BackScreen->Blt(&otherGoStopSize, ResourceImage[8], &goStop[yourSecondPae], DDBLT_WAIT | DDBLT_KEYSRC, NULL);


			//��ư�� Ŭ���Ǹ� ��� ȣ��
			if (Count != 0){

				if (myResult > yourResult){
					//�״�� ���� ���� �̱�
					result = 0;
				}
				else if (yourResult > myResult){
					//�״�� ���� ���� ��
					result = 1;
				}
				else{
					//���
					result = 2;
				}


				//1�� �ƹ��͵� ���� �ʴ´�, 2�� ���� ����, 3�� �ո��� ��´�.
				if (myChoice == 1 && yourChoice == 1){
					turn = turn + 1;
					if (Count > 0){
						Pae();
						Count = 0;
						yourChoice = -1;
						checkMoney();
						CommSend();
						myChoice = -1;
					}
				}
				else if (myChoice == 1 && yourChoice == 2){
					turn = turn + 1;
					if (Count > 0){
						Pae();
						Count = 0;
						yourChoice = -1;
						result = 1; //������ ��
						checkMoney();
						CommSend();
						myChoice = -1;

					}
				}
				else if (myChoice == 1 && yourChoice == 3){
					turn = turn + 1;
					if (Count > 0){
						Pae();
						Count = 0;
						yourChoice = -1;
						result = 0; //������ �̱�
						checkMoney();
						CommSend();
						myChoice = -1;
					}
					_PlayAVI("DATA//��ٸ�.AVI");
				}
				else if (myChoice == 2 && yourChoice == 1){
					turn = turn + 1;
					if (Count > 0){
						Pae();
						Count = 0;
						yourChoice = -1;
						result = 3; // ������ �̱� 4��� ����
						checkMoney();
						CommSend();
						myChoice = -1;
					}
				}
				else if (myChoice == 2 && yourChoice == 2){
					turn = turn + 1;
					if (Count > 0){
						Pae();
						Count = 0;
						yourChoice = -1;
						checkMoney();
						CommSend();
						myChoice = -1;
					}
				}
				else if (myChoice == 2 && yourChoice == 3){
					turn = turn + 1;
					if (Count > 0){
						Pae();
						Count = 0;
						yourChoice = -1;
						result = 1; // ������ ��
						checkMoney();
						win = 1;
						CommSend();
						myChoice = -1;
					}
					_PlayAVI("DATA//�ո������ư�.avi");
				}
				else if (myChoice == 3 && yourChoice == 1){
					turn = turn + 1;
					if (Count > 0){
						Pae();
						Count = 0;
						yourChoice = -1;
						result = 1;//������ ��
						checkMoney();
						CommSend();
						myChoice = -1;
					}
					_PlayAVI("DATA//��ٸ�.AVI");
				}
				else if (myChoice == 3 && yourChoice == 2){
					turn = turn + 1;
					if (Count > 0){
						Pae();
						Count = 0;
						yourChoice = -1;
						result = 0; //������ �̱�
						checkMoney();
						win = 2;
						CommSend();
						myChoice = -1;
					}
					_PlayAVI("DATA//�ո������ư�.avi");
				}
				else if (myChoice == 3 && yourChoice == 3){
					turn = turn + 1;
					if (Count > 0){
						Pae();
						Count = 0;
						yourChoice = -1;
						checkMoney();
						CommSend();
						myChoice = -1;
					}
				}
				else {

					TextLocation.left = 300;
					TextLocation.right = 600;
					TextLocation.top = 200;
					TextLocation.bottom = 300;
					BackScreen->Blt(&TextLocation, ResourceImage[2], &TextSize, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

				}


			}

			//���� ���� Button

			ButtonLocation.left = 600;
			ButtonLocation.right = 723;
			ButtonLocation.top = 70;
			ButtonLocation.bottom = 110;

			ButtonRect.left = 0;
			ButtonRect.right = 680;
			ButtonRect.top = 1;
			ButtonRect.bottom = 314;
			BackScreen->Blt(&ButtonLocation, ResourceImage[5], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			//���� ���� Button

			ButtonLocation.left = 1000;
			ButtonLocation.right = 1154;
			ButtonLocation.top = 370;
			ButtonLocation.bottom = 447;

			ButtonRect.left = 0;
			ButtonRect.right = 680;
			ButtonRect.top = 313;
			ButtonRect.bottom = 625;
			BackScreen->Blt(&ButtonLocation, ResourceImage[5], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			//Nothing Button

			ButtonLocation.left = 1000;
			ButtonLocation.right = 1154;
			ButtonLocation.top = 274;
			ButtonLocation.bottom = 345;

			ButtonRect.left = 0;
			ButtonRect.top = 625;
			ButtonRect.right = 680;
			ButtonRect.bottom = 932;
			BackScreen->Blt(&ButtonLocation, ResourceImage[5], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);


			//�� ���� ��� Button
			ButtonLocation.left = 1000;
			ButtonLocation.right = 1154;
			ButtonLocation.top = 470;
			ButtonLocation.bottom = 580;

			ButtonRect.left = 0;
			ButtonRect.top = 934;
			ButtonRect.right = 680;
			ButtonRect.bottom = 1243;
			BackScreen->Blt(&ButtonLocation, ResourceImage[5], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);


			//�� �� 
			TextLocation.left = 50;
			TextLocation.right = 170;
			TextLocation.top = 400;
			TextLocation.bottom = 440;

			ButtonRect.left = 0;
			ButtonRect.top = 0;
			ButtonRect.right = 730;
			ButtonRect.bottom = 360;

			BackScreen->Blt(&TextLocation, ResourceImage[7], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
			//~��° ��
			TextLocation.left = 100;
			TextLocation.right = 220;
			TextLocation.top = 100;
			TextLocation.bottom = 170;

			ButtonRect.left = 730;
			ButtonRect.top = 0;
			ButtonRect.right = 1460;
			ButtonRect.bottom = 360;
			BackScreen->Blt(&TextLocation, ResourceImage[7], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			//����
			TextLocation.left = 110;
			TextLocation.right = 140;
			TextLocation.top = 120;
			TextLocation.bottom = 160;
			BackScreen->Blt(&TextLocation, ResourceImage[7], &Number[turn], DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			//��� ��
			TextLocation.left = 500;
			TextLocation.right = 620;
			TextLocation.top = 400;
			TextLocation.bottom = 440;

			ButtonRect.left = 0;
			ButtonRect.top = 360;
			ButtonRect.right = 730;
			ButtonRect.bottom = 724;
			BackScreen->Blt(&TextLocation, ResourceImage[7], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			//�� �ݾ� �� ��� �ݾ�
			TextLocation.left = 950;
			TextLocation.right = 1200;
			TextLocation.top = 100;
			TextLocation.bottom = 200;

			ButtonRect.left = 0;
			ButtonRect.top = 724;
			ButtonRect.right = 1460;
			ButtonRect.bottom = 1083;

			BackScreen->Blt(&TextLocation, ResourceImage[7], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			//�� ��
			TextLocation.left = 1050;
			TextLocation.right = 1200;
			TextLocation.top = 110;
			TextLocation.bottom = 150;


			BackScreen->Blt(&TextLocation, ResourceImage[3], &Money[myMoney], DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			//��� ��
			TextLocation.left = 1070;
			TextLocation.right = 1200;
			TextLocation.top = 150;
			TextLocation.bottom = 190;


			BackScreen->Blt(&TextLocation, ResourceImage[3], &Money[yourMoney], DDBLT_WAIT | DDBLT_KEYSRC, NULL);

			if (ZokBoClick == true){
				ZokBo.left = 0;
				ZokBo.right = 857;
				ZokBo.top = 0;
				ZokBo.bottom = 960;
				BackScreen->Blt(&ZokBoSize, ResourceImage[6], &ZokBo, DDBLT_WAIT, NULL);
			}

		}
		else if (win == 1){
			BackScreen->BltFast(0, 0, ResourceImage[0], &BackRect, DDBLTFAST_WAIT);
		}
		else{
			BackScreen->BltFast(0, 0, ResourceImage[1], &BackRect, DDBLTFAST_WAIT);
		}
		}
	if (FullScreen)
		RealScreen->Flip(NULL, DDFLIP_WAIT);
	else{
		RECT WinRect;
		RECT Rect = { 0, 0, 1280, 720 };

		GetWindowRect(MainHwnd, &WinRect);
		RealScreen->Blt(&WinRect, BackScreen, &Rect, DDBLT_WAIT, NULL);
	}

}

//��ư �۵�
long FAR PASCAL WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case    WM_MOUSEMOVE:   MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		break;
	case	WM_LBUTTONDOWN:	LeftButton = TRUE;
		GameStart = true;
		if (ZokBoClick == false){
			if (600 <= MouseX && MouseX <= 723 && 40 <= MouseY && MouseY <= 78)
			{
				ZokBoClick = true;
			}
		}
		else{
			ZokBoClick = false;
		}
		if (LeftButton == TRUE){
			//�ƹ��͵� ���� �ʴ´� ��ư
			if (1000 <= MouseX && MouseX <= 1154 && 250 <= MouseY && MouseY <= 310)
			{
				PlaySound(NULL, NULL, SND_ASYNC);
				Count++;
				myChoice = 1;
				mySendData = 1;
				CommSend();
				_PlayAVI("DATA//�ƹ��͵������ʴ´�.avi");
				PlaySound("Sound//OST.WAV", NULL, SND_ASYNC);	
			}


			//�� �� ��ư
			if (1000 <= MouseX && MouseX <= 1154 && 342 <= MouseY && MouseY <= 410)
			{
				PlaySound(NULL, NULL, SND_ASYNC);
				Count++;
				myChoice = 2;
				mySendData = 1;
				CommSend();
				_PlayAVI("DATA//���廩��.avi");				
				PlaySound("Sound//OST.WAV", NULL, SND_ASYNC);
			}

			//�� ���� ��ư
			if (1000 <= MouseX && MouseX <= 1154 && 447 <= MouseY && MouseY <= 540)
			{
				PlaySound(NULL, NULL, SND_ASYNC);
				Count++;
				myChoice = 3;
				mySendData = 1;
				CommSend();
				_PlayAVI("DATA//�ո���.avi");
				PlaySound("Sound//OST.WAV", NULL, SND_ASYNC);
			}
		}
	
		break;
	case	WM_LBUTTONUP:	LeftButton = FALSE;
		break;
	case	WM_RBUTTONDOWN:	RightButton = TRUE;
		break;
	case	WM_RBUTTONUP:	RightButton = FALSE;
		break;

	case    WM_DESTROY:  _WindowMode();
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		if (yourSendData == 0){
			CommSend();
		}
			_GameProc(0);		
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if (!_GameMode(hInstance, nCmdShow, 1280, 720, 32, false)) return FALSE;


	CommInit(NULL, NULL);
	//�׷��� �ʱ�ȭ
	ResourceImage[0] = DDLoadBitmap(DirectOBJ, "DATA//end1.BMP", 0, 0, SYSTEM);	
	ResourceImage[1] = DDLoadBitmap(DirectOBJ, "DATA//win.BMP", 0, 0, SYSTEM);	
	ResourceImage[2] = DDLoadBitmap(DirectOBJ, "DATA//Choice.BMP", 0, 0, SYSTEM);	
	ResourceImage[3] = DDLoadBitmap(DirectOBJ, "DATA//Money.BMP", 0, 0,SYSTEM);
	ResourceImage[4] = DDLoadBitmap(DirectOBJ, "DATA//Sonmogazi.BMP", 0, 0, SYSTEM);	
	ResourceImage[5] = DDLoadBitmap(DirectOBJ, "DATA//Button.BMP", 0, 0, SYSTEM);	
	ResourceImage[6] = DDLoadBitmap(DirectOBJ, "DATA//ZokBo.BMP", 0, 0, SYSTEM);
	ResourceImage[7] = DDLoadBitmap(DirectOBJ, "DATA//Texts.BMP", 0, 0, SYSTEM);
	ResourceImage[8] = DDLoadBitmap(DirectOBJ, "DATA//Stop.BMP", 0, 0, SYSTEM);
	ResourceImage[9] = DDLoadBitmap(DirectOBJ, "DATA//Back.BMP", 0, 0, SYSTEM);
	ResourceImage[10] = DDLoadBitmap(DirectOBJ, "DATA//main.bmp", 0, 0, SYSTEM);
	DDSetColorKey(ResourceImage[0], BLACK);
	DDSetColorKey(ResourceImage[1], BLACK);
	DDSetColorKey(ResourceImage[2], BLACK);
	DDSetColorKey(ResourceImage[3], BLACK);
	DDSetColorKey(ResourceImage[4], BLACK);
	DDSetColorKey(ResourceImage[5], BLACK);
	DDSetColorKey(ResourceImage[6], BLACK);
	DDSetColorKey(ResourceImage[7], BLACK);
	DDSetColorKey(ResourceImage[8], BLACK);
	DDSetColorKey(ResourceImage[9], BLACK);
	DDSetColorKey(ResourceImage[10], BLACK);

	//���� �ʱ�ȭ
	if (SoundCard)
	{
		
		Sound[0] = SndObjCreate(SoundOBJ, "Sound//OST.WAV", 1);
	    Sound[1] = SndObjCreate(SoundOBJ, "Sound//���廩��.WAV", 1);
		Sound[2] = SndObjCreate(SoundOBJ, "Sound//Select3.WAV", 1);
		//Sound[3] = SndObjCreate(SoundOBJ, "Sound//Check.WAV", 1);
		//Sound[4] = SndObjCreate(SoundOBJ, "Sound//Start.WAV", 1);
		//3,4�� ����� �ȵ�. ������ ��..
	}
	turn = 0;
	randomize(); 
	Pae();
	CommSend();
	PlaySound("Sound//OST.WAV", NULL, SND_ASYNC);
		SetTimer(MainHwnd, 1, 10, NULL);

	// Main message loop
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyWindow(MainHwnd);

	return TRUE;
}

