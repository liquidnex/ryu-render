#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "glenv.h"
#include "singleton.h"

class Global : public Singleton<Global>
{
public:
    GLFWwindow* MainWindow = nullptr;
};

#endif