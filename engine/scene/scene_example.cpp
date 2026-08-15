#include "scene_manager.h"
#include <android/log.h>

#define LOG_TAG "AniForge-Example"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace aniforge {

/*
 * EXEMPLO DE COMO USAR O SCENE MANAGER
 * 
 * Este arquivo demonstra como usar o sistema de cenas e game objects
 */

class ExampleGameObject : public GameObject {
public:
    ExampleGameObject(const std::string& name) : GameObject(name) {}
    
    void start() override {
        LOGI("ExampleGameObject started: %s", getName().c_str());
        getTransform().setPosition(0.0f, 0.0f, 0.0f);
    }
    
    void update(float deltaTime) override {
        // Girar o objeto
        getTransform().rotate(45.0f * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    void render() override {
        // Renderizar o objeto
        LOGI("Rendering: %s at position (%.2f, %.2f, %.2f)", 
             getName().c_str(),
             getTransform().getPosition().x,
             getTransform().getPosition().y,
             getTransform().getPosition().z);
    }
    
    void cleanup() override {
        LOGI("ExampleGameObject cleanup: %s", getName().c_str());
    }
};

void createExampleScene() {
    // Obter o SceneManager singleton
    SceneManager* sceneManager = SceneManager::getInstance();
    
    // Criar uma nova cena
    auto scene = sceneManager->createScene("MainScene");
    
    // Criar game objects
    auto cube = std::make_shared<ExampleGameObject>("Cube");
    cube->getTransform().setPosition(0.0f, 0.0f, 0.0f);
    cube->getTransform().setScale(1.0f, 1.0f, 1.0f);
    
    auto sphere = std::make_shared<ExampleGameObject>("Sphere");
    sphere->getTransform().setPosition(2.0f, 0.0f, 0.0f);
    sphere->getTransform().setScale(0.5f, 0.5f, 0.5f);
    
    auto light = std::make_shared<ExampleGameObject>("Light");
    light->getTransform().setPosition(5.0f, 5.0f, 5.0f);
    
    // Adicionar à cena
    scene->addGameObject(cube);
    scene->addGameObject(sphere);
    scene->addGameObject(light);
    
    // Carregar a cena
    sceneManager->loadScene("MainScene");
    
    LOGI("Example scene created with %d game objects", scene->getGameObjectCount());
}

}
