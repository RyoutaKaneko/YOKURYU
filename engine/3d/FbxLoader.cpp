#include "FbxLoader.h"
#include <cassert>
#include "Vector3.h"
#include "DirectXMath.h"

//�ÓI�ϐ��̎���
const std::string FbxLoader::baseDirectory =
"Resources/";
const std::string FbxLoader::defaultTextureFileName =
"white1x1.png";

//�C���X�^���X���擾
FbxLoader* FbxLoader::GetInstance() {
	static FbxLoader instance;
	return &instance;
}

//������
void FbxLoader::Initialize(ID3D12Device* device) {

	//�ď������`�F�b�N
	assert(fbxManager == nullptr);
	//�������烁���o�ϐ��ɑ��
	this->device = device;
	//FBX�}�l�[�W���[�̐���
	fbxManager = FbxManager::Create();
	//FBX�}�l�[�W���[�̓��o�͐ݒ�
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
	fbxManager->SetIOSettings(ios);
	//FBX�C���|�[�^�[�̐���
	fbxImporter = FbxImporter::Create(fbxManager, "");
}

//���f���ǂݍ���
FbxModel* FbxLoader::LoadModelFlomFile(const string& modelName) {
	const string directoryPath = baseDirectory + modelName + "/";
	const string fileName = modelName + ".fbx";
	//�A��
	const string fullPath = directoryPath + fileName;

	//�t�@�C�������w�肵�ēǂݍ���
	if (!fbxImporter->Initialize(fullPath.c_str(), -1, fbxManager->GetIOSettings())) {
		assert(0);
	}
	FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");

	//�t�@�C�������V�[���ɃC���|�[�g
	fbxImporter->Import(fbxScene);

	//���f������
	FbxModel* model = new FbxModel();
	model->name = modelName;
	//�m�[�h�����擾
	int nodeCount = fbxScene->GetNodeCount();

	model->nodes.reserve(nodeCount);

	ParseNodeRecursive(model, fbxScene->GetRootNode());
	model->fbxScene = fbxScene;

	//�o�b�t�@����
	model->CreateBuffers(device);
	assert(model->indices.size());

	return model;
}

//�m�[�h���
void FbxLoader::ParseNodeRecursive(FbxModel* model, FbxNode* fbxNode, Node* parent) {

	model->nodes.emplace_back();
	Node& node = model->nodes.back();
	//�m�[�h�����擾
	node.name = fbxNode->GetName();

	//fbx�m�[�h�̃��[�J���ړ����
	FbxDouble3 rotation = fbxNode->LclRotation.Get();
	FbxDouble3 scaling = fbxNode->LclScaling.Get();
	FbxDouble3 translation = fbxNode->LclTranslation.Get();

	//�`���ϊ����đ��
	node.rotation = { (float)rotation[0],(float)rotation[1],(float)rotation[2],0.0f };
	node.scaling = { (float)scaling[0],(float)scaling[1],(float)scaling[2],0.0f };
	node.translation = { (float)translation[0],(float)translation[1],(float)translation[2],1.0f };

	//��]�p��Degree���烉�W�A���ɕϊ�
	node.rotation.x = Matrix4::ConvertToRadian(node.rotation.x);
	node.rotation.y = Matrix4::ConvertToRadian(node.rotation.y);
	node.rotation.z = Matrix4::ConvertToRadian(node.rotation.z);

	//�p�s��̌v�Z
	Matrix4 matScaling, matRotation, matTranslation;
	Matrix4 matRotX, matRotY, matRotZ;
	Vector3 scl = { node.scaling.x,node.scaling.y ,node.scaling.z };
	matScaling = Matrix4::identity();
	matScaling.scale(scl);
	matRotation = Matrix4::identity();
	matRotation *= matRotZ.rotateZ(Matrix4::ConvertToRadian(node.rotation.z));
	matRotation *= matRotX.rotateX(Matrix4::ConvertToRadian(node.rotation.x));
	matRotation *= matRotY.rotateY(Matrix4::ConvertToRadian(node.rotation.y));
	Vector3 trl = { node.translation.x,node.translation.y,node.translation.z };
	matTranslation = Matrix4::identity();
	matTranslation.translate(trl);

	//���[�J���ϊ��s��̌v�Z
	node.tranform = Matrix4::identity();
	node.tranform *= matScaling;
	node.tranform *= matRotation;
	node.tranform *= matTranslation;

	//�O���[�o���ό`�s��̌v�Z
	node.globalTransform = node.tranform;
	if (parent) {
		node.parent = parent;
		//�e�̕ό`����Z
		node.globalTransform *= parent->globalTransform;
	}

	//���b�V�����
	FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

	if (fbxNodeAttribute) {
		if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh) {
			model->meshNode = &node;
			ParseMesh(model, fbxNode);
		}
	}

	//�q�m�[�h�ɑ΂��čċN�Ăяo��
	for (int i = 0; i < fbxNode->GetChildCount(); i++) {
		ParseNodeRecursive(model, fbxNode->GetChild(i), &node);
	}


}

