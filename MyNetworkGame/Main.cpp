#include <windows.h>
#include <time.h>
#include <windowsx.h>
#include <math.h>
#include <ddraw.h>
#include <dsound.h>
#include <stdio.h>


#include "dsutil.h"
#include "ddutil.h"

long FAR PASCAL WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND MainHwnd;

LPDIRECTDRAW         DirectOBJ;
LPDIRECTDRAWSURFACE  RealScreen;
LPDIRECTDRAWSURFACE  BackScreen;
LPDIRECTDRAWCLIPPER	 ClipScreen;

LPDIRECTDRAWSURFACE  StopImage;
LPDIRECTDRAWSURFACE  ResourceImage[10];
LPDIRECTDRAWSURFACE  BackImage;

LPDIRECTSOUND       SoundOBJ = NULL;
LPDIRECTSOUNDBUFFER SoundDSB = NULL;
DSBUFFERDESC        DSB_desc;
HSNDOBJ Sound[10];

int MouseX, MouseY;
bool Click = false;

//void CommInit(int argc, char **argv);
//void CommSend();
//////////////////////////////////////////////////////////////////////////////////


BOOL _InitDirectSound(void)
{
	if (DirectSoundCreate(NULL, &SoundOBJ, NULL) == DS_OK)
	{
		if (SoundOBJ->SetCooperativeLevel(MainHwnd, DSSCL_PRIORITY) != DS_OK) return FALSE;

		memset(&DSB_desc, 0, sizeof(DSBUFFERDESC));
		DSB_desc.dwSize = sizeof(DSBUFFERDESC);
		DSB_desc.dwFlags = DSBCAPS_PRIMARYBUFFER;

		if (SoundOBJ->CreateSoundBuffer(&DSB_desc, &SoundDSB, NULL) != DS_OK) return FALSE;
		SoundDSB->SetVolume(0);
		SoundDSB->SetPan(0);
		return TRUE;
	}
	return FALSE;
}


BOOL Fail(HWND hwnd, char *Output)
{
	ShowWindow(hwnd, SW_HIDE);
	MessageBox(hwnd, Output, "Game Programming", MB_OK);
	DestroyWindow(hwnd);
	return FALSE;
}

void _ReleaseAll(void)
{
	if (DirectOBJ != NULL)
	{

		if (BackScreen != NULL)
		{
			BackScreen->Release();
			BackScreen = NULL;
		}
		if (RealScreen != NULL)
		{
			RealScreen->Release();
			RealScreen = NULL;
		}
		if (StopImage != NULL)
		{
			StopImage->Release();
			StopImage = NULL;
		}
		for (int i = 0; i < 5; i++)
		{
		if (ResourceImage[i] != NULL)
			{
				ResourceImage[i]->Release();
				ResourceImage[i] = NULL;
			}
		}

		DirectOBJ->Release();
		DirectOBJ = NULL;
	}
}


