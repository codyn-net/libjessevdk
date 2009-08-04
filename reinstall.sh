#!/bin/bash

for i in base math os network db; do
	echo "Building libjessevdk-$i-0.1..."

	(cd $i && make distclean >/dev/null; packeteer install --package libjessevdk-$i-0.1)
done
