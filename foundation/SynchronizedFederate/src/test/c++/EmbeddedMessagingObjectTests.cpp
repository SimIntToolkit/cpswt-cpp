#include "EmbeddedMessagingObjectTests.hpp"
#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjecttestcpp/sender/Sender.hpp"
#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessagingobjecttestcpp/receiver/Receiver.hpp"
#include <cmath>

#include <boost/lexical_cast.hpp>

typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot InteractionRoot;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging EmbeddedMessaging;

typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot ObjectRoot;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::ObjectRoot_p::TestObject TestObject;

typedef ::edu::vanderbilt::vuisis::cpswt::hla::embeddedmessagingobjecttestcpp::sender::Sender Sender;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::embeddedmessagingobjecttestcpp::receiver::Receiver Receiver;


void EmbeddedMessagingObjectTests::compareStringLists(
  const std::list<std::string> &list1, const std::list<std::string> &list2
) {

    CPPUNIT_ASSERT_EQUAL(list1.size(), list2.size());
    std::list<std::string>::const_iterator stlCit1 = list1.begin();
    std::list<std::string>::const_iterator stlCit2 = list2.begin();
    while(stlCit1 != list1.end()) {
        CPPUNIT_ASSERT_EQUAL(*stlCit1, *stlCit2);
        ++stlCit1;
        ++stlCit2;
    }
}

bool EmbeddedMessagingObjectTests::stringListsNotEqual(
  const std::list<std::string> &list1, const std::list<std::string> &list2
) {

    if (list1.size() != list2.size()) {
        return true;
    }
    std::list<std::string>::const_iterator stlCit1 = list1.begin();
    std::list<std::string>::const_iterator stlCit2 = list2.begin();
    while(stlCit1 != list1.end()) {
        if (*stlCit1 != *stlCit2) {
            return true;
        }
        ++stlCit1;
        ++stlCit2;
    }

    return false;
}

