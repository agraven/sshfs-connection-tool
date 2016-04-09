# SSHFS Connection Tool
A GTK-3 based front-end for the sshfs tool written in C. The application is currently in very early stages, and has various issues, like:
* Missing features
* Features that are implemented in unholy manners (primarily string manipulation)
* Lack of polish
* Etc.

Here is a screenshot of the application:
![screenshot](http://i.imgur.com/Bzy8ygm.png "Screenshot")

The theme used is [Arc-Dark](https://github.com/horst3180/Arc-theme)

## Dependencies
The project depends on the following
* gtk >= 3.6
* sshfs

## Building
The project is autotools-based, and can be built with the usual:
./configure && make && sudo make install

If configure is missing then running autogen.sh will generate it.
