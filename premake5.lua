workspace "SMMO"
    architecture "x64"
    --toolset "msc-ClangCL"
    toolset "msc"

    configurations
    {
        "Debug",
        "Release"
    }

    startproject "Server"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

newoption
{
    trigger = "graphics",
    value = "OPENGL_VERSION",
    description = "version of OpenGL to build raylib against",
    allowed = {
	    { "opengl11", "OpenGL 1.1"},
	    { "opengl21", "OpenGL 2.1"},
	    { "opengl33", "OpenGL 3.3"},
	    { "opengl43", "OpenGL 4.3"}
    },
    default = "opengl33"
}

--include "Game/vendor/raylib_premake5.lua"

filter {}

local directories = {
    "./",
    "Game/",
    "Game/vendor/"
}

local function DeleteVSFiles(path)
    os.remove(path .. "*.sln")
    os.remove(path .. "*.vcxproj")
    os.remove(path .. "*.vcxproj.filters")
    os.remove(path .. "*.vcxproj.user")
    print("Deleting VS files for " .. path)
end

newaction
{
    trigger = "clean",
    description = "Remove all binaries, int-binaries, vs files",
    execute = function()
        os.rmdir("./bin")
        print("Successfully removed binaries")
        os.rmdir("./bin-int")
        print("Successfully removed intermediate binaries")
        os.rmdir("./.vs")

        for _, v in pairs(directories) do
            DeleteVSFiles(v)
        end

        print("Successfully removed vs project files")
        print("Done!")
    end
}

filter {}

local EngineProjectFolder = "Engine"
local ServerProjectFolder = "Server"

local WindowsCommonBuildOptions = { "-std:c++17", "-W4", "-WX", "-wd4100", "-wd4201", "-wd4127", "-wd4701", "-wd4189",
"-wd4995", "-wd4244", "-Oi", "-GR", "-GR-", "-EHs-c-", "-D_HAS_EXCEPTIONS=0" }

project "Engine"
    kind "SharedLib"
    language "C++"
    cdialect "C99"
    cppdialect "C++17"
    staticruntime "off"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        EngineProjectFolder .. "/src/**.cpp",
        EngineProjectFolder .. "/src/**.c",
        EngineProjectFolder .. "/src/**.h",
        EngineProjectFolder .. "/vendor/flecs/flecs.c",
        EngineProjectFolder .. "/vendor/enet/enet.h",
        EngineProjectFolder .. "/vendor/librg/librg.h",
        EngineProjectFolder .. "/vendor/cmp/cmp.c",
        EngineProjectFolder .. "/vendor/cmp/cmp.h",
    }

    defines
    {
        "SCAL_BUILD_DLL",
        "flecs_EXPORTS",
        "OGREMAIN_STATIC_DEFINE"
    }

    includedirs
    {
        EngineProjectFolder .. "/src",
        EngineProjectFolder .. "/vendor",
    }

    libdirs
    {
        "C:/Program Files/MySQL/MySQL Server 8.0/lib",
        --"%{wks.location}/bin/" .. outputdir .. "/raylib/",
        "D:/dev-libs/ogre/build/lib/RelWithDebInfo"
    }

    links
    {
        "OgreMain",
        "OgreBites",
        "OgreRTShaderSystem",
    }

    -- -Xclang passes to clang compiler regular -Wno doesnt work with clang-cl :)
    filter "toolset:msc-ClangCL"
        buildoptions
        { 
            "-Wno-c++98-compat-pedantic", "-Wno-old-style-cast", "-Wno-extra-semi-stmt",
            "-Xclang -Wno-missing-braces", "-Xclang -Wno-missing-field-initializers",
            "-Wno-error=misleading-indentation", "-Xclang -Wno-unused-variable",
            "-Wno-error=unused-command-line-argument",
            "-Xclang -Wno-unused-but-set-variable"
        }

    filter "configurations:Debug"
        defines "SCAL_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "SCAL_RELEASE"
        runtime "Release"
        optimize "on"

    filter "system:Windows"
        defines "SCAL_PLATFORM_WINDOWS"
        systemversion "latest"
        buildoptions
        {
            WindowsCommonBuildOptions
        }
        links
        {
            --"raylib.lib",
            "mysqlclient"
        }

    filter "system:Unix"
        defines "SCAL_PLATFORM_LINUX"
        links
        {
            --"raylib.so",
            "libmysqlclient"
        }


    filter {}

    postbuildcommands
    {
        ("{COPYFILE} %{wks.location}bin/" .. outputdir .. "/%{prj.name}/Engine.dll "
            .. "%{wks.location}bin/" .. outputdir .. "/%{prj.name}/../Server/Engine.dll")
    }

project "Server"
    kind "ConsoleApp"
    language "C++"
    cdialect "C99"
    cppdialect "C++17"
    staticruntime "off"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        ServerProjectFolder .. "/src/**.cpp",
        ServerProjectFolder .. "/src/**.c",
        ServerProjectFolder .. "/src/**.h",
    }

    defines
    {
        "OGREMAIN_STATIC_DEFINE",
      --  "SCAL_BUILD_DLL"
    }

    includedirs
    {
        EngineProjectFolder .. "/src",
        EngineProjectFolder .. "/vendor",
        ServerProjectFolder .. "/src",
        ServerProjectFolder .. "/vendor",
    }

    libdirs
    {
        "C:/Program Files/MySQL/MySQL Server 8.0/lib",
        --"%{wks.location}/bin/" .. outputdir .. "/raylib/",
        "D:/dev-libs/ogre/build/lib/RelWithDebInfo"
    }

    links
    {
        "Engine",
        "OgreMain",
        "OgreBites",
        "OgreRTShaderSystem",
    }

    -- -Xclang passes to clang compiler regular -Wno doesnt work with clang-cl :)
    filter "toolset:msc-ClangCL"
        buildoptions
        { 
            "-Wno-c++98-compat-pedantic", "-Wno-old-style-cast", "-Wno-extra-semi-stmt",
            "-Xclang -Wno-missing-braces", "-Xclang -Wno-missing-field-initializers",
            "-Wno-error=misleading-indentation", "-Xclang -Wno-unused-variable",
            "-Wno-error=unused-command-line-argument",
            "-Xclang -Wno-unused-but-set-variable"
        }

    filter "configurations:Debug"
        defines "SCAL_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "SCAL_RELEASE"
        runtime "Release"
        optimize "on"

    filter "system:Windows"
        defines "SCAL_PLATFORM_WINDOWS"
        systemversion "latest"
        buildoptions
        {
            WindowsCommonBuildOptions
        }
        links
        {
            --"raylib.lib",
            --"mysqlclient"
        }

    filter "system:Unix"
        defines "SCAL_PLATFORM_LINUX"
        links
        {
            --"raylib.so",
           -- "libmysqlclient"
        }

    filter {}
