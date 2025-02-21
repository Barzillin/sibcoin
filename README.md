Sibcoin Core staging tree
===============================

Copyright (c) 2009-2018 Bitcoin Core Developers

Copyright (c) 2014-2019 Dash Core Developers

Copyright (c) 2015-2020 Sibcoin Core Developers


What is Sibcoin?
----------------

Sibcoin is an experimental new digital currency that enables anonymous, instant
payments to anyone, anywhere in the world. Sibcoin uses peer-to-peer technology
to operate with no central authority: managing transactions and issuing money
are carried out collectively by the network. Sibcoin Core is the name of open
source software which enables the use of this currency.


License
-------

SibCore is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.

Development Process
-------------------

Building process
-----------------

Ubuntu 18.04 Lts (tested)
Add:
sudo apt-get install curl, sudo, snapd, git
sudo apt-get install autoconf
sudo apt install libc6-dev
sudo apt-get install libtool
sudo apt-get install pkg-config
sudo apt-get install build-essential
sudo apt-get install libqt4-dev libminiupnpc-dev
sudo apt-get install libboost-all-dev -y
sudo apt install libevent-dev

sudo apt-add-repository universe
sudo apt update
sudo apt install python-minimal

sudo apt update
curl https://bootstrap.pypa.io/pip/2.7/get-pip.py --output get-pip.py
sudo python2 get-pip.py

sudo apt-get install python-twisted-web
pip install zope.interface==3.8.0

sudo apt-get install curl build-essential libtool autotools-dev automake pkg-config python3 bsdmainutils cmake

**compiling Sibcoin from git**

Use the autogen script to prepare the build environment.

    ./autogen.sh
    ./configure
    make

Always verify the signatures and checksums.


Development tips and tricks
---------------------------

**compiling for debugging**

Run configure with the --enable-debug option, then make. Or run configure with
CXXFLAGS="-g -ggdb -O0" or whatever debug flags you need.

**debug.log**

If the code is behaving strangely, take a look in the debug.log file in the data directory;
error and debugging message are written there.

The -debug=... command-line option controls debugging; running with just -debug will turn
on all categories (and give you a very large debug.log file).

The Qt code routes qDebug() output to debug.log under category "qt": run with -debug=qt
to see it.

**testnet and regtest modes**

Run with the -testnet option to run with "play sibcoins" on the test network, if you
are testing multi-machine code that needs to operate across the internet.

If you are testing something that can run on one machine, run with the -regtest option.
In regression test mode blocks can be created on-demand; see qa/rpc-tests/ for tests
that run in -regtest mode.

**DEBUG_LOCKORDER**

SibCore is a multithreaded application, and deadlocks or other multithreading bugs
can be very difficult to track down. Compiling with -DDEBUG_LOCKORDER (configure
CXXFLAGS="-DDEBUG_LOCKORDER -g") inserts run-time checks to keep track of what locks
are held, and adds warning to the debug.log file if inconsistencies are detected.
