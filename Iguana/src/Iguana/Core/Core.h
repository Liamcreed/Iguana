#pragma once
#ifdef NDEBUG
#define RELEASE
#else
#define DEBUG
#endif

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

#define ERROR "\033[1;31m[ERROR]\033[0m " 
#define VULKAN_ERROR "\033[1;31m[VULKAN ERROR]\033[0m " 
#define INFO "\x1B[1;34m[INFO]\033[0m "
#define WARNING "\x1B[1;33m[WARNING]\033[0m " 

#define LOG(type) std::cerr<<type

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args &&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
