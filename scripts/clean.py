import os
import sys
import shutil

# can be called for 'Krystal' or 'KrystalEditor'
if __name__ == '__main__':
  target = ("B:" if len(sys.argv) >= 2 and "KrystalEditor" in sys.argv[1] else "K:") + "\\build"
  if os.path.exists(target):
    try:
      # Remove the entire 'build' directory and its contents
      shutil.rmtree(target)
      print(f"Successfully deleted the build directory at {target}.")
    except Exception as e:
      print(f"Error deleting the build directory at {target}: {e}")
  else:
    print(f"No build directory found at {target}. Nothing to delete.")