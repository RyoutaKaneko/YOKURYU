/**
 * @file JsonLoader.cpp
 * @brief レベルエディタJsonファイル読み込みクラス
 * @author カネコ_リョウタ
 */

#pragma once
#include "Vector4.h"
#pragma warning(push)
#pragma	warning(disable:4282)
#pragma	warning(disable:4283)
#pragma	warning(disable:4285)
#include <json.hpp>
#pragma warning(pop)
#include <string>
#include <vector>
#include "Matrix4.h"

// レベルデータ
struct LevelData {

	struct ObjectData {
		// ファイル名
		std::string fileName;
		// 平行移動
		Vector4 translation;
		// 回転角
		Vector4 rotation;
		// スケーリング
		Vector4 scaling;
	};

	// オブジェクト配列
	std::vector<ObjectData> objects;
};

class JsonLoader {
public:
	/// <summary>
	/// ファイル読み込み
	/// </summary>
	/// <param name="fileName"></param>
	/// <returns></returns>
	LevelData* LoadFile(const std::string& fileName);
public:
	// デフォルトの読み込みディレクトリ
	static const std::string kDefaultBaseDirectory;
	// ファイル拡張子
	static const std::string kExtension;

};