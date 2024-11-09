import sys
from project import Project
from timer_helpers import end_timer, start_timer

def build_project():
  start_timer()
  code: Project = Project()

  THIRD_PARTY_ROOT: str = "K:/src/ThirdParty/"

  code.src_root = "K:/src/"
  code.third_party_root = THIRD_PARTY_ROOT
  code.include_dirs = ["K:/include/", f"{THIRD_PARTY_ROOT}Glad/include"]
  code.build_output_dir = "K:/build/"
  code.build_object_output_dir = code.build_output_dir + "obj/"

  code.defines = {
    "KRYS_ENABLE_ASSERTS":"1",
    "KRYS_ENABLE_LOGGING":"1",
    "KRYS_ENABLE_DEBUG_BREAK":"1",
    "KRYS_ENABLE_PERFORMANCE_CHECKS":"1",
    "_ITERATOR_DEBUG_LEVEL":"2"
  }

  code.disabled_warnings = [
    "4100", "4201"
  ]

  # remember that Foobj\ is the setting Fo with the value obj\ to point it at build\obj\
  code.compiler_settings = [
    "c", "Foobj\\", "nologo", "Zi",
    "Oi", "FC", "W4", "WX", "MP",
    "EHsc", "std:c++latest", "MTd"
  ]

  code.linker_settings = [
    "nologo", f"OUT:{code.build_output_dir}Krystal.lib",
  ]

  code.custom_source_files = {
    "Core": ["Core/**/*.cpp"],
    "Win32Platform": ["Platform/Win32/**/*.cpp"],
  }

  code.third_party_source_files = {
    "Glad": ["Glad/src/*.c"],
  }

  code.ignore_includes = [
    "stddef.h", "stdio.h", "stdint.h", "stdlib.h",
    "winapifamily.h", "hidusage.h", "windows.h",
    "signal.h", "TargetConditionals.h", "dlfcn.h",
    "string.h", "inttypes.h"
  ]

  code.ignore_files = []

  returncode = code.build()
  end_timer()
  sys.exit(returncode)

if __name__ == '__main__':
  build_project()
