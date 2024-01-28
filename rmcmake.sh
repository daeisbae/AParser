find . -iwholename '*cmake*' -not -name CMakeLists.txt -and -not -name rmcmake.sh -and -not -name cmake-single-platform.yml -delete
find . -name Makefile -delete
find . -name AParser -delete
find . -name 'lib*.a' -delete