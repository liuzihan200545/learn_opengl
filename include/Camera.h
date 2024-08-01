#include <core.h>

float lastFrame;

class Screen_info{
public:
    Screen_info(){};
    Screen_info(float screen_width, float screen_height): screen_height(screen_height), screen_width(screen_width){}
    float screen_width;
    float screen_height;
};

class Camera{
public:
    Camera(Screen_info screen, glm::vec3 cameraPos, glm::vec3 cameraFront = glm::vec3 (0.0f, 0.0f, -1.0f));

    glm::mat4 view_matrix(){
        return glm::lookAt(m_cameraPos,m_cameraPos+m_cameraFront,m_cameraUp);
    }

    void move_forward(float delta_time){
        m_cameraPos += m_cameraFront * delta_time * camera_speed;
    }

    void move_backward(float delta_time){
        m_cameraPos -= m_cameraFront * delta_time * camera_speed;
    }

    void move_left(float delta_time){
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * camera_speed * delta_time;
    }

    void move_right(float delta_time){
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * camera_speed * delta_time;
    }



    void camera_mouse_callback(double xpos, double ypos){
        if(firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.05;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        m_cameraFront = glm::normalize(front);
    }

    void camera_scroll_callback(double xoffset, double yoffset){
        if(fov >= 1.0f && fov <= 45.0f)
            fov -= yoffset;
        if(fov <= 1.0f)
            fov = 1.0f;
        if(fov >= 45.0f)
            fov = 45.0f;
    }

    float get_fov()const{
        return fov;
    }

private:
    Screen_info m_screen;

    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp = glm::vec3 (0.0f,1.0f,0.0f);
    float camera_speed = 2.5f;
    bool firstMouse = true;
    float pitch = 0;
    float yaw = -90;
    float fov = 45.0f;
    float lastX;
    float lastY;
};

Camera::Camera(Screen_info screen, glm::vec3 cameraPos, glm::vec3 cameraFront):
    m_screen(screen),
    m_cameraPos(cameraPos),
    m_cameraFront(cameraFront),
    lastX(screen.screen_width/2),
    lastY(screen.screen_height/2){}


