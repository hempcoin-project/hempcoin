#!/bin/bash

set -e

./autogen.sh
cd depends && make $MAKEJOBS $OPT
cd $TRAVIS_BUILD_DIR && ./configure --prefix=$TRAVIS_BUILD_DIR/depends/$HOST $CONF
make $MAKEJOBS $GOAL
echo "all done"
exit 0
