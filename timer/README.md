
Timers for inactive connections
===============
Inactive connections hold resources and hurt server performance. A server timer closes those connections and frees the resources. `alarm` periodically raises SIGALRM, and the signal handler uses a pipe to tell the main loop to run the tasks on the timer list.
> * Unified event source
> * Timer based on an ascending linked list
> * Close inactive connections
