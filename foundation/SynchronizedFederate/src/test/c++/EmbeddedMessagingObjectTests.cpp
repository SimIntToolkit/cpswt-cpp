#include "EmbeddedMessagingObjectTests.hpp"
#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjectcpptest/sender/Sender.hpp"
#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjectcpptest/receiver/Receiver.hpp"

#include <boost/lexical_cast.hpp>

typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot InteractionRoot;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging EmbeddedMessaging;

typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot ObjectRoot;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject TestObject;

typedef ::edu::vanderbilt::vuisis::cpswt::hla::embeddedmessagingobjectcpptest::sender::Sender Sender;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::embeddedmessagingobjectcpptest::receiver::Receiver Receiver;


void EmbeddedMessagingObjectTests::testObjectNetworkPropagation() {

    //
    // CREATE Sender -- ALSO INITIALIZES TABLES IN InteractionRoot AND ObjectRoot
    //
    FederateConfigSP senderFederateConfigSP = getNewFederateConfigSP("Sender");
    Sender sender(senderFederateConfigSP.get());

    //
    // CLASS HANDLES FOR FEDERATE-SPECIFIC EmbeddedMessaging INTERACTIONS
    //
    int embeddedMessagingReceiverInteractionClassHandle = InteractionRoot::get_class_handle(
            EmbeddedMessaging::get_hla_class_name() + ".Receiver"
    );
    int embeddedMessagingOmnetFederateInteractionClassHandle = InteractionRoot::get_class_handle(
            EmbeddedMessaging::get_hla_class_name() + ".OmnetFederate"
    );

    //
    // LIST OF INTERACTION-DATA FOR INTERACTIONS SENT BY SENDER
    //
    RTIAmbassadorTest2::SentInteractionDataSPList &sentInteractionDataSPList =
            RTIAmbassadorTest2::get_sent_interaction_data_sp_list();

    //
    // LIST OF REGISTERED-OBJECT-DATA FOR OBJECTS REGISTERED BY SENDER
    //
    RTIAmbassadorTest2::RegisteredObjectDataSPList &registeredObjectDataSPList =
            RTIAmbassadorTest2::get_registered_object_data_sp_list();

    //
    // LIST OF UPDATED-OBJECT-DATA FOR OBJECTS FOR WHICH "updateAttibutes" WAS CALLED BY SENDER
    //
    RTIAmbassadorTest2::UpdatedObjectDataSPList &updatedObjectDataSPList =
            RTIAmbassadorTest2::get_updated_object_data_sp_list();

    // WHEN SENDER WAS CREATED, IT REGISTERED ONE OBJECT
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(registeredObjectDataSPList.size()));

    // GET DATA FOR REGISTERED OBJECT
    RTIAmbassadorTest2::RegisteredObjectDataSP registeredObjectDataSP = registeredObjectDataSPList.back();
    RTIAmbassadorTest2::RegisteredObjectData &registeredObjectData = *registeredObjectDataSP;

    int objectClassHandle = registeredObjectData.getObjectClassHandle();
    int objectHandle = registeredObjectData.getObjectHandle();

    // MAKE SURE CLASS HANDLE OF REGISTERED OBJECT IS CORRECT
    CPPUNIT_ASSERT_EQUAL(TestObject::get_class_handle(), objectClassHandle);

    // ALSO WHEN SENDER WAS CREATED, IT SENT OUT 2 INTERACTIONS
    // * ONE FederateJoinInteraction
    // * ONE EmbeddedMessaging.Receiver INTERACTION TO TELL THE RECEIVER ONLY TO RECEIVE ATTRIBUTE
    //   UPDATES FOR THE OBJECT THROUGH A NETWORK (I.E. NOT DIRECTLY FROM THE RTI).
    CPPUNIT_ASSERT_EQUAL(2, static_cast<int>(sentInteractionDataSPList.size()));

    // ONLY INTERESTED IN THE EmbeddedMessaging.Receiver INTERACTION
    RTIAmbassadorTest2::SentInteractionDataSP objectUpdatesOnlyThroughNetworkInteractionDataSP =
            sentInteractionDataSPList.back();
    RTIAmbassadorTest2::SentInteractionData &objectUpdatesOnlyThroughNetworkInteractionData =
      *objectUpdatesOnlyThroughNetworkInteractionDataSP;

    // MAKE SURE CLASS HANDLE OF SENT EmbeddedMessaging.Receiver INTERACTION IS FOR
    // EmbeddedMessaging.Receiver CLASS
    int embeddedMessagingReceiverInteractionDataClassHandle =
            objectUpdatesOnlyThroughNetworkInteractionData.getInteractionClassHandle();
    CPPUNIT_ASSERT_EQUAL(
            embeddedMessagingReceiverInteractionClassHandle, embeddedMessagingReceiverInteractionDataClassHandle
    );

    // CREATE A LOCAL INTERACTION INSTANCE FROM THE INTERACTION DATA OF THE SENT EmbeddedMessagingReceiver
    // INTERACTION
    const RTI::ParameterHandleValuePairSet &embeddedMessagingDiscoverParameterHandleValuePairSet =
            objectUpdatesOnlyThroughNetworkInteractionData.getParameterHandleValuePairSet();
    InteractionRoot::SP localEmbeddedMessagingReceiverInteractionRootSP = InteractionRoot::create_interaction(
            embeddedMessagingReceiverInteractionDataClassHandle, embeddedMessagingDiscoverParameterHandleValuePairSet
    );

    // CAST THE LOCAL INTERACTION TO EmbeddedInteraction.Receiver
    edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::Receiver::SP
      localEmbeddedMessagingReceiverInteractionSP =
        boost::dynamic_pointer_cast<
          edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::Receiver
        >(localEmbeddedMessagingReceiverInteractionRootSP);

    // MAKE SURE THE CREATED LOCAL INTERACTION IS OF TYPE EmbeddedInteraction.Receiver
    CPPUNIT_ASSERT(localEmbeddedMessagingReceiverInteractionSP);

    edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::Receiver
      &localEmbeddedMessagingReceiverInteraction = *localEmbeddedMessagingReceiverInteractionSP;

    // command FOR EmbeddedInteraction.Receiver INTERACTION SHOULD BE "discover"
    CPPUNIT_ASSERT_EQUAL(localEmbeddedMessagingReceiverInteraction.get_command(), std::string("discover"));
    // hlaClassName FOR EmbeddedInteraction.Receiver INTERACTION SHOULD BE for TestOBject
    CPPUNIT_ASSERT_EQUAL(
            localEmbeddedMessagingReceiverInteraction.get_hlaClassName(), TestObject::get_hla_class_name())
    ;

    // messagingJson SHOULD CONTAIN THE OBJECT HANDLE FOR THE OBJECT REGISTERED BY THE SENDER
    std::istringstream jsonInputStream(localEmbeddedMessagingReceiverInteraction.get_messagingJson());

    Json::Value jsonObject;
    jsonInputStream >> jsonObject;

    CPPUNIT_ASSERT_EQUAL(jsonObject["object_handle"].asInt(), sender.getTestObject().getObjectHandle());
    CPPUNIT_ASSERT_EQUAL(jsonObject["object_handle"].asInt(), objectHandle);

    // THROW AWAY INTERACTION DATA SENT BY SENDER UP TO THIS POINT -- ALREADY TESTED
    sentInteractionDataSPList.clear();

    // EXECUTE THE SENDER -- SHOULD ASSIGN ATTRIBUTE VALUES TO REGISTERED OBJECT AND SEND OUT
    // THE NEW VALUES OF THE ATTRIBUTES IT PUBLISHES VIA AN "updateAttributes" CALL.
    sender.execute();

    // NUMBER OF OBJECTS UPDATED BY SENDER SHOULD BE 1
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(updatedObjectDataSPList.size()));

    // GET THE DATA ASSOCIATED WITH THE UPDATED ATTRIBUTES OF THE REGISTERED OBJECT
    RTIAmbassadorTest2::UpdatedObjectDataSP updatedObjectDataSP = updatedObjectDataSPList.back();
    RTIAmbassadorTest2::UpdatedObjectData &updatedObjectData = *updatedObjectDataSP;

    // GET THE REGISTERED OBJECT DIRECTLY FROM THE SENDER
    TestObject &senderTestObject = sender.getTestObject();

    // OBJECT HANDLE OF UPDATED OBJECT SHOULD BE EQUAL TO OBJECT HANDLE OF REGISTERED OBJECT
    CPPUNIT_ASSERT_EQUAL(senderTestObject.getObjectHandle(), updatedObjectData.getObjectHandle());

    // ReflectedAttributes SHOULD BE PRESENT IN THE UPDATED-OBJECT DATA, AND SHOULD ONLY
    // CONTAIN DATA FOR 7 ATTRIBUTE -- THE NUMBER THAT ARE PUBLISHED.
    CPPUNIT_ASSERT_EQUAL(7, static_cast<int>(updatedObjectData.getAttributeHandleValuePairSet().size()));

    // CREATE A LOCAL OBJECT INSTANCE FROM THE OBJECT-DATA THAT WAS SENT OUT FROM THE "updateAttributes"
    // CALL
    ObjectRoot::SP localTestObjectObjectRootSP =
            ObjectRoot::create_object(objectClassHandle, updatedObjectData.getAttributeHandleValuePairSet());

    TestObject::SP localTestObjectSP =
        boost::dynamic_pointer_cast<TestObject>(localTestObjectObjectRootSP);

    // THE LOCAL OBJECT SHOULD BE A TestObject
    CPPUNIT_ASSERT(localTestObjectSP);

    TestObject &localTestObject = *localTestObjectSP;

    // THE ATTRIBUTES THAT ARE PUBLISHED FOR THE REGISTERED OBJECT SHOULD HAVE THE SAME VALUES
    // AS THE CORRESPONDING ATTRIBUTES IN THE LOCAL OBJECT
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_BooleanValue1(), localTestObject.get_BooleanValue1());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_BooleanValue2(), localTestObject.get_BooleanValue2());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_ByteValue(), localTestObject.get_ByteValue());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_CharValue(), localTestObject.get_CharValue());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(senderTestObject.get_DoubleValue(), localTestObject.get_DoubleValue(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(senderTestObject.get_FloatValue(), localTestObject.get_FloatValue(), 0.001);
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_IntValue(), localTestObject.get_IntValue());

    // THE ATTRIBUTES THAT ARE *NOT* PUBLISHED FOR THE REGISTERED OBJECT SHOULD *NOT* HAVE THE SAME VALUES
    // AS THE CORRESPONDING ATTRIBUTES IN THE LOCAL OBJECT
    CPPUNIT_ASSERT(senderTestObject.get_LongValue() != localTestObject.get_LongValue());
    CPPUNIT_ASSERT(senderTestObject.get_ShortValue() != localTestObject.get_ShortValue());
    CPPUNIT_ASSERT(senderTestObject.get_StringValue() != localTestObject.get_StringValue());

    // WHEN THE SENDER CALLED "updateAttributes" FOR THE REGISTERED OBJECT, IT SHOULD ALSO HAVE
    // SENT AN EmbeddedMessaging.OmnetFederate INTERACTION TO SEND THE UPDATED ATTRIBUTES THROUGH
    // A SIMULATED NETWORK.
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(sentInteractionDataSPList.size()));

    // GET THE INTERACTION-DATA ASSOCIATED WITH THE ATTRIBUTES UPDATE
    RTIAmbassadorTest2::SentInteractionDataSP updatedAttributesEmbeddedMessagingOmnetFederateDataSP =
      sentInteractionDataSPList.back();

    RTIAmbassadorTest2::SentInteractionData &updatedAttributesEmbeddedMessagingOmnetFederateData =
      *updatedAttributesEmbeddedMessagingOmnetFederateDataSP;

    // THE CLASS HANDLE OF THE INTERACTION ASSOCIATED WITH THE ATTRIBUTES UPDATE SHOULD
    // THAT OF THE OmnetFederate-SPECIFIC EmbeddedMessaging INTERACTION
    int updateAttributesEmbeddedMessagingOmnetFederateClassHandle =
            updatedAttributesEmbeddedMessagingOmnetFederateData.getInteractionClassHandle();
    CPPUNIT_ASSERT_EQUAL(
            embeddedMessagingOmnetFederateInteractionClassHandle,
            updateAttributesEmbeddedMessagingOmnetFederateClassHandle
    );

    // CREATE A LOCAL INSTANCE OF THE INTERACTION ASSOCIATED WITH THE ATTRIBUTES UPDATE
    InteractionRoot::SP localEmbeddedMessagingOmnetFederateInteractionRootSP = InteractionRoot::create_interaction(
            updateAttributesEmbeddedMessagingOmnetFederateClassHandle,
           updatedAttributesEmbeddedMessagingOmnetFederateData.getParameterHandleValuePairSet()
    );

    edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::OmnetFederate::SP
      localEmbeddedMessagingOmnetFederateInteractionSP =
        boost::dynamic_pointer_cast<
          edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::OmnetFederate
        >(localEmbeddedMessagingOmnetFederateInteractionRootSP);


    // THE LOCAL INTERACTION SHOULD BE OF THE OmnetFederate-SPECIFIC EmbeddedMessaging CLASS
    CPPUNIT_ASSERT(localEmbeddedMessagingOmnetFederateInteractionSP);

    // CAST THE LOCAL INTERACTION TO THE OmnetFederate-SPECIFIC EmbeddedMessaging CLASS
    ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::OmnetFederate
      &localEmbeddedMessagingOmnetFederateInteraction = *localEmbeddedMessagingOmnetFederateInteractionSP;

    // THE command FOR THE LOCAL EmbeddedMessaging.OmnetFederate INTERACTION SHOULD BE "object"
    CPPUNIT_ASSERT_EQUAL(localEmbeddedMessagingOmnetFederateInteraction.get_command(), std::string("object"));

    // THE hlaClassName SHOULD BE FOR TestObject
    CPPUNIT_ASSERT_EQUAL(
            localEmbeddedMessagingOmnetFederateInteraction.get_hlaClassName(), TestObject::get_hla_class_name()
    );

    std::istringstream jsonInputStream2(localEmbeddedMessagingOmnetFederateInteraction.get_messagingJson());

    Json::Value objectReflectorJson;
    jsonInputStream2 >> objectReflectorJson;

    Json::Value objectReflectorJsonPropertiesMap = objectReflectorJson["properties"];

    // THE messagingJson SHOULD BE FOR ALL OF THE PUBLISHED ATTRIBUTES
    CPPUNIT_ASSERT_EQUAL(7, static_cast<int>(objectReflectorJsonPropertiesMap.size()));

    // GET ClassAndPropertyNameValueMap FOR THE senderTestObject
    const ObjectRoot::ClassAndPropertyNameValueSPMap &senderClassAndPropertyNameValueSPMap =
            senderTestObject.getClassAndPropertyNameValueSPMap();

    // GET TestObject CLASS SUBSCRIBED ATTRIBUTE NAMES (ClassAndPropertyName SET)
    ClassAndPropertyNameSet &testObjectPublishedAttributeSet =
            *TestObject::get_published_attribute_name_set_sp();

    // testObjectClassAndPropertyNameSet SHOULD HAVE 7 MEMBERS
    CPPUNIT_ASSERT_EQUAL(7, static_cast<int>(testObjectPublishedAttributeSet.size()));

    // MAKE SURE objectReflector HAS SAME JSON-ENCODED ATTRIBUTE VALUES AS VALUES OF ATTRIBUTES
    // FOR senderTestObject
    for(const ClassAndPropertyName &classAndPropertyName: testObjectPublishedAttributeSet) {
        const ObjectRoot::Value &value = *senderClassAndPropertyNameValueSPMap.find(classAndPropertyName)->second;
        std::string valueString = value.getDataType() == ObjectRoot::Value::CHARACTER ?
          boost::lexical_cast<std::string>(value.asInt()) : value.asString();
        CPPUNIT_ASSERT_EQUAL(
                valueString,
                objectReflectorJsonPropertiesMap[static_cast<std::string>(classAndPropertyName)].asString()
        );
    }

    // CLEAR OBJECTS IN ObjectRoot._objectHandleInstanceMap, SINCE THE Receiver FEDERATE ALSO USES IT.
    sender.unregisterObject(senderTestObject);


    // CLEAR THE AMBASSADOR PROXY FOR THE Receiver FEDERATE
    RTIAmbassadorTest2::clear();

    // CREATE THE RECEIVER FEDERATE
    FederateConfigSP receiverFederateConfigSP = getNewFederateConfigSP("Receiver");
    Receiver receiver(receiverFederateConfigSP.get());

    // THE RECEIVER SHOULD NOT HAVE THE TestObject YET
    CPPUNIT_ASSERT(!receiver.getTestObjectSP());

    // HAVE THE RECEIVER FEDERATE DISCOVER THE OBJECT INSTANCE SENT BY THE SENDER
    receiver.discoverObjectInstance(objectHandle, objectClassHandle, nullptr);

    Receiver::ReceiverATRCallback advanceTimeRequest(receiver);
    receiver.putAdvanceTimeRequest(0, advanceTimeRequest);

    // ALSO HAVE THE RECEIVER RECEIVE THE EmbeddedMessaging.Receiver INTERACTION THAT TELLS IS TO IGNORE
    // ATTRIBUTE UPDATES FOR THE TestObject WHEN RECEIVED DIRECTLY FROM THE RTI, AND ONLY RECEIVE
    // THEM THROUGH EmbeddedMessaging
    receiver.receiveInteraction(
            embeddedMessagingReceiverInteractionDataClassHandle,
            embeddedMessagingDiscoverParameterHandleValuePairSet,
            nullptr
    );

    CPPUNIT_ASSERT(!receiver.getTestObjectSP());

    // TRY TO UPDATE OBJECT IN RECEIVER DIRECTLY FROM RTI
    receiver.reflectAttributeValues(
            objectHandle,
            updatedObjectData.getAttributeHandleValuePairSet(),
            updatedObjectData.getRTIfedTime(),
            nullptr,
            RTI::EventRetractionHandle()
    );

    // THE Receiver SHOULD IGNORE THE "reflectAttributeValues" CALL ABOVE, SO PERFORMED THE ACTIONS ASSOCIATED T
    receiver.execute();

    // THE RECEIVER SHOULD *STILL* Not HAVE THE TestObject YET AS IT SHOULD NOT ACCEPT UPDATES FOR THE OBJECT
    // DIRECTLY FROM THE RTI
    CPPUNIT_ASSERT(!receiver.getTestObjectSP());

    // SEND THE RECEIVER THE EmbeddedMessaging.Receiver INTERACTION THAT CONTAINS THE ATTRIBUTES UPDATE
    // FOR THE DISCOVERED OBJECT
    receiver.receiveInteraction(
            updatedAttributesEmbeddedMessagingOmnetFederateData.getInteractionClassHandle(),
            updatedAttributesEmbeddedMessagingOmnetFederateData.getParameterHandleValuePairSet(),
            updatedAttributesEmbeddedMessagingOmnetFederateData.getRTIfedTime(),
            nullptr,
            RTI::EventRetractionHandle()
    );

    // THIS WILL CAUSE THE Receiver TO APPLY THE ObjectReflector TO ITS LOCAL COPY OF THE TestObject INSTANCE
    // AND MAKE THE INSTANCE ACCESSIBLE THROUGH ITS getTestObject() METHOD
    receiver.execute();

    // THE RECEIVER SHOULD NOW HAVE THE OBJECT
    TestObject::SP receivedTestObjectSP = receiver.getTestObjectSP();
    CPPUNIT_ASSERT(receivedTestObjectSP);

    TestObject &receivedTestObject = *receivedTestObjectSP;
    CPPUNIT_ASSERT(!receivedTestObject.get_BooleanValue1());
    CPPUNIT_ASSERT(!receivedTestObject.get_BooleanValue2());

    CPPUNIT_ASSERT(senderTestObject.get_ByteValue() != receivedTestObject.get_ByteValue());

    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_CharValue(), receivedTestObject.get_CharValue());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(senderTestObject.get_DoubleValue(), receivedTestObject.get_DoubleValue(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(senderTestObject.get_FloatValue(), receivedTestObject.get_FloatValue(), 0.001);
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_IntValue(), receivedTestObject.get_IntValue());

    CPPUNIT_ASSERT(senderTestObject.get_LongValue() != receivedTestObject.get_LongValue());
    CPPUNIT_ASSERT(senderTestObject.get_ShortValue() != receivedTestObject.get_ShortValue());
    CPPUNIT_ASSERT(senderTestObject.get_StringValue() != receivedTestObject.get_StringValue());
}

CPPUNIT_TEST_SUITE_REGISTRATION( EmbeddedMessagingObjectTests );
