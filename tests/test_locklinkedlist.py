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
    lib = ensure_library("libspinlock.so")
    extra_env = {"LD_LIBRARY_PATH": str(os.path.dirname(lib))}
    test_locklinkedlist = test_root().joinpath("test_locklinkedlist")

    if not test_locklinkedlist.exists():
        run(["make", "-C", str(test_root()), str(test_locklinkedlist)])

    with tempfile.TemporaryDirectory() as tmpdir:
        with subtest("Checking lock linked list"):
            with open(f"{tmpdir}/stdout", "w+") as stdout:
                run_project_executable(
                    str(test_locklinkedlist),
                    stdout=stdout,
                    extra_env=extra_env,
                )


if __name__ == "__main__":
    main()
