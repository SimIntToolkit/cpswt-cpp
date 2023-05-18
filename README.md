# CPSWT C++ Integration

Integrates support for C++ federates into the Cyber-Physical Systems WindTunnel.

Any C++-based federate will use the classes in this repository in order to execute.

The primary projects relating to CPSWT functionality are as follows.  Any projects not listed are under development
or are not currently being used.

## foundation/core

This project contains classes needed for core functionality of any C++ class that implements an HLA interaction or
object class.  A description of some of the more important classes follows:

* TypeMedley

  An instance of this class can represent an HLA interaction parameter of any allowed type (boolean, byte, character, double, float,
  int, long, short, String).


* Attribute

  Derived from the TypeMedley class, an instance of this class can represent an HLA object attribute of any allowed
  type (boolean, byte, character, double, float, int, long, short, String).  It also detects when an attribute
  of an object has changed, so that on an object attribute update, only the values of the attributes that have
  changed are sent into the HLA.


* ClassAndPropertyName

  An instance of this class names a property (parameter of attribute) of an interaction or object that is qualified
  with the name of the interaction or object class in which it is directly defined.  This disambiguates two
  properties of the same name but which are defined in different classes.


* InteractionRootInterface

  Abstract class defining the base interaction of all C++ class implementations of HLA interaction classes.


* ObjectRootInterface

  Abstract class defining the base interaction of all C++ class implementations of HLA object classes.


## foundation/CppTestHarness

This project allows rti stubs to be created for testing of C++ federates, interactions, and objects


## foundation/rti-base

This project the C++ base classes for C++ classes that implement HLA interaction and object classes in CPSWT. These
C++ base classes, InteractionRoot and ObjectRoot, actually contain all of the functionality needed to implement any HLA
interaction or object class. As such, they allow C++-based federates to use dynamic messaging: this enables the
federates to manipulate any HLA interaction or object class instance using only the InteractionRoot or ObjectRoot C++
class, respectively. That is, an HLA interaction or object instance can be manipulated without an explicit
corresponding C++ class.

As well, rti-base contains the explicit corresponding Java class implementations for the a set of built-in HLA
interaction and object classes that are built-in to CPSWT.  This classes are derived from InteractionRoot and
ObjectRoot, and are listed below (indentation shows inheritance):

HLA Interactions:

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

HLA Objects:

    ObjectRoot
      FederateObject

## foundation/config

This project contains Java classes that read federate configuration files.

## foundation/SyncronizedFederate

This project contains the **SynchronizedFederate** class, which is the base class of all C++-based federates.
