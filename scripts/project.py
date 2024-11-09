import os
import re
import sys
from glob import glob
import subprocess

def capture_vs_environment():
  vs_vars_path = r"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
  command = f'"{vs_vars_path}" x64 & set'
  output = subprocess.check_output(command, shell=True, text=True)
  env = {}
  for line in output.splitlines():
    if '=' in line:
      key, value = line.split('=', 1)
      env[key] = value
  return env

def setup_build_environment():
  if is_vs_environment_initialized():
    print("Environment already initialized.")
  else:
    print("Initializing environment...")
    os.environ.update(capture_vs_environment())

# Check for specific environment variables that vcvarsall.bat would set
def is_vs_environment_initialized():
  return 'VSCMD_VER' in os.environ and 'INCLUDE' in os.environ

class Project:
  src_root: str
  third_party_root: str
  include_dirs: list[str]
  build_output_dir: str
  build_object_output_dir: str

  # compiler/linker settings
  defines: dict[str, str]
  disabled_warnings: list[str]
  compiler_settings: list[str]
  linker_settings: list[str]

  # third party dependencies
  third_party_source_files: dict[str, list[str]]
  # dict of source files from the project.
  custom_source_files: dict[str, list[str]]
  # .h/hpp files to ignore during conditional compilation
  ignore_includes: list[str]
  # .c/cpp files to ignore during conditional compilation
  ignore_files: list[str]
  # Regular expression to match #include "file.h" or #include <file>
  include_pattern = re.compile(r'#include\s*[<"]([^">]+)[">]')

  def ensure_build_dirs_exist(self):
    if not os.path.exists(self.build_output_dir):
      os.mkdir(self.build_output_dir)
    if not os.path.exists(self.build_object_output_dir):
      os.mkdir(self.build_object_output_dir)

  def build(self):
    self.ensure_build_dirs_exist()
    source_files = self.get_source_files()
    cwd = os.curdir

    returncode = 0
    if not source_files:
      return returncode
       
    setup_build_environment()
    env = os.environ.copy()
    if source_files:
      os.chdir(self.build_output_dir)
      compiler_settings = self.get_compiler_settings()
      disabled_warnings = self.get_disabled_warnings()
      defines = self.get_defines()
      include_dirs = self.get_include_dirs()
      cl_command = " ".join(["cl", compiler_settings, disabled_warnings, source_files, defines, include_dirs])

      # Pass the environment to subprocess
      returncode = subprocess.run(cl_command, shell=True, env=env).returncode

    if returncode:
      print("Error occurred during compilation.")
    else:
      print("Compiled successfully.")

    linker_files = " ".join(self.get_matching_files([self.build_object_output_dir + "**/*.obj"]))
    linker_settings = self.get_linker_settings()
    lib_command = " ".join(["lib", linker_settings, linker_files])

    # Pass the environment to subprocess
    returncode = subprocess.run(lib_command, shell=True, env=env).returncode

    if returncode:
        print("Error occurred during linking.")
    else:
        print("Linked successfully.")

    os.chdir(cwd)
    return returncode

  def get_matching_files(self, file_search_patterns: list[str]) -> list[str]:
    matches = [glob(self.replace_forward_slashes(pattern), recursive=True) for pattern in file_search_patterns]
    return [x for xs in matches for x in xs]

  def extract_filename_without_extension(self, file_path):
    filename = os.path.basename(file_path)
    filename_without_extension, _ = os.path.splitext(filename)
    return filename_without_extension

  def any_include_changed_after_obj_last_modified(self, obj_last_compiled, file_path, already_checked, already_warned):
    if file_path in already_checked:
        return False
    already_checked[file_path] = True

    if os.path.getmtime(file_path) > obj_last_compiled:
        return True

    with open(file_path, 'r') as file:
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

  def file_needs_compiling(self, file_path, already_checked, already_warned):
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

  def get_source_files(self) -> str:
    # When triggered by the on save task, the file saved is passed as an 
    # argument. We can skip checking files in that case and just recompile the one that changed.
    if (len(sys.argv) > 1):
      file_path = sys.argv[1]
      file_name = file_path.split("\\")[-1]
      if ".c" in file_name:
        print(f"Recompiling {file_name}")
        return file_path
    files = []
    for _, file_paths in self.third_party_source_files.items():
      files.extend(
        self.get_matching_files([self.replace_forward_slashes(f"{self.third_party_root}{path}") for path in file_paths])
      )

    for _, file_paths in self.custom_source_files.items():
      files.extend(
        self.get_matching_files([self.replace_forward_slashes(f"{self.src_root}{path}") for path in file_paths])
      )

    already_checked = {name: True for name in self.ignore_files}
    already_warned = {name: True for name in self.ignore_includes}
    files_needing_compilation = [f for f in files if self.file_needs_compiling(f, already_checked, already_warned)]

    count = len(files_needing_compilation)
    if count == 0:
      print(f"No files need recompiling.")
    else: 
      print(f"Recompiling {count} of {len(files)} files.")

    return " ".join(files_needing_compilation)

  def get_defines(self) -> str:
    defines = [f"-D{name}={value}" for name, value in self.defines.items()]
    return " ".join(defines)

  def collect_args(self, prefix: str, args: list[str], sep: str = " ") -> str:
    results = []
    for arg in args:
      results.append(prefix + arg)
    return sep.join(results)

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
