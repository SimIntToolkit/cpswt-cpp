<!-- CPSWT documentation master file, created by
sphinx-quickstart on Mon May 23 12:55:51 2022.
You can adapt this file completely to your liking, but it should at least
contain the root `toctree` directive. -->
# CPSWT Intallation for HelloWorldCpp example on Ubuntu 20.04 LTS (Focal Fossa)

Before performing these instructions, you must first perform the instructions at
[CPSWT Intallation for HelloWorldJava example on Ubuntu 20.04 LTS (Focal Fossa)](https://github.com/SimIntToolkit/cpswt-core/blob/develop/examples/HelloWorldJava/UbuntuFocalInstall/ubuntuFocalInstall.md)

The following CPSWT installation instructions were performed on a VirtualBox VM with 128 GB Disk and 12GB RAM.

Currently, only Ubuntu 20.04 LTS (Focal Fossa) is supported.

**NOTE**: There are several text boxes in the instructions below that contain commands that you need to execute at the shell command-line.

To copy any of these commands, hover over the textbox and a small “copy” button will appear at the right of the textbox
(two rounded rectangles, one on top of the other).  Press this button, and the command will be copied to your
clipboard.

Then, to paste the command in your shell, select your shell window and press SHIFT-CTRL-V.

## Build CPSWT C++ Packages and Publish to Archiva


1. Clone the cpswt-cpp git repository:


    1. Change your directory to <CPSWT-HOME>:

```bash
cd <CPSWT-HOME>
```


    2. Clone the repository:

```bash
git clone git@github.com:SimIntToolkit/cpswt-cpp.git
```


2. Change to the `<CPSWT-HOME>/cpswt-cpp` directory:

```bash
cd <CPSWT-HOME>/cpswt-cpp
```


3. Install the gradle wrapper:

```bash
gradle wrapper --gradle-version=8.0
```

4. Execute the following sequence of commands **in order**:

```bash
./gradlew :foundation:CppTestHarness:publish
./gradlew :foundation:core-cpp:publish
./gradlew :foundation:C2WConsoleLogger:publish
./gradlew :foundation:rti-base-cpp:publish
./gradlew :foundation:CPSWTConfig:publish
./gradlew :foundation:SynchronizedFederate:publish
```

**NOTE**: When *C++ packages* are published to Archiva using Gradle as in this step, each publish command (as above) actually publishes 3 packages:


    * <package-name>


    * <package-name>_debug


    * <package-name>_release


5. To test if the C++ packages have been published to Archiva, do the following:


    1. Go to `http://localhost:8080` using your Google Chrome browser


    2. On the resulting page, click on `Browse` in the upper left-hand corner under `Artifacts`


    3. Under `Browse Repository` in the top-middle-left of the page, click on the small down-arrow on the right side of a small textbox.


    4. In the resulting drop-down menu, click `Archive Managed Snapshot Repository`


    5. Click on `org.cpswt`, which should be a short ways down the page from `Browse Repository` mentioned above.


    6. A list should appear that contains all of the packages<cpp packages> you published above using `./gradlew` (in alphabetical order).
*The published* Java packages *will also be shown*.


        * C2WConsoleLogger


        * C2WConsoleLogger_debug


        * C2WConsoleLogger_release


        * core-cpp


        * core-cpp_debug


        * core-cpp_release


        * CppTestHarness


        * CppTestHarness_debug


        * CppTestHarness_release


        * CPSWTConfig


        * CPSWTConfig_debug


        * CPSWTConfig_release


        * rti-base-cpp


        * rti-base-cpp_debug


        * rti-base-cpp_release


        * SynchronizedFederate


        * SynchronizedFederate_debug


        * SynchronizedFederate_release


**This concludes the setup for CPSWT for the HelloWorldCpp example!**
