import os
import re
import sys
from glob import glob
import subprocess

def capture_vs_environment()->dict[str, str]:
  vs_vars_path: str = r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
  command: str = f'"{vs_vars_path}" x64 & set'
  output: str = subprocess.check_output(command, shell=True, text=True)
  env: dict[str, str] = {}
  for line in output.splitlines():
    if '=' in line:
      key, value = line.split('=', 1)
      env[key] = value
  return env

def setup_build_environment()->None:
  if is_vs_environment_initialized():
    print("Environment already initialized.")
    return None
  print("Initializing environment...")
  os.environ.update(capture_vs_environment())

# Check for specific environment variables that vcvarsall.bat would set
def is_vs_environment_initialized()->bool:
  return 'VSCMD_VER' in os.environ and 'INCLUDE' in os.environ

PROJECT_TYPE_LIBRARY: str = "lib"
PROJECT_TYPE_EXE: str = "link"

class Project:
  name: str
  type: str = PROJECT_TYPE_LIBRARY
  src_root: str
  third_party_root: str
  include_dirs: list[str] = []
  build_output_dir: str
  build_object_output_dir: str

  # compiler/linker settings
  defines: dict[str, str] = {}
  disabled_warnings: list[str] = []
  compiler_settings: list[str] = []
  linker_settings: list[str] = []
  linked_libraries: list[str] = []
  # third party dependencies
  third_party_source_files: dict[str, list[str]] = {}
  # dict of source files from the project.
  custom_source_files: dict[str, list[str]] = {}
  # .h/hpp files to ignore during conditional compilation
  ignore_includes: list[str] = []
  # .c/cpp files to ignore during conditional compilation
  ignore_files: list[str] = []
  # Regular expression to match #include "file.h" or #include <file>
  include_pattern = re.compile(r'#include\s*[<"]([^">]+)[">]')

  def ensure_build_dirs_exist(self)->None:
    if not os.path.exists(self.build_output_dir):
      os.mkdir(self.build_output_dir)
    if not os.path.exists(self.build_object_output_dir):
      os.mkdir(self.build_object_output_dir)

  def compile_translation_units(self, source_files: str, env: dict[str, str]):
    os.chdir(self.build_output_dir)
    compiler_settings: str = self.get_compiler_settings()
    disabled_warnings: str = self.get_disabled_warnings()
    defines: str = self.get_defines()
    include_dirs: str = self.get_include_dirs()
    cl_command: str = " ".join(["cl", compiler_settings, disabled_warnings, source_files, defines, include_dirs])
    return subprocess.run(cl_command, shell=True, env=env).returncode

  def link(self, env: dict[str, str])->int:
    os.chdir(self.build_output_dir)
    obj_files: str = " ".join(self.get_matching_files([self.build_object_output_dir + "**/*.obj"]))
    linker_settings: str = self.get_linker_settings()
    linked_libs: str = self.get_linked_libraries()
    linker_type: str = self.type
    link_command: str = " ".join([linker_type, linker_settings, obj_files, linked_libs]).replace("  ", " ")
    return subprocess.run(link_command, shell=True, env=env).returncode

  def build(self)->int:
    print(f"Building '{self.name}'")
    saved_current_working_dir: str = os.curdir
    self.ensure_build_dirs_exist()

    source_files: str = self.get_source_files()
       
    setup_build_environment()
    env: dict[str, str] = os.environ.copy()

    if source_files:
      returncode: int = self.compile_translation_units(source_files, env)
      print("Error occurred during compilation." if returncode else "Compiled successfully.")

    returncode = self.link(env)
    print("Error occurred during linking." if returncode else "Linked successfully.")

    os.chdir(saved_current_working_dir)
    return returncode

  def get_matching_files(self, file_search_patterns: list[str])->list[str]:
    matches: list[list[str]] = [glob(self.replace_forward_slashes(pattern), recursive=True) for pattern in file_search_patterns]
    return [x for xs in matches for x in xs]

  def extract_filename_without_extension(self, file_path)->str:
    filename: str = os.path.basename(file_path)
    filename_without_extension, _ = os.path.splitext(filename)
    return filename_without_extension

  def any_include_changed_after_obj_last_modified(self, obj_last_compiled, file_path, already_checked, already_warned)->bool:
    if file_path in already_checked:
      return False
    already_checked[file_path] = True

    if os.path.getmtime(file_path) > obj_last_compiled:
      return True

    with open(file_path, 'r', encoding="utf8") as file:
      for line in file:
        match = self.include_pattern.search(line)
        if match:
          include_file = match.group(1)

          if '.' not in include_file:
            continue # std lib file

          if include_file in already_warned:
            continue # avoid flooding console

          # Resolve the full path of the include file relative to include_dirs
          full_include_path = None
          for include_dir in self.include_dirs:
            candidate_path = os.path.join(include_dir, include_file)
            if os.path.exists(candidate_path):
              full_include_path = candidate_path
              break

          if not full_include_path:
            print(f"Warning: Include file {include_file} not found in include directories.")
            already_warned[include_file] = True
            continue

          # Recursively check referenced includes
          if self.any_include_changed_after_obj_last_modified(obj_last_compiled, full_include_path, already_checked, already_warned):
            return True

    return False

  def file_needs_compiling(self, file_path, already_checked, already_warned)->bool:
    try:
      source_last_modified = os.path.getmtime(file_path)
      file_name = self.extract_filename_without_extension(file_path)
      obj_last_compiled = os.path.getmtime(f"{self.build_object_output_dir}{file_name}.obj")

      if source_last_modified > obj_last_compiled:
        return True # .c/.cpp has changed since .obj was last compiled

      # check if any .h/.hpp files in the translation have changed simple the last compilation 
      return self.any_include_changed_after_obj_last_modified(obj_last_compiled, file_path, already_checked, already_warned)
    except FileNotFoundError:
      return True # .obj file doesn't exist

  def get_files(self)->list[str]:
    files = []
    for _, file_paths in self.third_party_source_files.items():
      files.extend(
        self.get_matching_files([self.replace_forward_slashes(f"{self.third_party_root}{path}") for path in file_paths])
      )
    for _, file_paths in self.custom_source_files.items():
      files.extend(
        self.get_matching_files([self.replace_forward_slashes(f"{self.src_root}{path}") for path in file_paths])
      )
    return files

  def get_source_files(self) -> str:
    files: list[str] = self.get_files()
    # When triggered by the on save task, the file saved is passed as an 
    # argument. We can skip checking files in that case and just recompile the one that changed.
    if (len(sys.argv) >= 3 and "tests" not in sys.argv[2]):
      file_path: str = sys.argv[2]
      file_name: str = file_path.split("\\")[-1]
      if next((file for file in files if file.endswith(file_name)), None) is not None:
        print(f"Recompiling {file_name}")
        return file_path
      elif ".h" not in file_name:
        print(f"{file_name} not included in source files - compilation skipped.")
        return ""

    already_checked = {name: True for name in self.ignore_files}
    already_warned = {name: True for name in self.ignore_includes}
    
    files_needing_compilation = [file for file in files if self.file_needs_compiling(file, already_checked, already_warned)]

    count = len(files_needing_compilation)
    print(f"No files need recompiling." if not count else f"Recompiling {count} of {len(files)} files.")

    return " ".join(files_needing_compilation)

  def get_defines(self) -> str:
    return " ".join([f"-D{name}={value}" for name, value in self.defines.items()])

  def collect_args(self, prefix: str, args: list[str], sep: str = " ") -> str:
    return sep.join([prefix + arg for arg in args])

  def replace_forward_slashes(self, string: str) -> str:
    return string.replace("/", "\\")

  def get_include_dirs(self) -> str:
    return self.collect_args(" -I", self.include_dirs)

  def get_disabled_warnings(self) -> str:
    return self.collect_args("-wd", self.disabled_warnings)

  def get_compiler_settings(self) -> str:
    return self.collect_args("-", self.compiler_settings)

  def get_linker_settings(self) -> str:
    return self.collect_args("-", self.linker_settings)

  def get_linked_libraries(self) -> str:
    return self.collect_args("", self.linked_libraries)
