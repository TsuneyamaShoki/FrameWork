#pragma once

//! Include
#include "DrTypeArray.h"

//! DrUtility
namespace DrNUtlity
{
	//! [class] �t�@�C���p�X����͂���Utility
	class DrFilePathAnalyzer
	{
	protected:
		DrString m_filePath;		//���[�J���̃t�@�C���p�X
		DrString m_fullPath;		//�t���p�X
		DrString m_extension;		//�t�@�C���̊g���q
		DrString m_fileName;		//�f�B���N�g�����܂܂Ȃ��t�@�C���̖��O
		DrString m_localDirectory;	//�t�@�C�����܂܂Ȃ��f�B���N�g���\��
		DrString m_fullDirectory;	//�t�@�C�����܂܂Ȃ��t���p�X�̃f�B���N�g���\��
	public:
		//! �R���X�g���N�^
		DrFilePathAnalyzer(){};
		DrFilePathAnalyzer(DrString filepass);

		//! �t�@�C���p�X����͂���
		DrBool Analize(DrString str);

		//! �t�@�C�������擾����
		DrString GetFilePath();

		//! �t�@�C���̃t���p�X���擾����
		DrString GetFullPath();

		//! �t�@�C���̊g���q���擾����
		DrString GetExtension();

		//! �g���q���������t�@�C�������擾����
		DrString GetFileName();

		//! ���[�J���f�B���N�g�����擾����
		DrString GetLocalDirectory();

		//! �t���f�B���N�g�����擾����
		DrString GetFullDirectory();
	};

	//! �t�@�C���f�B���N�g���Ɋւ���Utility
	class DrFileDirectory
	{
	protected:
		DrString m_directory;
		DrList<DrString> m_extensions;
		DrBool m_searchSubFolder;
	public:
		//! Constructor
		DrFileDirectory(DrString directory);

		//! �T�u�t�H���_�������ΏۂɊ܂߂邩�ǂ����̐ݒ�
		// TRUE		�܂߂�
		// FALSE	�܂߂Ȃ�
		void SetSearchSubFolderFlag(DrBool searchSubFolder);

		//! ��������g���q��ǉ�
		DrBool AddExtension(DrString& extencion);

		//! ��������g���q���폜
		DrBool RemoveExtension(DrString& extencion);

		//! ���ׂẴt�@�C���p�X���擾����
		DrList<DrString> GetFileList();
	};
	
	//! �t�@�C���p�X����t�@�C�����������擾
	DrString PassToFileName(DrString str);

	//! �g���q�̎擾
	DrString FileToExtension(DrString str);

	//! �t���p�X�̎擾
	DrString LocalToFullPath(DrString localPath);

	DrString FileToLocalDirectory(DrString str);

	//! ��������n�b�V���l�ɕϊ�
	DR_HASH StringToHash(const DrString& str);
}