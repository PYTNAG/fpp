#include "vulkan.h"

#include <vector>
#include <optional>

Application::Vulkan::QueueFamilyIndices Application::Vulkan::findQueueFamilies(VkPhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    std::vector<VkQueueFamilyProperties> queueFamilies;

    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    if (!queueFamilyCount)
    {
        throw std::runtime_error("failed to get physical device's queue families properties");
    }
    else
    {
        queueFamilies.resize(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto &queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                indices.graphicsFamily = i;
                break;
            }

            i++;
        }
    }

    return indices;
}

bool Application::Vulkan::QueueFamilyIndices::isComplete()
{
    return graphicsFamily.has_value();
}

Application::Vulkan::Vulkan(const char *title) : m_title(title)
{
    if (initInstance() == VK_SUCCESS)
    {
        pickPhysicalDevice();
        createLogicalDevice();
    }
    else
    {
        throw std::runtime_error("failed to create vulkan instance");
    }
}

VkResult Application::Vulkan::initInstance()
{
    VkInstanceCreateInfo instanceInfo{};
    VkApplicationInfo appInfo{};

    // app info
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = m_title;
    appInfo.applicationVersion = Application::VERSION;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // instance info
    instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;

    return vkCreateInstance(&instanceInfo, nullptr, &m_instance);
}

bool Application::Vulkan::isDeviceSuitable(VkPhysicalDevice device)
{
    QueueFamilyIndices indices = findQueueFamilies(device);

    return indices.isComplete();
}

VkResult Application::Vulkan::pickPhysicalDevice()
{
    uint32_t physicalDeviceCount = 0U;
    std::vector<VkPhysicalDevice> devices;

    VkResult result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr);

    if (!physicalDeviceCount)
    {
        throw std::runtime_error("failed to find GPUs with Vulkan support");
    }

    if (result == VK_SUCCESS)
    {
        devices.resize(physicalDeviceCount);
        result = vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, devices.data());

        for (const VkPhysicalDevice &device : devices)
        {
            if (isDeviceSuitable(device))
            {
                m_physicalDevice = device;
                break;
            }
        }

        if (m_physicalDevice == VK_NULL_HANDLE)
        {
            throw std::runtime_error("failed to find a suitable GPU");
        }
    }

    return result;
}

void Application::Vulkan::createLogicalDevice()
{
    QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);
    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    
}

Application::Vulkan::~Vulkan()
{
    vkDestroyInstance(m_instance, nullptr);
}