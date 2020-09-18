# aria2cmanager

编译：

资源转换：`windres main.rc -o main.o`

C++版本（推荐）：`g++ main.cpp main.o -m64 -fexec-charset=GBK -finput-charset=UTF-8 -static -o 下载小工具`

C 语言版本（停更）：`gcc main.c main.o -m64 -fexec-charset=GBK -finput-charset=UTF-8 -static-libgcc -static-libstdc++ -o 下载小工具.exe`