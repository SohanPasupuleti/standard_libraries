#!/usr/bin/env -S uv run --script

import os
import shutil
import subprocess
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parent
BUILD_DIR = PROJECT_ROOT / "build_windows"

VCPKG_ROOT = Path(os.environ["VCPKG_ROOT"])
VCPKG_CACHE = PROJECT_ROOT / ".vcpkg_cache"

BUILD_CONFIG = "Release"
TARGET_TRIPLET = "x64-mingw-dynamic"
HOST_TRIPLET = "x64-mingw-dynamic"

def run(command, *, env=None):
    """Execute a command and stop if it fails."""
    print(f"\n>>> {' '.join(map(str, command))}\n")

    subprocess.run(
        [str(arg) for arg in command],
        cwd=PROJECT_ROOT,
        env=env,
        check=True
    )


def require_tool(name):
    """Ensure a required executable is available."""
    path = shutil.which(name)

    if path is None:
        raise RuntimeError(f"Required tool not found: {name}")

    return path

def main():
    print("<< CHECKING REQUIRED TOOLS >>")

    # Check required tools
    cmake = require_tool("cmake")
    ninja = require_tool("ninja")
    clang = require_tool("clang")
    clangxx = require_tool("clang++")
    gfortran = require_tool("gfortran")

    # Configure vcpkg cache
    print("\n<< CONFIGURING VCPKG CACHE >>")

    VCPKG_CACHE.mkdir(parents=True, exist_ok=True)

    env = os.environ.copy()
    env["VCPKG_DEFAULT_BINARY_CACHE"] = str(VCPKG_CACHE)

    # Configure CMake
    print("\n<< CONFIGURING CMAKE >>")

    run([
        cmake,
        "-S", PROJECT_ROOT,
        "-B", BUILD_DIR,
        "-G", "Ninja",

        f"-DCMAKE_MAKE_PROGRAM={ninja}",
        f"-DCMAKE_BUILD_TYPE={BUILD_CONFIG}",

        f"-DCMAKE_C_COMPILER={clang}",
        f"-DCMAKE_CXX_COMPILER={clangxx}",
        f"-DCMAKE_Fortran_COMPILER={gfortran}",

        f"-DCMAKE_TOOLCHAIN_FILE={VCPKG_ROOT / 'scripts/buildsystems/vcpkg.cmake'}",

        "-DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=lld",

        f"-DVCPKG_TARGET_TRIPLET={TARGET_TRIPLET}",
        f"-DVCPKG_HOST_TRIPLET={HOST_TRIPLET}",

        "-DCMAKE_C_COMPILER_TARGET=x86_64-w64-mingw32",
        "-DCMAKE_CXX_COMPILER_TARGET=x86_64-w64-mingw32",

    ], env=env)

    # Build
    print("\n<< BUILDING PROJECT >>")

    run([
        cmake,
        "--build", BUILD_DIR,
        "--parallel"
    ], env=env)

    # Run
    print("\n<< RUNNING PROGRAM >>")

    executable = BUILD_DIR / "main.exe"

    if not executable.exists():
        raise FileNotFoundError(executable)

    run([executable], env=env)


if __name__ == "__main__":
    main()