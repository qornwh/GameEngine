#include "GameEngine.h"

int main(void)
{
    GameEngine::GetInstance().Init();
    GameEngine::GetInstance().Loop();

    return 0;
}

/*
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "GameInstance.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "CameraActor.h"
#include "TestActor.h"

int main(void)
{
    GLFWwindow* window;

    // glfw 초기화
    if (!glfwInit())
    {
        return -1;
    }

    // 윈도우 생성
    window = glfwCreateWindow(1024, 720, "Graphics Viewer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // 윈도우 속성 설정
    glfwSetWindowAttrib(window, GL_CONTEXT_PROFILE_MASK, GLFW_OPENGL_CORE_PROFILE);
    // 3.3 버전으로 지정
    glfwSetWindowAttrib(window, GLEW_VERSION_MAJOR, 3);
    glfwSetWindowAttrib(window, GLEW_VERSION_MINOR, 3);
    // 더블 버퍼링 활성화
    glfwSetWindowAttrib(window, GLFW_DOUBLEBUFFER, GLFW_TRUE);

    // 현재 윈도우를 컨텍스로 설정
    glfwMakeContextCurrent(window);

    // glew 초기화
    auto err = glewInit();
    if (err != GLEW_OK)
    {
        return -1;
    }

    std::vector<Vertex> arr(4);
    arr[0].position = glm::vec3(0.5f, 0.5f, 0.0f);
    arr[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
    arr[2].position = glm::vec3(-0.5f, -0.5f, 0.0f);
    arr[3].position = glm::vec3(-0.5f, 0.5f, 0.0f);

    arr[0].tex_coord = glm::vec2(1.0f, 1.0f);
    arr[1].tex_coord = glm::vec2(1.0f, 0.0f);
    arr[2].tex_coord = glm::vec2(0.0f, 0.0f);
    arr[3].tex_coord = glm::vec2(0.0f, 1.0f);
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    Shader shader;
    shader.Load("Shaders/base.vert", "Shaders/base.frag");

    Model model;
    model.Load("Assets/backpack/backpack.obj");

    CameraActor* actor = new CameraActor();

    actor->SetPosition(glm::vec3(0.f, 0.f, 20.f));

    // 루프
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        shader.SetActive();
        glm::mat4 worldTransform = glm::mat4(1.0f);
        worldTransform = glm::translate(worldTransform, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        worldTransform = glm::scale(worldTransform, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

        glm::mat4 viewProjection = actor->GetPerspective() * actor->GetView();
        shader.SetUniformMat4("uWorldTransform", worldTransform);
        shader.SetUniformMat4("uViewPorjection", viewProjection);
        model.Draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
*/
