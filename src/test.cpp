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
    //
    glm::mat4 trans(1.0f);
    glm::mat4 trans1(1.0f);

    trans1 = glm::translate(trans1, glm::vec3(0.0f, 0.0f, 0.0f));
    trans1 = glm::scale(trans1,glm::vec3(0.5f,0.3f,1.3f));

    unsigned int a[] = {3,3,2};
    auto vertex = VertexArray(vertices,sizeof(vertices),indices,sizeof(indices),a,3);



    auto vertex1 = VertexArray(vertices,sizeof(vertices),indices,sizeof(indices),a,3);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        vertex.bindVAO();
        trans = glm::translate(trans, glm::vec3(0.0f, 0.0f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime()/1000.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.setMat4("trans",trans);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr);

        vertex1.bindVAO();
        shader.setMat4("trans",trans1);
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