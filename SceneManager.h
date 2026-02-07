#pragma once
#include <Novice.h>
#include "GameManager.h"

class SceneTitle;
class SceneGame;
class SceneResult;

// シーン切り替え
#pragma region シーン切り替え
class IScene {
public:
	virtual ~IScene() = default;

	// 次のシーンを返す
	virtual IScene *Update(char *keys, char *preKeys) = 0;
	virtual void Draw() = 0;
};
#pragma endregion

// SceneManager
#pragma region SceneManager
class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void Initialize();
    void Update(char *keys, char *preKeys);
    void Draw() const;

private:
    IScene *scene_ = nullptr;
};
#pragma endregion