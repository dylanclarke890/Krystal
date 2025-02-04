from project import PROJECT_TYPE_LIBRARY, Project
from shared_settings import ignore_includes, compiler_settings, disabled_warnings, defines, linker_settings

def get_engine_project():
  THIRD_PARTY_ROOT: str = "K:/src/ThirdParty/"

  code: Project = Project()
  code.name = "ENGINE"
  code.type = PROJECT_TYPE_LIBRARY
  code.src_root = "K:/src/"
  code.third_party_root = THIRD_PARTY_ROOT
  code.include_dirs = [
    "K:/include/",
    f"{THIRD_PARTY_ROOT}Glad/include",
    f"{THIRD_PARTY_ROOT}stb",
  ]
  code.build_output_dir = "K:/build/"
  code.build_object_output_dir = code.build_output_dir + "obj/"
  code.disabled_warnings = disabled_warnings
  code.compiler_settings = compiler_settings
  code.ignore_includes = ignore_includes
  code.defines = defines
  code.ignore_files = []
  code.linker_settings = linker_settings
  code.linker_settings.extend([f"OUT:{code.build_output_dir}Krystal.lib"])
  code.custom_source_files = {
    "Core": ["Core/**/*.cpp"],
    "Debug": ["Debug/**/*.cpp"],
    "Events": ["Events/**/*.cpp"],
    "Graphics": ["Graphics/**/*.cpp"],
    "IO": ["IO/**/*.cpp"],
    "MTL": ["MTL/**/*.cpp"],
    "Win32Platform": ["Platform/Win32/**/*.cpp"],
    "Utils": ["Utils/**/*.cpp"],
  }
  code.third_party_source_files = {
    "Glad": ["Glad/src/*.c"],
    "stb": ["stb/stb.cpp"],
  }

  return code