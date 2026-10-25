
Authentication and database connection pool
===============
Database connection pool
> * Singleton, so there is only one pool
> * Pool stored in a list
> * Fixed pool size
> * Mutex for thread safety

Authentication
> * HTTP POST
> * Check the login username and password
> * User registration, safe under concurrent threads
