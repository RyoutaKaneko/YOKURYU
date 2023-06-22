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
	//�G�C���A�X
private:
	using string = std::string;

public:
	//�V���O���g���C���X�^���X�̎擾
	//<return>�C���X�^���X</return>
	static FbxLoader* GetInstance();

	//������
	void Initialize(ID3D12Device* device);

	//fbx�t�@�C�����烂�f���ǂݍ���
	FbxModel* LoadModelFlomFile(const string& modelName);

	//�m�[�h���
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode,Node* parent = nullptr);

	//���b�V�����
	void ParseMesh(FbxModel* model, FbxNode* fbxNode);
	//�T�u
	void ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh);
	void ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh);
	void ParseMatrial(FbxModel* model, FbxNode* fbxNode);
	void LoadTexture(FbxModel* model, const std::string& fullPath);

	static void ConvertMatrixFromFbx(Matrix4 dst, const FbxAMatrix& src);

	//�t�@�C�������o
	std::string ExtracFileName(const std::string& path);

	//��n��
	void Finalize();

	//�X�L�j���O���̓ǂݎ��
	void ParseSkin(FbxModel* model, FbxMesh* fbxMesh);

private:
	//D3D12�f�o�C�X
	ID3D12Device* device = nullptr;
	//FBX�}�l�[�W���[
	FbxManager* fbxManager = nullptr;
	//FBX�C���|�[�^�[
	FbxImporter* fbxImporter = nullptr;

private:
	//private�ȃR���X�g���N�^
	FbxLoader() = default;
	//private�ȃf�X�g���N�^
	~FbxLoader() = default;
	//�R�s�[�R���X�g���N�^���֎~
	FbxLoader(const FbxLoader& obj) = delete;
	//�R�s�[������Z�q���֎~
	void operator=(const FbxLoader& obj) = delete;

//private�ÓI�֐�
private:
	static const string defaultTextureFileName;
public:
	static const string baseDirectory;
};