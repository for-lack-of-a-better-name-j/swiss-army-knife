import os
import sys
from pathlib import Path


def main():
    target_str = sys.argv[1] if len(sys.argv) > 1 else "."
    target_dir = Path(target_str)

    print(f"Walking directory: {target_dir.resolve()}")

    for dirpath, dirnames, filenames in os.walk(target_dir.resolve()):
        print(
            f"The path: {dirpath} has the dirnames {dirnames} which contain the filenames {filenames}"
        )


if __name__ == "__main__":
    main()
