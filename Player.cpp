#include "player.h"
#include <Novice.h>

Player::Player() {
	position_ = { 640.0f, 320.0f };
	speed_ = 5.0f;
	radius_ = 15.0f;

	// 体力
	hp_ = 5;

	// 弾
	shootCoolTime_ = 0;
	for (int i = 0; i < kBulletMax; i++) {
		bullets_.push_back(new PlayerBullet());
	}
}

Player::~Player() {
	for (PlayerBullet *bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize() {
	position_ = { 640.0f, 320.0f };
	hp_ = 5;
};

void Player::Update(char *keys, std::vector<EnemyBullet *> &enemyBullets) {
	// 弾発射のクールダウン
	if (shootCoolTime_ > 0) {
		shootCoolTime_--;
	}

	// 弾発射入力
	if (keys[DIK_SPACE] && shootCoolTime_ == 0) {
		for (PlayerBullet *bullet : bullets_) {
			if (!bullet->isShoot_) {
				bullet->position_ = position_;
				bullet->isShoot_ = true;
				shootCoolTime_ = 10;
				break;
			}
		}
	}

	// 移動入力
	if (keys[DIK_W]) position_.y -= speed_;
	if (keys[DIK_A]) position_.x -= speed_;
	if (keys[DIK_S]) position_.y += speed_;
	if (keys[DIK_D]) position_.x += speed_;

	// 左右壁
	if (position_.x < radius_) {
		position_.x = radius_;
	} else if (position_.x > 1280.0f - radius_) {
		position_.x = 1280.0f - radius_;
	}

	// 上下壁
	if (position_.y < radius_) {
		position_.y = radius_;
	} else if (position_.y > 720.0f - radius_) {
		position_.y = 720.0f - radius_;
	}

	// 弾更新
	for (PlayerBullet *bullet : bullets_) {
		if (!bullet->IsShoot()) continue;
		bullet->Update();
	}

	// 敵の弾→自機の当たり判定
	for (EnemyBullet *bullet : enemyBullets) {
		if (!bullet->IsShoot()) continue;

		if (common::IsHitCirle(
			position_, radius_,							// 自機
			bullet->GetPosition(), bullet->GetRadius()	// 敵の弾
		)) {
			// 発射フラグを下す
			bullet->Deactivate();
			hp_--;
			break;
		}
	}
}

void Player::Draw() {
	// 自機弾
	for (PlayerBullet *bullet : bullets_) {
		if (bullet && bullet->IsShoot()) {
			bullet->Draw();
		}
	}

	// 自機
	Novice::DrawEllipse(
		static_cast<int>(position_.x), static_cast<int>(position_.y),
		static_cast<int>(radius_), static_cast<int>(radius_),
		0.0f, 0xFFFFFFFF, kFillModeSolid
	);

	// HP
	Novice::ScreenPrintf(0, 0, "Player HP : %d", hp_);
}