import os
from datetime import timedelta, datetime

compile_start: datetime = datetime.now()

def format_date(date: datetime, ms_precision: int = 3):
  return date.strftime("%H:%M:%S:%f")[:-(6-ms_precision)]

def start_timer():
  os.system('cls')
  compile_start = datetime.now()
  print("Build started at: " + format_date(compile_start))

def end_timer():
  end_time: datetime = datetime.now()
  time_taken: timedelta = end_time - compile_start
  print(f"Build finished at: {format_date(end_time)}")
  print(f"Build completed in {str(round(time_taken.total_seconds(), 3))}s")
