#include "ImGuiActor.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Macro.h"
#include "Actor.h"

ImGuiActor::ImGuiActor() : actor_(nullptr)
{
}

ImGuiActor::~ImGuiActor()
{
}

void ImGuiActor::Draw()
{
    ImGui::Begin("Actor Data");

    if (actor_ != nullptr)
    {
        ImGui::InputFloat3("Translate", glm::value_ptr(actor_->GetPosition()));
        ImGui::InputFloat3("Rotate", glm::value_ptr(actor_->GetRotate()));
        ImGui::InputFloat3("Scale", glm::value_ptr(actor_->GetScale()));
    }
    else
    {
        glm::vec3 zero = vec3Zero;
        ImGui::InputFloat3("Translate", &zero[0]);
        ImGui::InputFloat3("Rotate", &zero[0]);
        ImGui::InputFloat3("Scale", &zero[0]);
    }

    ImGui::End();
}

void ImGuiActor::SetActor(Actor* actor)
{
    actor_ = actor;
}
