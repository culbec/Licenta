#!/usr/bin/sh

echo "Number of arguments:				$#"
echo "PID current process:				$$"
echo "PID last background process:			$!"
echo "Last returncode:					$?"
echo "Shell options:					$-"
echo "Last argument of the last executed command:	'$_'"
echo

# $* and $@ have the same effect when they do not have quotes
echo '$* without quotes:'
./print_args.sh $*

echo '$@ without quotes:'
./print_args.sh $@

# all arguments as a whole word
echo '$* with quotes:'
./print_args.sh "$*"

# all arguments, as separate strings
echo '$@ with quotes:'
./print_args.sh "$@"
