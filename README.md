# Photon-Stream for C++

To read about what the photon-stream and its file-formats go to the [initial Python repo](https://github.com/fact-project/photon_stream).

This is a C++ reader and writer for the FACT photon-stream.

All you need to either read or write binary photon-stream files is in ```photon_stream.h```.
Since we do not hate our lifes, wu use __only__ the C++ ```std``` library.

To see examples on the usage of ```photon_stream.h```, take a look into the example directory.
There we have:

- An ASCII event-viewer which draws FACT events onto your command line
- A table tool to print a table like summary  

