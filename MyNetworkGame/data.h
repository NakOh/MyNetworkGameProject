#define PRC MSG msg; if ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) ){if ( !GetMessage(&msg, NULL, 0, 0) ) return msg.wParam;TranslateMessage( &msg );DispatchMessage( &msg );}else if(Act)
#define SCENE SetRect(&BackRect, 0, 0, 800, 600); _DrawBmp(BackRect, 0, 0, BmpScreen[0], DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT)
#define SetR(lprc, left, top, right, bottom) SetRect(lprc, left, top, left+right, top+bottom);

BOOL ReplayFlag, Quit = false, key, key2, Act = true;
extern HSNDOBJ Sound[];
RECT BackRect;




void _Play(int num)
{
	if (SoundCard) SndObjPlay(Sound[num], NULL);
}

int Click()
{
	bool loop = true;
	key = true;
	while (loop)
	{
		PRC
		if (LeftButton || _GetKeyState(VK_RETURN) || _GetKeyState(VK_SPACE))
		{
			if (!key)
			{
				key = true;
				loop = false;
			}
		}
		else key = false;
	}
	return 0;
}

void Change(int to)
{
	//√ ±‚»≠
	int i;
	if (to == 99)
	{
		for (i = 1; i <= 100; i++)
		{
			_DrawBar(400 - i * 4, 300 - i * 3, 400 + i * 4, 300 + i * 3, BLACK);
			_CopyScreen(false);
		}
	}
	else
	{
		char* fname[] = { "DATA//main.bmp", "DATA//end1.bmp", "DATA//end2.bmp" };
		ResourceImage[10] = DDLoadBitmap(DirectOBJ, fname[to], 0, 0, SYSTEM);
		SetRect(&BackRect, 0, 0, 1280, 720);
		_DrawBmp(BackRect, 0, 0, ResourceImage[10], DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);
		_CopyScreen(false);
		
	}
}