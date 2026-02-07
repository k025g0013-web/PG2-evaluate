#pragma once
#include <Novice.h>
#include "GameManager.h"
#include "SceneManager.h"

class SceneTitle;
class SceneGame;
class SceneResult;

// タイトル
class SceneTitle : public IScene {
public:
    IScene *Update(char *keys, char *preKeys) override;
    void Draw() override;
};

// ゲーム本編
class SceneGame : public IScene {
public:
    SceneGame();
    IScene *Update(char *keys, char *preKeys) override;
    void Draw() override;

private:
    GameManager gameManager_;
};

// リザルト
class SceneResult : public IScene {
public:
    IScene *Update(char *keys, char *preKeys) override;
    void Draw() override;
};