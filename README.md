# Project `"cpswt-cpp"` for CPSWT

The cpswt-cpp project contains all software needed to run C++-based federates in CPSWT.
However, to run a federation with C++-based federates, you need the Java-based `federation-manager` module
from the `cpswt-core` project, along with all modules from `cpswt-core` on which it depends.

> ##### Table of Contents
> 
> * [Project `"cpswt-cpp"` for CPSWT](#project-cpswt-cpp-for-cpswt)
>   * [Constituent Modules](#constituent-modules)
>     * [foundation/core](#foundation-core)
>     * [foundation/CppTestHarness](#foundation-cpptestharness)
>     * [foundation/rti-base](#foundation-rti-base)
>     * [foundation/config](#foundation-config)
>     * [foundation/SyncronizedFederate](#foundation-syncronizedfederate)
>   * [CPSWT Installation for HelloWorldCpp example on Ubuntu 20.04 LTS (Focal Fossa)](#cpswt-installation-for-helloworldcpp-example-on-ubuntu-20-04-lts-focal-fossa)
>     * [Software for C++-based Federates](#software-for-c-based-federates)
>       * [Build CPSWT C++ Packages and Publish to Archiva](#build-cpswt-c-packages-and-publish-to-archiva)

## Constituent Modules

`cpswt-cpp` contains the modules needed to run C++-based federates in the Cyber-Physical Systems Wind Tunnel (CPSWT)
federates.

The modules used for C++-base federates are as follows. Any modules not listed are under development or are not
currently being used.

### foundation/core

This project contains classes needed for core functionality of any C++ class that implements an HLA interaction or
object class.  A description of some of the more important classes follows:

* TypeMedley

  An instance of this class can represent an HLA interaction parameter of any allowed type
  (boolean, byte, character, double, float, int, JSON, long, short, String).
* Attribute

  Derived from the TypeMedley class, an instance of this class can represent an HLA object attribute of any allowed
  type (boolean, byte, character, double, float, int, long, short, String). It also detects when an attribute of an
  object has changed, so that on an object attribute update, only the values of the attributes that have changed are
  sent into the HLA.
* ClassAndPropertyName

  An instance of this class names a property (parameter of attribute) of an interaction or object that is qualified
  with the name of the interaction or object class in which it is directly defined. This disambiguates two properties
  of the same name but which are defined in different classes.
* InteractionRootInterface

  Abstract class defining the base interaction of all C++ class implementations of HLA interaction classes.
* ObjectRootInterface

  Abstract class defining the base interaction of all C++ class implementations of HLA object classes.

### foundation/CppTestHarness

This project allows rti stubs to be created for testing of C++ federates, interactions, and objects

### foundation/rti-base

This project the C++ base classes for C++ classes that implement HLA interaction and object classes in CPSWT.
These C++ base classes, InteractionRoot and ObjectRoot, actually contain all of the functionality needed to implement
any HLA interaction or object class. As such, they allow C++-based federates to use dynamic messaging: this enables
the federates to manipulate any HLA interaction or object class instance using only the InteractionRoot or ObjectRoot
C++ class, respectively. That is, an HLA interaction or object instance can be manipulated without an explicit
corresponding C++ class.

As well, rti-base contains the explicit corresponding Java class implementations for the a set of built-in HLA
interaction and object classes that are built-in to CPSWT. This classes are derived from InteractionRoot and
ObjectRoot, and are listed below (indentation shows inheritance):

HLA Interactions:

```default
InteractionRoot
  C2WInteractionRoot
    ActionBase
    EmbeddedMessaging
    FederateJoinInteraction
    FederateResignInteraction
    OutcomeBase
    SimLog
      VeryLowPrio
      LowPrio
      MediumPrio
      HighPrio
    SimulationControl
      SimPause
      SimResume
      SimEnd
```

HLA Objects:

```default
ObjectRoot
  FederateObject
```

### foundation/config

This project contains Java classes that read federate configuration files.

### foundation/SyncronizedFederate

This project contains the SynchronizedFederate class, which is the base class of all C++-based federates.

<a id="cpswtcppsoftwareinstallation"></a>

## CPSWT Installation for HelloWorldCpp example on Ubuntu 20.04 LTS (Focal Fossa)

Before performing these instructions, you must first perform the instructions at
CPSWT Software Installation and Instructions to Build and Publish cpswt-core Modules on Ubuntu 20.04 LTS (Focal Fossa) <[https://github.com/SimIntToolkit/cpswt-core/blob/develop/READE.md](https://github.com/SimIntToolkit/cpswt-core/blob/develop/READE.md)>\`_

The following CPSWT installation instructions were performed on a VirtualBox VM with 128 GB Disk and 12GB RAM.

Currently, only Ubuntu 20.04 LTS (Focal Fossa) is supported.

**NOTE**: There are several text boxes in the instructions below that contain commands that you need to execute at the shell command-line.

To copy any of these commands, hover over the textbox and a small “copy” button will appear at the right of the textbox
(two rounded rectangles, one on top of the other).  Press this button, and the command will be copied to your
clipboard.

Then, to paste the command in your shell, select your shell window and press SHIFT-CTRL-V.

### Software for C++-based Federates

The following instructions show how to install, build and publish software needed to use C++-based federates in CPSWT.

#### Build CPSWT C++ Packages and Publish to Archiva

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

   <a id="cpp-packages"></a>

   #### NOTE
   When *C++ packages* are published to Archiva using Gradle as in this step, each publish command (as above) actually publishes 3 packages:
   * <package-name>
   * <package-name>_debug
   * <package-name>_release
5. To test if the C++ packages have been published to Archiva, do the following:
   1. Go to `http://localhost:8080` using your Google Chrome browser
   2. On the resulting page, click on `Browse` in the upper left-hand corner under `Artifacts`
   3. Under `Browse Repository` in the top-middle-left of the page, click on the small down-arrow on the right side of a small textbox.
   4. In the resulting drop-down menu, click `Archive Managed Snapshot Repository`
   5. Click on `org.cpswt`, which should be a short ways down the page from `Browse Repository` mentioned above.
   6. A list should appear that contains all of the `packages<cpp packages>` you published above using `./gradlew` (in alphabetical order).
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
