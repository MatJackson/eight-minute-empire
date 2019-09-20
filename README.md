# eight-minute-empire
COMP 345 project.

### To configure Qt on CLion

Make sure you have Qt installed.

1. Go in `Preferences` => `Build, Execution, Deployment` => `CMake`.
2. Add the Qt/5.13.1/clang_64/lib/cmake` path to `CMake options` as -DCMAKE_PREFIX_PATH`

   Example:
   `-DCMAKE_PREFIX_PATH=/Users/tamar/Qt/5.13.1/clang_64/lib/cmake`

