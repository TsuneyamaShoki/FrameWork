
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

	//! MainWindow�𐶐�����
	//  hIns        �A�v���P�[�V�������N�������ۂ̃C���X�^���X�f�[�^
	//  cmd         �A�v���P�[�V�������N�������ۂ̃R�}���h���C���f�[�^
	//  windowSz    �A�v���P�[�V�����E�B���h�E�̃T�C�Y(�w�肵�Ȃ��ꍇ�̓f�t�H���g)
	static DrBool CreateMainWindow(HINSTANCE hIns, DrInt cmd, DrInt2 windowSz = DrInt2());
	
	//! �E�B���h�E�̖��O��ݒ�(���̃��\�b�h��Create����O��Call����K�v������܂��B)
	static void SetWindowTitle(DrString name);

	//! �E�B���h�E�v���V�[�W����ݒ�(���̃��\�b�h��Create����O��Call����K�v������܂��B)
	static void SetProc(WNDPROC proc);

	//! MainWindowHandle���擾
	static HWND GetMainHWND();

	//! �E�B���h�E�T�C�Y���擾
	static DrInt2 GetWindowSize();

	//! �A�X�y�N�g��擾
	static DrF32 GetAspect();

	virtual ~DrWindow();
};
