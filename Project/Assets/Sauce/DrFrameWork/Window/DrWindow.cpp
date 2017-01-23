#include "DrWindow.h"

//! Prototype
LRESULT CALLBACK DefaultWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//! Initialize
HWND DrWindow::m_mainWindowHandle = nullptr;
DrBool DrWindow::m_isInstialize =false;

DrInt2 DrWindow::m_mainWindowSize (1980 ,1024);
WNDPROC DrWindow::m_windowProc = DefaultWindowProc;
DrUint DrWindow::m_windowStyle =CS_HREDRAW | CS_VREDRAW;
DrString DrWindow::m_windowName = "DrFramework";


//! MainWindowを生成する
DrBool DrWindow:: CreateMainWindow(HINSTANCE hIns, DrInt cmd, DrInt2 sz )
{
	WNDCLASSEX wc;

	//ウィンドウの初期設定
	wc.cbSize = sizeof(WNDCLASSEX);                   //ウィンドウのサイズを設定（メモリ）
	wc.style = m_windowStyle;                           //ウィンドウのスタイルを設定
	wc.hInstance = hIns;                                //アプリケーションのインスタンスを登録
	wc.lpszClassName = "DrFrameworkMainWindow";         //名前を設定
	wc.lpfnWndProc = m_windowProc;                      //プロシージャの登録
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);      //アイコンを設定
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        //カーソルを設定
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  //BGカラーの設定
	wc.lpszMenuName = NULL;                             //メニューの名前を設定
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
		return DR_FALSE;

	if (sz.x <= 0 || sz.y <= 0)
		sz = m_mainWindowSize;

	//ウィンドウを作成
	m_mainWindowHandle = CreateWindow(
		wc.lpszClassName,
		m_windowName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		sz.x,
		sz.y,
		NULL,
		NULL,
		hIns,
		NULL);

	if (m_mainWindowHandle == nullptr)
		return DR_FALSE;

	ShowWindow(m_mainWindowHandle, cmd);
	UpdateWindow(m_mainWindowHandle);

	return DR_TRUE;
}

//! ウィンドウの名前を設定(このメソッドはCreateする前にCallする必要があります。)
void DrWindow::SetWindowTitle(DrString name)
{
	m_windowName = name;
}

//! ウィンドウプロシージャを設定(このメソッドはCreateする前にCallする必要があります。)
void DrWindow::SetProc(WNDPROC proc)
{
	if (!m_isInstialize)
		m_windowProc = proc;
}

//! MainWindowHandleを取得
HWND DrWindow::GetMainHWND()
{
	return m_mainWindowHandle;
}

//! ウィンドウサイズを取得
DrInt2 DrWindow::GetWindowSize()
{
	RECT rect;
	GetWindowRect(m_mainWindowHandle, &rect);
	return DrInt2(rect.right - rect.left, rect.bottom - rect.top);
}

//! アスペクト比取得
// !Todo
DrF32 DrWindow::GetAspect()
{
	return 0.f;
}

//! Default windowproc
LRESULT CALLBACK DefaultWindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//! 解放
DrWindow::~DrWindow()
{

}