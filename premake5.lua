workspace "Krystal"
  architecture "x64"
  configurations { "Debug", "Release", "Publish" }

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

project "Krystal"
  location "Krystal"
  kind "SharedLib"
  language "C++"

  targetdir("bin/" .. outputdir .. "/%{prj.name}")
  objdir("bin-obj/" .. outputdir .. "/%{prj.name}")
  
  files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
  includedirs { "%{prj.name}/third-party/spdlog/include" }
  
  filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"
    defines { "KRYS_PLATFORM_WINDOWS", "KRYS_BUILD_DLL" }

    postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") }

  filter "configurations:Debug"
    defines "KRYS_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "KRYS_RELEASE"
    optimize "On"

  filter "configurations:Debug"
    defines "KRYS_PUBLISH"
    optimize "On"

project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  language "C++"

  targetdir("bin/" .. outputdir .. "/%{prj.name}")
  objdir("bin-obj/" .. outputdir .. "/%{prj.name}")
  
  files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
  includedirs { "Krystal/third-party/spdlog/include", "Krystal/src" }
  links { "Krystal" }

  filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"
    defines { "KRYS_PLATFORM_WINDOWS" }

  filter "configurations:Debug"
    defines "KRYS_DEBUG"
    symbols "On"

  filter "configurations:Release"
    defines "KRYS_RELEASE"
    optimize "On"

  filter "configurations:Debug"
    defines "KRYS_PUBLISH"
    optimize "On"