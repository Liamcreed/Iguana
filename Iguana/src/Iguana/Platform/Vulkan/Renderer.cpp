#include "pch.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>

namespace Iguana
{
    //Validation Layers
    const std::vector<const char *> validationLayers{
        "VK_LAYER_KHRONOS_validation"};
#ifdef DEBUG
    const bool validationLayersEnabled = true;
#else
    const bool validationLayersEnabled = true;
#endif
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData)
    {
        LOG(VULKAN_ERROR) << pCallbackData->pMessage << std::endl;
        return VK_FALSE;
    }
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pDebugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else
        {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks *pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(instance, debugMessenger, pAllocator);
        }
    }
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo)
    {
        createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = DebugCallback;
    }
    std::vector<const char *> GetRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (validationLayersEnabled)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return extensions;
    }

    VkInstance Renderer::m_Instance;
    VkPhysicalDevice Renderer::m_PhysicalDevice = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT Renderer::m_DebugMessenger;
    VkDevice Renderer::m_Device;

    void Renderer::Create()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = NULL;
        appInfo.pApplicationName = "Iguana";
        appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
        appInfo.pEngineName = "Vulkan Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo instanceInfo{};
        instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceInfo.pApplicationInfo = &appInfo;

        auto extensions = GetRequiredExtensions();
        instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        instanceInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (validationLayersEnabled)
        {
            instanceInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            instanceInfo.ppEnabledLayerNames = validationLayers.data();

            populateDebugMessengerCreateInfo(debugCreateInfo);
            instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
        }
        else
        {
            instanceInfo.enabledLayerCount = 0;
            instanceInfo.pNext = nullptr;
        }

        VK_CALL(vkCreateInstance(&instanceInfo, nullptr, &m_Instance));

        if (validationLayersEnabled)
        {
            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            populateDebugMessengerCreateInfo(createInfo);

            VK_CALL(CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger));
        }
        uint32_t physicalDeviceCount = 0;
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, nullptr);

        VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[physicalDeviceCount];
        vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, physicalDevices);

        for (int i = 0; i < physicalDeviceCount; i++)
        {
            VkPhysicalDeviceProperties props;
            vkGetPhysicalDeviceProperties(physicalDevices[i], &props);
            LOG(INFO) << "Device:               " << props.deviceName << std::endl;

            VkPhysicalDeviceFeatures features;
            vkGetPhysicalDeviceFeatures(physicalDevices[i], &features);
            LOG(INFO) << "Geometry Shader:      " << features.geometryShader << std::endl;

            VkPhysicalDeviceMemoryProperties memoryProps;
            vkGetPhysicalDeviceMemoryProperties(physicalDevices[i], &memoryProps);

            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &queueFamilyCount, NULL);
            VkQueueFamilyProperties *queueFamilyProps = new VkQueueFamilyProperties[queueFamilyCount];
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[i], &queueFamilyCount, queueFamilyProps);
            LOG(INFO) << "Queue family count:   " << queueFamilyCount << std::endl;
            delete[] queueFamilyProps;
        }

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.pNext = NULL;
        queueCreateInfo.flags = 0;
        queueCreateInfo.queueFamilyIndex = 0; //TODO: choose correct family index
        queueCreateInfo.queueCount = 4;       //TODO: choose correct count
        queueCreateInfo.pQueuePriorities = NULL;

        VkPhysicalDeviceFeatures usedFeatures = {};

        VkDeviceCreateInfo deviceCreateInfo{};
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pNext = NULL;
        deviceCreateInfo.flags = 0; 
        deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        deviceCreateInfo.queueCreateInfoCount =  0;
        deviceCreateInfo.enabledLayerCount =  0;
        deviceCreateInfo.ppEnabledLayerNames = NULL;
        deviceCreateInfo.enabledExtensionCount = 0;
        deviceCreateInfo.ppEnabledExtensionNames = NULL;
        deviceCreateInfo.pEnabledFeatures =  &usedFeatures;

        VK_CALL(vkCreateDevice(physicalDevices[0], &deviceCreateInfo, NULL, &m_Device));
    }
    void Renderer::Clean()
    {
        if (validationLayersEnabled)
        {
            DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
        }

        vkDestroyInstance(m_Instance, nullptr);
    }
} // namespace Iguana