void FbxLoader::ParseMesh(FbxModel* model, FbxNode* fbxNode) {
	FbxMesh* fbxMesh = fbxNode->GetMesh();

	//���_���W�ǂݎ��
	ParseMeshVertices(model, fbxMesh);
	//��
	ParseMeshFaces(model, fbxMesh);
	//�}�e���A��
	ParseMatrial(model, fbxNode);
	//�X�L�j���O���ǂݎ��
	ParseSkin(model, fbxMesh);

}
//���_���ǂݎ��
void FbxLoader::ParseMeshVertices(FbxModel* model, FbxMesh* fbxMesh) {
	auto& vertices = model->vertices;

	//���_���W�̃f�[�^�̐�
	const int controlPointsCount = fbxMesh->GetControlPointsCount();

	//�K�v���������_�f�[�^���m��
	FbxModel::VertexPosNormalUvSkin vert{};
	model->vertices.resize(controlPointsCount, vert);

	//fbx���b�V���̒��_���W�z����擾
	FbxVector4* pCoord = fbxMesh->GetControlPoints();

	//fbx���b�V���̑S���_���W�����f�����̔z��ɃR�s�[����
	for (int i = 0; i < controlPointsCount; i++) {
		FbxModel::VertexPosNormalUvSkin& vertex = vertices[i];
		//���W�̃R�s�[
		vertex.pos.x = (float)pCoord[i][0];
		vertex.pos.y = (float)pCoord[i][1];
		vertex.pos.z = (float)pCoord[i][2];
	}
}
//�ʏ��ǂݎ��
void FbxLoader::ParseMeshFaces(FbxModel* model, FbxMesh* fbxMesh) {
	auto& vertices = model->vertices;
	auto& indices = model->indices;

	//1�t�@�C���ɕ������b�V���̃��f���͔�Ή�
	assert(indices.size() == 0);

	//�ʂ̐�
	const int polygonCount = fbxMesh->GetPolygonCount();
	//uv�f�[�^�̐�
	const int textureUVCount = fbxMesh->GetTextureUVCount();
	//uv�����X�g
	FbxStringList uvNames;
	fbxMesh->GetUVSetNames(uvNames);

	//�ʂ��Ƃ̏��ǂݎ��
	for (int i = 0; i < polygonCount; i++) {
		const int polygonSize = fbxMesh->GetPolygonSize(i);
		assert(polygonSize <= 4);

		for (int j = 0; j < polygonSize; j++) {
			int index = fbxMesh->GetPolygonVertex(i, j);
			assert(index >= 0);
			//���_�@���ǂݍ���
			FbxModel::VertexPosNormalUvSkin& vertex = vertices[index];
			FbxVector4 normal;
			if (fbxMesh->GetPolygonVertexNormal(i, j, normal)) {
				vertex.normal.x = (float)normal[0];
				vertex.normal.y = (float)normal[1];
				vertex.normal.z = (float)normal[2];
			}
			//�e�N�X�`��uv�ǂݍ���
			if (textureUVCount > 0) {
				FbxVector2 uvs;
				bool lUnmappedUV;
				//0�Ԍ��ߑł��œǂݍ���
				if (fbxMesh->GetPolygonVertexUV(i, j, uvNames[0], uvs, lUnmappedUV)) {
					vertex.uv.x = (float)uvs[0];
					vertex.uv.y = (float)uvs[1];
				}
			}

			//�C���f�b�N�X�z��ɒ��_�C���f�b�N�X��ǉ�
			if (j < 3) {
				indices.push_back(index);
			}
			//4���_
			else {
				int index2 = indices[indices.size() - 1];
				int index3 = index;
				int index0 = indices[indices.size() - 3];
				indices.push_back(index2);
				indices.push_back(index3);
				indices.push_back(index0);
			}
		}
	}

}
//�}�e���A���ǂݍ���
void FbxLoader::ParseMatrial(FbxModel* model, FbxNode* fbxNode) {
	const int materialCount = fbxNode->GetMaterialCount();
	if (materialCount > 0) {
		FbxSurfaceMaterial* material = fbxNode->GetMaterial(0);
		bool textureLoaded = false;

		if (material) {
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
				FbxSurfaceLambert* lambert =
					static_cast<FbxSurfaceLambert*>(material);

				//�����W��
				FbxPropertyT<FbxDouble3> ambient = lambert->Ambient;
				model->ambient.x = (float)ambient.Get()[0];
				model->ambient.y = (float)ambient.Get()[1];
				model->ambient.z = (float)ambient.Get()[2];

				//�g�U���ˌ��W��
				FbxPropertyT<FbxDouble3> diffuse = lambert->Diffuse;
				model->diffuse.x = (float)diffuse.Get()[0];
				model->diffuse.y = (float)diffuse.Get()[1];
				model->diffuse.z = (float)diffuse.Get()[2];
			}
			//�f�B�t���[�Y�e�N�X�`�������o��
			const FbxProperty diffuseProperty =
				material->FindProperty(FbxSurfaceMaterial::sDiffuse);
			if (diffuseProperty.IsValid()) {
				const FbxFileTexture* texture = diffuseProperty.GetSrcObject<FbxFileTexture>();
				if (texture) {
					const char* filepath = texture->GetFileName();
					//�t�@�C���p�X����t�@�C�������o
					string path_str(filepath);
					string name = ExtracFileName(path_str);
					//�e�N�X�`���ǂݍ���
					LoadTexture(model, baseDirectory + model->name + "/" + name);
					textureLoaded = true;
				}
			}
		}
		//�e�N�X�`�����Ȃ��ꍇ���e�N�X�`����\��
		if (!textureLoaded) {
			LoadTexture(model, baseDirectory + defaultTextureFileName);
		}
	}
}

