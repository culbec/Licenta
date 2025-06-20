#!/bin/bash

# a), b), c), d), e) are all present in the script explanation

# /usr/sbin is a symbolic link to /usr/bin
# F will take the paths to all files in /usr/bin that are regular files
for F in `find /usr/sbin -type f`; do
    # [ ! -x $F ]                           ----- tests if the file is not marked as executable
    # grep -q -E "^-(.{2}x|.{5}x|.{8}x)"    ----- verifies if the file is executable by the owner, owner group or by others (if the file is executable by the current user?)
    if [ ! -x $F ] && ls -l "$F" | grep -q -E "^-(.{2}x|.{5}x|.{8}x)"
    then
        # interogates a snapshot of the active processes
        # verifies if the file is executing
        # excludes the process of 'grep' which interogates the existence of the process pointed by file in the snapshot
        # prints $F: <total processes that are running the $F file>
        echo "$F:" `ps -e -f | grep -E "$F" | grep -E -v "grep" | wc -l`
    fi
done