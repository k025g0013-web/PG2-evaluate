#pragma once
#include "Player.h"
#include "Enemy.h"
#include <string>

class GameManager {
public:
    // 初期化
    void Initialize() {
        isGameOver_ = false;

        player_.Initialize();
        enemyManager_.Initialize();
    }

    // 更新
    void Update(char *keys) {
        // 敵更新
        enemyManager_.Update(
            player_.GetPosition(),
            player_.GetBullets()
        );

        // 全ての敵の弾のアクセッサからの取得
        std::vector<EnemyBullet *> enemyBullets =
            enemyManager_.GetAllEnemyBullets();

        // 自機更新
        player_.Update(
            keys,
            enemyBullets
        );

        // ゲームオーバー条件
        if (player_.GetHP() <= 0) {
            isGameOver_ = true;
        }
    }

    // 描画
    void Draw() {
        enemyManager_.Draw();
        player_.Draw();
    }

    bool IsGameOver() const { return isGameOver_; }

private:
    Player player_;
    EnemyManager enemyManager_;

    bool isGameOver_ = false;
};
