#include "PlayerBullet.h"
#include <Novice.h>

PlayerBullet::PlayerBullet() {
	position_ = { -100.0f, -100.0f };
	speed_ = 7.5f;
	radius_ = 15.0f;

	// 発射フラグ
	isShoot_ = false;
}

PlayerBullet::~PlayerBullet() {
}

void PlayerBullet::Update() {
	if (isShoot_) {
		// 移動
		position_.x += speed_;

		// 壁判定
		if (position_.x >= 1280.0f + radius_) {
			position_ = { -100.0f, -100.0f };
			isShoot_ = false;
		}
	}
}

void PlayerBullet::Draw() {
	if (isShoot_) {
		// 弾
		Novice::DrawEllipse(
			static_cast<int>(position_.x), static_cast<int>(position_.y),
			static_cast<int>(radius_), static_cast<int>(radius_),
			0.0f, 0xFFFFFFFF, kFillModeSolid
		);
	}
}

void PlayerBullet::Shoot(const Vector2 &startPos) {
	position_ = startPos;
	isShoot_ = true;
}