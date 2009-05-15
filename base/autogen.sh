#!/bin/sh
# Run this to generate all the initial makefiles, etc.

ccbuild-autotools --namespace libjessevdk generate
autoreconf --install
