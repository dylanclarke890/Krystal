from project import PROJECT_TYPE_EXE, Project
from shared_settings import ignore_includes, compiler_settings, disabled_warnings, defines, linker_settings

def get_editor_project():
  THIRD_PARTY_ROOT: str = "K:/src/ThirdParty/"

  code: Project = Project()
  code.name = "EDITOR"
  code.type = PROJECT_TYPE_EXE
  code.src_root = "B:/src/"
  code.third_party_root = THIRD_PARTY_ROOT
  code.include_dirs = ["B:/include/", "K:/include/", f"{THIRD_PARTY_ROOT}Glad/include"]
  code.build_output_dir = "B:/build/"
  code.build_object_output_dir = code.build_output_dir + "obj/"
  code.disabled_warnings = disabled_warnings
  code.compiler_settings = compiler_settings
  code.ignore_includes = ignore_includes
  code.defines = defines
  code.ignore_files = []
  code.linker_settings = linker_settings
  code.linker_settings.extend([f"OUT:{code.build_output_dir}KrystalEditor.exe", "DEBUG:FULL", "LIBPATH:\"K:\\build\""])
  code.linked_libraries = ["Winmm.lib", "user32.lib", "gdi32.lib", "OpenGL32.lib", "Krystal.lib"]
  code.custom_source_files = {
    "All": ["**/*.cpp", "**/*.c"],
  }
  code.third_party_source_files = {
    "Glad": ["Glad/src/*.c"],
  }

  return code