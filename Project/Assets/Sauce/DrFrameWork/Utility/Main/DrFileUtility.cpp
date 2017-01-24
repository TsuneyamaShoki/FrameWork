

//! Include
#include <Windows.h>
#include "DrFileUtility.h"

using namespace DrNUtlity;

#pragma region //! DrFilePathAnalyzer

DrFilePathAnalyzer::DrFilePathAnalyzer(DrString filepath)
{
	Analize(filepath);
}

DrBool DrFilePathAnalyzer::Analize(DrString filepath)
{
	m_filePath = filepath;
	m_extension = FileToExtension(m_filePath);
	m_fullPath = LocalToFullPath(m_filePath);
	m_fileName = PassToFileName(m_filePath);
	m_localDirectory = FileToLocalDirectory(m_filePath);
	m_fullDirectory = LocalToFullPath(m_localDirectory);

	return DR_TRUE;
}

//! Getter
DrString DrFilePathAnalyzer::GetFilePath()
{
	return m_filePath;
}
DrString DrFilePathAnalyzer::GetFullPath()
{
	return m_fullPath;
}
DrString DrFilePathAnalyzer::GetExtension()
{
	return m_extension;
}
DrString DrFilePathAnalyzer::GetFileName()
{
	return m_fileName;
}
DrString DrFilePathAnalyzer::GetLocalDirectory()
{
	return m_localDirectory;
}
DrString DrFilePathAnalyzer::GetFullDirectory()
{
	return m_fullDirectory;
}

#pragma endregion

#pragma region //! DrFileDirectory

DrFileDirectory::DrFileDirectory(DrString directory) :
m_searchSubFolder(DR_TRUE)
{
	if (directory.empty())
		return;
	m_directory = directory;
	if (m_directory[m_directory.size() - 1] != '/' &&
		m_directory[m_directory.size() - 1] != '\\')
		m_directory += '/';
}

void DrFileDirectory::SetSearchSubFolderFlag(DrBool searchSubFolder)
{
	m_searchSubFolder = searchSubFolder;
}

DrBool DrFileDirectory::AddExtension(DrString& extencion)
{
	m_extensions.push_back(extencion);
	return DR_TRUE;
}

DrBool DrFileDirectory::RemoveExtension(DrString& extencion)
{
	m_extensions.remove(extencion);
	return DR_TRUE;
}

DrList<DrString> DrFileDirectory::GetFileList()
{
	DrList<DrString> fileList;
	WIN32_FIND_DATA tFindFileData;
	// �ŏ��Ɉ�v����t�@�C�����擾
	HANDLE hFile = ::FindFirstFile((m_directory + "*").c_str(), &tFindFileData);

	if (INVALID_HANDLE_VALUE == hFile) {
		return fileList;
	}
	do {

		DrString filename = tFindFileData.cFileName;

		//! ���g���Q�Ƃ���Ɩ������[�v�ɂȂ�̂ŉ��
		if (filename == "." || filename == "..")
			continue;

		// �t�H���_���ǂ����𔻒�
		if (tFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//�T�u�t�H���_�̌���
			if (m_searchSubFolder == DR_FALSE)
				continue;

			DrFileDirectory subfolder(m_directory + filename);
			subfolder.SetSearchSubFolderFlag(DR_TRUE);
			for each (auto var in m_extensions)
				subfolder.AddExtension(var);

			DrList<DrString>&& subFolderFiles = subfolder.GetFileList();
			for each (auto var in subFolderFiles)
				fileList.push_back(var);
		}
		else
		{
			DrString extention = FileToExtension(filename);

			// �g���q���ݒ肳��Ă��Ȃ��ꍇ�͑S�Ẵt�@�C�����i�[
			if (m_extensions.empty())
				fileList.push_back(m_directory + filename);
			else
			{
				//�g���q���ݒ肳��Ă���ꍇ�͎w��̊g���q�̃t�@�C���Ȃ烊�X�g�ɒǉ�
				for each (auto var in m_extensions)
				if (var == extention)
				{
					fileList.push_back(m_directory + filename);
					break;
				}
			}
		}

		// ���Ɉ�v����t�@�C���̌���
	} while (::FindNextFile(hFile, &tFindFileData));

	// �����n���h�������
	::FindClose(hFile);
	return fileList;
}

#pragma endregion

#pragma region //! Function
//! �t�@�C���p�X����t�@�C�����������擾
DrString PassToFileName(DrString str)
{
	auto index = str.rfind("/");

	if (index == DrString::npos)
		index = str.rfind("\\");

	if (index == DrString::npos)
		return str;

	return str.substr(index + 1, str.size() - 1);
}

//! �g���q�̎擾
DrString FileToExtension(DrString str)
{
	auto index = str.rfind('.');
	if (index == DrString::npos)
		return "";
	return str.substr(str.rfind('.'), str.size() - 1);
}

//! �t���p�X�̎擾
DrString LocalToFullPath(DrString localPath)
{
	char szFullPath[MAX_PATH] = { '\0' };
	char *szFilePart;

	GetFullPathName(
		localPath.c_str(), /* �t�@�C�����𑊑΃p�X�Ŏw�� */
		sizeof(szFullPath) / sizeof(szFullPath[0]),
		szFullPath,
		&szFilePart);

	return szFullPath;
}

DrString FileToLocalDirectory(DrString str)
{
	auto index = str.rfind("/");

	if (index == DrString::npos)
		index = str.rfind("\\");

	if (index == DrString::npos)
		return "";

	return str.substr(0, index + 1);
}

//! ��������n�b�V���l�ɕϊ�
inline DR_HASH StringToHash(const DrString& str)
{
	DR_HASH h = 0;
	const char* val = str.c_str();
	int len = str.length();

	for (int i = 0; i < len; i++) {
		h = 31 * h + val[i];
	}
	return h;
}
#pragma endregion