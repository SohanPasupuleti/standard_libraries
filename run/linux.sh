set -e

echo "<< RUN SCRIPT FOR OS [Linux] >>"

echo ""
echo "<< CLEANING BUILD CACHE >>"

mkdir -p build_linux
rm -f build_linux/CMakeCache.txt

echo "<< RUNNING CMAKE >>"
	
cmake -S . -B build_linux \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gcc \
    -DCMAKE_CXX_COMPILER=g++ \
    -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
    -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic \
    -DVCPKG_HOST_TRIPLET=x64-mingw-dynamic

echo ""
echo "<< BUILDING PROJECT >>"

cmake --build build_linux -j

echo ""
echo "<< RUNNING PROGRAM >>"
./build_linux/main.exe
