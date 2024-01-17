workspace "ABC"
    configurations { "Debug", "Release" }

    project "project"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        architecture "x86_64"
        targetdir "bin/%{cfg.buildcfg}"

        files { 
            "src/**.h", 
            "src/**.cpp",
            "src/**.hpp"
        }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
    project "tests"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        architecture "x86_64"
        targetdir "bin/%{cfg.buildcfg}"

        files { 
            "tests/**.h", 
            "tests/**.cpp",
            "tests/**.hpp",
            "src/**.h", 
            "src/**.cpp",
            "src/**.hpp",
            "resources/images/**.png"
        }

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
