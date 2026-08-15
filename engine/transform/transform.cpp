#include "transform.h"
#include <glm/gtx/quaternion.hpp>

namespace aniforge {

Transform::Transform()
    : position(0.0f, 0.0f, 0.0f),
      rotation(1.0f, 0.0f, 0.0f, 0.0f),
      scale(1.0f, 1.0f, 1.0f),
      modelMatrix(1.0f),
      dirty(true) {
}

void Transform::updateMatrix() {
    if (!dirty) return;
    
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    dirty = false;
}

void Transform::setPosition(const glm::vec3& pos) {
    position = pos;
    dirty = true;
}

void Transform::setPosition(float x, float y, float z) {
    setPosition(glm::vec3(x, y, z));
}

void Transform::translate(const glm::vec3& offset) {
    position += offset;
    dirty = true;
}

void Transform::setRotation(const glm::quat& rot) {
    rotation = glm::normalize(rot);
    dirty = true;
}

void Transform::setRotation(float x, float y, float z) {
    glm::quat qx = glm::angleAxis(glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qy = glm::angleAxis(glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat qz = glm::angleAxis(glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    setRotation(qz * qy * qx);
}

void Transform::setRotation(float angle, const glm::vec3& axis) {
    setRotation(glm::angleAxis(glm::radians(angle), glm::normalize(axis)));
}

void Transform::rotate(float angle, const glm::vec3& axis) {
    glm::quat delta = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    rotation = glm::normalize(delta * rotation);
    dirty = true;
}

void Transform::setScale(const glm::vec3& s) {
    scale = s;
    dirty = true;
}

void Transform::setScale(float x, float y, float z) {
    setScale(glm::vec3(x, y, z));
}

const glm::mat4& Transform::getModelMatrix() {
    updateMatrix();
    return modelMatrix;
}

glm::vec3 Transform::getForward() const {
    return glm::normalize(glm::vec3(
        -2.0f * (rotation.x * rotation.z - rotation.w * rotation.y),
        -2.0f * (rotation.y * rotation.z + rotation.w * rotation.x),
        -(1.0f - 2.0f * (rotation.x * rotation.x + rotation.y * rotation.y))
    ));
}

glm::vec3 Transform::getRight() const {
    return glm::normalize(glm::vec3(
        1.0f - 2.0f * (rotation.y * rotation.y + rotation.z * rotation.z),
        2.0f * (rotation.x * rotation.y + rotation.w * rotation.z),
        2.0f * (rotation.x * rotation.z - rotation.w * rotation.y)
    ));
}

glm::vec3 Transform::getUp() const {
    return glm::normalize(glm::vec3(
        2.0f * (rotation.x * rotation.y - rotation.w * rotation.z),
        1.0f - 2.0f * (rotation.x * rotation.x + rotation.z * rotation.z),
        2.0f * (rotation.y * rotation.z + rotation.w * rotation.x)
    ));
}

}
