#include "pchstrat.h"

namespace StratEngine{

    Camera::Camera()
    {
        m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
        m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
        m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        UpdateCameraVectors();
    }

    Camera::~Camera()
    {

    }

    void Camera::MoveCamera(CameraMovement direction, float deltatime)
    {
        float velocity = this->m_Speed * deltatime;
        switch(direction)
        {     
            case CameraMovement::FORWARD:
                m_Position += m_Front * velocity;
            break;
            case CameraMovement::BACKWARD:
                m_Position -= m_Front * velocity;
            break;
            case CameraMovement::LEFT:
                m_Position -= m_Right * velocity;
            break;
            case CameraMovement::RIGHT:
                m_Position += m_Right * velocity;
            break;

        }
        UpdateCameraVectors();
    }

    void Camera::ProcessMouseMovement(float xPos, float yPos)
    {
        if(m_firstTime)
        {
            m_LastX = xPos;
            m_LastY = yPos;
            m_firstTime = false;
        }

        float xoffset = xPos - m_LastX;
        float yoffset = m_LastY - yPos;
        xoffset *= m_MouseSensitivity;
        yoffset *= m_MouseSensitivity;

        m_Yaw   += xoffset;
        m_Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (true)
        {
            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        m_LastX = xPos;
        m_LastY = yPos; 
        UpdateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        glm::mat4 view = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        return view;
    }
    void Camera::UpdateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        m_Up    = glm::normalize(glm::cross(m_Right, m_Front));
    }
}
