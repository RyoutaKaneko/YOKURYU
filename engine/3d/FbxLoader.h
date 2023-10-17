/**
 * @file FbxLoader.cpp
 * @brief fbxモデルの読み込みクラス
 * @author カネコ_リョウタ
 */

#pragma once
#pragma warning(push)
#pragma	warning(disable:26495)
#pragma	warning(disable:26451)
#include <fbxsdk.h>
#pragma warning(pop)
#include "d3d12.h"
#include "d3dx12.h"
#include <string>
#include "FbxModel.h"
#include "Matrix4.h"
#pragma warning(push)
#pragma	warning(disable:26813)
#include "DirectXTex.h"
#pragma warning(pop)

class FbxLoader {
	//エイリアス
private:
	using string = std::string;

public:
	//シングルトンインスタンスの取得
	//<return>インスタンス</return>
	static FbxLoader* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// fbxファイルからモデル読み込み
	/// </summary>
	/// <param name="modelName">モデル名</param>
	/// <returns></returns>
	FbxModel* LoadModelFlomFile(const string& modelName);

	/// <summary>
	/// ノード解析
	/// </summary>
	/// <param name="model">モデル名</param>
	/// <param name="fbxNode">ノード</param>
	/// <param name="parent">親子</param>
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode,Node* parent = nullptr);

	/// <summary>
	/// メッシュ解析
	/// </summary>
	/// <param name="model">モデル名</param>
	/// <param name="fbxNode">ノード</param>
	void ParseMesh(FbxModel* model, FbxNode* fbxNode);
	
	/// <summary>
	/// メッシュの頂点計算
	/// </summary>
	/// <param name="model">モデル名</param>
	/// <param name="fbxMesh">メッシュ</param>
	void ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh);

	/// <summary>
	/// メッシュの面計算
	/// </summary>
	/// <param name="model">モデル名</param>
	/// <param name="fbxMesh">メッシュ</param>
	void ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh);

	/// <summary>
	/// マテリアル解析
	/// </summary>
	/// <param name="model">モデル名</param>
	/// <param name="fbxNode">ノード</param>
	void ParseMatrial(FbxModel* model, FbxNode* fbxNode);

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <param name="model">モデル名</param>
	/// <param name="fullPath">マテリアルフルパス</param>
	void LoadTexture(FbxModel* model, const std::string& fullPath);

	/// <summary>
	/// fbxAMatrixからMatrix4に変換
	/// </summary>
	/// <param name="dst">単位行列</param>
	/// <param name="src">変換する行列</param>
	static void ConvertMatrixFromFbx(Matrix4 dst, const FbxAMatrix& src);

	/// <summary>
	/// ファイル名抽出
	/// </summary>
	/// <param name="path">ファイルパス</param>
	/// <returns></returns>
	std::string ExtracFileName(const std::string& path);

	/// <summary>
	/// 終了
	/// </summary>
	void Finalize();

	/// <summary>
	/// スキニング情報の読み取り
	/// </summary>
	/// <param name="model">モデル名</param>
	/// <param name="fbxMesh">メッシュ</param>
	void ParseSkin(FbxModel* model, FbxMesh* fbxMesh);

private:
	//D3D12デバイス
	ID3D12Device* device = nullptr;
	//FBXマネージャー
	FbxManager* fbxManager = nullptr;
	//FBXインポーター
	FbxImporter* fbxImporter = nullptr;

private:
	//privateなコンストラクタ
	FbxLoader() = default;
	//privateなデストラクタ
	~FbxLoader() = default;
	//コピーコンストラクタを禁止
	FbxLoader(const FbxLoader& obj) = delete;
	//コピー代入演算子を禁止
	void operator=(const FbxLoader& obj) = delete;

//private静的関数
private:
	static const string defaultTextureFileName;
public:
	static const string baseDirectory;
};