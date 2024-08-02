#include "core.h"
#include "Camera.h"
#include <format>
#include "mesh.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

auto screen_info = Screen_info(SCR_WIDTH, SCR_HEIGHT);
auto camera = Camera(screen_info,glm::vec3(0.0f, 0.0f,  3.0f));

GLFWwindow* glInit(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
#pragma endregion
    // glfw window creation
#pragma region
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }
    return window;
}

void call_backs_and_settings(GLFWwindow* window){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
}

int main(){
    //Init resources and functions
    auto window = glInit();
    call_backs_and_settings(window);

    //Create shader
    auto shader = Shader("../shaders/vs1.glsl","../shaders/fs1.glsl");
    auto shader1 = Shader("../shaders/vs2.glsl","../shaders/fs2.glsl");

    //Create texture
    auto texture = Texture("../assets/container.jpg",0);
    shader.setInt("Sampler",0);

    auto light_pos = glm::vec3(0.0f,0.9f,0.0f);

    //Create mvp translations
    glm::mat4 model1(1.0f);
    glm::mat4 projection(1.0f);
    //shader.setMat4("model",model);
    glm::mat4 model2(1.0f);
    model2 = glm::translate(model1,light_pos);
    model2 = glm::scale(model2, glm::vec3(0.2f));

    //Create the model
    unsigned int a[] = {3,2,3};
    auto vertex1 = VertexArray(vertices,sizeof(vertices),indices,sizeof(indices),a,3);
    auto vertex2 = VertexArray(vertices,sizeof(vertices),indices,sizeof(indices),a,3);

    //Main loop
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        projection = glm::perspective(glm::radians(camera.get_fov()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.use();
        shader.setVec3("objectColor",glm::vec3(1.0f, 0.5f, 0.31f));
        shader.setVec3("lightColor",glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setMat4("projection",projection);
        auto view = camera.view_matrix();
        shader.setMat4("view",view);
        shader.setMat4("model",model1);
        shader.setVec3("lightPos",light_pos);
        shader.setVec3("viewPos",camera.get_pos());
        vertex1.bindVBO();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/(8*sizeof(float)));

        shader1.use();
        shader1.setMat4("model",model2);
        shader1.setMat4("projection",projection);
        shader1.setMat4("view",camera.view_matrix());
        shader1.setVec3("lightColor",glm::vec3(1.0f, 1.0f, 1.0f));

        //std::cout << std::format("x:{} y:{} z:{}",camera.get_pos().x,camera.get_pos().y,camera.get_pos().z) << std::endl;
        vertex2.bindVBO();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/(8*sizeof(float)));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}


void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    auto currentFrame = static_cast<float>(glfwGetTime());
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.move_forward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.move_backward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.move_left(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.move_right(deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.camera_mouse_callback(xpos,ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.camera_scroll_callback(xoffset,yoffset);
}
