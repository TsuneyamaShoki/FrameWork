
#include <Windows.h>
#include "DrTypeArray.h"
class DrWindow
{
#pragma region //private:
private:
	static HWND m_mainWindowHandle;
	static DrBool m_isInstialize;

	static DrInt2 m_mainWindowSize;
	static WNDPROC m_windowProc;
	static DrUint m_windowStyle;
	static DrString m_windowName;

	#pragma endregion:
protected:
public:

	//! MainWindowを生成する
	//  hIns        アプリケーションを起動した際のインスタンスデータ
	//  cmd         アプリケーションを起動した際のコマンドラインデータ
	//  windowSz    アプリケーションウィンドウのサイズ(指定しない場合はデフォルト)
	static DrBool CreateMainWindow(HINSTANCE hIns, DrInt cmd, DrInt2 windowSz = DrInt2());
	
	//! ウィンドウの名前を設定(このメソッドはCreateする前にCallする必要があります。)
	static void SetWindowTitle(DrString name);

	//! ウィンドウプロシージャを設定(このメソッドはCreateする前にCallする必要があります。)
	static void SetProc(WNDPROC proc);

	//! MainWindowHandleを取得
	static HWND GetMainHWND();

	//! ウィンドウサイズを取得
	static DrInt2 GetWindowSize();

	//! アスペクト比取得
	static DrF32 GetAspect();

	virtual ~DrWindow();
};
