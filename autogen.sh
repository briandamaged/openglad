#!/usr/bin/env sh
# $Id$


# Regenerate configuration files
aclocal
autoheader
automake -a
autoconf

# Run configure for this platform
#./configure $*
echo "Now you are ready to run ./configure"
