#include "GameBaseScene.h"


void GameBaseScene::LoadObjFromLevelEditor(const std::string& fileName) {
	JsonLoader* file = nullptr;
	LevelData* levelData = file->LoadFile(fileName);

	//�I�u�W�F�N�g�z�u
	for (auto& objectData : levelData->objects) {
		//�t�@�C��������o�^�ς݃��f��������
		Model* model = nullptr;
		decltype(models)::iterator it = models.find(objectData.fileName);
		if (it != models.end()) { model = it->second; }
		//���f�����w�肵��3DObject�𐶐�
		Object3d* newObject = Object3d::Create();
		newObject->Initialize();
		newObject->SetModel(model);
		//���W
		Vector3 pos;
		pos = Vector3(objectData.translation.x, objectData.translation.y, objectData.translation.z);
		newObject->SetPosition(pos);
		//��]�p
		Vector3 rot;
		rot = Vector3(objectData.rotation.x, objectData.rotation.y, objectData.rotation.z);
		newObject->SetRotation(rot);
		//�X�P�[��
		Vector3 scale;
		scale = Vector3(objectData.scaling.x, objectData.scaling.y, objectData.scaling.z);
		newObject->SetScale(scale);
		//�z��ɓo�^
		objects.push_back(newObject);
	}
}
