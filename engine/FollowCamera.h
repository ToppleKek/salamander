#ifndef ENGLISH_GAME_FOLLOWCAMERA_H
#define ENGLISH_GAME_FOLLOWCAMERA_H

#include <memory>
#include "GameObject.h"

#define CAMERA_SPEED 10
#define MAX_CAMREA_SPEED 64

class FollowCamera {
public:
    FollowCamera() = default;
    explicit FollowCamera(std::shared_ptr<GameObject> target);

    void set_target(std::shared_ptr<GameObject> new_target);
    void update();
    [[nodiscard]] const Vector2D &pos() const noexcept;

private:
    std::shared_ptr<GameObject> m_target;
    Vector2D m_pos;
    int m_new_pos_offset{};
    int m_current_pos_offset{};
    int m_last_x{};
};

#endif //ENGLISH_GAME_FOLLOWCAMERA_H
