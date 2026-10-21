GLOBS=(
	vcpkg.json
	vcpkg-configuration.json
	cmake/mingw-clang-toolchain.cmake
	CMakeLists.txt
	run.sh
)

for file in "${GLOBS[@]}"; do
    echo "<< $file >>"
    cat "$file"
	echo ""
done