# SSHFS Connection Tool
A GTK-3 based front-end for the sshfs tool written in C. The application is currently in very early stages, and has various issues, like:
* Missing features
* Features that are implemented in unholy manners (primarily command invocations)
* Lack of polish
* Etc.

## Dependencies
The project only depends on sshfs and gtk-3.12 (may be compatible with earlier versions).

## Building
The project is autotools-based and can be built with the usual
./configure && make && sudo make install

The resources.c file can be manually rebuilt with build.sh in case make doesn't take care of it.
