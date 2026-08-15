#include "scene.h"
#include <algorithm>
#include <android/log.h>

#define LOG_TAG "AniForge-Scene"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace aniforge {

Scene::Scene(const std::string& name)
    : name(name), initialized(false) {
    LOGI("Scene created: %s", name.c_str());
}

Scene::~Scene() {
    cleanup();
}

std::shared_ptr<GameObject> Scene::createGameObject(const std::string& name) {
    auto gameObject = std::make_shared<GameObject>(name);
    addGameObject(gameObject);
    return gameObject;
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject) {
    if (!gameObject) return;
    
    gameObjects.push_back(gameObject);
    if (initialized) {
        gameObject->start();
    }
    
    LOGI("GameObject added to scene %s: %s", name.c_str(), gameObject->getName().c_str());
}

void Scene::removeGameObject(std::shared_ptr<GameObject> gameObject) {
    if (!gameObject) return;
    
    auto it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
    if (it != gameObjects.end()) {
        gameObject->cleanup();
        gameObjects.erase(it);
        LOGI("GameObject removed from scene %s: %s", name.c_str(), gameObject->getName().c_str());
    }
}

void Scene::removeGameObject(const std::string& name) {
    auto obj = findGameObject(name);
    if (obj) {
        removeGameObject(obj);
    }
}

std::shared_ptr<GameObject> Scene::findGameObject(const std::string& name) {
    for (auto& obj : gameObjects) {
        if (obj->getName() == name) {
            return obj;
        }
    }
    return nullptr;
}

void Scene::start() {
    LOGI("Starting scene: %s with %zu GameObjects", name.c_str(), gameObjects.size());
    
    for (auto& obj : gameObjects) {
        if (obj->isActive()) {
            obj->start();
        }
    }
    
    initialized = true;
}

void Scene::update(float deltaTime) {
    for (auto& obj : gameObjects) {
        if (obj->isActive()) {
            obj->update(deltaTime);
        }
    }
}

void Scene::render() {
    for (auto& obj : gameObjects) {
        if (obj->isActive()) {
            obj->render();
        }
    }
}

void Scene::cleanup() {
    LOGI("Cleaning up scene: %s", name.c_str());
    
    for (auto& obj : gameObjects) {
        obj->cleanup();
    }
    
    gameObjects.clear();
    initialized = false;
}

}
