import argparse
import sys
from pathlib import Path


def parse_args():
    parser = argparse.ArgumentParser(description="CLI argument parser demonstration")
    parser.add_argument(
        "-v", "--verbose", action="store_true", help="Enable verbose output"
    )
    parser.add_argument(
        "-c", "--count", default=1, type=int, help="Number of tasks, defaults to 1"
    )
    parser.add_argument("target", action="store", help="Target path", type=Path)
    return parser.parse_args(sys.argv[1:])


if __name__ == "__main__":
    args_out = parse_args()

    if args_out.verbose:
        print(
            f"verbose args_out: \n    count: {args_out.count}\n    target: {args_out.target}"
        )
    else:
        print(f"args_out:\n    target: {args_out.target}")
