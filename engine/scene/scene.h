#ifndef ANIFORGE_SCENE_H
#define ANIFORGE_SCENE_H

#include <string>
#include <vector>
#include <memory>
#include "../gameobject/gameobject.h"

namespace aniforge {

class Scene {
private:
    std::string name;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    bool initialized;

public:
    Scene(const std::string& name = "Scene");
    virtual ~Scene();
    
    // Name
    void setName(const std::string& n) { name = n; }
    std::string getName() const { return name; }
    
    // GameObject management
    std::shared_ptr<GameObject> createGameObject(const std::string& name = "GameObject");
    void addGameObject(std::shared_ptr<GameObject> gameObject);
    void removeGameObject(std::shared_ptr<GameObject> gameObject);
    void removeGameObject(const std::string& name);
    
    std::shared_ptr<GameObject> findGameObject(const std::string& name);
    std::vector<std::shared_ptr<GameObject>>& getGameObjects() { return gameObjects; }
    
    // Lifecycle
    virtual void start();
    virtual void update(float deltaTime);
    virtual void render();
    virtual void cleanup();
    
    bool isInitialized() const { return initialized; }
    int getGameObjectCount() const { return gameObjects.size(); }
};

}

#endif
