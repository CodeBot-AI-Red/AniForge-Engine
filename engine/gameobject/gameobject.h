#ifndef ANIFORGE_GAMEOBJECT_H
#define ANIFORGE_GAMEOBJECT_H

#include <string>
#include <vector>
#include <memory>
#include "../transform/transform.h"

namespace aniforge {

class GameObject {
private:
    std::string name;
    bool active;
    Transform transform;
    std::vector<std::shared_ptr<GameObject>> children;
    GameObject* parent;

public:
    GameObject(const std::string& name = "GameObject");
    virtual ~GameObject();
    
    // Name
    void setName(const std::string& n) { name = n; }
    std::string getName() const { return name; }
    
    // Active state
    void setActive(bool a) { active = a; }
    bool isActive() const { return active; }
    
    // Transform
    Transform& getTransform() { return transform; }
    const Transform& getTransform() const { return transform; }
    
    // Hierarchy
    void addChild(std::shared_ptr<GameObject> child);
    void removeChild(std::shared_ptr<GameObject> child);
    GameObject* getParent() const { return parent; }
    std::vector<std::shared_ptr<GameObject>>& getChildren() { return children; }
    
    // Lifecycle
    virtual void start() {}
    virtual void update(float deltaTime) {}
    virtual void render() {}
    virtual void cleanup() {}
    
    // Utility
    void setEnabled(bool enabled) { setActive(enabled); }
    bool getEnabled() const { return isActive(); }
};

}

#endif
