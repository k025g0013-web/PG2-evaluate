#include "EnemyBullet.h"
#include <Novice.h>

#pragma region EnemyBullet
EnemyBullet::EnemyBullet() {
	position_ = { -100.0f, -100.0f };
	velocity_ = { 0.0f, 0.0f };
	speed_ = 7.5f;
	radius_ = 15.0f;

	// 発射フラグ
	isShoot_ = false;
}

EnemyBullet::~EnemyBullet() {
}

void EnemyBullet::Shoot(const Vector2 &startPos, const Vector2 &targetPos) {
	position_ = startPos;	// 発射開始地点	
	velocity_ = targetPos;	// 目標地点

	// 発射フラグ
	isShoot_ = true;
}

void EnemyBullet::Update() {
	// 未発射時は関数処理を終了
	if (!isShoot_) return;

	// 移動
	position_.x += velocity_.x * speed_;
	position_.y += velocity_.y * speed_;

	// 壁判定
	if (position_.x < -radius_ || position_.x > 1280.0f + radius_ ||
		position_.y < -radius_ || position_.y > 720.0f + radius_ ) {
		isShoot_ = false;
	}
}

void EnemyBullet::Draw() {
	// 未発射時は関数処理を終了
	if (!isShoot_) return;

	// 弾
	Novice::DrawEllipse(
		static_cast<int>(position_.x), static_cast<int>(position_.y),
		static_cast<int>(radius_), static_cast<int>(radius_),
		0.0f, 0xFF0000FF, kFillModeSolid
	);
}
#pragma endregion

#pragma region EnemyBullet
EnemyBulletManager::EnemyBulletManager() {
	bullets_.resize(kMaxBullet);
}

void EnemyBulletManager::Shoot(const Vector2 &startPos, const Vector2 &targetPos) {
	// 各敵の弾発射
	for (auto &bullet : bullets_) {
		if (!bullet.isShoot_) {
			bullet.Shoot(startPos, targetPos);
			break;
		}
	}
}

void EnemyBulletManager::Update() {
	// 更新
	for (auto &bullet : bullets_) {
		bullet.Update();
	}
}

void EnemyBulletManager::Draw() {
	for (auto &bullet : bullets_) {
		bullet.Draw();
	}
}
#pragma endregion