#ifndef ANIFORGE_ENGINE_H
#define ANIFORGE_ENGINE_H

namespace aniforge {
    
    class Engine {
    private:
        bool initialized;

    public:
        Engine();
        void init();
        void update(float deltaTime);
        void render();
        void cleanup();
        bool isInitialized() const { return initialized; }
    };

}

#endif
