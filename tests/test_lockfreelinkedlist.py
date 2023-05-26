#!/usr/bin/env python3

import os
import tempfile

from testsupport import (
    run,
    subtest,
    warn,
    test_root,
    run_project_executable,
    ensure_library,
)


def main() -> None:
    # Run the test program
    lib = ensure_library("liblockfreelinkedlist.so")
    extra_env = {"LD_LIBRARY_PATH": str(os.path.dirname(lib))}
    test_lockfreelinkedlist = test_root().joinpath("test_lockfreelinkedlist")

    if not test_lockfreelinkedlist.exists():
        run(["make", "-C", str(test_root()), str(test_lockfreelinkedlist)])

    with tempfile.TemporaryDirectory() as tmpdir:
        with subtest("Checking lock free linked list"):
            with open(f"{tmpdir}/stdout", "w+") as stdout:
                run_project_executable(
                    str(test_lockfreelinkedlist),
                    stdout=stdout,
                    extra_env=extra_env,
                )


if __name__ == "__main__":
    main()
