#include "window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan.h"

Application::Window::Window(const char *title, const Application::Size size)
: m_title(title)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_instance = glfwCreateWindow(size.width, size.height, title, nullptr, nullptr);

    m_vulkan = initVulkan();
}

void Application::Window::mainloop()
{
    while (!glfwWindowShouldClose(m_instance))
    {
        glfwPollEvents();
    }
}

std::shared_ptr<Application::Vulkan> Application::Window::initVulkan()
{
    std::shared_ptr<Vulkan> vulkan(new Vulkan(m_title));
    return vulkan;
}

Application::Window::~Window()
{
    glfwDestroyWindow(m_instance);

    glfwTerminate();
}