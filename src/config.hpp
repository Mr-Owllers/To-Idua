#include <iostream>

// check if the system is unix or windows
#if defined(_WIN32) || defined(_WIN64)
    #define OS_WINDOWS 1
    #define OS_UNIX 0
    #include <windows.h>
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    #define OS_UNIX 1
    #define OS_WINDOWS 0
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
#else
    #error "Unknown OS"
#endif

// get the home directory for unix
#if OS_UNIX
    std::string HOME = getpwuid(getuid())->pw_dir;
// get the home directory for windows
#elif OS_WINDOWS
    std::string HOME = getenv("APPDATA");
#endif

// path to the json file
#if defined(_WIN32) || defined(_WIN64)
    std:string file = HOME + "Roaming\\to-idua\\ideas.json";
    #define PATH file.c_str()
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    std::string file = HOME + "/.config/to-idua/ideas.json";
    #define PATH file.c_str()
#endif

// see if the file exists
#if defined(_WIN32) || defined(_WIN64)
    #define FILE_EXISTS(path) (GetFileAttributes(path) != INVALID_FILE_ATTRIBUTES)
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    #define FILE_EXISTS(path) (access(path, F_OK) != -1)
#endif
