#pragma once

//! Include
#include "DrTypeArray.h"

//! DrUtility
namespace DrNUtlity
{
	//! [class] ファイルパスを解析するUtility
	class DrFilePathAnalyzer
	{
	protected:
		DrString m_filePath;		//ローカルのファイルパス
		DrString m_fullPath;		//フルパス
		DrString m_extension;		//ファイルの拡張子
		DrString m_fileName;		//ディレクトリを含まないファイルの名前
		DrString m_localDirectory;	//ファイルを含まないディレクトリ構成
		DrString m_fullDirectory;	//ファイルを含まないフルパスのディレクトリ構成
	public:
		//! コンストラクタ
		DrFilePathAnalyzer(){};
		DrFilePathAnalyzer(DrString filepass);

		//! ファイルパスを解析する
		DrBool Analize(DrString str);

		//! ファイル名を取得する
		DrString GetFilePath();

		//! ファイルのフルパスを取得する
		DrString GetFullPath();

		//! ファイルの拡張子を取得する
		DrString GetExtension();

		//! 拡張子を除いたファイル名を取得する
		DrString GetFileName();

		//! ローカルディレクトリを取得する
		DrString GetLocalDirectory();

		//! フルディレクトリを取得する
		DrString GetFullDirectory();
	};

	//! ファイルディレクトリに関するUtility
	class DrFileDirectory
	{
	protected:
		DrString m_directory;
		DrList<DrString> m_extensions;
		DrBool m_searchSubFolder;
	public:
		//! Constructor
		DrFileDirectory(DrString directory);

		//! サブフォルダを検索対象に含めるかどうかの設定
		// TRUE		含める
		// FALSE	含めない
		void SetSearchSubFolderFlag(DrBool searchSubFolder);

		//! 検索する拡張子を追加
		DrBool AddExtension(DrString& extencion);

		//! 検索する拡張子を削除
		DrBool RemoveExtension(DrString& extencion);

		//! すべてのファイルパスを取得する
		DrList<DrString> GetFileList();
	};
	
	//! ファイルパスからファイル名だけを取得
	DrString PassToFileName(DrString str);

	//! 拡張子の取得
	DrString FileToExtension(DrString str);

	//! フルパスの取得
	DrString LocalToFullPath(DrString localPath);

	DrString FileToLocalDirectory(DrString str);

	//! 文字列をハッシュ値に変換
	DR_HASH StringToHash(const DrString& str);
}