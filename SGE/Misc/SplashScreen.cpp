//====================================================================================================
// Filename:	SplashScreen.cpp
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Misc/SplashScreen.h"

//====================================================================================================
// Message Router
//====================================================================================================

static LRESULT CALLBACK MessageRouter(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	static SplashScreen* s_pSplashInstance = nullptr;
	if (WM_CREATE == uMessage)
	{
		s_pSplashInstance = (SplashScreen*)((LPCREATESTRUCT)lParam)->lpCreateParams;
	}

	// Check if we have captured the splash window instance
	if (nullptr != s_pSplashInstance)
	{
		// Route message to the splash window
		return s_pSplashInstance->SplashWindowProc(hWindow, uMessage, wParam, lParam);
	}
	else
	{
		// Pass on to the default message handler
		return DefWindowProcA(hWindow, uMessage, wParam, lParam);
	}
}

//====================================================================================================
// Class Definitions
//====================================================================================================

SplashScreen::SplashScreen() :
	mSplashWindow(0),
	mBitmap(0),
	mWinWidth(0),
	mWinHeight(0)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SplashScreen::~SplashScreen()
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void SplashScreen::Initialize(const char* pFilename)
{
	// Create a splash window class
	WNDCLASSEXA wc;

	// Fill the window class structure
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= NULL;
	wc.lpfnWndProc		= MessageRouter;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= GetModuleHandle(nullptr);
	wc.hIcon			= nullptr;
	wc.hCursor			= LoadCursor(nullptr, IDC_WAIT);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName		= nullptr;
	wc.lpszClassName	= "Splash";
	wc.hIconSm			= nullptr;

	// Register the splash window class
	RegisterClassExA(&wc);

	// Load the bitmap
	mBitmap = (HBITMAP)LoadImageA(0, pFilename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// Get the bitmap size
	BITMAP bmp;
	GetObject(mBitmap, sizeof(BITMAP), &bmp);
	mWinWidth = bmp.bmWidth;
	mWinHeight = bmp.bmHeight;

	// Get screen resolution
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Set splash window position to the center of the screen
	int iPosX = (iScreenWidth - mWinWidth) / 2;
	int iPosY = (iScreenHeight - mWinHeight) / 2;

	// Create a new splash window
	mSplashWindow = CreateWindowExA
	(
		WS_EX_TOPMOST,			  // Extended style
		"Splash",				   // Class Definitions name (we are using a system class here)
		"Splash",				   // Window name
		WS_POPUP,				   // Style
		iPosX, iPosY,			   // Position
		mWinWidth, mWinHeight,	// Dimensions
		nullptr,					   // Handle to parent window
		nullptr,					   // Handle to menu
		nullptr,					   // Handle to instance
		this						// Passing "this" so we can receive messages later
	);
}

//----------------------------------------------------------------------------------------------------

void SplashScreen::Terminate()
{
	// Release the bitmap
	if (0 != mBitmap)
	{
		DeleteObject(mBitmap);
		mBitmap = nullptr;
	}

	// Destroy the window
	DestroyWindow(mSplashWindow);

	// Unregister class
	UnregisterClassA("Splash", GetModuleHandle(nullptr));
}

//----------------------------------------------------------------------------------------------------

void SplashScreen::Show(int iMilliSeconds)
{
	// Show the splash screen
	UpdateWindow(mSplashWindow);
	ShowWindow(mSplashWindow, SW_SHOWNORMAL);

	// Record the start time
	int iStartTime = timeGetTime();

	MSG msg;
	memset(&msg, 0, sizeof(MSG));

	// Start the message loop
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Check if we are given a time duration
			if (0 != iMilliSeconds)
			{
				// Check if time is up
				int iCurrentTime = timeGetTime();
				if (iCurrentTime> iStartTime + iMilliSeconds)
				{
					Hide();
					break;
				}
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------

void SplashScreen::Hide()
{
	// Hide the splash screen
	ShowWindow(mSplashWindow, SW_HIDE);
}

//----------------------------------------------------------------------------------------------------

LRESULT CALLBACK SplashScreen::SplashWindowProc(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_PAINT:
		{
			// Repaint the window
			OnPaint();
			return 0;
		}
	}

	// Pass on to the default message handler
	return DefWindowProcA(hWindow, uMessage, wParam, lParam);
}

//----------------------------------------------------------------------------------------------------

void SplashScreen::OnPaint()
{
	// Check if we have a bitmap loaded
	if (0 == mBitmap)
	{
		return;
	}

	// Repaint the window
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(mSplashWindow, &ps);
	HDC hMemDC = CreateCompatibleDC(hDC);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, mBitmap);
	BitBlt(hDC, 0, 0, mWinWidth, mWinHeight, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);

	// Done painting
	EndPaint(mSplashWindow, &ps);
}