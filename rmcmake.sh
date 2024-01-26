find . -iwholename '*cmake*' -not -name CMakeLists.txt -and -not -name rmcmake.sh -delete
find . -name Makefile -delete
find . -name Parser -delete