#!/bin/bash

rm -rf /tmp/libcurl3
rm -rf /tmp/libcurl4

source /etc/upstream-release/lsb-release 2>/dev/null || source /etc/lsb-release

apt-get update
pushd /tmp
apt-get download libcurl4
dpkg-deb -R libcurl4_*.deb libcurl4/
sed -i '/^Conflicts: libcurl3/d' libcurl4/DEBIAN/control
dpkg-deb -b libcurl4 libcurl4-custom.deb
dpkg -i libcurl4-custom.deb
apt-get download libcurl3
dpkg-deb -R libcurl3_*.deb libcurl3/
sed -i '/^Conflicts: libcurl4/d' libcurl3/DEBIAN/control
dpkg-deb -b libcurl3 libcurl3-custom.deb
dpkg -i libcurl3-custom.deb
popd

apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 5AFA7A83
echo "deb [arch=amd64] http://ubuntu.openvidu.io/6.15.0 bionic kms6" | tee /etc/apt/sources.list.d/kurento.list


DEBIAN_FRONTEND=noninteractive apt-get update && mk-build-deps --install --remove --tool="apt-get -o Debug::pkgProblemResolver=yes --target-release '*-backports' --no-install-recommends --no-remove --yes" ./debian/control

PACKAGE_VERSION="$(dpkg-parsechangelog --show-field Version)"

gbp dch --ignore-branch --git-author --spawn-editor=never --new-version="${PACKAGE_VERSION}.${DISTRIB_RELEASE}" --release ./debian/

GBP_BUILDER="debuild --preserve-env --no-tgz-check -i -I"
export CTEST_OUTPUT_ON_FAILURE=1
export GST_DEBUG_NO_COLOR=1

gbp buildpackage --git-ignore-new --git-ignore-branch --git-upstream-tree=SLOPPY --git-builder="debuild --preserve-env --no-tgz-check -i -I" -uc -us

find "$(realpath ..)" -maxdepth 1 -type f -name '*.*deb' -not -path "./" -print0 | xargs -0 --no-run-if-empty mv --target-directory="."




