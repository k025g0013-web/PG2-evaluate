#pragma once
#include <vector>
#include "common.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"

class Player {
public:
	Player();	// コンストラクト
	~Player();	// デストラクト

	void Initialize();
	void Update(char *keys, std::vector<EnemyBullet *> &enemyBullets);
	void Draw();

	// アクセッサ
	Vector2 GetPosition() const { return position_; }
	float GetRadius() const { return radius_; }
	int GetHP() const { return hp_; }
	const std::vector<PlayerBullet *> &GetBullets() const { return bullets_; }

public:
	Vector2 position_;
	float speed_;
	float radius_;
	
	// 弾
	static const int kBulletMax = 10;
	std::vector<PlayerBullet*> bullets_;
	int shootCoolTime_;

	// 体力
	int hp_;
};