/**
 * @file JsonLoader.cpp
 * @brief ���x���G�f�B�^Json�t�@�C���ǂݍ��݃N���X
 * @author �J�l�R_�����E�^
 */

#pragma once
#include "Vector4.h"
#pragma warning(push)
#pragma	warning(disable:4282)
#pragma	warning(disable:4283)
#pragma	warning(disable:4285)
#include <json.hpp>
#pragma warning(pop)
#include <string>
#include <vector>
#include "Matrix4.h"

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
	/// <summary>
	/// �t�@�C���ǂݍ���
	/// </summary>
	/// <param name="fileName"></param>
	/// <returns></returns>
	LevelData* LoadFile(const std::string& fileName);
public:
	// �f�t�H���g�̓ǂݍ��݃f�B���N�g��
	static const std::string kDefaultBaseDirectory;
	// �t�@�C���g���q
	static const std::string kExtension;

};