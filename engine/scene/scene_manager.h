#ifndef ANIFORGE_SCENE_MANAGER_H
#define ANIFORGE_SCENE_MANAGER_H

#include <string>
#include <map>
#include <memory>
#include "scene.h"

namespace aniforge {

class SceneManager {
private:
    std::map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> activeScene;
    static SceneManager* instance;
    
    SceneManager();

public:
    ~SceneManager();
    
    static SceneManager* getInstance();
    
    // Scene management
    std::shared_ptr<Scene> createScene(const std::string& name);
    void addScene(const std::string& name, std::shared_ptr<Scene> scene);
    void removeScene(const std::string& name);
    std::shared_ptr<Scene> getScene(const std::string& name);
    
    // Active scene
    void loadScene(const std::string& name);
    std::shared_ptr<Scene> getActiveScene() { return activeScene; }
    
    // Lifecycle
    void update(float deltaTime);
    void render();
    void cleanup();
    
    // Utility
    int getSceneCount() const { return scenes.size(); }
    bool hasScene(const std::string& name) const;
};

}

#endif
