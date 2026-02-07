#pragma once
#include <vector>
#include "common.h"

#pragma region EnemyBullet
class EnemyBullet {
public:
	EnemyBullet();		// コンストラクト
	~EnemyBullet();		// デストラクト

	void Update();
	void Draw();

	// 発射
	void Shoot(const Vector2 &startPos, const Vector2 &targetPos);
	
	// アクセッサ
	bool IsShoot() const { return isShoot_; }
	Vector2 GetPosition() const { return position_; }
	float GetRadius() const { return radius_; }
	
	// 発射フラグを下す
	void Deactivate() { isShoot_ = false; }

public:
	Vector2 position_;
	Vector2 velocity_;
	float speed_;
	float radius_;

	// 発射フラグ
	bool isShoot_;
};

#pragma region EnemyBulletManager
class EnemyBulletManager {
public:
	EnemyBulletManager();	// コンストラクト

	void Update();
	void Draw();

	// 発射
	void Shoot(const Vector2 &startPos, const Vector2 &targetPos);

public:
	// 最大数
	static const int kMaxBullet = 64;
	std::vector<EnemyBullet> bullets_;
};
#pragma endregion