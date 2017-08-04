#! /bin/bash
#
# python-setup.sh
#
# Copyright © 2017 Mathieu Gaborit (matael) <mathieu@matael.org>
#
# Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
# Mathieu (matael) Gaborit wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer or coffee in return
#
# Sets up the python environment for the python prototype

VENV=virtualenv
PY=python3

DEFAULT_DIR=./python

check_if_install() {
	command -v $1 >/dev/null 2>&1 || {
		echo "$1 is required. Please install it first.";
		exit 1
	}
}

# use the basedir passed as argument
case "$1" in
	"--help" )
		echo "Usage :"
		echo "	$0 [base dir]"
		echo ""
		echo "Default base dir: $DEFAULT_DIR"
		exit 1
		;;
	"" )
		basedir="$DEFAULT_DIR"
		;;
	* )
		basedir="$1"
		;;
esac

echo "Using base dir : $basedir"

# check for virtualenv and python
check_if_install $VENV
check_if_install $PY

# create the virtualenv dir and activate
$VENV --python=$PY "$basedir/.venv"
source "$basedir/.venv/bin/activate"

# install requirements
pip install -r $basedir/requirements.txt


