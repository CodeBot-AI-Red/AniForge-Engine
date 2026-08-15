#include "scene_manager.h"
#include <android/log.h>

#define LOG_TAG "AniForge-SceneManager"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace aniforge {

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager() : activeScene(nullptr) {
    LOGI("SceneManager initialized");
}

SceneManager::~SceneManager() {
    cleanup();
}

SceneManager* SceneManager::getInstance() {
    if (!instance) {
        instance = new SceneManager();
    }
    return instance;
}

std::shared_ptr<Scene> SceneManager::createScene(const std::string& name) {
    auto scene = std::make_shared<Scene>(name);
    addScene(name, scene);
    return scene;
}

void SceneManager::addScene(const std::string& name, std::shared_ptr<Scene> scene) {
    if (!scene) {
        LOGE("Cannot add null scene");
        return;
    }
    
    scenes[name] = scene;
    LOGI("Scene added: %s (total: %zu)", name.c_str(), scenes.size());
}

void SceneManager::removeScene(const std::string& name) {
    auto it = scenes.find(name);
    if (it != scenes.end()) {
        if (activeScene == it->second) {
            activeScene = nullptr;
        }
        it->second->cleanup();
        scenes.erase(it);
        LOGI("Scene removed: %s", name.c_str());
    }
}

std::shared_ptr<Scene> SceneManager::getScene(const std::string& name) {
    auto it = scenes.find(name);
    if (it != scenes.end()) {
        return it->second;
    }
    LOGE("Scene not found: %s", name.c_str());
    return nullptr;
}

void SceneManager::loadScene(const std::string& name) {
    auto scene = getScene(name);
    if (!scene) {
        LOGE("Cannot load scene: %s (not found)", name.c_str());
        return;
    }
    
    if (activeScene) {
        activeScene->cleanup();
    }
    
    activeScene = scene;
    activeScene->start();
    LOGI("Scene loaded: %s", name.c_str());
}

void SceneManager::update(float deltaTime) {
    if (activeScene) {
        activeScene->update(deltaTime);
    }
}

void SceneManager::render() {
    if (activeScene) {
        activeScene->render();
    }
}

void SceneManager::cleanup() {
    LOGI("Cleaning up SceneManager");
    
    for (auto& pair : scenes) {
        pair.second->cleanup();
    }
    
    scenes.clear();
    activeScene = nullptr;
}

bool SceneManager::hasScene(const std::string& name) const {
    return scenes.find(name) != scenes.end();
}

}