BOOL _GameMode(HINSTANCE hInstance, int nCmdShow, DWORD  x, DWORD  y, DWORD  bpp, int FullScreen)
{
	WNDCLASS wc;
	DDSURFACEDESC ddsd;
	DDSCAPS ddscaps;
	LPDIRECTDRAW pdd;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "GameProg";
	RegisterClass(&wc);

	if (FullScreen){
		MainHwnd = CreateWindowEx(
			0, "GameProg", NULL, WS_POPUP, 0, 0,
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			NULL, NULL, hInstance, NULL);
	}
	else{
		MainHwnd = CreateWindow("GameProg", "WindowMode",
			WS_OVERLAPPEDWINDOW, 0, 0, x, y, NULL, NULL, hInstance, NULL);
	}
	if (!MainHwnd) return FALSE;


	// 다이렉트 드로우(DD) 생성
	if (FAILED(DirectDrawCreate(NULL, &pdd, NULL)))
		return Fail(MainHwnd, "DirectDrawCreate");
	// DD에 연결
	if (FAILED(pdd->QueryInterface(IID_IDirectDraw, (LPVOID *)&DirectOBJ)))
		return Fail(MainHwnd, "QueryInterface");

	// 윈도우 핸들의 협력 단계를 설정한다.
	if (FullScreen){
		if (FAILED(DirectOBJ->SetCooperativeLevel(MainHwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN)))
			return Fail(MainHwnd, "SetCooperativeLevel");
		// Set full screen display mode
		if (FAILED(DirectOBJ->SetDisplayMode(x, y, bpp)))
			return Fail(MainHwnd, "SetDisplayMode");

		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount = 1;
		if (FAILED(DirectOBJ->CreateSurface(&ddsd, &RealScreen, NULL)))
			return Fail(MainHwnd, "CreateSurface");

		memset(&ddscaps, 0, sizeof(ddscaps));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		if (FAILED(RealScreen->GetAttachedSurface(&ddscaps, &BackScreen)))
			return Fail(MainHwnd, "GetAttachedSurface");
	}
	else{
		if (FAILED(DirectOBJ->SetCooperativeLevel(MainHwnd, DDSCL_NORMAL)))
			return Fail(MainHwnd, "SetCooperativeLevel");

		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		ddsd.dwBackBufferCount = 0;
		if (FAILED(DirectOBJ->CreateSurface(&ddsd, &RealScreen, NULL)))
			return Fail(MainHwnd, "CreateSurface");

		memset(&ddsd, 0, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		ddsd.dwWidth = x;
		ddsd.dwHeight = y;
		if (FAILED(DirectOBJ->CreateSurface(&ddsd, &BackScreen, NULL)))
			return Fail(MainHwnd, "CreateSurface");

		if (FAILED(DirectOBJ->CreateClipper(0, &ClipScreen, NULL)))
			return Fail(MainHwnd, "CreateClipper");

		if (FAILED(ClipScreen->SetHWnd(0, MainHwnd)))
			return Fail(MainHwnd, "SetHWnd");

		if (FAILED(RealScreen->SetClipper(ClipScreen)))
			return Fail(MainHwnd, "SetClipper");

		SetWindowPos(MainHwnd, NULL, 0, 0, x, y, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	SetFocus(MainHwnd);
	ShowWindow(MainHwnd, nCmdShow);
	UpdateWindow(MainHwnd);
	ShowCursor(TRUE);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// Implmentation Here




void _GameProc(int FullScreen)
{
	RECT	BackRect = { 0, 0, 1280, 720 };
	RECT    ZokBoSize = { 0, 30, 1280, 700 };
	RECT    myGoStopSize, otherGoStopSize;
	RECT    ButtonRect, goStop[20], ZokBo;


	srand(120);
	// BackGround
	BackScreen->BltFast(0, 0, BackImage, &BackRect, NULL);

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
	BackScreen->Blt(&myGoStopSize, StopImage, &goStop[rand() % 20], DDBLT_WAIT | DDBLT_KEYSRC, NULL);

	//Random으로 한 장 뽑기! 상대 패!

	otherGoStopSize.left = 500;
	otherGoStopSize.right = otherGoStopSize.left + 80;
	otherGoStopSize.top = 500;
	otherGoStopSize.bottom = otherGoStopSize.top + 100;
	BackScreen->Blt(&otherGoStopSize, StopImage, &goStop[rand() % 20], DDBLT_WAIT | DDBLT_KEYSRC, NULL);


	//Nothing Button
	ButtonRect.left = 0;
	ButtonRect.top = 0;
	ButtonRect.right = 154;
	ButtonRect.bottom = 80;
	BackScreen->BltFast(1000, 300, ResourceImage[5], &ButtonRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//밑장 빼기 Button
	ButtonRect.left = 0;
	ButtonRect.top = 94;
	ButtonRect.right = 154;
	ButtonRect.bottom = 174;
	BackScreen->BltFast(1000, 400, ResourceImage[5], &ButtonRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//손 모가지 잡기 Button
	ButtonRect.left = 0;
	ButtonRect.top = 187;
	ButtonRect.right = 154;
	ButtonRect.bottom = 267;
	BackScreen->BltFast(1000, 500, ResourceImage[5], &ButtonRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//~번째 경기
	ButtonRect.left = 180;
	ButtonRect.top = 0;
	ButtonRect.right = 318;
	ButtonRect.bottom = 40;
	BackScreen->BltFast(100, 100, ResourceImage[5], &ButtonRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//족보 보기
	ButtonRect.left = 318;
	ButtonRect.top = 0;
	ButtonRect.right = 441;
	ButtonRect.bottom = 40;
	BackScreen->BltFast(600, 100, ResourceImage[5], &ButtonRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//내 금액 및 상대 금액
	ButtonRect.left = 441;
	ButtonRect.top = 0;
	ButtonRect.right = 633;
	ButtonRect.bottom = 69;
	BackScreen->BltFast(1000, 100, ResourceImage[5], &ButtonRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//내 패 
	ButtonRect.left = 180;
	ButtonRect.top = 40;
	ButtonRect.right = 255;
	ButtonRect.bottom = 80;
	BackScreen->BltFast(50, 400, ResourceImage[5], &ButtonRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	//상대 패
	ButtonRect.left = 180;
	ButtonRect.top = 80;
	ButtonRect.right = 304;
	ButtonRect.bottom = 117;
	BackScreen->BltFast(500, 400, ResourceImage[5], &ButtonRect, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);


	if (Click == true){
		ZokBo.left = 0;
		ZokBo.right = 857;
		ZokBo.top = 0;
		ZokBo.bottom = 960;
		BackScreen->Blt(&ZokBoSize, ResourceImage[6], &ZokBo, DDBLT_WAIT, NULL);
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

long FAR PASCAL WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		MouseX = LOWORD(lParam);
		MouseY = HIWORD(lParam);
		break;

	case WM_LBUTTONDOWN:
		if (Click == false){
			if (600 <= MouseX <= 723 && 70 <= MouseY <= 110)
			{
				Click = true;
			}
		}
		else{
			Click = false;
		}
		break;

	case WM_DESTROY:
		_ReleaseAll();
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		//	CommSend();
			_GameProc(0);
		
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		case VK_F12:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;


		case VK_LEFT:
			
			return 0;

		case VK_RIGHT:
			return 0;

		case VK_UP:
			return 0;

		case VK_DOWN:
			return 0;


		case VK_SPACE:
			break;

		case VK_CONTROL:
			break;
		}
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if (!_GameMode(hInstance, nCmdShow, 1280, 720, 32, 0)) return FALSE;

	//CommInit(NULL, NULL);

	
	StopImage = DDLoadBitmap(DirectOBJ, "Stop.BMP", 0, 0);
	DDSetColorKey(StopImage, RGB(0, 0, 0));

	ResourceImage[0] = DDLoadBitmap(DirectOBJ, "First.BMP", 0, 0);
	DDSetColorKey(ResourceImage[0], RGB(0, 0, 0));

	ResourceImage[1] = DDLoadBitmap(DirectOBJ, "Ending.BMP", 0, 0);
	DDSetColorKey(ResourceImage[1], RGB(0, 0, 0));

	ResourceImage[2] = DDLoadBitmap(DirectOBJ, "Horror.BMP", 0, 0);
	DDSetColorKey(ResourceImage[2], RGB(0, 0, 0));

	ResourceImage[3] = DDLoadBitmap(DirectOBJ, "Setting.BMP", 0, 0);
	DDSetColorKey(ResourceImage[3], RGB(0, 0, 0));

	ResourceImage[4] = DDLoadBitmap(DirectOBJ, "Sonmogazi.BMP", 0, 0);
	DDSetColorKey(ResourceImage[4], RGB(0, 0, 0));

	ResourceImage[5] = DDLoadBitmap(DirectOBJ, "Button.BMP", 0, 0);
	DDSetColorKey(ResourceImage[5], RGB(0, 0, 0));

	ResourceImage[6] = DDLoadBitmap(DirectOBJ, "ZokBo.BMP", 0, 0);
	DDSetColorKey(ResourceImage[6], RGB(0, 0, 0));
	
	BackImage = DDLoadBitmap(DirectOBJ, "Back.BMP", 0, 0);
	DDSetColorKey(BackImage, RGB(0, 0, 0));

	if (_InitDirectSound())
	{
		Sound[0] = SndObjCreate(SoundOBJ, "OST.mp3", 1);
		Sound[1] = SndObjCreate(SoundOBJ, "Select2.mp3", 1);
		Sound[2] = SndObjCreate(SoundOBJ, "Select3.mp3", 1);
	}

	SetTimer(MainHwnd, 1, 10, NULL);


	// Main message loop
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	DestroyWindow(MainHwnd);

	return TRUE;
}


