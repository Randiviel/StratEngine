#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace StratEngine
{
    enum class CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class Camera 
    {
        public:
            Camera();
            ~Camera();

            void MoveCamera(CameraMovement direction, float deltatime);
            void ProcessMouseMovement(float xPos, float yPos);
            glm::mat4 GetViewMatrix();
            inline void ResetFirstTime() { m_firstTime = true; };
        private:
            glm::vec3 m_Position;
            glm::vec3 m_Front;
            glm::vec3 m_Up;
            glm::vec3 m_Right;
            glm::vec3 m_WorldUp;
            float m_Speed = 15.0f;
            float m_FOV = 45.0f;
            float m_Pitch = 0.0f;
            float m_Yaw = -90.0f;
            float m_MouseSensitivity = 0.05f;
            float m_LastX;
            float m_LastY;
            bool m_firstTime = true;

        private:
            void UpdateCameraVectors();
            
    };
}