

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
	// 最初に一致するファイルを取得
	HANDLE hFile = ::FindFirstFile((m_directory + "*").c_str(), &tFindFileData);

	if (INVALID_HANDLE_VALUE == hFile) {
		return fileList;
	}
	do {

		DrString filename = tFindFileData.cFileName;

		//! 自身を参照すると無限ループになるので回避
		if (filename == "." || filename == "..")
			continue;

		// フォルダかどうかを判定
		if (tFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//サブフォルダの検索
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

			// 拡張子が設定されていない場合は全てのファイルを格納
			if (m_extensions.empty())
				fileList.push_back(m_directory + filename);
			else
			{
				//拡張子が設定されている場合は指定の拡張子のファイルならリストに追加
				for each (auto var in m_extensions)
				if (var == extention)
				{
					fileList.push_back(m_directory + filename);
					break;
				}
			}
		}

		// 次に一致するファイルの検索
	} while (::FindNextFile(hFile, &tFindFileData));

	// 検索ハンドルを閉じる
	::FindClose(hFile);
	return fileList;
}

#pragma endregion

#pragma region //! Function
//! ファイルパスからファイル名だけを取得
DrString PassToFileName(DrString str)
{
	auto index = str.rfind("/");

	if (index == DrString::npos)
		index = str.rfind("\\");

	if (index == DrString::npos)
		return str;

	return str.substr(index + 1, str.size() - 1);
}

//! 拡張子の取得
DrString FileToExtension(DrString str)
{
	auto index = str.rfind('.');
	if (index == DrString::npos)
		return "";
	return str.substr(str.rfind('.'), str.size() - 1);
}

//! フルパスの取得
DrString LocalToFullPath(DrString localPath)
{
	char szFullPath[MAX_PATH] = { '\0' };
	char *szFilePart;

	GetFullPathName(
		localPath.c_str(), /* ファイル名を相対パスで指定 */
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

//! 文字列をハッシュ値に変換
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