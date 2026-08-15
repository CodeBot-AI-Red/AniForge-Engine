#ifndef ANIFORGE_TRANSFORM_H
#define ANIFORGE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace aniforge {

class Transform {
private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    
    glm::mat4 modelMatrix;
    bool dirty;
    
    void updateMatrix();

public:
    Transform();
    
    // Position
    void setPosition(const glm::vec3& pos);
    void setPosition(float x, float y, float z);
    glm::vec3 getPosition() const { return position; }
    void translate(const glm::vec3& offset);
    
    // Rotation
    void setRotation(const glm::quat& rot);
    void setRotation(float x, float y, float z);
    void setRotation(float angle, const glm::vec3& axis);
    glm::quat getRotation() const { return rotation; }
    void rotate(float angle, const glm::vec3& axis);
    
    // Scale
    void setScale(const glm::vec3& s);
    void setScale(float x, float y, float z);
    void setScale(float s) { setScale(s, s, s); }
    glm::vec3 getScale() const { return scale; }
    
    // Matrix
    const glm::mat4& getModelMatrix();
    
    // Direction vectors
    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;
};

}

#endif
