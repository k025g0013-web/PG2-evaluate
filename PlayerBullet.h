#pragma once
#include "common.h"

class PlayerBullet {
public:
	PlayerBullet();		// コンストラクト
	~PlayerBullet();	// デストラクト

	void Update();
	void Draw();

	// アクセッサ
	bool IsShoot() const { return isShoot_; }
	Vector2 GetPosition() const { return position_; }
	float GetRadius() const { return radius_; }

	// 発射
	void Shoot(const Vector2& startPos);

	// 発射フラグを下す
	void Deactivate() { isShoot_ = false; }

private:
	Vector2 position_;
	float speed_;
	float radius_;

	// 発射フラグ
	bool isShoot_;
};