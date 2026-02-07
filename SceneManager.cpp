#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() = default;

SceneManager::~SceneManager() {
    delete scene_;
}

void SceneManager::Initialize() {
    scene_ = new SceneTitle();
}

void SceneManager::Update(char *keys, char *preKeys) {
    IScene *next = scene_->Update(keys, preKeys);
    if (next != scene_) {
        delete scene_;
        scene_ = next;
    }
}

void SceneManager::Draw() const {
    scene_->Draw();
}
