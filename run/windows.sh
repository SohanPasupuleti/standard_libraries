set -e

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build_windows"
OS_NAME=WINDOWS

echo "<< RUN SCRIPT FOR OS [$OS_NAME] >>"

# echo ""
# echo "<< CLEANING BUILD CACHE >>"
# rm -rf build_windows

echo "<< CREATING LOCAL CACHE FOR VCPKG >>"
mkdir -p "$PROJECT_ROOT/.vcpkg_cache"
export VCPKG_DEFAULT_BINARY_CACHE="$PROJECT_ROOT/.vcpkg_cache"

echo ""
echo "<< RUNNING CMAKE >>"
cmake \
    -S "$PROJECT_ROOT" \
    -B "$BUILD_DIR" \
    -G Ninja \
	-DCMAKE_MAKE_PROGRAM="$(which ninja)" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
	-DCMAKE_Fortran_COMPILER=gfortran \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
	-DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" \
	-DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic \
	-DVCPKG_HOST_TRIPLET=x64-mingw-dynamic \
    -DCMAKE_C_FLAGS="--target=x86_64-w64-mingw32" \
    -DCMAKE_CXX_FLAGS="--target=x86_64-w64-mingw32" 

echo ""
echo "<< BUILDING PROJECT >>"
cmake --build "$BUILD_DIR" -j

echo ""
echo "<< RUNNING PROGRAM >>"
"$BUILD_DIR/main.exe"