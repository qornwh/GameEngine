#include "GameEngine.h"
#include "TestGameWorld.h"
#include "Actor.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

GameEngine::GameEngine() : world_(nullptr), window_(nullptr)
{
}

GameEngine::~GameEngine()
{
	if (world_ != nullptr)
	{
		delete world_;
	}

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void GameEngine::Init()
{
    /* glfw 초기화 */
    if (!glfwInit())
    {
        assert(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    /* 윈도우 생성 */
    window_ = glfwCreateWindow(1024, 720, "Graphics Viewer", NULL, NULL);
    if (!window_)
    {
        glfwTerminate();
        assert(-1);
    }

    // 더블 버퍼링 활성화
    //glfwSetWindowAttrib(window_, GLFW_DOUBLEBUFFER, GLFW_TRUE);
    /* 현재 윈도우를 컨텍스로 설정 */
    glfwMakeContextCurrent(window_);

    glEnable(GL_DEPTH_TEST);

    /* glew 초기화 */
    auto err = glewInit();
    if (err != GLEW_OK)
    {
        assert(-1);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    OpenWorld();
}

void GameEngine::OpenWorld()
{
	if (world_ != nullptr)
	{
		delete world_;
	}
	world_ = new TestGameWorld();
    world_->Start();
}

void GameEngine::Loop()
{
    if (world_ == nullptr) return;

    while (!glfwWindowShouldClose(window_))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Imgui 프레임 시작
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        world_->Update();
        world_->AfterUpdate();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}
