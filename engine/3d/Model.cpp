#include "Model.h"

#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

// �ÓI�����o�ϐ��̎���
ID3D12Device* Model::device = nullptr;

Model* Model::LoadFromOBJ(const string& modelname, const string& texname)
{
	// �V����Model�^�̃C���X�^���X�̃��������m��
	Model* model = new Model();

	// �f�X�N���v�^�q�[�v�̐���
	model->InitializeDescriptorHeap();

	// OBJ�t�@�C������f�[�^��ǂݍ���
	model->LoadFromOBJInternal(modelname);

	// �o�b�t�@����
	model->CreateBuffers();

	//model->LoadTexture(texname);
	
	return model;
}

void Model::LoadMaterial(const std::string& directoryPath, const std::string& filename)
{
	// �t�@�C���X�g���[��
	std::ifstream file;
	// �}�e���A���t�@�C�����J��
	file.open(directoryPath + filename);
	// �t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		assert(0);
	}

	// 1�s���ǂݍ���
	string line;
	while (getline(file, line)) {
		// 1�s���̕�������X�g���[���ɕϊ�
		std::istringstream line_stream(line);

		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');

		// �擪�̃^�u�����͖�������
		if (key[0] == '\t')
		{
			key.erase(key.begin()); // �擪�̕������폜
		}
		// �擪������newmtl�Ȃ�}�e���A����
		if (key == "newmtl")
		{
			// �}�e���A�����ǂݍ���
			line_stream >> material.name;
		}
		// �擪������Ka�Ȃ�A���r�G���g�F
		if (key == "Ka")
		{
			line_stream >> material.ambient.x;
			line_stream >> material.ambient.y;
			line_stream >> material.ambient.z;
		}
		// �擪������Kd�Ȃ�f�B�t���[�Y�F
		if (key == "Kd")
		{
			line_stream >> material.diffuse.x;
			line_stream >> material.diffuse.y;
			line_stream >> material.diffuse.z;
		}
		// �擪������Ks�Ȃ�X�y�L�����[�F
		if (key == "Ks")
		{
			line_stream >> material.specular.x;
			line_stream >> material.specular.y;
			line_stream >> material.specular.z;
		}
		// �擪������map_Kd�Ȃ�e�N�X�`���t�@�C����
		if (key == "map_Kd") {
			// �e�N�X�`���̃t�@�C�����ǂݍ���
			line_stream >> material.textureFilename;
			// �e�N�X�`���ǂݍ���
			LoadTexture(directoryPath, material.textureFilename);
		}
	}
	// �t�@�C�������
	file.close();
}

void Model::LoadTexture(const std::string& directoryPath, const std::string& filename)
{
	HRESULT result = S_FALSE;

	TexMetadata metadata{};
	ScratchImage scratchImg{};

	// �t�@�C���p�X������
	string filepath = directoryPath + filename;

	// ���j�R�[�h������ɕϊ�����
	wchar_t wfilepath[128];
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, filepath.c_str(), -1, wfilepath, _countof(wfilepath));

	result = LoadFromWICFile(
		wfilepath, WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	assert(SUCCEEDED(result));

	ScratchImage mipChain{};
	// �~�b�v�}�b�v����
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result)) {
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	// �ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = MakeSRGB(metadata.format);

	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format, metadata.width, (UINT)metadata.height, (UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps =
		CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);

	// �e�N�X�`���p�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // �e�N�X�`���p�w��
		nullptr, IID_PPV_ARGS(&texbuff));
	assert(SUCCEEDED(result));

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	for (size_t i = 0; i < metadata.mipLevels; i++) {
		const Image* img = scratchImg.GetImage(i, 0, 0); // ���f�[�^���o
		result = texbuff->WriteToSubresource(
			(UINT)i,
			nullptr,              // �S�̈�փR�s�[
			img->pixels,          // ���f�[�^�A�h���X
			(UINT)img->rowPitch,  // 1���C���T�C�Y
			(UINT)img->slicePitch // 1���T�C�Y
		);
		assert(SUCCEEDED(result));
	}

	// �V�F�[�_���\�[�X�r���[�쐬
	cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
	gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // �ݒ�\����
	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(texbuff.Get(), //�r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc, //�e�N�X�`���ݒ���
		cpuDescHandleSRV
	);

}

