#include "Scene.h"

IScene *SceneTitle::Update(char *keys, char *preKeys) {
    if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
        return new SceneGame();
    }
    return this;
}

void SceneTitle::Draw() {
    Novice::ScreenPrintf(0, 0, "TITLE - PRESS SPACE");
}

SceneGame::SceneGame() {
    gameManager_.Initialize();
}

IScene *SceneGame::Update(char *keys, char *preKeys) {
    // 参照しないpreKeysを黙らせる
    (void)preKeys;

    gameManager_.Update(keys);
    if (gameManager_.IsGameOver()) {
        return new SceneResult();
    }
    return this;
}

void SceneGame::Draw() {
    gameManager_.Draw();
}

IScene *SceneResult::Update(char *keys, char *preKeys) {
    if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
        return new SceneTitle();
    }
    return this;
}

void SceneResult::Draw() {
    Novice::ScreenPrintf(0, 0, "RESULT");
}
