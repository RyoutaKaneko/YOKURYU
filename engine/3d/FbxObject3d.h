///**
// * @file FbxObject3d.cpp
// * @brief fbx���f����3d�I�u�W�F�N�g�Ƃ��Ĉ������߂̃N���X
// * @author �J�l�R_�����E�^
// */
//
//#pragma once
//#include "FbxModel.h"
//#include "ViewProjection.h"
//#include "WorldTransform.h"
//#include "Vector2.h"
//#include "Vector3.h"
//#include "Vector4.h"
//#include "Matrix4.h"
//#include <Windows.h>
//#include <wrl.h>
//#include <d3d12.h>
//#include <d3dx12.h>
//#include <string>
//
//class FbxObject3d {
//protected://�G�C���A�X
//	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
//public:
//	/// <summary>
//	/// �ÓI������
//	/// </summary>
//	/// <param name="device">�f�o�C�X</param>
//	static void StaticInitialize(ID3D12Device* device);
//
//	/// <summary>
//	/// �J�������Z�b�g
//	/// </summary>
//	/// <param name="view_">�J����</param>
//	static void SetCamera(ViewProjection* view_) { FbxObject3d::view = view_; }
//
//	/// <summary>
//	/// �`��O����
//	/// </summary>
//	/// <param name="cmdList">�R�}���h���X�g</param>
//	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
//	
//	/// <summary>
//	/// �`��㏈��
//	/// </summary>
//	static void PostDraw();
//
//	/// <summary>
//	/// �O���t�B�b�N�X�p�C�v���C������
//	/// </summary>
//	static void CreateGraphicsPipeline();
//private://�ÓI�����o�ϐ�
//	static ID3D12Device* device;
//	static ViewProjection* view;
//public://�T�u�N���X
//	struct ConstBufferDataTransform {
//		Matrix4 viewproj;
//		Matrix4 world;
//		Vector3 cameraPos;
//	};
//public://�����o�֐�
//	/// <summary>
//	/// ������
//	/// </summary>
//	void Initialize();
//
//	/// <summary>
//	/// �X�V
//	/// </summary>
//	void Update();
//
//	/// <summary>
//	/// ���f�����Z�b�g
//	/// </summary>
//	/// <param name="model_">���f��</param>
//	void SetModel(FbxModel* model_) { this->model = model_; }
//
//	/// <summary>
//	/// �`��
//	/// </summary>
//	/// <param name="viewProjection">�J����</param>
//	void Draw(ViewProjection* viewProjection);
//
//	/// <summary>
//	/// ���W���擾
//	/// </summary>
//	/// <returns></returns>
//	const Vector3& GetPosition() const { return worldTransform.GetPosition(); }
//
//	/// <summary>
//	/// ���W���Z�b�g
//	/// </summary>
//	/// <param name="position">���W</param>
//	void SetPosition(const Vector3& position) { this->worldTransform.GetPosition() = position; }
//	
//	/// <summary>
//	/// �X�P�[�����擾
//	/// </summary>
//	/// <param name="scale">�X�P�[��</param>
//	void SetScale(const Vector3& scale) { this->worldTransform.GetScale() = scale; }
//
//	/// <summary>
//	/// �X�P�[�����擾
//	/// </summary>
//	/// <returns></returns>
//	const Vector3& GetScale()  { return worldTransform.GetScale(); }
//	
//	/// <summary>
//	/// �I�u�W�F�N�g�̉�]���Z�b�g
//	/// </summary>
//	/// <param name="rotationZ">��]��</param>
//	void SetRotation(const Vector3& rotation) { this->worldTransform.GetRotation() = rotation; }
//
//	/// <summary>
//	/// �I�u�W�F�N�g�̉�]���擾
//	/// </summary>
//	/// <returns></returns>
//	const Vector3& GetRotation()  { return worldTransform.GetRotation(); }
//
//protected://�����o�ϐ�
//	ComPtr<ID3D12Resource> constBuffTransform;
//private:
//	static ComPtr<ID3D12RootSignature> rootsignature;
//	static ComPtr<ID3D12PipelineState> pipelinestate;
//	// �R�}���h���X�g
//	static ID3D12GraphicsCommandList* cmdList;
//
//	WorldTransform worldTransform;
//	FbxModel* model = nullptr;
//};