void Model::LoadTexture(const std::string& filename)
{
	HRESULT result = S_FALSE;

	TexMetadata metadata{};
	ScratchImage scratchImg{};

	// �t�@�C���p�X������
	string filepath = filename;

	// ���j�R�[�h������ɕϊ�����
	wchar_t wfilepath[128];
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, filepath.c_str(), -1, wfilepath, _countof(wfilepath));

	result = LoadFromWICFile(
		wfilepath, WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	assert(SUCCEEDED(result));

	ScratchImage mipChain{};
	// �~�b�v�}�b�v����
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result)) {
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	// �ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = MakeSRGB(metadata.format);

	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format, metadata.width, (UINT)metadata.height, (UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps =
		CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);

	// �e�N�X�`���p�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // �e�N�X�`���p�w��
		nullptr, IID_PPV_ARGS(&texbuff));
	assert(SUCCEEDED(result));

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	for (size_t i = 0; i < metadata.mipLevels; i++) {
		const Image* img = scratchImg.GetImage(i, 0, 0); // ���f�[�^���o
		result = texbuff->WriteToSubresource(
			(UINT)i,
			nullptr,              // �S�̈�փR�s�[
			img->pixels,          // ���f�[�^�A�h���X
			(UINT)img->rowPitch,  // 1���C���T�C�Y
			(UINT)img->slicePitch // 1���T�C�Y
		);
		assert(SUCCEEDED(result));
	}

	// �V�F�[�_���\�[�X�r���[�쐬
	cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
	gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // �ݒ�\����
	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(texbuff.Get(), //�r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc, //�e�N�X�`���ݒ���
		cpuDescHandleSRV
	);

}

void Model::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial,float alpha_)
{
	// nullptr�`�F�b�N
	assert(device);
	assert(cmdList);

	// ���_�o�b�t�@�r���[�̐ݒ�
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	// �C���f�b�N�X�o�b�t�@�̐ݒ�
	cmdList->IASetIndexBuffer(&ibView);
	//alpha�l�ݒ�
	SetAlpha(alpha_);
	// �萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(rootParamIndexMaterial,
		constBuffB1->GetGPUVirtualAddress());

	// �f�X�N���v�^�q�[�v�̔z��
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	if (material.textureFilename.size() > 0) {
		// �V�F�[�_���\�[�X�r���[���Z�b�g
		cmdList->SetGraphicsRootDescriptorTable(3, gpuDescHandleSRV);
	}

	// �`��R�}���h
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}

void Model::LoadFromOBJInternal(const string& modelname)
{
	HRESULT result = S_FALSE;

	// �t�@�C���X�g���[��
	std::ifstream file;
	// .obj�t�@�C�����J��
	const string filename = modelname + ".obj"; // "modelname.obj"
	const string directoryPath = "Resources/" + modelname + "/"; // "Resources/modelname/"
	file.open(directoryPath + filename); // "Resources/modelname.obj"
	// �t�@�C���I�[�v�����s���`�F�b�N
	if (file.fail()) {
		assert(0);
	}
	vector<Vector3> positions; // ���_���W
	vector<Vector3> normals;   // �@���x�N�g��
	vector<Vector2> texcoords; // �e�N�X�`��UV
	// �P�s���ǂݍ���
	string line;
	while (getline(file, line)) {

		// �P�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		// ���p�X�p�[�X��؂�ōs�̐擪��������擾
		string key;
		getline(line_stream, key, ' ');

		// �擪�����񂪂��Ȃ璸�_���W
		if (key == "v") {
			// X,Y,Z���W�ǂݍ���
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// ���W�f�[�^�ɒǉ�
			positions.emplace_back(position);
			// ���_�f�[�^�ɒǉ�
			/*VertexPosNormalUvSkin vertex{};
			vertex.pos = position;
			vertices.emplace_back(vertex);*/
		}

		// �擪�����񂪂��Ȃ�|���S���i�O�p�`�j
		if (key == "f") {
			// ���p�X�y�[�X��؂�ōs�̑�����ǂݍ���
			string index_string;
			while (getline(line_stream, index_string, ' ')) {
				// ���_�C���f�b�N�X�P���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
				std::istringstream index_stream(index_string);
				unsigned short indexPosition, indexNormal, indexTexcoord;
				index_stream >> indexPosition;
				index_stream.seekg(1, ios_base::cur); // �X���b�V�����΂�
				index_stream >> indexTexcoord;
				index_stream.seekg(1, ios_base::cur); // �X���b�V�����΂�
				index_stream >> indexNormal;
				// ���_�f�[�^�̒ǉ�
				VertexPosNormalUvSkin vertex{};
				vertex.pos = positions[indexPosition - 1];
				vertex.normal = normals[indexNormal - 1];
				vertex.uv = texcoords[indexTexcoord - 1];
				vertices.emplace_back(vertex);
				// ���_�C���f�b�N�X�ɒǉ�
				//indices.emplace_back(indexPosition - 1);
				indices.emplace_back((unsigned short)indices.size());
			}
		}

		// �擪������vt�Ȃ�e�N�X�`��
		if (key == "vt")
		{
			// U,V�����ǂݍ���
			Vector2 texcoord{};
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			// V�������]
			texcoord.y = 1.0f - texcoord.y;
			// �e�N�X�`�����W�f�[�^�ɒǉ�
			texcoords.emplace_back(texcoord);
		}

		// �擪������vn�Ȃ�@���x�N�g��
		if (key == "vn") {
			// X,Y,Z�����ǂݍ���
			Vector3 normal{};
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;
			// �@���x�N�g���e�[�^�ɒǉ�
			normals.emplace_back(normal);
		}

		// �擪������mtllib�Ȃ�}�e���A��
		if (key == "mtllib")
		{
			// �}�e���A���̃t�@�C�����ǂݍ���
			string filename;
			line_stream >> filename;
			// �}�e���A���ǂݍ���
			LoadMaterial(directoryPath, filename);
		}
	}
	// �t�@�C���ƕ���
	file.close();
}