//�e�N�X�`���ǂݍ���
void FbxLoader::LoadTexture(FbxModel* model, const std::string& fullPath) {
	HRESULT result = S_FALSE;
	//WIC�e�N�X�`���̃��[�h
	DirectX::TexMetadata& metadata = model->metaData;
	DirectX::ScratchImage& scratchImage = model->scratchImg;
	//���j�R�[�h������ɕϊ�
	wchar_t wfilepath[128];
	MultiByteToWideChar(CP_ACP, 0, fullPath.c_str(), -1, wfilepath, _countof(wfilepath));
	result = DirectX::LoadFromWICFile(wfilepath, DirectX::WIC_FLAGS_NONE, &metadata, scratchImage);

	if (FAILED(result)) {
		assert(0);
	}
}

//�t�@�C�������o
std::string FbxLoader::ExtracFileName(const std::string& path) {
	size_t pos1;
	//��؂蕶��""���o�Ă����ԍŌ�̕���������
	pos1 = path.rfind("\\");
	if (pos1 != string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}
	//��؂蕶��'/'
	pos1 = path.rfind('/');
	if (pos1 != string::npos) {
		return path.substr(pos1 + 1, path.size() - pos1 - 1);
	}

	return path;
}

//��n��
void FbxLoader::Finalize() {
	//�e��C���X�^���X�̔j��
	fbxImporter->Destroy();
	fbxManager->Destroy();
}

void FbxLoader::ConvertMatrixFromFbx(Matrix4 dst, const FbxAMatrix& src) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dst.m[i][j] = (float)src.Get(i, j);
		}
	}
}