void EmbeddedMessagingObjectTests::testObjectNetworkPropagation() {

    //
    // CREATE Sender -- ALSO INITIALIZES TABLES IN InteractionRoot AND ObjectRoot
    //
    FederateConfigSP senderFederateConfigSP = getNewFederateConfigSP("Sender");
    Sender sender(senderFederateConfigSP.get());

    //
    // CLASS HANDLES FOR FEDERATE-SPECIFIC EmbeddedMessaging INTERACTIONS
    //
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
    // * FederateJoinInteraction
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(sentInteractionDataSPList.size()));

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
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_BooleanValue1(), localTestObject.get_BooleanValue1());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_BooleanValue2(), localTestObject.get_BooleanValue2());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_ByteValue(), localTestObject.get_ByteValue());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_CharValue(), localTestObject.get_CharValue());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(senderTestObject.get_FloatValue(), localTestObject.get_FloatValue(), 0.001);
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_IntValue(), localTestObject.get_IntValue());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_LongValue(), localTestObject.get_LongValue());
    CPPUNIT_ASSERT_EQUAL(senderTestObject.get_ShortValue(), localTestObject.get_ShortValue());
    compareStringLists(senderTestObject.get_StringListValue1(), localTestObject.get_StringListValue1());
    compareStringLists(senderTestObject.get_StringListValue2(), localTestObject.get_StringListValue2());

    // THE ATTRIBUTES THAT ARE *NOT* PUBLISHED FOR THE REGISTERED OBJECT SHOULD *NOT* HAVE THE SAME VALUES
    // AS THE CORRESPONDING ATTRIBUTES IN THE LOCAL OBJECT
    CPPUNIT_ASSERT(fabs(senderTestObject.get_DoubleValue() - localTestObject.get_DoubleValue()) > 0.001);
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
            case TypeMedley::STRINGLIST: {
                std::list<std::string> jsonStringListValue;
                for(auto item: jsonValue) {
                    jsonStringListValue.push_back(item.asString());
                }
                compareStringLists(value.asStringList(), jsonStringListValue);
                break;
            }
        }
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

    // THE Receiver SHOULD IGNORE THE "reflectAttributeValues" CALL ABOVE, SO PERFORMED THE ACTIONS ASSOCIATED T
    receiver.execute();

    // THE RECEIVER SHOULD NOW HAVE THE OBJECT
    CPPUNIT_ASSERT(receiver.getTestObjectSP());

    TestObject &receivedTestObject = *receiver.getTestObjectSP();
    // NOT SUBSCRIBED BY Receiver, SO receivedTestObject.get_BooleanValue1() HAS DEFAULT VALUE OF false,
    // BUT localTestObject.get_BooleanValue1 IS INCIDENTALLY false
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_BooleanValue1(), localTestObject.get_BooleanValue1());
    // NOT PUBLISHED BY Sender, SO BOTH HAVE DEFAULT VALUE
    CPPUNIT_ASSERT_DOUBLES_EQUAL(receivedTestObject.get_DoubleValue(), localTestObject.get_DoubleValue(), 0.001);
    // NOT SUBSCRIBED BY Receiver
    CPPUNIT_ASSERT(fabs(receivedTestObject.get_FloatValue() - localTestObject.get_FloatValue()) > 0.001);
    // NOT PUBLISHED BY Sender, SO BOTH HAVE DEFAULT VALUE
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_StringValue(), localTestObject.get_StringValue());

    // BOTH PUBLISHED BY SENDER AND SUBSCRIBED BY RECEIVER
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_BooleanValue2(), localTestObject.get_BooleanValue2());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_ByteValue(), localTestObject.get_ByteValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_CharValue(), localTestObject.get_CharValue());
    compareStringLists(receivedTestObject.get_StringListValue1(), localTestObject.get_StringListValue1());

    // THESE ARE UPDATED THROUGH THE NETWORK, SO NOT RECEIVED YET
    CPPUNIT_ASSERT(receivedTestObject.get_IntValue() != localTestObject.get_IntValue());
    CPPUNIT_ASSERT(receivedTestObject.get_LongValue() != localTestObject.get_LongValue());
    CPPUNIT_ASSERT(receivedTestObject.get_ShortValue() != localTestObject.get_ShortValue());
    CPPUNIT_ASSERT(stringListsNotEqual(
      receivedTestObject.get_StringListValue2(), localTestObject.get_StringListValue2()
    ));

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

    // NOT SUBSCRIBED BY Receiver, SO receivedTestObject.get_BooleanValue1() HAS DEFAULT VALUE OF false,
    // BUT localTestObject.get_BooleanValue1 IS INCIDENTALLY false
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_BooleanValue1(), localTestObject.get_BooleanValue1());
    // NOT PUBLISHED BY Sender, SO BOTH HAVE DEFAULT VALUE
    CPPUNIT_ASSERT_DOUBLES_EQUAL(receivedTestObject.get_DoubleValue(), localTestObject.get_DoubleValue(), 0.001);
    // NOT SUBSCRIBED BY Receiver
    CPPUNIT_ASSERT(fabs(receivedTestObject.get_FloatValue() - localTestObject.get_FloatValue()) > 0.001);
    // NOT PUBLISHED BY Sender, SO BOTH HAVE DEFAULT VALUE
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_StringValue(), localTestObject.get_StringValue());
    compareStringLists(receivedTestObject.get_StringListValue1(), localTestObject.get_StringListValue1());

    // BOTH PUBLISHED BY SENDER AND SUBSCRIBED BY RECEIVER
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_BooleanValue2(), localTestObject.get_BooleanValue2());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_ByteValue(), localTestObject.get_ByteValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_CharValue(), localTestObject.get_CharValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_IntValue(), localTestObject.get_IntValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_LongValue(), localTestObject.get_LongValue());
    CPPUNIT_ASSERT_EQUAL(receivedTestObject.get_ShortValue(), localTestObject.get_ShortValue());
    compareStringLists(receivedTestObject.get_StringListValue2(), localTestObject.get_StringListValue2());
}

CPPUNIT_TEST_SUITE_REGISTRATION( EmbeddedMessagingObjectTests );