void Model::InitializeDescriptorHeap()
{
	assert(device);

	HRESULT result = S_FALSE;

	// �f�X�N���v�^�q�[�v�𐶐�	
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	descHeapDesc.NumDescriptors = 1; // �V�F�[�_�[���\�[�X�r���[1��
	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//����
	if (FAILED(result)) {
		assert(0);
	}

	// �f�X�N���v�^�T�C�Y���擾
	descriptorHandleIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

}

void Model::CreateBuffers()
{
	HRESULT result = S_FALSE;

	std::vector<VertexPosNormalUvSkin> realVertices;

	/*UINT sizeVB = static_cast<UINT>(sizeof(vertices));*/
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUvSkin) * vertices.size());

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeVB);

	// ���_�o�b�t�@����
	result = device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));

	// ���_�o�b�t�@�ւ̃f�[�^�]��
	VertexPosNormalUvSkin* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		/*memcpy(vertMap, vertices, sizeof(vertices));*/
		std::copy(vertices.begin(), vertices.end(), vertMap);
		vertBuff->Unmap(0, nullptr);
	}

	// ���_�o�b�t�@�r���[�̍쐬
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	/*vbView.SizeInBytes = sizeof(vertices);*/
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	/*UINT sizeIB = static_cast<UINT>(sizeof(indices));*/
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());
	// ���\�[�X�ݒ�
	resourceDesc.Width = sizeIB;

	// �C���f�b�N�X�o�b�t�@����
	result = device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&indexBuff));

	// �C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	if (SUCCEEDED(result)) {

		// �S�C���f�b�N�X�ɑ΂���
		//for (int i = 0; i < _countof(indices); i++)
		//{
		//	indexMap[i] = indices[i];	// �C���f�b�N�X���R�s�[
		//}

		std::copy(indices.begin(), indices.end(), indexMap);

		indexBuff->Unmap(0, nullptr);
	}

	// �C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	/*ibView.SizeInBytes = sizeof(indices);*/
	ibView.SizeInBytes = sizeIB;

	// nullptr�`�F�b�N
	assert(device);

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps1 = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	//HRESULT result;

	resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB1) + 0xff) & ~0xff);

	// �萔�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProps1,
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB1)
	);

	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB1* constMap1 = nullptr;
	result = constBuffB1->Map(0, nullptr, (void**)&constMap1);
	if (SUCCEEDED(result)) {
		constMap1->ambient = material.ambient;
		constMap1->diffuse = material.diffuse;
		constMap1->specular = material.specular;
		constMap1->alpha = material.alpha;
		constBuffB1->Unmap(0, nullptr);
	}
}

void Model::SetAlpha(float alpha_) {

	HRESULT result = S_FALSE;

	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB1* constMap1 = nullptr;
	result = constBuffB1->Map(0, nullptr, (void**)&constMap1);
	if (SUCCEEDED(result)) {
		constMap1->alpha = alpha_;
		constBuffB1->Unmap(0, nullptr);
	}
}