#pragma once
#include <vulkan/vulkan.h>

namespace Iguana
{
    class Renderer
    {
    private:
        static VkInstance mInstance;
        static VkPhysicalDevice mPhysicalDevice;
        static VkDevice mDevice;
        static VkDebugUtilsMessengerEXT mDebugMessenger;
    public:
        static void Create();
        static void Clean();
    };
} // namespace Iguana
