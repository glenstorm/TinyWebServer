#include "config.h"

int main(int argc, char *argv[])
{
    //Database settings to edit: login name, password, database name
    string user = "root";
    string passwd = "root";
    string databasename = "qgydb";

    //Parse command-line arguments
    Config config;
    config.parse_arg(argc, argv);

    WebServer server;

    //Initialize
    server.init(config.PORT, user, passwd, databasename, config.LOGWrite, 
                config.OPT_LINGER, config.TRIGMode,  config.sql_num,  config.thread_num, 
                config.close_log, config.actor_model);
    

    //Logging
    server.log_write();

    //Database
    server.sql_pool();

    //Thread pool
    server.thread_pool();

    //Trigger mode
    server.trig_mode();

    //Listen
    server.eventListen();

    //Run
    server.eventLoop();

    return 0;
}