#pragma once
#include "Vector4.h"
#include <json.hpp>
#include <string>
#include <vector>

// ���x���f�[�^
struct LevelData {

	struct ObjectData {
		// �t�@�C����
		std::string fileName;
		// ���s�ړ�
		Vector4 translation;
		// ��]�p
		Vector4 rotation;
		// �X�P�[�����O
		Vector4 scaling;
	};

	// �I�u�W�F�N�g�z��
	std::vector<ObjectData> objects;
};

class JsonLoader {
public:
	//�t�@�C���ǂݍ���
	LevelData* LoadFile(const std::string& fileName);
public:
	// �f�t�H���g�̓ǂݍ��݃f�B���N�g��
	static const std::string kDefaultBaseDirectory;
	// �t�@�C���g���q
	static const std::string kExtension;

};