#pragma once
#include <string>
#include <vector>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#pragma warning(push)
#pragma warning(disable:26813)
#include<DirectXTex.h>
#pragma warning(pop)
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#pragma warning(push)
#pragma	warning(disable:26495)
#pragma	warning(disable:26451)
#include <fbxsdk.h>
#pragma warning(pop)

//�m�[�h
struct Node {
	//���O
	std::string name;
	//�X�P�[��
	Vector4 scaling = { 1,1,1,0 };
	//��]�p
	Vector4 rotation = { 0,0,0,0 };
	//���[�J���ړ�
	Vector4 translation = { 0,0,0,1 };
	//���[�J���ό`�s��
	Matrix4 tranform;
	//�O���[�o���ό`�s��
	Matrix4 globalTransform;
	//�e�m�[�h
	Node* parent = nullptr;
};

class FbxModel {
public:
	friend class FbxLoader;
public://�萔
	//�{�[���C���f�b�N�X�̍ő吔
	static const int MAX_BONE_INDICES = 4;
//�T�u�N���X
public:
	struct VertexPosNormalUvSkin {
		Vector3 pos;
		Vector3 normal;
		Vector2 uv;
		UINT boneIndex[MAX_BONE_INDICES];
		float boneWeight[MAX_BONE_INDICES];
	};
	//�{�[��
	struct Bone {
		std::string name;
		//�����p���̋t�s��
		Matrix4 inInitialPose;
		//�N���X�^�[
		FbxCluster* fbxCluster;
		//�R���X�g���N�^
		Bone(const std::string& name) {
			this->name = name;
		}
	};

private://�G�C���A�X
	template <class T> using ComPtr =
		Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using TexMetadata = DirectX::TexMetadata;
	using sSratchImage = DirectX::ScratchImage;
	//std::���ȗ�
	using string = std::string;
	template <class T> using vector =
		std::vector<T>;
private:
	//���f���̖��O
	std::string name;
	//�m�[�h�z��
	std::vector<Node> nodes;
	//���b�V�������m�[�h
	Node* meshNode = nullptr;
	//���_�f�[�^
	std::vector<VertexPosNormalUvSkin> vertices;
	//���_�C���f�b�N�X
	std::vector<unsigned int>indices;
	//�A���r�G���g
	Vector3 ambient = { 1,1,1 };
	//�f�B�t���[�Y
	Vector3 diffuse = { 1,1,1 };
	//�e�N�X�`�����^�f�[�^
	DirectX::TexMetadata metaData = {};
	//�X�N���b�`�C���[�W
	DirectX::ScratchImage scratchImg = {};
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//�C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	//�C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	//SRV�p�f�X�N���v�^�[�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	//�{�[���z��
	std::vector<Bone> bones;
	//FBX�V�[��
	FbxScene* fbxScene = nullptr;

public://�֐�
	~FbxModel();
	void CreateBuffers(ID3D12Device* device);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//���f���̕ό`�s��擾
	const Matrix4& GetModelTransform() { return meshNode->globalTransform; }
	//getter
	std::vector<Bone>& GetBones() { return bones; }
	FbxScene* GetFbxScene() { return fbxScene; }
};