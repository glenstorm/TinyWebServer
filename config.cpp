#include "config.h"

Config::Config(){
    //Port number, default 9006
    PORT = 9006;

    //Log write mode, default synchronous
    LOGWrite = 0;

    //Trigger combination, default listenfd LT + connfd LT
    TRIGMode = 0;

    //listenfd trigger mode, default LT
    LISTENTrigmode = 0;

    //connfd trigger mode, default LT
    CONNTrigmode = 0;

    //Graceful close, disabled by default
    OPT_LINGER = 0;

    //Database connection pool size, default 8
    sql_num = 8;

    //Number of threads in the pool, default 8
    thread_num = 8;

    //Close log, disabled by default (logging stays on)
    close_log = 0;

    //Concurrency model, default proactor
    actor_model = 0;
}

void Config::parse_arg(int argc, char*argv[]){
    int opt;
    const char *str = "p:l:m:o:s:t:c:a:";
    while ((opt = getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
        case 'p':
        {
            PORT = atoi(optarg);
            break;
        }
        case 'l':
        {
            LOGWrite = atoi(optarg);
            break;
        }
        case 'm':
        {
            TRIGMode = atoi(optarg);
            break;
        }
        case 'o':
        {
            OPT_LINGER = atoi(optarg);
            break;
        }
        case 's':
        {
            sql_num = atoi(optarg);
            break;
        }
        case 't':
        {
            thread_num = atoi(optarg);
            break;
        }
        case 'c':
        {
            close_log = atoi(optarg);
            break;
        }
        case 'a':
        {
            actor_model = atoi(optarg);
            break;
        }
        default:
            break;
        }
    }
}