#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>
#include <direct.h>
void createFolder(char *folderName)
{
    // 文件夹不存在则创建文件夹
    if (access(folderName, 0) == -1)
    {
        mkdir(folderName);
    }
}
char *getLink()
{
    static char link[2048];
    printf("输入下载地址，按Enter开始下载\n> ");
    gets(link);
    return link;
}
char *formatLink(char *input)
{
    static char output[2048];
    int len = strlen(input);
    for (int i, j = 0; i < len; i++)
    {
        // if (input[i] == '&')
        // {
        //     output[j++] = '\\';
        //     output[j] = input[i];
        // }
        output[j++] = input[i];
    }
    return output;
}
char *mergeCommand(char *input)
{
    char aria2c[] = "aria2c -s16 -x16 -c --dir=Download -U \"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.61 Safari/537.36\" ";
    static char output[4096];
    strcat(output, aria2c);
    strcat(output, "\"");
    strcat(output, input);
    strcat(output, "\"");
    return output;
}
int download(char *input)
{
    int i;
    createFolder("Download");
    i = system(input);
    return i;
}
int start()
{
    char link[2048], input[2048], command[4096];
    /*获取下载地址*/
    strcpy(input, getLink());
    /*格式化地址*/
    // strcpy(link, input);
    strcpy(link, formatLink(input));
    /*拼接命令行*/
    strcpy(command, mergeCommand(link));
    /*执行下载*/
    printf("\n==========开始下载==========\n\n");
    if (!download(command))
    {
        printf("\n\n==========下载完成==========\n\n");
    }
    else
    {
        printf("\n\n==========下载失败==========\n\n");
    }
    return 0;
}
int main()
{
    // SetConsoleOutputCP(65001); //解决UTF8中文乱码
    printf("提示：可以先复制下载地址，然后在这里右键粘贴\n\n");
    start();
    while (1)
    {
        sleep(36000000);
    }
    return 0;
}