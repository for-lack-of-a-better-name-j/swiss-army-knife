from pathlib import Path

log_file = Path("output.log")
# This will create the file if it does not exist
# Also the "with" statement will close the file
# if the python program crashes
with log_file.open("a", encoding="utf-8") as f:
    f.write("Another log entry\n")
