/**
 * @file FbxLoader.cpp
 * @brief fbx���f���̓ǂݍ��݃N���X
 * @author �J�l�R_�����E�^
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
	//�G�C���A�X
private:
	using string = std::string;

public:
	//�V���O���g���C���X�^���X�̎擾
	//<return>�C���X�^���X</return>
	static FbxLoader* GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// fbx�t�@�C�����烂�f���ǂݍ���
	/// </summary>
	/// <param name="modelName">���f����</param>
	/// <returns></returns>
	FbxModel* LoadModelFlomFile(const string& modelName);

	/// <summary>
	/// �m�[�h���
	/// </summary>
	/// <param name="model">���f����</param>
	/// <param name="fbxNode">�m�[�h</param>
	/// <param name="parent">�e�q</param>
	void ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode,Node* parent = nullptr);

	/// <summary>
	/// ���b�V�����
	/// </summary>
	/// <param name="model">���f����</param>
	/// <param name="fbxNode">�m�[�h</param>
	void ParseMesh(FbxModel* model, FbxNode* fbxNode);
	
	/// <summary>
	/// ���b�V���̒��_�v�Z
	/// </summary>
	/// <param name="model">���f����</param>
	/// <param name="fbxMesh">���b�V��</param>
	void ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh);

	/// <summary>
	/// ���b�V���̖ʌv�Z
	/// </summary>
	/// <param name="model">���f����</param>
	/// <param name="fbxMesh">���b�V��</param>
	void ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh);

	/// <summary>
	/// �}�e���A�����
	/// </summary>
	/// <param name="model">���f����</param>
	/// <param name="fbxNode">�m�[�h</param>
	void ParseMatrial(FbxModel* model, FbxNode* fbxNode);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="model">���f����</param>
	/// <param name="fullPath">�}�e���A���t���p�X</param>
	void LoadTexture(FbxModel* model, const std::string& fullPath);

	/// <summary>
	/// fbxAMatrix����Matrix4�ɕϊ�
	/// </summary>
	/// <param name="dst">�P�ʍs��</param>
	/// <param name="src">�ϊ�����s��</param>
	static void ConvertMatrixFromFbx(Matrix4 dst, const FbxAMatrix& src);

	/// <summary>
	/// �t�@�C�������o
	/// </summary>
	/// <param name="path">�t�@�C���p�X</param>
	/// <returns></returns>
	std::string ExtracFileName(const std::string& path);

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �X�L�j���O���̓ǂݎ��
	/// </summary>
	/// <param name="model">���f����</param>
	/// <param name="fbxMesh">���b�V��</param>
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