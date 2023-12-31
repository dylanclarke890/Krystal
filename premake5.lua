outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

workspace "Krystal"
  architecture "x64"
  configurations { "Debug", "Release", "Publish" }
  startproject "Sandbox"
  flags { "MultiProcessorCompile" }

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Krystal/third-party/GLFW/include"
IncludeDir["glad"] = "Krystal/third-party/glad/include"
IncludeDir["imgui"] = "Krystal/third-party/imgui"
IncludeDir["glm"] = "Krystal/third-party/glm"
IncludeDir["stb_image"] = "Krystal/third-party/stb_image"

group "Dependencies"
  include "Krystal/third-party/GLFW"
  include "Krystal/third-party/glad"
  include "Krystal/third-party/imgui"

group ""
project "Krystal"
  location "Krystal"
  kind "StaticLib"
  staticruntime "on"
  language "C++"
  cppdialect "C++20"
  
  targetdir("bin/" .. outputdir .. "/%{prj.name}")
  objdir("bin-obj/" .. outputdir .. "/%{prj.name}")

  pchheader "krys-pch.h"
  pchsource "Krystal/src/krys-pch.cpp"
  
  files { 
    "%{prj.name}/src/**.h",
     "%{prj.name}/src/**.cpp",
     "%{prj.name}/third-party/stb_image/**.h",
     "%{prj.name}/third-party/stb_image/**.cpp",
     "%{prj.name}/third-party/glm/glm/**.hpp",
     "%{prj.name}/third-party/glm/glm/**.inl"
  }

  defines {
    "_CRT_SECURE_NO_WARNINGS"
  }

  includedirs {
    "%{prj.name}/third-party/spdlog/include", 
    "%{prj.name}/src",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.glad}",
    "%{IncludeDir.imgui}",
    "%{IncludeDir.glm}",
    "%{IncludeDir.stb_image}"
  }

  links {
    "ImGui",
    "glad",
    "GLFW",
    "opengl32.lib"
  }
  
  filter "system:windows"
    systemversion "latest"
    defines { "GLFW_INCLUDE_NONE" }

  filter "configurations:Debug"
    defines {"KRYS_DEBUG", "KRYS_ENABLE_ASSERTS" }
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    defines "KRYS_RELEASE"
    runtime "Release"
    optimize "on"

  filter "configurations:Publish"
    defines "KRYS_PUBLISH"
    runtime "Release"
    optimize "on"

project "Sandbox"
  location "Sandbox"
  kind "ConsoleApp"
  staticruntime "on"
  cppdialect "C++20"
  language "C++"

  targetdir("bin/" .. outputdir .. "/%{prj.name}")
  objdir("bin-obj/" .. outputdir .. "/%{prj.name}")
  
  files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
  includedirs { 
    "Krystal/src",
    "Krystal/third-party",
    "Krystal/third-party/spdlog/include",
    "%{IncludeDir.glm}"
  }

  links { "Krystal" }

  filter "system:windows"
    systemversion "latest"

  filter "configurations:Debug"
    defines "KRYS_DEBUG"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    defines "KRYS_RELEASE"
    runtime "Release"
    optimize "on"

  filter "configurations:Publish"
    defines "KRYS_PUBLISH"
    runtime "Release"
    optimize "on"