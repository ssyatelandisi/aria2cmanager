#include <iostream>
#include <direct.h>
#include <string>
#include <windows.h>
#include <conio.h>
/*
 * 函数单词小写，用_链接
 * 类名大驼峰
 * 变量小驼峰
 * 常量全大写 
 */

/* 创建string floderName文件夹 */
void create_floder(std::string folderName)
{
    // 文件夹不存在则创建文件夹
    if (-1 == access(folderName.c_str(), 0))
    {
        mkdir(folderName.c_str());
    }
}

/* 获取输入地址 */
std::string get_link()
{
    std::cout << "提示：可以先复制下载地址，然后在这里右键粘贴\n"
              << std::endl;
    std::string link;
    std::cin >> link;
    return link.c_str();
}

/* 开始下载 */
int run_download(std::string link)
{
    std::string command = "aria2c -s16 -x16 -c --dir=Downloads -U \"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36\" " + link;
    system(command.c_str());
    return 1;
}

int main(int argc, char const *argv[])
{
    SetConsoleOutputCP(65001);     //解决UTF8中文乱码
    std::string link = get_link(); //获取下载链接
    create_floder("Downloads");    //创建Downloads文件夹
    run_download(link.c_str());    //开始下载
    std::cout << "按ESC退出" << std::endl;
    std::cin.sync();
    char c;
    while (c = getch())
    {
        if (27 == c)
            exit(0);
    }
    return 0;
}
