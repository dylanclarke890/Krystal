import os
from datetime import timedelta, datetime

compile_start: datetime = datetime.now()

def format_date(date: datetime):
  return date.strftime("%H:%M:%S:%f")[:-3]

def start_timer():
  os.system('cls')
  compile_start = datetime.now()
  print("Build started at: " + format_date(compile_start))

def end_timer():
  end_time: datetime = datetime.now()
  time_taken: timedelta = end_time - compile_start
  print(f"Build finished at: {format_date(end_time)}")
  print(f"Total time taken: ({str(round(time_taken.total_seconds(), 3))}s)")
