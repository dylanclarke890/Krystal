# remember that Foobj\ is the setting Fo with the value obj\ to point it at build\obj\
compiler_settings = [
  "c", "Foobj\\", "nologo", "Zi",
  "Oi", "FC", "W4", "WX", "MP",
  "EHsc", "std:c++latest", "MTd"
]

linker_settings = [
  "nologo"
]

defines = {
  "KRYS_ENABLE_ASSERTS":"1",
  "KRYS_ENABLE_LOGGING":"1",
  "KRYS_ENABLE_DEBUG_BREAK":"1",
  "KRYS_ENABLE_PERFORMANCE_CHECKS":"1",
  "KRYS_ENABLE_PROFILING":"1",
  "KRYS_ENABLE_TESTS":"1",
  "_ITERATOR_DEBUG_LEVEL":"2"
}

disabled_warnings = ["5063", "4702"]

ignore_includes = [
  "stddef.h", "stdio.h", "stdint.h", "stdlib.h",
  "winapifamily.h", "hidusage.h", "windows.h",
  "signal.h", "TargetConditionals.h", "dlfcn.h",
  "string.h", "inttypes.h", "limits.h", "stdarg.h", 
  "math.h", "assert.h", "emmintrin.h", "intrin.h",
  "arm_neon.h", "fcntl.h", "sys/stat.h", "unistd.h",
  "machine/endian.h", "sys/byteorder.h", "endian.h"
]

# ----------- COMPILER FLAGS ------------
# |  FLAG  |  DESCRIPTION
# |--------|------------------------------
# |    c   | compile but do not link.
# |    D   | compiler level #defines.
# |   FC   | compile-time errors show full path to source code.
# |   FO   | specify a name/output dir for object files.
# |   MP   | enable multi-processing compilation.
# | nologo | turn off compiler name banner.
# |   Oi   | use intrinsics whenever possible.
# |   O2   | enable optimisations.
# |   std  | compiler version e.g. c++20.
# |   wd   | disable warnings for a specific warning code.
# |   W4   | compile-time warnings level.
# |   WX   | treat warnings as errors.
# |   Zi   | generate debug info.
# |   EH   | Exception handling.
# |  EHs   | Enables stack unwinding when exceptions are thrown.
# |  EHc   | "Extern C" functions never throw exceptions.
# ----------- COMPILER FLAGS ------------

# ------------ LINKER FLAGS -------------
# |  nologo | turn off compiler name banner.
# |   OUT   | specify .lib/.dll filename.
# | LIBPATH | default path to look in when linking libraries.
# ------------ LINKER FLAGS -------------

# ----------- CUSTOM DEFINES ------------
# |  NAME                          |  Description
# |--------------------------------|-------------
# | KRYS_ENABLE_DEBUG_BREAK        | Turn on breakpoints (needed for asserts).
# | KRYS_ENABLE_ASSERTS            | Runtime asserts that trigger a break point on fail.
# | KRYS_ENABLE_LOGGING            | Turn on logging.
# | KRYS_ENABLE_PERFORMANCE_CHECKS | Log performance stats.
# ----------- CUSTOM DEFINES ------------

# ------------ LINKED LIBS --------------
# |-----------|---------------------------
# |   LIB     |  Description
# |  user32   | General windows OS apis.
# |  Winmm    | timeGetDevCaps, timeBeginPeriod etc.
# |  Gdi32    | Generic Windows API required for graphics.
# |  OpenGL32 | Windows lib for OpenGL (TODO: we should be linking to this completely dynamically).
# |  assimp   | Asset-Importer-Lib.
# |  Krystal  | The Krystal game engine!
# ------------ LINKED LIBS --------------