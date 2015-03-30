**Note:** the fetcher is actually called **spider** in the source code.

Fetcher is the module that allows the whole system to interact with the Web. Namely, it fetches pages via HTTP _(and even HTTPS)_.

Currently, all of it's parts are implemented via different stuff of Qt4.

## Internals ##

The fetcher consists of two threads:
  * one connects to the Web (the main thread);
  * and the second one interacts with the [database](database.md).

They interact with each other via queued-connected signals and a data structure, called CRequest. Each instance of that structure is allocated in the heap (via new operator), the pointer to which is delivered with appropriate inter-thread signals.

### Database ###

Database connectivity is outsourced to the worker thread. The thread uses QSql module (which had to be recompiled to support PostgreSQL, see [the database page](database.md)).

The thread regularily scans the database for new urls. For each new url the thread alloctes and initializes a CRequest structure and sends it to the main thread. The main thread processed the request (see below) and bounces that structure back to the worker thread, which exctracts the response information from the structure and puts it into the database.

Since only the worker thread allocates a timer to check the database regularly, it also checks the exit condition and initiates the shutdown process when necessary.

The shutdown process is implemented via a net of signals (death of the database object triggers the exit of the worker thread, which triggers the death of the web object, which eventually forces the main thread's event loop to exit). Everything should be clean after that. However, QNetworkAccessManager seems to spawn some auxilliary threads, which are not stoped properly. (Anyway, who cares?..)

### Web ###

The web interface is implemented via QNetwork module of Qt. It is managed by the web object, which operates in the main thread. (Surprisingly, the QNetworkAccessManager didn't seem to work properly in any worker thread.)

When the web object receives a CRequest structure in asks the net manager to _get_ it. When the response is ready (the net manager issues `finished` signal), the structure is filled with various response data and is sent back to the worker thread.