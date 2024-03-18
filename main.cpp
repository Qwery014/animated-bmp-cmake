#include "afxwin.h"
#include <fstream>
#include "CMyWindow.h"

#define WM_MY_TIMER (WM_USER + 1)

void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR evnt, DWORD time)
{
	::PostThreadMessage(AfxGetThread()->m_nThreadID, WM_MY_TIMER, 0, 0);
}

int bitmapCounter = 0;
int bitmapCounter1 = 0;
int bitmapCounter2 = 0;

class CMyApp : public CWinApp
{
	CMyWindow* window;

	virtual BOOL InitInstance() override
	{
		window = new CMyWindow();
		m_pMainWnd = window;
		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();

		m_pMainWnd->SetTimer(NULL, 50, &TimerProc);

		return TRUE;
	}

	

	afx_msg void OnMyTimer(WPARAM wParam, LPARAM lParam)
	{
		bitmapCounter = (bitmapCounter + 1) % ((LoadFileConfigVar.rows - 1) * LoadFileConfigVar.columns + LoadFileConfigVar.lastRow);
		window->imageStatic.SetBitmap(window->bitmap[bitmapCounter]);

		bitmapCounter1 = (bitmapCounter1 + 1) % ((LoadFileConfigVar1.rows - 1) * LoadFileConfigVar1.columns + LoadFileConfigVar1.lastRow);
		window->imageStatic1.SetBitmap(window->bitmap1[bitmapCounter1]);

		bitmapCounter2 = (bitmapCounter2 + 1) % ((LoadFileConfigVar2.rows - 1) * LoadFileConfigVar2.columns + LoadFileConfigVar2.lastRow);
		window->imageStatic2.SetBitmap(window->bitmap2[bitmapCounter2]);
	}

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_THREAD_MESSAGE(WM_MY_TIMER, &CMyApp::OnMyTimer)
END_MESSAGE_MAP()

CMyApp myApplication;
