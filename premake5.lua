workspace "Pong"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

project "Pong"
    location "Pong"
    language "C++"
    cppdialect "C++20"
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
        "glfw3.lib",
        "freetype.lib"
    }

    postbuildcommands
    {
        "{COPY} %{wks.location}dependencies/lib/freetype.dll %{cfg.targetdir}",  -- Copies the freetype DLL to the build directory
        "{MKDIR} %{cfg.targetdir}/fonts",                                        -- Makes fonts folder
        "{COPYDIR} %{prj.location}fonts %{cfg.targetdir}/fonts"                  -- Copies fonts to fonts folder
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG", "GLEW_STATIC" }
        symbols "On"
        kind "ConsoleApp"
        entrypoint "mainCRTStartup"
    
    filter "configurations:Release"
        defines { "NDEBUG", "GLEW_STATIC" }
        optimize "On"
        kind "WindowedApp"
        entrypoint "mainCRTStartup"