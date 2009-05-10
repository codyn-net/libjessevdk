#!/bin/sh
# Run this to generate all the initial makefiles, etc.

aclocal && autoconf && automake --add-missing
