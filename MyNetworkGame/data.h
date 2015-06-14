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
