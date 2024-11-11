import sys
from engine import get_engine_project
from editor import get_editor_project
from timer_helpers import end_timer, start_timer

# can be called from 'Krystal' or 'KrystalEditor'
if __name__ == '__main__':
  start_timer()
  code = get_editor_project() if len(sys.argv) >= 2 and (
    "KrystalEditor" in sys.argv[1] or "B:\\" in sys.argv[1]
    ) else get_engine_project()
  returncode = code.build()
  end_timer()
  sys.exit(returncode)