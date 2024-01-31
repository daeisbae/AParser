# Remove CMake generated files
find . -iwholename '*cmake*' -not -name CMakeLists.txt -and -not -name rmcmake.sh -and -not -name cmake-single-platform.yml -delete
find . -name 'lib*.a' -delete
find . -name Makefile -delete

# Remove Executable
find . -name AParser -delete
find . -name test_stringutil -delete

# Remove gtest package
find . -name '_deps' -type d -exec rm -r {} +
find . -name lib -delete
find . -name bin -delete