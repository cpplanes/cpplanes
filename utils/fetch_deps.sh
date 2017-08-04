#! /bin/bash
#
# fetch_deps.sh
#
# Copyright © 2017 Mathieu Gaborit (matael) <mathieu@matael.org>
#
# Licensed under the "THE BEER-WARE LICENSE" (Revision 42):
# Mathieu (matael) Gaborit wrote this file. As long as you retain this notice you
# can do whatever you want with this stuff. If we meet some day, and you think
# this stuff is worth it, you can buy me a beer or coffee in return
#
# Installs dependencies for cpplanes
#
# - Eigen http://eigen.tuxfamily.org/

project_name='cpplanes'
readme_file='README.rst'
root_dir="$PWD"

wget_flags="--quiet" # --show-progress"

## About Eigen
eigen_archivetype='tar.gz'
eigen_version='3.3.4'
eigen_downloadurl='https://bitbucket.org/eigen/eigen/get'
eigen_projecturl='http://eigen.tuxfamily.org/'
eigen_archive="$eigen_version.$eigen_archivetype"
eigen_archiveurl="$eigen_downloadurl/$eigen_archive"

if [[ "$1" != '--force' ]]; then
	[ ! -e "$readme_file" ] || [ "$(head -n 1 "$readme_file" | cut -d ' ' -f1 )" != "$project_name" ] && {
		echo "This script must be started at the root of the git repo."
		echo "If you know what you're doing (which I strongly doubt about), use --force"
	}
fi

# create the main dir if it doesn't exist
[[ -d deps ]] || {
	echo "Creating deps/"
	mkdir deps/
}

########## EIGEN (http://eigen.tuxfamily.org/) ##########
cd deps/

echo "Installing Eigen ( $eigen_projecturl )"
echo "-> Downloading v. $eigen_version from $eigen_archiveurl"
wget $wget_flags "$eigen_archiveurl" -O "$eigen_archive"
# trick to get the name of the dir
case "$eigen_archivetype" in
	'tar.gz')
		tar xzf "$eigen_archive";;
	'tar.bz2')
		tar xjf "$eigen_archive";;
	'zip')
		unzip -qq "$eigen_archive";;
esac
mv eigen-eigen-* eigen/
rm "$eigen_archive"

cd $root_dir
