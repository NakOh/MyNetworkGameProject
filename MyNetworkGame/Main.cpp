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
LPDIRECTDRAWSURFACE  ResourceImage[4];
LPDIRECTDRAWSURFACE  BackImage;

LPDIRECTSOUND       SoundOBJ = NULL;
LPDIRECTSOUNDBUFFER SoundDSB = NULL;
DSBUFFERDESC        DSB_desc;
HSNDOBJ Sound[10];

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


	// ´ÙÀÌ·ºÆ® µå·Î¿ì(DD) »ý¼º
	if (FAILED(DirectDrawCreate(NULL, &pdd, NULL)))
		return Fail(MainHwnd, "DirectDrawCreate");
	// DD¿¡ ¿¬°á
	if (FAILED(pdd->QueryInterface(IID_IDirectDraw, (LPVOID *)&DirectOBJ)))
		return Fail(MainHwnd, "QueryInterface");

	// À©µµ¿ì ÇÚµéÀÇ Çù·Â ´Ü°è¸¦ ¼³Á¤ÇÑ´Ù.
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



RECT    srcRect[20];
void _GameProc(int FullScreen)
{
	RECT	BackRect = { 0, 0, 1280, 720 };
	

	// BackGround
	BackScreen->BltFast(0, 0, BackImage, &BackRect, NULL);

	// 10¿ù ´ÜÇ³ »ç½¿
	srcRect[0].left = 5;
	srcRect[0].top = 5;
	srcRect[0].right = 50;
	srcRect[0].bottom = 75;
	BackScreen->BltFast(10, 50, StopImage, &srcRect[0], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	// 10¿ù ´ÜÇ³ Ã»´Ü
	srcRect[1].left = 50;
	srcRect[1].top = 5;
	srcRect[1].right = 95;
	srcRect[1].bottom = 75;
	BackScreen->BltFast(55, 50, StopImage, &srcRect[1], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	// 9¿ù ±¹È­ ½ÖÇÇ
	srcRect[2].left = 117;
	srcRect[2].top = 5;
	srcRect[2].right = 162;
	srcRect[2].bottom = 75;
	BackScreen->BltFast(95, 50, StopImage, &srcRect[2], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//9¿ù ±¹È­ Ã»´Ü
	srcRect[3].left = 162;
	srcRect[3].top = 5;
	srcRect[3].right = 207;
	srcRect[3].bottom = 75;
	BackScreen->BltFast(145, 50, StopImage, &srcRect[3], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//8¿ù °ø»ê ±¤
	srcRect[4].left = 230;
	srcRect[4].top = 5;
	srcRect[4].right = 275;
	srcRect[4].bottom = 75;
	BackScreen->BltFast(195, 50, StopImage, &srcRect[4], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	
	//8¿ù °ø»ê »õ
	srcRect[5].left = 275;
	srcRect[5].top = 5;
	srcRect[5].right = 320;
	srcRect[5].bottom = 75;
	BackScreen->BltFast(245, 50, StopImage, &srcRect[5], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//7¿ù È«½Î¸® ¸äµÅÁö
	srcRect[6].left = 343;
	srcRect[6].top = 5;
	srcRect[6].right = 388;
	srcRect[6].bottom = 75;
	BackScreen->BltFast(295, 50, StopImage, &srcRect[6], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//7¿ù È«½Î¸® ÃÊ´Ü
	srcRect[7].left = 388;
	srcRect[7].top = 5;
	srcRect[7].right = 433;
	srcRect[7].bottom = 75;
	BackScreen->BltFast(345, 50, StopImage, &srcRect[7], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//6¿ù ¸ð¶õ ³ªºñ
	srcRect[8].left = 5;
	srcRect[8].top = 90;
	srcRect[8].right = 50;
	srcRect[8].bottom = 160;
	BackScreen->BltFast(395, 50, StopImage, &srcRect[8], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//6¿ù ¸ð¶õ Ã»´Ü
	srcRect[9].left = 50;
	srcRect[9].top = 90;
	srcRect[9].right = 95;
	srcRect[9].bottom = 160;
	BackScreen->BltFast(445, 50, StopImage, &srcRect[9], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//5¿ù ³­ÃÊ ±×¸²
	srcRect[10].left = 117;
	srcRect[10].top = 90;
	srcRect[10].right = 162;
	srcRect[10].bottom = 160;
	BackScreen->BltFast(495, 50, StopImage, &srcRect[10], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//5¿ù ³­ÃÊ ÃÊ´Ü
	srcRect[11].left = 164;
	srcRect[11].top = 90;
	srcRect[11].right =207;
	srcRect[11].bottom = 160;
	BackScreen->BltFast(545, 50, StopImage, &srcRect[11], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//4¿ù Èæ½Î¸® »õ
	srcRect[12].left = 230;
	srcRect[12].top = 90;
	srcRect[12].right = 274;
	srcRect[12].bottom = 160;
	BackScreen->BltFast(595, 50, StopImage, &srcRect[12], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//4¿ù Èæ½Î¸® ÃÊ´Ü
	srcRect[13].left = 276;
	srcRect[13].top = 90;
	srcRect[13].right = 319;
	srcRect[13].bottom = 160;
	BackScreen->BltFast(645, 50, StopImage, &srcRect[13], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//3¿ù º¢²É ±¤
	srcRect[14].left = 342;
	srcRect[14].top = 90;
	srcRect[14].right = 385;
	srcRect[14].bottom = 160;
	BackScreen->BltFast(695, 50, StopImage, &srcRect[14], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//3¿ù º¢²É È«´Ü
	srcRect[15].left = 388;
	srcRect[15].top = 90;
	srcRect[15].right = 431;
	srcRect[15].bottom = 160;
	BackScreen->BltFast(745, 50, StopImage, &srcRect[15], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//2¿ù ¸ÅÈ­ »õ
	srcRect[16].left = 6;
	srcRect[16].top = 176;
	srcRect[16].right = 49;
	srcRect[16].bottom = 242;
	BackScreen->BltFast(795, 50, StopImage, &srcRect[16], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//2¿ù ¸ÅÈ­ È«´Ü
	srcRect[17].left = 52;
	srcRect[17].top = 176;
	srcRect[17].right = 95;
	srcRect[17].bottom = 242;
	BackScreen->BltFast(845, 50, StopImage, &srcRect[17], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//1¿ù ¼Ò³ª¹« ±¤
	srcRect[18].left = 119;
	srcRect[18].top = 176;
	srcRect[18].right = 161;
	srcRect[18].bottom = 242;
	BackScreen->BltFast(895, 50, StopImage, &srcRect[18], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);

	//1¿ù ¼Ò³ª¹« È«´Ü
	srcRect[19].left = 164;
	srcRect[19].top = 176;
	srcRect[19].right = 207;
	srcRect[19].bottom = 242;
	BackScreen->BltFast(945, 50, StopImage, &srcRect[19], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);



	srand(120);
	BackScreen->BltFast(50, 200, StopImage, &srcRect[rand() % 20], DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	
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
		//MouseX = LOWORD(lParam);
		//MouseY = HIWORD(lParam);
		break;

	case WM_LBUTTONDOWN:
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


