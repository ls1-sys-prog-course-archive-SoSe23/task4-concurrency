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
    test_locklinkedlist = test_root().joinpath("test_locklinkedlist")
    if not test_locklinkedlist.exists():
        run(["make", "-C", str(test_root()), str(test_locklinkedlist)])

    with subtest("Checking lock linked list"):
        run_project_executable(str(test_locklinkedlist))


if __name__ == "__main__":
    main()
