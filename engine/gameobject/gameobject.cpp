#include "gameobject.h"
#include <algorithm>
#include <android/log.h>

#define LOG_TAG "AniForge-GameObject"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace aniforge {

GameObject::GameObject(const std::string& name)
    : name(name), active(true), parent(nullptr) {
    LOGI("GameObject created: %s", name.c_str());
}

GameObject::~GameObject() {
    cleanup();
    children.clear();
    LOGI("GameObject destroyed: %s", name.c_str());
}

void GameObject::addChild(std::shared_ptr<GameObject> child) {
    if (!child) return;
    
    child->parent = this;
    children.push_back(child);
    child->start();
    
    LOGI("Child added to %s: %s", name.c_str(), child->getName().c_str());
}

void GameObject::removeChild(std::shared_ptr<GameObject> child) {
    if (!child) return;
    
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end()) {
        child->parent = nullptr;
        children.erase(it);
        LOGI("Child removed from %s: %s", name.c_str(), child->getName().c_str());
    }
}

}
