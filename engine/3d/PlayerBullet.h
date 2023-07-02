#pragma once
#include "Vector3.h"
#include <Model.h>
#include "ViewProjection.h"
#include <Model.h>
#include <WorldTransform.h>
#include <cassert>
#include "Object3d.h"

class PlayerBullet : public Object3d 
{
  public:
	///< summary>
	///������
	///</summary>
	void BulletInitialize(const Vector3& position, const Vector3& velocity);

	///< summary>
	///������
	///</summary>
	void Update();


	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();


  public:
	bool IsDead() const { return isDead_; }
	int GetR() { return r; }
	WorldTransform* GetWorldTransForm() { return &worldTransform_; }

  private:
	//���f��
	Model* bulletModel = nullptr;
	
	//���x
	Vector3 velocity_;
	
	//����
	static const int32_t kLifeTime = 60 * 3;
	//�f�X�喃
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;
	int r = 2;
	
};
