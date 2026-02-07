#pragma once
#include <vector>
#include <array>
#include "common.h"
#include "EnemyBullet.h"
#include "PlayerBullet.h"

#pragma region Enemy
class Enemy {
public:
	Enemy();	// コンストラクト
	~Enemy();	// デストラクト

	void Update(const Vector2 &playerPos, std::vector<PlayerBullet *> playerBullets);
	void Draw();

	// 敵の呼び出し
	void Activate(const Vector2 &spawnPos);
	
	// アクセッサ
	float GetRadius() const { return radius_; }
	bool IsAlive() const { return isAlive_; }
	const std::vector<EnemyBullet *> &GetBullets() const { return bullets_; }

private:
	Vector2 position_;
	float speed_;
	float radius_;

	// 弾
	static const int kBulletMax = 5;
	std::vector<EnemyBullet*> bullets_;
	int shootCoolTime_;

	// 生存フラグ
	bool isAlive_ = false;
};
#pragma endregion

#pragma region EnemyManager
class EnemyManager {
public:
	EnemyManager() {	// コンストラクト
		spawnTimer_ = 0;
		spawnInterval_ = 0;
	}

	// 敵の最大数
	static const int kMaxEnemy = 16;

	void Initialize();
	void Update(const Vector2 &playerPos, std::vector<PlayerBullet *> playerBullets);
	void Draw();

	// 全ての敵の弾のアクセッサ
	std::vector<EnemyBullet *> GetAllEnemyBullets() {
		std::vector<EnemyBullet *> result;

		for (auto &enemy : enemies_) {
			for (EnemyBullet *bullet : enemy.GetBullets()) {
				result.push_back(bullet);
			}
		}

		return result;
	}

private:
	// 敵のスポーン
	void SpawnEnemy();

	// 敵
	Enemy enemies_[kMaxEnemy];

	// スポーン管理用タイマー
	int spawnTimer_;
	int spawnInterval_;
};
#pragma endregion