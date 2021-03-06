#!/bin/bash
# 2017-05-02 (cc) <paul4hough@gmail.com>
#
ver=1.01.01

function DoD {
  if ! $*
  then
    echo error:$ "$*"
    exit 2
  fi
}
tdir=`pwd`
export TZ=MST

DoD make -C unit test
DoD make -C .. dist
rm -rf dist
DoD mkdir dist
rm -rf install
DoD mkdir install
DoD cd dist
DoD tar xzf ../../libclue-${ver}.tar.gz
DoD cd libclue-${ver}
# pending libvalid deployment
#DoD ./configure --prefix=$tdir/install
#DoD make install
echo 'all tests passed'
