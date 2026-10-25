#ifndef CONFIG_H
#define CONFIG_H

#include "webserver.h"

using namespace std;

class Config
{
public:
    Config();
    ~Config(){};

    void parse_arg(int argc, char*argv[]);

    //Port number
    int PORT;

    //Log write mode
    int LOGWrite;

    //Trigger combination mode
    int TRIGMode;

    //listenfd trigger mode
    int LISTENTrigmode;

    //connfd trigger mode
    int CONNTrigmode;

    //Graceful close
    int OPT_LINGER;

    //Database connection pool size
    int sql_num;

    //Number of threads in the pool
    int thread_num;

    //Whether logging is closed
    int close_log;

    //Concurrency model
    int actor_model;
};

#endif