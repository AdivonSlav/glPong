workspace "Pong"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

project "Pong"
    location "Pong"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir ("bin/%{cfg.buildcfg}-%{cfg.architecture}")
    objdir ("bin/intermediates/%{cfg.buildcfg}-%{cfg.architecture}")

    files
    {
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.h"
    }

    includedirs
    {
        "$(SolutionDir)/dependencies/include"
    }

    libdirs
    {
        "$(SolutionDir)/dependencies/lib"
    }

    links
    {
        "opengl32.lib",
        "glew32s.lib",
        "glfw3.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG", "GLEW_STATIC" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG", "GLEW_STATIC" }
        optimize "On"