#pragma once

#include <stdint.h>
#include <memory>
#include <GLFW/glfw3.h>

#include "vulkan.h"

namespace Application
{
    struct Size
    {
        int width, height;

        Size(int width, int height) : width(width), height(height) {}
    };

    class Window
    {
    public:
        Window(const char *title, const Size size);
        Window(const Window &) = delete;
        Window(const Window &&) = delete;

        ~Window();

        void mainloop();

    private:
        std::shared_ptr<Application::Vulkan> initVulkan();

        GLFWwindow *m_instance = nullptr;
        std::shared_ptr<Vulkan> m_vulkan = nullptr;

        const char *m_title = nullptr;
    };
}
