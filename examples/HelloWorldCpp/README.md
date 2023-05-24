## To run the HelloWorld example:

[Note: Steps below assume that you have installed CPSWT on your computer as shown in
[CPSWT Installation Instructions for HelloWorldJava example on Ubuntu 20.04 (Focal Fossa)](UbuntuFocalInstall/ubuntuFocalInstall.md) and
[CPSWT Installation Instructions for HelloWorldCpp example on Ubuntu 20.04 (Focal Fossa)](UbuntuFocalInstall/ubuntuFocalInstall.md)]

[Note: Steps below assume that you are already able to run [HelloWorldJava example](https://github.com/SimIntToolkit/cpswt-core/tree/develop/examples/HelloWorldJava)
from the [cpswt-core](https://github.com/SimIntToolkit/cpswt-core) repository]

* Open a terminal and change directory to the HelloWorldCpp directory

* For the first run only, enter the following command:

          gradle wrapper --gradle-version=7.4

* To run the federation, enter the following command:

          ./gradlew :runFederation

### Explanation of HelloWorld example:

In its CPSWT model, the FOM of the HelloWorld example is shown in the figure below:

![HelloWorldCppFOM](Images/HelloWorldCppFOM.png)

The Source federate published the Ping interaction and sends out an infinite sequence of them, printing a message for
each Ping it sends.

The Sink federate subscribes to the Ping interaction and, upon receipt, prints a message to this affect.  It also
publishes a PingCount object that has a single integer attribute pingCount.  It increments pingCount for each Ping
interaction it receives, while also printing the value of pingCount.

The PingCounter federate subscribes to the PingCount object and prints the value of its pingCount attribute
every time it changes.
