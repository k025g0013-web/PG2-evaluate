#include "Enemy.h"
#include <Novice.h>

#pragma region Enemy
Enemy::Enemy() {
	position_ = { -1000.0f, 0.0f };
	speed_ = -2.5f;
	radius_ = 32.0f;

	// 生存フラグ
	isAlive_ = false;

	// 弾
	shootCoolTime_ = 0;
	for (int i = 0; i < kBulletMax; i++) {
		bullets_.push_back(new EnemyBullet());
	}
}

Enemy::~Enemy() {
}

void Enemy::Activate(const Vector2 &spawnPos) {
	position_ = spawnPos;
	isAlive_ = true;
	
	for (EnemyBullet *bullet : bullets_) {
		bullet->Deactivate();
	}
};

void Enemy::Update(const Vector2 &playerPos, std::vector<PlayerBullet *> playerBullets) {
	// 弾の更新
	for (EnemyBullet *bullet : bullets_) {
		bullet->Update();
	}

	// 死亡時は関数処理を終了
	if (!isAlive_) return;

	// 弾発射のクールダウン
	if (shootCoolTime_ > 0) {
		shootCoolTime_--;
	}

	// 移動
	position_.x += speed_;

	// 壁処理
	if (position_.x < -radius_) {
		position_ = { -1000.0f, 0.0f };
		isAlive_ = false;
	}

	// 弾の発射
	if (shootCoolTime_ == 0) {
		for (EnemyBullet *bullet : bullets_) {
			if (!bullet->IsShoot()) {
				// 敵とプレイヤーの距離を計算
				Vector2 dir = {
					playerPos.x - position_.x,
					playerPos.y - position_.y
				};

				// ベクトルの計算
				float length =
					sqrtf(dir.x * dir.x + dir.y * dir.y);

				dir.x /= length;
				dir.y /= length;

				// 発射
				bullet->Shoot(position_, dir);
				shootCoolTime_ = 60;	// クールタイム
				break;
			}
		}
	}

	// 自機の弾→敵の当たり判定
	for (PlayerBullet * bullet: playerBullets) {
		if (!bullet->IsShoot()) continue;

		if (common::IsHitCirle(
			position_, radius_,							// 敵
			bullet->GetPosition(), bullet->GetRadius()	// 自機の弾
		)) {
			// 発射フラグを下す
			bullet->Deactivate();

			// 生存フラグを下す
			position_ = { -1000.0f, 0.0f };
			isAlive_ = false;
			break;
		}
	}
}

void Enemy::Draw() {
	// 弾
	for (EnemyBullet *bullet : bullets_) {
		bullet->Draw();
	}

	// 死亡時は関数処理を終了
	if (!isAlive_) return;

	// 敵
	Novice::DrawEllipse(
		static_cast<int>(position_.x), static_cast<int>(position_.y),
		static_cast<int>(radius_), static_cast<int>(radius_),
		0.0f, 0xFF0000FF, kFillModeSolid
	);
}
#pragma endregion

#pragma region EnemyManager
void EnemyManager::Initialize() {
	spawnInterval_ = 90;
	spawnTimer_ = spawnInterval_;
}

void EnemyManager::SpawnEnemy() {
	// スポーンタイマー
	if (spawnTimer_ > 0) {
		spawnTimer_--;
		return;
	}

	for (auto &enemy : enemies_) {
		if (!enemy.IsAlive()) {
			// 敵の半径取得
			float enemyRadius = enemy.GetRadius();

			// 生成場所
			Vector2 spawnPos = {
				1280.0f,
				common::RandHelperFloat(	// 乱数生成
					enemyRadius, 720.0f - enemyRadius
				)
			};

			// 敵の呼び出し
			enemy.Activate(spawnPos);

			// タイマーリセット
			spawnTimer_ = spawnInterval_;
			break;
		}
	}
}

void EnemyManager::Update(const Vector2 &playerPos, std::vector<PlayerBullet *> playerBullets) {
	// 生成
	SpawnEnemy();

	// 更新
	for (auto &enemy : enemies_) {
		enemy.Update(playerPos, playerBullets);
	}
}

void EnemyManager::Draw() {
	for (auto &enemy : enemies_) {
		if (!enemy.IsAlive()) continue;
		enemy.Draw();
	}
}
#pragma endregion