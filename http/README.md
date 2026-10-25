
HTTP connection handler
===============
The HTTP connection class is built from a main state machine and a line state machine. The main machine calls the line machine, and the line machine passes its state and the parsed data back.
> * The client sends an HTTP request
> * The line machine reads data, updates its own state and the received data, and passes them to the main machine
> * The main machine updates its state from the line machine and either responds or keeps reading
