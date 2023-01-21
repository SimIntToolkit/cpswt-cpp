#!/bin/bash

#for package in CppTestHarness core-cpp C2WConsoleLogger rti-base-cpp CPSWTConfig SynchronizedFederate; do
for package in SynchronizedFederate; do

    echo "PLEASE REMOVE THE FOLLOWING PACKAGES FROM YOUR MAVEN REPOSITORY:"
    echo
    echo "edu.vanderbilt.vuisis.cpswt.$package"
    echo "edu.vanderbilt.vuisis.cpswt.${package}_debug"
    echo "edu.vanderbilt.vuisis.cpswt.${package}_release"
    echo
    echo -n "PRESS ENTER ONCE THESE PACKAGES HAVE BEEN REMOVED: "
    read dummy
    echo

    COMMAND="./gradlew :foundation:$package:build --rerun-tasks --refresh-dependencies"
    echo "Executing \"$COMMAND\"":
    $COMMAND
    if [ $? -ne 0 ]; then
        echo "COMMAND \"$COMMAND\" FAILED.  PLEASE FIX THE PROBLEM AND RERUN THIS SCRIPT"
        exit 1
    fi
    echo
    COMMAND="./gradlew :foundation:$package:publish"
    $COMMAND
    if [ $? -ne 0 ]; then
        echo "COMMAND \"$COMMAND\" FAILED.  PLEASE FIX THE PROBLEM AND RERUN THIS SCRIPT"
        exit 2
    fi
    echo

done

echo "DONE"
