#!/bin/bash
# Author: Yogesh Barve
export PATH=$PATH:/home/vagrant/c2wt-dev/dependency/omnetpp/omnetpp-4.6/bin
export RTI_HOME=/home/vagrant/c2wt-dev/dependency/portico/portico-2.1.0
export INETMANET_HOME=/home/vagrant/c2wt-dev/dependency/inet/inetmanet-2.0-inetmanet-2.2/
export CONFIGNAME='gcc-debug'
export GENERIC_OMNET_FEDERATE_FOLDER_PATH=/home/vagrant/c2wt-dev/c2wt-cpp/c2wtng-cpp/foundation/OmnetFederate/src/main/gnu

export LD_LIBRARY_PATH=$RTI_HOME/jre/lib/amd64/server/
export OMNET_PATH=$PWD/target/classes

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$RTI_HOME/lib/gcc4/:/home/vagrant/c2wt-dev/dependency/inet/inetmanet-2.0-inetmanet-2.2/out/gcc-debug/src
export C2WDBURL=""
export C2WDBFILE=""
mvn package -P OmnetFed,OmnetFederate


ulimit -c unlimited
cd target/bin-exec/

export RTI_RID_FILE=.

#./target/bin-exec/MapperEx-OmnetFederate-cpp -u Cmdenv -c General -n MapperEx.ini
#./MapperEx-OmnetFederate-cpp -u Cmdenv -c General -n ".;$INETMANET_HOME/src;$GENERIC_OMNET_FEDERATE_FOLDER_PATH" -f MapperEx.ini
#./MapperEx-OmnetFederate-cpp -h
./MapperEx-OmnetFederate-cpp -u Cmdenv -G -c General -n ".;$GENERIC_OMNET_FEDERATE_FOLDER_PATH;$INETMANET_HOME/src" -f MapperEx.ini
