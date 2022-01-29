#include "FollowCamera.h"
#include "Logger.h"

FollowCamera::FollowCamera(std::shared_ptr<GameObject> target) : m_target{std::move(target)} {}

void FollowCamera::set_target(std::shared_ptr<GameObject> new_target) {
    m_target = std::move(new_target);
}

void FollowCamera::update() {
    if (m_target != nullptr) {
        int dx = m_last_x - m_target->pos().x();

        // Don't move the camera if the target isn't moving
        if (dx == 0) {
            m_pos.set_x(m_target->pos().x() + m_current_pos_offset);
            return;
        }

        m_last_x = m_target->pos().x();
        bool left = dx > 0;

        m_new_pos_offset = left ? -1300 : -300;

        if (m_current_pos_offset != m_new_pos_offset)
            m_current_pos_offset = m_current_pos_offset < m_new_pos_offset ? m_current_pos_offset += CAMERA_SPEED : m_current_pos_offset -= CAMERA_SPEED;

        m_pos.set_x(m_target->pos().x() + m_current_pos_offset);
    }

}

const Vector2D &FollowCamera::pos() const noexcept {
    return m_pos;
}
