if [ ! -d "build" ]; then
    mkdir build;
    cmake -G "Visual Studio 17 2022" -B build -DCMAKE_BUILD_TYPE=Release -T host=x86 -A win32;
fi

# Use --config RelWithDebInfo to get debug symbols
cmake --build build --config Release --target ALL_BUILD;