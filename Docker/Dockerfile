FROM ubuntu:20.04
MAINTAINER Yogesh Barve <yogesh.d.barve@vanderbilt.edu>, Himanshu Neema <himanshu@isis.vanderbilt.edu>, Harmon Nine <harmon.s.nine@vanderbilt.edu>

RUN DEBIAN_FRONTEND=noninteractive apt-get update --fix-missing

RUN DEBIAN_FRONTEND=noninteractive apt-get install bison cmake flex g++ gcc git \
        iputils-ping libboost1.67-all-dev libmysqlclient-dev libopenscenegraph-dev libosgearth-dev \
        openjdk-8-jdk python-is-python3 software-properties-common qt5-default qt5-qmake vim wget -y

RUN cd /tmp && git clone https://github.com/mysql/mysql-connector-cpp.git --single-branch --branch 1.1
RUN cd /tmp/mysql-connector-cpp && \
        cmake . && \
        make clean && \
        make && \
        make install
RUN rm -rf /tmp/mysql-connector-cpp


ENV OMNETPP_RELEASE 5.6.2
ENV OMNETPP_HOME /opt/omnetpp-${OMNETPP_RELEASE}
ENV OMNETPP_WORKSPACE_DIR /home/omnetpp/workspace

RUN cd /tmp && wget -cq https://github.com/omnetpp/omnetpp/releases/download/omnetpp-${OMNETPP_RELEASE}/omnetpp-${OMNETPP_RELEASE}-src-linux.tgz

RUN mkdir -p /opt
RUN cd /opt && tar xf /tmp/omnetpp-${OMNETPP_RELEASE}-src-linux.tgz
RUN cd ${OMNETPP_HOME} && /bin/bash -ic ". ./setenv && ./configure && make"
RUN rm /tmp/omnetpp-${OMNETPP_RELEASE}-src-linux.tgz

ENV PATH $PATH:${OMNETPP_HOME}/bin

ENV INET_RELEASE 4.2.5
ENV INET_HOME ${OMNETPP_WORKSPACE_DIR}/inet4

RUN cd /tmp && wget -cq https://github.com/inet-framework/inet/releases/download/v${INET_RELEASE}/inet-${INET_RELEASE}-src.tgz

RUN mkdir -p /home/omnetpp/workspace
RUN cd /home/omnetpp/workspace && tar xf /tmp/inet-${INET_RELEASE}-src.tgz
RUN cd /home/omnetpp/workspace/inet4 && make makefiles && make
RUN rm /tmp/inet-${INET_RELEASE}-src.tgz

RUN mkdir -p ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/CPSWT/main ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/CPSWT/hla
RUN mkdir -p ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/Project


ENV PORTICO_RELEASE 2.1.0
ENV RTI_HOME /opt/portico-${PORTICO_RELEASE}

RUN cd /tmp && wget -cq https://downloads.sourceforge.net/project/portico/Portico/portico-${PORTICO_RELEASE}/portico-${PORTICO_RELEASE}-linux64.tar.gz
RUN cd /opt && tar xf /tmp/portico-${PORTICO_RELEASE}-linux64.tar.gz
RUN rm /tmp/portico-${PORTICO_RELEASE}-linux64.tar.gz

RUN mkdir -p /root/.ssh && chmod 700 /root/.ssh
COPY git-ssh-key /root/.ssh/id_rsa
RUN ssh-keyscan github.com >> ~/.ssh/known_hosts

RUN cd /tmp && git clone --branch updates-for-inet4,-omnetpp5 --single-branch git@github.com:SimIntToolkit/cpswt-cpp.git
RUN cd ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/CPSWT && cp -r /tmp/cpswt-cpp/foundation/core .
RUN cd ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/CPSWT && cp -r /tmp/cpswt-cpp/foundation/SynchronizedFederate .
RUN cd ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/CPSWT && cp -r /tmp/cpswt-cpp/foundation/rti-base .
RUN cd ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/CPSWT && cp -r /tmp/cpswt-cpp/foundation/C2WConsoleLogger .
RUN cd ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/CPSWT && cp -r /tmp/cpswt-cpp/foundation/config .
RUN rm -rf /tmp/cpswt-cpp

COPY run-sim.sh ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/CPSWT
COPY var_mods.make ${OMNETPP_WORKSPACE_DIR}/OmnetFederate/CPSWT
