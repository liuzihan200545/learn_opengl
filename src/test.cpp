#include <core.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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


int main()
{
    GLFWwindow *window = glInit();

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    auto shader = Shader("../src/shader1.glsl","../src/shader.glsl");
    shader.use();

    //auto t1 = Texture("../assets/container.jpg",0);
    auto t2 = Texture("../assets/wall.jpg",1);
    shader.setInt("Sampler1",1);
    //shader.setInt("Sampler2",1);

    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view(1.0f);
    // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    shader.setMat4("model",model);
    shader.setMat4("view",view);
    shader.setMat4("projection",projection);

    unsigned int a[] = {3,3,2};
    auto vertex = VertexArray(vertices,sizeof(vertices),indices,sizeof(indices),a,3);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        vertex.bindVAO();

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}