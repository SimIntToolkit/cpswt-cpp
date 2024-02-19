#include "EmbeddedMessagingObjectTests.hpp"
#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjecttestcpp/sender/Sender.hpp"
#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjecttestcpp/receiver/Receiver.hpp"
#include <cmath>

#include <boost/lexical_cast.hpp>

typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot InteractionRoot;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::
  InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging EmbeddedMessaging;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::
  InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::TestOmnetFederate TestOmnetFederate;

typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot ObjectRoot;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject TestObject;

typedef ::edu::vanderbilt::vuisis::cpswt::hla::embeddedmessagingobjecttestcpp::sender::Sender Sender;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::embeddedmessagingobjecttestcpp::receiver::Receiver Receiver;


void EmbeddedMessagingObjectTests::testObjectNetworkPropagation() {

    std::cout << "STARTING \"EmbeddedMessagingObjectTests::testObjectNetworkPropagation\"" << std::endl;
    std::cout << std::endl;

    RTIAmbassadorTest2 &rtiAmbassadorTest2 = RTIAmbassadorTest2::get_instance();

    //
    // CREATE Sender -- ALSO INITIALIZES TABLES IN InteractionRoot AND ObjectRoot
    //
    FederateConfigSP senderFederateConfigSP = getNewFederateConfigSP("Sender");
    Sender sender(senderFederateConfigSP.get());

    rtiAmbassadorTest2.setSynchronizedFederate(sender);

    //
    // CLASS HANDLES FOR FEDERATE-SPECIFIC EmbeddedMessaging INTERACTIONS
    //
    int embeddedMessagingOmnetFederateInteractionClassHandle = InteractionRoot::get_class_handle(
            EmbeddedMessaging::get_hla_class_name() + ".TestOmnetFederate"
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
    // * FederateJoinInteraction
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(sentInteractionDataSPList.size()));

    // THROW AWAY INTERACTION DATA SENT BY SENDER UP TO THIS POINT -- ALREADY TESTED
    sentInteractionDataSPList.clear();

    // EXECUTE THE SENDER -- SHOULD ASSIGN ATTRIBUTE VALUES TO REGISTERED OBJECT AND SEND OUT
    // THE NEW VALUES OF THE ATTRIBUTES IT PUBLISHES VIA AN "updateAttributes" CALL.
    sender.initialize();

    sender.iteration();
    sender.iteration();

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
    // CONTAIN DATA FOR 10 ATTRIBUTES -- THE NUMBER THAT ARE PUBLISHED.
    CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(updatedObjectData.getAttributeHandleValuePairSet().size()));

    // CREATE A LOCAL OBJECT INSTANCE FROM THE OBJECT-DATA THAT WAS SENT OUT FROM THE "updateAttributes"
    // CALL
    ObjectRoot::SP localTestObjectRootSP =
            ObjectRoot::create_object(objectClassHandle, updatedObjectData.getAttributeHandleValuePairSet());

    TestObject::SP localTestObjectSP =
        boost::dynamic_pointer_cast<TestObject>(localTestObjectRootSP);

    // THE LOCAL OBJECT SHOULD BE A TestObject
    CPPUNIT_ASSERT(localTestObjectSP);

    TestObject &localTestObject = *localTestObjectSP;

    // THE ATTRIBUTES THAT ARE PUBLISHED FOR THE REGISTERED OBJECT SHOULD HAVE THE SAME VALUES
    // AS THE CORRESPONDING ATTRIBUTES IN THE LOCAL OBJECT
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_BoolValue1(), localTestObject.get_BoolValue1());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_BoolValue2(), localTestObject.get_BoolValue2());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_ByteValue(), localTestObject.get_ByteValue());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_CharValue(), localTestObject.get_CharValue());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(senderTestObject.get_FloatValue(), localTestObject.get_FloatValue(), 0.001);
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_IntValue(), localTestObject.get_IntValue());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_LongValue(), localTestObject.get_LongValue());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_ShortValue(), localTestObject.get_ShortValue());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_JSONValue1(), localTestObject.get_JSONValue1());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_JSONValue2(), localTestObject.get_JSONValue2());

    // THE ATTRIBUTES THAT ARE *NOT* PUBLISHED FOR THE REGISTERED OBJECT SHOULD *NOT* HAVE THE SAME VALUES
    // AS THE CORRESPONDING ATTRIBUTES IN THE LOCAL OBJECT
    CPPUNIT_ASSERT(fabs(senderTestObject.get_DoubleValue() - localTestObject.get_DoubleValue()) > 0.001);
    CPPUNIT_ASSERT(senderTestObject.get_StringValue() != localTestObject.get_StringValue());

    // WHEN THE SENDER CALLED "updateAttributes" FOR THE REGISTERED OBJECT, IT SHOULD ALSO HAVE
    // SENT AN EmbeddedMessaging.TestOmnetFederate INTERACTION TO SEND THE UPDATED ATTRIBUTES THROUGH
    // A SIMULATED NETWORK.
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(sentInteractionDataSPList.size()));

    // GET THE INTERACTION-DATA ASSOCIATED WITH THE ATTRIBUTES UPDATE
    RTIAmbassadorTest2::SentInteractionDataSP updatedAttributesEmbeddedMessagingOmnetFederateDataSP =
      sentInteractionDataSPList.back();

    RTIAmbassadorTest2::SentInteractionData &updatedAttributesEmbeddedMessagingOmnetFederateData =
      *updatedAttributesEmbeddedMessagingOmnetFederateDataSP;

    // THE CLASS HANDLE OF THE INTERACTION ASSOCIATED WITH THE ATTRIBUTES UPDATE SHOULD
    // THAT OF THE TestOmnetFederate-SPECIFIC EmbeddedMessaging INTERACTION
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

    TestOmnetFederate::SP localEmbeddedMessagingOmnetFederateInteractionSP =
      boost::dynamic_pointer_cast<TestOmnetFederate>(localEmbeddedMessagingOmnetFederateInteractionRootSP);

    // THE LOCAL INTERACTION SHOULD BE OF THE TestOmnetFederate-SPECIFIC EmbeddedMessaging CLASS
    CPPUNIT_ASSERT(localEmbeddedMessagingOmnetFederateInteractionSP);

    // CAST THE LOCAL INTERACTION TO THE TestOmnetFederate-SPECIFIC EmbeddedMessaging CLASS
    TestOmnetFederate &localEmbeddedMessagingOmnetFederateInteraction =
      *localEmbeddedMessagingOmnetFederateInteractionSP;

    std::istringstream jsonInputStream2(localEmbeddedMessagingOmnetFederateInteraction.get_messagingJson());

    Json::Value objectReflectorJson;
    jsonInputStream2 >> objectReflectorJson;

    // THE messaging_type FOR THE LOCAL EmbeddedMessaging.TestOmnetFederate INTERACTION SHOULD BE "object"
    std::string messagingType = objectReflectorJson["messaging_type"].asString();
    CPPUNIT_ASSERT_EQUAL(messagingType, std::string("object"));

    // THE hlaClassName SHOULD BE FOR TestObject
    std::string messagingName = objectReflectorJson["messaging_name"].asString();
    CPPUNIT_ASSERT_EQUAL(messagingName, TestObject::get_hla_class_name());

    Json::Value objectReflectorJsonPropertiesMap = objectReflectorJson["properties"];

    // THE messagingJson SHOULD BE FOR ALL OF THE PUBLISHED ATTRIBUTES
    CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(objectReflectorJsonPropertiesMap.size()));

    // GET ClassAndPropertyNameValueMap FOR THE senderTestObject
    const ObjectRoot::ClassAndPropertyNameValueSPMap &senderClassAndPropertyNameValueSPMap =
            senderTestObject.getClassAndPropertyNameValueSPMap();

    // GET TestObject CLASS SUBSCRIBED ATTRIBUTE NAMES (ClassAndPropertyName SET)
    ClassAndPropertyNameSet &testObjectPublishedAttributeSet =
            *TestObject::get_published_attribute_name_set_sp();

    // testObjectClassAndPropertyNameSet SHOULD HAVE 7 MEMBERS
    CPPUNIT_ASSERT_EQUAL(10, static_cast<int>(testObjectPublishedAttributeSet.size()));

    // MAKE SURE objectReflector HAS SAME JSON-ENCODED ATTRIBUTE VALUES AS VALUES OF ATTRIBUTES
    // FOR senderTestObject
    for(const ClassAndPropertyName &classAndPropertyName: testObjectPublishedAttributeSet) {

        const ObjectRoot::Value &value = *senderClassAndPropertyNameValueSPMap.find(classAndPropertyName)->second;
        const Json::Value jsonValue = objectReflectorJsonPropertiesMap[static_cast<std::string>(classAndPropertyName)];

        switch(value.getDataType()) {
            case TypeMedley::BOOLEAN: {
                CPPUNIT_ASSERT_EQUAL(value.asBool(), jsonValue.asBool());
                break;
            }
            case TypeMedley::CHARACTER: {
                int intValue = 0;
                if (jsonValue.isString()) {
                    std::string stringValue = jsonValue.asString();
                    intValue = stringValue.size() > 0 ? stringValue[0] : 0;
                } else {
                    intValue = jsonValue.isNumeric() ? value.asInt() : 0;
                }
                char jsonCharValue = static_cast<char>(intValue);
                CPPUNIT_ASSERT_EQUAL(value.asChar(), jsonCharValue);
                break;
            }
            case TypeMedley::SHORT: {
                short jsonShortValue = static_cast<short>(jsonValue.asInt());
                CPPUNIT_ASSERT_EQUAL(value.asShort(), jsonShortValue);
                break;
            }
            case TypeMedley::INTEGER: {
                CPPUNIT_ASSERT_EQUAL(value.asInt(), jsonValue.asInt());
                break;
            }
            case TypeMedley::LONG: {
                long jsonLongValue = static_cast<long>(jsonValue.asInt64());
                CPPUNIT_ASSERT_EQUAL(value.asLong(), jsonLongValue);
                break;
            }
            case TypeMedley::FLOAT: {
                CPPUNIT_ASSERT_EQUAL(value.asFloat(), jsonValue.asFloat());
                break;
            }
            case TypeMedley::DOUBLE: {
                CPPUNIT_ASSERT_EQUAL(value.asDouble(), jsonValue.asDouble());
                break;
            }
            case TypeMedley::STRING: {
                CPPUNIT_ASSERT_EQUAL(value.asString(), jsonValue.asString());
                break;
            }
            case TypeMedley::JSON: {
                CPPUNIT_ASSERT_EQUAL(value.asJson(), jsonValue);
                break;
            }
        }
    }

    // CLEAR OBJECTS IN ObjectRoot._objectHandleInstanceMap, SINCE THE Receiver FEDERATE ALSO USES IT.
    sender.unregisterObject(senderTestObject);

    sender.iteration(); // EMPTY THE ATRQUEUE

    // CLEAR THE AMBASSADOR PROXY FOR THE Receiver FEDERATE
    RTIAmbassadorTest2::clear();
    rtiAmbassadorTest2.resetCurrentTime();

    //
    // CREATE THE RECEIVER FEDERATE
    //
    FederateConfigSP receiverFederateConfigSP = getNewFederateConfigSP("Receiver");
    Receiver receiver(receiverFederateConfigSP.get());

    rtiAmbassadorTest2.setSynchronizedFederate(receiver);

    // THE RECEIVER SHOULD NOT HAVE THE TestObject YET
    CPPUNIT_ASSERT(!receiver.getTestObjectSP());

    // HAVE THE RECEIVER FEDERATE DISCOVER THE OBJECT INSTANCE SENT BY THE SENDER
    receiver.discoverObjectInstance(objectHandle, objectClassHandle, nullptr);

