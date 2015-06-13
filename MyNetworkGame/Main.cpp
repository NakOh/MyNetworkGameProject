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
bool gam = false;
BOOL LeftButton, RightButton;
bool ZokBoClick = false;
bool NothingClick = false;
bool ZzangClick = false;
bool SonmogaziClick = false;
int myFirstPae, mySecondPae;
int yourFirstPae, yourSecondPae;
int myResult;
int yourResult;
bool result;
MSG msg;

//void CommInit(int argc, char **argv);
//void CommSend();
//////////////////////////////////////////////////////////////////////////////////
void _GameProc(int FullScreen)
{


	RECT	BackRect = { 0, 0, 1280, 720 };
	RECT    ZokBoSize = { 0, 30, 1280, 700 };
	RECT	ImageSize = { 700, 200, 1000, 600 };
	RECT    myGoStopSize, otherGoStopSize;
	RECT    ButtonRect, goStop[20], ZokBo, Nothing, Sonmogazi;

	// BackGround
	BackScreen->BltFast(0, 0, ResourceImage[9], &BackRect, NULL);

	// 10월 단풍 사슴
	goStop[0].left = 5;
	goStop[0].top = 5;
	goStop[0].right = 50;
	goStop[0].bottom = 75;

	// 10월 단풍 청단
	goStop[1].left = 50;
	goStop[1].top = 5;
	goStop[1].right = 95;
	goStop[1].bottom = 75;

	// 9월 국화 쌍피
	goStop[2].left = 117;
	goStop[2].top = 5;
	goStop[2].right = 162;
	goStop[2].bottom = 75;

	//9월 국화 청단
	goStop[3].left = 162;
	goStop[3].top = 5;
	goStop[3].right = 207;
	goStop[3].bottom = 75;

	//8월 공산 광
	goStop[4].left = 230;
	goStop[4].top = 5;
	goStop[4].right = 275;
	goStop[4].bottom = 75;

	//8월 공산 새
	goStop[5].left = 275;
	goStop[5].top = 5;
	goStop[5].right = 320;
	goStop[5].bottom = 75;

	//7월 홍싸리 멧돼지
	goStop[6].left = 343;
	goStop[6].top = 5;
	goStop[6].right = 388;
	goStop[6].bottom = 75;

	//7월 홍싸리 초단
	goStop[7].left = 388;
	goStop[7].top = 5;
	goStop[7].right = 433;
	goStop[7].bottom = 75;

	//6월 모란 나비
	goStop[8].left = 5;
	goStop[8].top = 90;
	goStop[8].right = 50;
	goStop[8].bottom = 160;

	//6월 모란 청단
	goStop[9].left = 50;
	goStop[9].top = 90;
	goStop[9].right = 95;
	goStop[9].bottom = 160;

	//5월 난초 그림
	goStop[10].left = 117;
	goStop[10].top = 90;
	goStop[10].right = 162;
	goStop[10].bottom = 160;

	//5월 난초 초단
	goStop[11].left = 164;
	goStop[11].top = 90;
	goStop[11].right = 207;
	goStop[11].bottom = 160;

	//4월 흑싸리 새
	goStop[12].left = 230;
	goStop[12].top = 90;
	goStop[12].right = 274;
	goStop[12].bottom = 160;

	//4월 흑싸리 초단
	goStop[13].left = 276;
	goStop[13].top = 90;
	goStop[13].right = 319;
	goStop[13].bottom = 160;

	//3월 벚꽃 광
	goStop[14].left = 342;
	goStop[14].top = 90;
	goStop[14].right = 385;
	goStop[14].bottom = 160;

	//3월 벚꽃 홍단
	goStop[15].left = 388;
	goStop[15].top = 90;
	goStop[15].right = 431;
	goStop[15].bottom = 160;

	//2월 매화 새
	goStop[16].left = 6;
	goStop[16].top = 176;
	goStop[16].right = 49;
	goStop[16].bottom = 242;

	//2월 매화 홍단
	goStop[17].left = 52;
	goStop[17].top = 176;
	goStop[17].right = 95;
	goStop[17].bottom = 242;

	//1월 소나무 광
	goStop[18].left = 119;
	goStop[18].top = 176;
	goStop[18].right = 161;
	goStop[18].bottom = 242;

	//1월 소나무 홍단
	goStop[19].left = 164;
	goStop[19].top = 176;
	goStop[19].right = 207;
	goStop[19].bottom = 242;


	//Random으로 한 장 뽑기!  사실 순서는 이미 srand에서 다 정해짐! 내 패!
	myGoStopSize.left = 50;
	myGoStopSize.right = myGoStopSize.left + 80;
	myGoStopSize.top = 500;
	myGoStopSize.bottom = myGoStopSize.top + 100;
	BackScreen->Blt(&myGoStopSize, ResourceImage[8], &goStop[myFirstPae], DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	//Random으로 한 장 뽑기! 상대 패!
	otherGoStopSize.left = 500;
	otherGoStopSize.right = otherGoStopSize.left + 80;
	otherGoStopSize.top = 500;
	otherGoStopSize.bottom = otherGoStopSize.top + 100;
	BackScreen->Blt(&otherGoStopSize, ResourceImage[8], &goStop[yourFirstPae], DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	//버튼이 클릭되면 두번째 패를 분배
	if (NothingClick==true || SonmogaziClick == true || ZzangClick == true){
		mySecondPae = random();
		while (mySecondPae == myFirstPae || mySecondPae == yourFirstPae){			
				mySecondPae = random();		
		}
		yourSecondPae = random();
		while (yourSecondPae == myFirstPae || yourSecondPae == yourFirstPae || yourSecondPae == mySecondPae){
			yourSecondPae = random();
		}
		CheckResult(myFirstPae,mySecondPae);
	}

	RECT ButtonLocation;


	//족보 보기 Button

	ButtonLocation.left = 600;
	ButtonLocation.right = 723;
	ButtonLocation.top = 70;
	ButtonLocation.bottom = 110;

	ButtonRect.left = 0;
	ButtonRect.right = 680;
	ButtonRect.top = 1;
	ButtonRect.bottom = 314;
	BackScreen->Blt(&ButtonLocation, ResourceImage[5], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	//밑장 빼기 Button

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


	//손 모가지 잡기 Button
	ButtonLocation.left = 1000;
	ButtonLocation.right = 1154;
	ButtonLocation.top = 470;
	ButtonLocation.bottom = 580;

	ButtonRect.left = 0;
	ButtonRect.top = 934;
	ButtonRect.right = 680;
	ButtonRect.bottom = 1243;
	BackScreen->Blt(&ButtonLocation, ResourceImage[5], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	
	RECT TextLocation;
	//내 패 
	TextLocation.left = 50;
	TextLocation.right = 170;
	TextLocation.top = 400;
	TextLocation.bottom = 440;

	ButtonRect.left = 0;
	ButtonRect.top = 0;
	ButtonRect.right = 730;
	ButtonRect.bottom = 360;

	BackScreen->Blt(&TextLocation, ResourceImage[7], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
	//~번째 판
	TextLocation.left = 100;
	TextLocation.right = 220;
	TextLocation.top = 100;
	TextLocation.bottom = 170;

	ButtonRect.left = 730;
	ButtonRect.top = 0;
	ButtonRect.right = 1460;
	ButtonRect.bottom = 360;
	BackScreen->Blt(&TextLocation, ResourceImage[7], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	//상대 패
	TextLocation.left = 500;
	TextLocation.right = 620;
	TextLocation.top = 400;
	TextLocation.bottom = 440;

	ButtonRect.left = 0;
	ButtonRect.top = 360;
	ButtonRect.right = 730;
	ButtonRect.bottom = 724;
	BackScreen->Blt(&TextLocation, ResourceImage[7], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	//내 금액 및 상대 금액
	TextLocation.left = 950;
	TextLocation.right = 1200;
	TextLocation.top = 100;
	TextLocation.bottom = 200;

	ButtonRect.left = 0;
	ButtonRect.top = 724;
	ButtonRect.right = 1460;
	ButtonRect.bottom = 1083;

	BackScreen->Blt(&TextLocation, ResourceImage[7], &ButtonRect, DDBLT_WAIT | DDBLT_KEYSRC, NULL);


	if (ZokBoClick == true){
		ZokBo.left = 0;
		ZokBo.right = 857;
		ZokBo.top = 0;
		ZokBo.bottom = 960;
		BackScreen->Blt(&ZokBoSize, ResourceImage[6], &ZokBo, DDBLT_WAIT, NULL);
	}
		
	if (NothingClick == true){
			Nothing.left = 0;
			Nothing.right = 800;
			Nothing.bottom = 533;
			Nothing.top = 0;
			BackScreen->Blt(&ImageSize, ResourceImage[0], &Nothing, DDBLT_WAIT, NULL);
		}

	if (SonmogaziClick == true){
			Sonmogazi.left = 0;
			Sonmogazi.right = 640;
			Sonmogazi.top = 0;
			Sonmogazi.bottom = 360;
			BackScreen->Blt(&ImageSize, ResourceImage[4], &Sonmogazi, DDBLT_WAIT, NULL);
		}

		if (ZzangClick == true){

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

//일단은 버튼 먹을 때
long FAR PASCAL WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case	WM_ACTIVATEAPP : Act = wParam;
		if (Act && gam){
			_ScreenMode(SCREEN_X, SCREEN_Y, BPP, FULL_SCREEN);
			_CopyScreen(false);
		}
	case    WM_MOUSEMOVE:   MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		break;
	case	WM_LBUTTONDOWN:	LeftButton = TRUE; 
		if (ZokBoClick == false){
			if (600 <= MouseX && MouseX <= 723 && 40 <= MouseY && MouseY <= 78)
			{
				ZokBoClick = true;
			}
		}
		else{
			ZokBoClick = false;
		}

		//아무것도 하지 않는다 버튼
		if (NothingClick == false){
			if (1000 <= MouseX && MouseX <= 1154 && 250 <= MouseY && MouseY <= 310)
			{
				NothingClick = true;
			}
		}
		else{
			NothingClick = false;
		}

		//밑 장 버튼
		if (ZzangClick == false){
			if (1000 <= MouseX && MouseX <= 1154 && 342 <= MouseY && MouseY <= 410)
			{
				ZzangClick = true;
			}
		}
		else{
			ZzangClick = false;
		}

		//손 모가지 버튼
		if (SonmogaziClick == false){
			if (1000 <= MouseX && MouseX <= 1154 && 447 <= MouseY && MouseY <= 540)
			{			
				PlaySound("Sound//밑장빼기.WAV", NULL, SND_ASYNC);
				SonmogaziClick = true;
			}
		}
		else{
			PlaySound("Sound//OST.WAV", NULL, SND_ASYNC);
			SonmogaziClick = false;

		}
		break;
	case	WM_LBUTTONUP:	
		break;
	case	WM_RBUTTONDOWN:	RightButton = TRUE;
		break;
	case	WM_RBUTTONUP:	RightButton = FALSE;
		break;

	case    WM_DESTROY:  _WindowMode();
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		//	CommSend();
			_GameProc(0);		
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if (!_GameMode(hInstance, nCmdShow, 1280, 720, 32, false)) return FALSE;
	//한글 사용 초기화
	InitXddFont("HANGUL.FNT", "ENGLISH.FNT");
	SetFontPattern(NORMAL_PATTERN);


	//CommInit(NULL, NULL);	

	//그래픽 초기화
	ResourceImage[0] = DDLoadBitmap(DirectOBJ, "DATA//First.BMP", 0, 0, SYSTEM);	
	ResourceImage[1] = DDLoadBitmap(DirectOBJ, "DATA//Ending.BMP", 0, 0, SYSTEM);	
	//ResourceImage[2] = DDLoadBitmap(DirectOBJ, "DATA//Horror.BMP", 0, 0, SYSTEM);	
	ResourceImage[3] = DDLoadBitmap(DirectOBJ, "DATA//Setting.BMP", 0, 0,SYSTEM);
	ResourceImage[4] = DDLoadBitmap(DirectOBJ, "DATA//Sonmogazi.BMP", 0, 0, SYSTEM);	
	ResourceImage[5] = DDLoadBitmap(DirectOBJ, "DATA//Button.BMP", 0, 0, SYSTEM);	
	ResourceImage[6] = DDLoadBitmap(DirectOBJ, "DATA//ZokBo.BMP", 0, 0, SYSTEM);
	ResourceImage[7] = DDLoadBitmap(DirectOBJ, "DATA//Texts.BMP", 0, 0, SYSTEM);
	ResourceImage[8] = DDLoadBitmap(DirectOBJ, "DATA//Stop.BMP", 0, 0, SYSTEM);
	ResourceImage[9] = DDLoadBitmap(DirectOBJ, "DATA//Back.BMP", 0, 0, SYSTEM);
	ResourceImage[10] = DDLoadBitmap(DirectOBJ, "DATA//main.bmp", 0, 0, SYSTEM);
	DDSetColorKey(ResourceImage[0], BLACK);
	DDSetColorKey(ResourceImage[1], BLACK);
	//DDSetColorKey(ResourceImage[2], RGB(0, 0, 0));
	DDSetColorKey(ResourceImage[3], BLACK);
	DDSetColorKey(ResourceImage[4], BLACK);
	DDSetColorKey(ResourceImage[5], BLACK);
	DDSetColorKey(ResourceImage[6], BLACK);
	DDSetColorKey(ResourceImage[7], BLACK);
	DDSetColorKey(ResourceImage[8], BLACK);
	DDSetColorKey(ResourceImage[9], BLACK);
	DDSetColorKey(ResourceImage[10], BLACK);

	//음향 초기화
	if (SoundCard)
	{
		Sound[0] = SndObjCreate(SoundOBJ, "Sound//OST.WAV", 1);
	    Sound[1] = SndObjCreate(SoundOBJ, "Sound//밑장빼기.WAV", 1);
		Sound[2] = SndObjCreate(SoundOBJ, "Sound//Select3.WAV", 1);
		//Sound[3] = SndObjCreate(SoundOBJ, "Sound//Check.WAV", 1);
		//Sound[4] = SndObjCreate(SoundOBJ, "Sound//Start.WAV", 1);
		//3,4번 재생이 안됨. 이유는 모름..
	}

	randomize();
	myFirstPae = random();
	yourFirstPae = random();
	while (myFirstPae == yourFirstPae){
		yourFirstPae = random();	
	}
	PlaySound("Sound//OST.WAV", NULL, SND_ASYNC);
	gam = true;


	SetTimer(MainHwnd, 1, 10, NULL);


	// Main message loop
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyWindow(MainHwnd);

	return TRUE;
}

