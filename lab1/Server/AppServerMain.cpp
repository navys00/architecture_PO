#include "AppServer.h"
#include "windows.h"

int main (int argc, char *argv[])
{
    int port = 8080;
    Server s;
    s.init(port);
    s.run();
}