//    Receiver::ReceiverATRCallback advanceTimeRequest(receiver);
//    receiver.putAdvanceTimeRequest(0, advanceTimeRequest);
//
    ObjectRoot::AttributeHandleSet &attributeHandleSet = *TestObject::get_subscribed_attribute_handle_set_sp();
    CPPUNIT_ASSERT_EQUAL(5, static_cast<int>(attributeHandleSet.size()));

    ObjectRoot::PropertyHandleValuePairSetSP subscribedAttributeHandleValuePairSetSP(
      RTI::AttributeSetFactory::create( attributeHandleSet.size() )
    );
    ObjectRoot::PropertyHandleValuePairSet &subscribedAttributeHandleValuePairSet =
      *subscribedAttributeHandleValuePairSetSP;

    const ObjectRoot::PropertyHandleValuePairSet &publishedAttributeHandleValuePairSet =
      updatedObjectData.getAttributeHandleValuePairSet();

    RTI::ULong valueLength;
    for(int ix = 0 ; ix < publishedAttributeHandleValuePairSet.size() ; ++ix) {
        int attributeHandle = publishedAttributeHandleValuePairSet.getHandle(ix);
        if (attributeHandleSet.isMember(attributeHandle)) {
            char *value = publishedAttributeHandleValuePairSet.getValuePointer( ix, valueLength );
            subscribedAttributeHandleValuePairSet.add(attributeHandle, value, valueLength);
        }
    }

    // TRY TO UPDATE OBJECT IN RECEIVER DIRECTLY FROM RTI
    receiver.reflectAttributeValues(
            objectHandle,
            subscribedAttributeHandleValuePairSet,
            updatedObjectData.getRTIfedTime(),
            nullptr,
            RTI::EventRetractionHandle()
    );

    // THE Receiver SHOULD ONLY UPDATE THOSE ATTRIBUTES THAT ARE DIRECTLY SUBSCRIBED (NOT SOFT SUBSCRIBED
    receiver.initialize();
    receiver.iteration();

    // THE RECEIVER SHOULD NOt HAVE THE OBJECT YET
    CPPUNIT_ASSERT(!receiver.getTestObjectSP());

    receiver.iteration();

    // THE RECEIVER SHOULD NOW HAVE THE OBJECT
    CPPUNIT_ASSERT(receiver.getTestObjectSP());

    TestObject &receivedTestObject = *receiver.getTestObjectSP();
    // NOT SUBSCRIBED BY Receiver, SO receivedTestObject.get_BoolValue1() HAS DEFAULT VALUE OF false,
    // BUT localTestObject.get_BoolValue1 IS INCIDENTALLY false
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_BoolValue1(), localTestObject.get_BoolValue1());
    // NOT PUBLISHED BY Sender, SO BOTH HAVE DEFAULT VALUE
    CPPUNIT_ASSERT_DOUBLES_EQUAL(receivedTestObject.get_DoubleValue(), localTestObject.get_DoubleValue(), 0.001);
    // NOT SUBSCRIBED BY Receiver
    CPPUNIT_ASSERT(fabs(receivedTestObject.get_FloatValue() - localTestObject.get_FloatValue()) > 0.001);
    // NOT PUBLISHED BY Sender, SO BOTH HAVE DEFAULT VALUE
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_StringValue(), localTestObject.get_StringValue());

    // BOTH PUBLISHED BY SENDER AND SUBSCRIBED BY RECEIVER
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_BoolValue2(), localTestObject.get_BoolValue2());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_ByteValue(), localTestObject.get_ByteValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_CharValue(), localTestObject.get_CharValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_JSONValue1(), localTestObject.get_JSONValue1());

    // THESE ARE UPDATED THROUGH THE NETWORK, SO NOT RECEIVED YET
    CPPUNIT_ASSERT(receivedTestObject.get_IntValue() != localTestObject.get_IntValue());
    CPPUNIT_ASSERT(receivedTestObject.get_LongValue() != localTestObject.get_LongValue());
    CPPUNIT_ASSERT(receivedTestObject.get_ShortValue() != localTestObject.get_ShortValue());
    CPPUNIT_ASSERT(receivedTestObject.get_JSONValue2() != localTestObject.get_JSONValue2());

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
    receiver.iteration();

    // NOT SUBSCRIBED BY Receiver, SO receivedTestObject.get_BoolValue1() HAS DEFAULT VALUE OF false,
    // BUT localTestObject.get_BoolValue1 IS INCIDENTALLY false
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_BoolValue1(), localTestObject.get_BoolValue1());
    // NOT PUBLISHED BY Sender, SO BOTH HAVE DEFAULT VALUE
    CPPUNIT_ASSERT_DOUBLES_EQUAL(receivedTestObject.get_DoubleValue(), localTestObject.get_DoubleValue(), 0.001);
    // NOT SUBSCRIBED BY Receiver
    CPPUNIT_ASSERT(fabs(receivedTestObject.get_FloatValue() - localTestObject.get_FloatValue()) > 0.001);
    // NOT PUBLISHED BY Sender, SO BOTH HAVE DEFAULT VALUE
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_StringValue(), localTestObject.get_StringValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_JSONValue1(), localTestObject.get_JSONValue1());

    // BOTH PUBLISHED BY SENDER AND SUBSCRIBED BY RECEIVER
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_BoolValue2(), localTestObject.get_BoolValue2());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_ByteValue(), localTestObject.get_ByteValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_CharValue(), localTestObject.get_CharValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_IntValue(), localTestObject.get_IntValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_LongValue(), localTestObject.get_LongValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_ShortValue(), localTestObject.get_ShortValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_JSONValue2(), localTestObject.get_JSONValue2());

    receiver.iteration();  // EMPTY THE ATRQUEUE

    RTIAmbassadorTest2::clear();
    rtiAmbassadorTest2.resetCurrentTime();

    std::cout << "ENDING \"EmbeddedMessagingObjectTests::testObjectNetworkPropagation\"" << std::endl;
    std::cout << std::endl;
}

CPPUNIT_TEST_SUITE_REGISTRATION( EmbeddedMessagingObjectTests );
