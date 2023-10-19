/**
 * @file WorldTransform.h
 * @brief 3d�I�u�W�F�N�g�̍��W�Ǘ��A�A�t�B���ϊ����s���N���X
 * @author �J�l�R_�����E�^
 */

#include "WorldTransform.h"
#include<cassert>
#include <d3dx12.h>

Microsoft::WRL::ComPtr<ID3D12Device> WorldTransform::device = nullptr;

void WorldTransform::StaticInitialize(ID3D12Device* device_)
{
	assert(device_);
	device = device_;
}

void WorldTransform::Initialize()
{
	CreateConstBuffer();
	Map();
	UpdateMatrix();
}

void WorldTransform::CreateConstBuffer()
{
	assert(device);

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff);

	HRESULT result;

	// �萔�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProps, // �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0));

	assert(SUCCEEDED(result));
}

void WorldTransform::Map()
{
	//�萔�o�b�t�@�̃}�b�s���O
	HRESULT result;//�}�b�s���O
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);//�}�b�s���O
	assert(SUCCEEDED(result));
}

void WorldTransform::UpdateMatrix()
{

	Matrix4 matScale, matRot, matTrans;
	Matrix4 matRotX, matRotY, matRotZ;

	//�e�s��v�Z
	matScale = Matrix4::identity();
	matScale.scale(scale);
	matRot = Matrix4::identity();
	matRot *= matRotZ.rotateZ(ToRadian(rotation.z));
	matRot *= matRotX.rotateX(ToRadian(rotation.x));
	matRot *= matRotY.rotateY(ToRadian(rotation.y));
	matTrans = Matrix4::identity();
	matTrans.translate(position);

	//���[���h�s��̍���
	matWorld = Matrix4::identity();
	matWorld *= matScale;
	matWorld *= matRot;
	matWorld *= matTrans;

	//�e�q�\��
	if (parent != nullptr) 
	{
		matWorld *= parent->matWorld;
	}

	//�萔�o�b�t�@�ɓ]��
	constMap->matWorld = matWorld;
}
