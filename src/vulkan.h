#pragma once

#include <stdint.h>
#include <vulkan/vulkan.h>
#include <stdexcept>

#include <optional>

#include "version.h"

namespace Application
{
    const uint32_t VERSION = MAKE_VERSION(1, 0, 0); 

    class Vulkan 
    {
    public:
        Vulkan(const char *title);
        Vulkan(const Vulkan &) = delete;
        Vulkan(const Vulkan &&) = delete;

        ~Vulkan();
    
    private:
        struct QueueFamilyIndices
        {
            std::optional<uint32_t> graphicsFamily;

            bool isComplete();
        };

        VkResult initInstance();

        VkResult pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        void createLogicalDevice();

        const char *m_title;

        VkInstance m_instance = VK_NULL_HANDLE;
        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkDevice m_device = VK_NULL_HANDLE;
    };
}
