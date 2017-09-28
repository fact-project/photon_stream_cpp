# Photon-Stream for C++

To read about what the photon-stream and its file-formats go to the [initial Python repo](https://github.com/fact-project/photon_stream).

This is a C++ reader and writer for the FACT photon-stream.

## All you need 
to either read or write binary photon-stream files:

```photon_stream.h```

__Only__ C++ ```std``` library.



## Examples
Examples on the usage of ```photon_stream.h```. Take a look into the ```example``` directory.

### ASCII event viewer 
Draws FACT events onto your command line.


![img](examples/viewer_1.png) ![img](examples/viewer_2.png)


```bash
g++ examples/docopt/docopt.cpp examples/viewer.cpp -o phs.viewer -std=gnu++11
```

### Table print
Prints a table summary of the events in the input.

```bash
g++ examples/docopt/docopt.cpp examples/table.cpp -o phs.table -std=gnu++11
```
Usage via ```PIPE``` and ```zcat``` to unzip the file.

```bash
zcat tests/resources/20170119_229_pass4_100events.phs.gz | ./phs.table
```
will print:

```
night    run event trigger  Az[deg] ZD[deg]  UnixTime[s]   photons
------------------------------------------------------------------
20170119 229     1      4  -63.25  33.07  1484895232.532244    4984
20170119 229     2      4  -63.25  33.07  1484895232.552913    4857
20170119 229     3      4  -63.25  33.07  1484895232.643769   10615
20170119 229     4      4  -63.25  33.07  1484895232.675652    5221
20170119 229     5      4  -63.25  33.07  1484895232.690576    4661
20170119 229     6      4  -63.25  33.07  1484895232.718719    5692
```
