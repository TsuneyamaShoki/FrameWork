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


//! MainWindow�𐶐�����
DrBool DrWindow:: CreateMainWindow(HINSTANCE hIns, DrInt cmd, DrInt2 sz )
{
	WNDCLASSEX wc;

	//�E�B���h�E�̏����ݒ�
	wc.cbSize = sizeof(WNDCLASSEX);                   //�E�B���h�E�̃T�C�Y��ݒ�i�������j
	wc.style = m_windowStyle;                           //�E�B���h�E�̃X�^�C����ݒ�
	wc.hInstance = hIns;                                //�A�v���P�[�V�����̃C���X�^���X��o�^
	wc.lpszClassName = "DrFrameworkMainWindow";         //���O��ݒ�
	wc.lpfnWndProc = m_windowProc;                      //�v���V�[�W���̓o�^
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);      //�A�C�R����ݒ�
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        //�J�[�\����ݒ�
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  //BG�J���[�̐ݒ�
	wc.lpszMenuName = NULL;                             //���j���[�̖��O��ݒ�
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
		return DR_FALSE;

	if (sz.x <= 0 || sz.y <= 0)
		sz = m_mainWindowSize;

	//�E�B���h�E���쐬
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

//! �E�B���h�E�̖��O��ݒ�(���̃��\�b�h��Create����O��Call����K�v������܂��B)
void DrWindow::SetWindowTitle(DrString name)
{
	m_windowName = name;
}

//! �E�B���h�E�v���V�[�W����ݒ�(���̃��\�b�h��Create����O��Call����K�v������܂��B)
void DrWindow::SetProc(WNDPROC proc)
{
	if (!m_isInstialize)
		m_windowProc = proc;
}

//! MainWindowHandle���擾
HWND DrWindow::GetMainHWND()
{
	return m_mainWindowHandle;
}

//! �E�B���h�E�T�C�Y���擾
DrInt2 DrWindow::GetWindowSize()
{
	RECT rect;
	GetWindowRect(m_mainWindowHandle, &rect);
	return DrInt2(rect.right - rect.left, rect.bottom - rect.top);
}

//! �A�X�y�N�g��擾
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

//! ���
DrWindow::~DrWindow()
{

}