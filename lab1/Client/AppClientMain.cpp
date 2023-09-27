#include "Appclient.h"
#include "helpers/UtilString.h"
#include <vector>

int main (int argc, char *argv[])
{
    if(argc < 3 || split(argv[1], ":").size() != 2) //argc - 3 компонента, argv[i] - один из компонентов argc
    {
        printf("USAGE: _AppClient.exe <HOST:PORT> <MESSAGE>\n\n");
        printf("Example: _AppClient.exe 192.168.1.1:12345 Hello world!\n");
        return 0;
    }
    
    std::string msg = argv[2]; //argv[2]- сообщение argv[1] - url адрес 12.0.0.1:12345
    for(int i = 3; i < argc; i++)
        msg += std::string(" ") + argv[i];

    Client c;
    c.send(argv[1], msg);
}