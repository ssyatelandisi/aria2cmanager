#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include <conio.h>
/*
 * 函数单词小写，用_链接
 * 类名大驼峰
 * 变量小驼峰
 * 常量全大写 
 */

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;

const char CONF[]("aria2.conf"); //bt下载配置文件名称

/* 创建string floderName文件夹 */
void create_floder(string folderName)
{
    // 文件夹不存在则创建文件夹
    if (-1 == access(folderName.c_str(), 0))
    {
        mkdir(folderName.c_str());
    }
}

class Aria2cManager
{
public:
    string link, command;

    /* 获取输入链接 */
    void get_link()
    {
        string link;
        cout << "提示：可以先复制下载地址，然后在这里右键粘贴\n"
             << endl;
        cin.sync();
        cin >> link;
        this->link = "\"" + link + "\"";
    }

    /* 赋值链接 */
    void set_link(string link)
    {
        this->link = "\"" + link + "\"";
    }

    /* 获取bt-tracker */
    void get_bt_tracker()
    {
        remove("trackers.txt");
        string commad = "aria2c --out=trackers.txt https://trackerslist.com/all_aria2.txt";
        system(commad.c_str());
        ifstream inFile("trackers.txt", ios::in);
        ofstream outFile(CONF, ios::out);
        outFile << "max-upload-limit=16K\nbt-tracker=";
        string data;
        inFile >> data;
        outFile << data;
        /*         char data[256];
        int index = 0;
        while (inFile.getline(data, 256))
        {
            string stream = data;
            if (stream.length() > 12)
            {
                if (index > 0)
                    outFile << "," << stream;
                else
                    outFile << stream;
                index++;
            }
        } */
        inFile.close();
        outFile.close();
        remove("trackers.txt");
    }

    /* 开始运行 */
    void run()
    {
        cout << this->link << endl;
        if (0 == this->link.compare(1, 7, "http://", 0, 7) ||
            0 == this->link.compare(1, 8, "https://", 0, 8) ||
            0 == this->link.compare(1, 6, "ftp://", 0, 6) ||
            0 == this->link.compare(1, 7, "sftp://", 0, 7))
        {
            this->command = "aria2c -s16 -x16 -c --dir=Downloads -U \"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36\" " + link;
        }
        else
        {
            this->get_bt_tracker();
            this->command = "aria2c -c --dir=Downloads --conf-path=aria2.conf " + link;
        }
        cout << this->command << endl;
        system(this->command.c_str());
    }
};

int main(int argc, char const *argv[])
{
    string link;
    Aria2cManager aria2c_manager;
    if (argc > 1)
    {
        link = argv[1];
        aria2c_manager.set_link(link);
    }
    else
    {
        aria2c_manager.get_link(); //获取下载链接
    }
    create_floder("Downloads"); //创建Downloads文件夹
    aria2c_manager.run();
    cout << "下载结束" << endl;
    cout << "按ESC退出" << endl;
    cin.sync();
    char c;
    while (c = getch())
    {
        if (27 == c)
            exit(0);
    }
    return 0;
}
