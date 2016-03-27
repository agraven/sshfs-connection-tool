#!/bin/sh
(cd builder/ && glib-compile-resources test.gresource.xml --target=../src/resources.c --generate-source)
#gcc src/*.c $(pkg-config --cflags gtk+-3.0) -Iinclude -o bin/gtk-test $(pkg-config --libs gtk+-3.0)