void FbxLoader::ParseSkin(FbxModel* model, FbxMesh* fbxMesh) {
	FbxSkin* fbxSkin =
	static_cast<FbxSkin*>(fbxMesh->GetDeformer(0, FbxDeformer::eSkin));
	//�X�L�j���O��񂪂Ȃ���ΏI��
	if (fbxSkin == nullptr) {
		return;
	}
	//�{�[���z��̎Q��
	std::vector<FbxModel::Bone>& bones = model->bones;
	//�{�[���̐�
	int clusterCount = fbxSkin->GetClusterCount();
	bones.reserve(clusterCount);

	//�S�Ẵ{�[���ɂ���
	for (int i = 0; i < clusterCount; i++) {
		//FBX�{�[�����
		FbxCluster* fbxCluster = fbxSkin->GetCluster(i);
		//�{�[�����̂̃m�[�h�̖��O���擾
		const char* boneName = fbxCluster->GetLink()->GetName();
		//�V�����{�[����ǉ����ǉ������{�[���̎Q�Ƃ𓾂�
		bones.emplace_back(FbxModel::Bone(boneName));
		FbxModel::Bone& bone = bones.back();
		//����{�[����Fbx�̃{�[����R�Â���
		bone.fbxCluster = fbxCluster;
		//FBX���珉���p���s����擾����
		FbxAMatrix fbxMat;
		fbxCluster->GetTransformLinkMatrix(fbxMat);
		//Matrix4�^�ɕϊ�����
		Matrix4 initialPose;
		ConvertMatrixFromFbx(initialPose, fbxMat);
		//�����p���s��̋t�s��𓾂�
		bone.inInitialPose.MakeInverse();
	}
	//�{�[���ԍ��ƃX�L���E�F�C�g�̃y�A
	struct WeightSet {
		UINT index;
		float weight;
	};

	//�񎟌��z��(�W���O�z��)
	//list:���_���e�����󂯂�{�[���̑S���X�g
	//vector:�����S���_��
	std::vector<std::list<WeightSet>>
	weightLists(model->vertices.size());
	//�S�Ẵ{�[���ɂ���
	for (int i = 0; i < clusterCount; i++) {
		FbxCluster* fbxCluster = fbxSkin->GetCluster(i);
		//���̃{�[���ɉe�����󂯂钸�_
		int controlPointIndicesCount = fbxCluster->GetControlPointIndicesCount();
		//���̃{�[���ɉe�����󂯂钸�_�̔z��
		int* controlPointIndices = fbxCluster->GetControlPointIndices();
		double* controlPointWeights = fbxCluster->GetControlPointWeights();
		//�e�����󂯂�S���_�ɂ���
		for (int j = 0; j < controlPointIndicesCount; j++) {
			int vertIndex = controlPointIndices[j];
			//�X�L���E�F�C�g
			float weight = (float)controlPointWeights[j];
			//���̒��_�̉e�����󂯂�{�[�����X�g�Ƀ{�[���ƃE�F�C�g�̃y�A��ǉ�
			weightLists[vertIndex].emplace_back(WeightSet{ (UINT)i,weight });
		}

		auto& vertices = model->vertices;
		for (int i = 0; i < vertices.size(); i++) {
			auto& weightList = weightLists[i];
			weightList.sort([](auto const& lhs, auto const& rhs) {
			//���̗v�f�̕����傫�����true �����łȂ����false��Ԃ�
			return lhs.weight > rhs.weight;
			});

			int weightArrayIndex = 0;
			//�~���\�[�g�ς݂̃E�F�C�g���X�g����
			for (auto& weightSet : weightList) {
				vertices[i].boneIndex[weightArrayIndex] = weightSet.index;
				vertices[i].boneWeight[weightArrayIndex] = weightSet.weight;
				//4�ɒB������I��
				if (++weightArrayIndex >= FbxModel::MAX_BONE_INDICES) {
					float weight = 0.0f;
					//2�Ԗڈȍ~�̃E�F�C�g�����v
					for (int j = 1; j < FbxModel::MAX_BONE_INDICES; j++) {
						weight += vertices[i].boneWeight[j];
					}
					//���v��1.0f(100%)�ɂȂ�悤�ɒ���
					vertices[i].boneWeight[0] = 1.0f - weight;
					break;
				}
			}
		}
	}
}