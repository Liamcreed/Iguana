#pragma once
#include <vulkan/vulkan.h>

namespace Iguana
{
    class Renderer
    {
    private:
        static VkInstance m_Instance;
        static VkPhysicalDevice m_PhysicalDevice;
        static VkDevice m_Device;
        static VkDebugUtilsMessengerEXT m_DebugMessenger;
    public:
        static void Create();
        static void Clean();
    };
} // namespace Iguana
