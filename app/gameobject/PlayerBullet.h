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
	void BulletInitialize(const Vector3& velocity);

	///< summary>
	///������
	///</summary>
	void Update();
	void HomingVec(Vector3 pos);


	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision(const CollisionInfo& info) override;


  public:
	bool IsDead() const { return isDead_; }
	WorldTransform* GetWorldTransForm() { return &worldTransform_; }
	bool GetIsHoming() { return isHoming; }
	void SetisHoming(bool isHoming_) { isHoming = isHoming_; }
	void SetLock(Object3d* obj) { lockObj = obj; }

  private:
	//���f��
	Model* bulletModel = nullptr;
	
	//���x
	Vector3 velocity_;
	
	//����
	static const int32_t kLifeTime = 60 * 8;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;
	bool isHoming = false;
	Object3d* lockObj = nullptr;
};
