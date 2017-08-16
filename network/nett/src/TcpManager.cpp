//
// Created by shiyunjie on 2017/6/9.
//

#include "TcpManager.h"

TcpManager::TcpManager()
{

}

TcpManager::~TcpManager()
{

}

int TcpManager::test()
{
    int i = 1000;
#ifdef _DEBUG
    i = 10;
#elif NDEBUG
    i = 100;
#endif
    return i;
}
