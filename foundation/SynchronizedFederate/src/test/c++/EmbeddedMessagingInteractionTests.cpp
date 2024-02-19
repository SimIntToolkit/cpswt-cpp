#include "EmbeddedMessagingInteractionTests.hpp"
#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessaginginteractiontestcpp/sender/Sender.hpp"
#include "edu/vanderbilt/vuisis/cpswt/hla/embeddedmessaginginteractiontestcpp/receiver/Receiver.hpp"
#include <cmath>

#include <boost/lexical_cast.hpp>

typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot InteractionRoot;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::
  InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging EmbeddedMessaging;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::
  InteractionRoot_p::C2WInteractionRoot_p::EmbeddedMessaging_p::TestOmnetFederate TestOmnetFederate;

typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot InteractionRoot;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::InteractionRoot_p::C2WInteractionRoot_p::TestInteraction TestInteraction;

typedef ::edu::vanderbilt::vuisis::cpswt::hla::embeddedmessaginginteractiontestcpp::sender::Sender Sender;
typedef ::edu::vanderbilt::vuisis::cpswt::hla::embeddedmessaginginteractiontestcpp::receiver::Receiver Receiver;

void checkTestInteractionJson(
  TestInteraction &senderTestInteraction, Json::Value &sentInteractionJson1, double time
) {
    // THE messaging_type FOR THE LOCAL EmbeddedMessaging.TestOmnetFederate INTERACTION SHOULD BE "interaction"
    std::string messagingType = sentInteractionJson1["messaging_type"].asString();
    CPPUNIT_ASSERT_EQUAL(messagingType, std::string("interaction"));

    // THE hlaClassName SHOULD BE FOR TestInteraction
    std::string messagingName = sentInteractionJson1["messaging_name"].asString();
    CPPUNIT_ASSERT_EQUAL(messagingName, TestInteraction::get_hla_class_name());

    Json::Value sentInteractionJsonPropertiesMap = sentInteractionJson1["properties"];

    // THE messagingJson SHOULD BE FOR ALL OF THE PARAMETERS, INCLUDING THOSE INHERITED FROM C2WINTERACTIONROOT
    CPPUNIT_ASSERT_EQUAL(14, static_cast<int>(sentInteractionJsonPropertiesMap.size()));

    // GET TestInteraction CLASS PARAMETER NAMES (ClassAndPropertyName SET)
    ClassAndPropertyNameList testInteractionClassAndPropertyNameList = TestInteraction::get_parameter_names();

    // testInteractionClassAndPropertyNameList SHOULD HAVE 11 MEMBERS
    CPPUNIT_ASSERT_EQUAL(11, static_cast<int>(testInteractionClassAndPropertyNameList.size()));

    // GET ClassAndPropertyNameValueMap FOR THE senderTestObject
    const InteractionRoot::ClassAndPropertyNameValueSPMap &senderClassAndPropertyNameValueSPMap =
            senderTestInteraction.getClassAndPropertyNameValueSPMap();

    // MAKE SURE INTERACTION ENCODED IN EMBEDDEDMESSAGING INTERACTION HAS SAME JSON-ENCODED ATTRIBUTE
    // VALUES AS VALUES OF PARAMETERS FOR senderTestInteraction
    for(const ClassAndPropertyName &classAndPropertyName: testInteractionClassAndPropertyNameList) {

        const InteractionRoot::Value &value = *senderClassAndPropertyNameValueSPMap.find(classAndPropertyName)->second;
        const Json::Value jsonValue = sentInteractionJsonPropertiesMap[static_cast<std::string>(classAndPropertyName)];

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
}

void EmbeddedMessagingInteractionTests::testInteractionNetworkPropagation() {

    std::cout << "STARTING \"EmbeddedMessagingInteractionTests::testInteractionNetworkPropagation\"" << std::endl;
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

    // ALSO WHEN SENDER WAS CREATED, IT SENT OUT 2 INTERACTIONS
    // * FederateJoinInteraction
    CPPUNIT_ASSERT(sentInteractionDataSPList.size() <= 2);

    // THROW AWAY INTERACTION DATA SENT BY SENDER UP TO THIS POINT -- ALREADY TESTED
    sentInteractionDataSPList.clear();

    // EXECUTE THE SENDER -- SHOULD ASSIGN PARAMETER VALUES TO TestInteraction INSTANCE AND
    // SEND IT TO THE RTI.
    sender.initialize();

    sender.iteration();  // FIRST CALL IS TO QUEUE INTERACTIONS
    sender.iteration();  // SECOND CALL IS TO SEND THEM (WHILE ADVANCING TO TIME = 1)

    // GET THE SEND INTERACTION DIRECTLY FROM THE SENDER
    // ** THIS WILL BE AN EMBEDDEDMESSSAGING INTERACTION CONTAINING A JSON-ENCODED TESTINTERACTION
    TestInteraction &senderTestInteraction = sender.getTestInteraction();

    // NUMBER OF INTERACTIONS SENT BY SENDER SHOULD BE 1
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(sentInteractionDataSPList.size()));

    // GET THE DATA ASSOCIATED WITH THE PARAMETERS OF THE SENT INTERACTION
    RTIAmbassadorTest2::SentInteractionDataSP sentInteractionEmbeddedMessagingOmnetFederateDataSP1 =
            sentInteractionDataSPList.back();
    RTIAmbassadorTest2::SentInteractionData &sentInteractionEmbeddedMessagingOmnetFederateData1 =
            *sentInteractionEmbeddedMessagingOmnetFederateDataSP1;

    // THE CLASS HANDLE OF THE INTERACTION ASSOCIATED WITH THE SENT TESTINTERACTION SHOULD BE
    // THAT OF THE TestOmnetFederate-SPECIFIC EmbeddedMessaging INTERACTION
    int sentInteractionEmbeddedMessagingOmnetFederateClassHandle1 =
            sentInteractionEmbeddedMessagingOmnetFederateData1.getInteractionClassHandle();
    CPPUNIT_ASSERT_EQUAL(
            embeddedMessagingOmnetFederateInteractionClassHandle,
            sentInteractionEmbeddedMessagingOmnetFederateClassHandle1
    );

    // MUST PRESERVE THIS FOR LATER, SO CAN'T BE A REFERENCE -- THE DATA FROM
    // sentInteractionEmbeddedMessagingOmnetFederateData1.getParameterHandleValuePairSet()
    // CAN AND WILL CHANGE
    const PropertyHandleValuePairSetForTesting sentInteractionEmbeddedMessagingOmnetFederateSuppliedParameters1 =
            sentInteractionEmbeddedMessagingOmnetFederateData1.getParameterHandleValuePairSet();

    // SuppliedParameters SHOULD BE PRESENT IN THE SENT INTERACTION DATA, AND SHOULD
    // CONTAIN DATA FOR 6 PARAMETERS -- ALL THOSE PRESENT IN AN EMBEDDEDMESSAGING INTERACTION.
    CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(sentInteractionEmbeddedMessagingOmnetFederateSuppliedParameters1.size()));


    // CREATE A LOCAL INTERACTION INSTANCE FROM THE INTERACTION-DATA THAT WAS SENT OUT FROM THE "sendInteraction"
    // CALL IN THE SENDER
    InteractionRoot::SP localEmbeddedMessagingOmnetFederateInteractionRootSP1 = InteractionRoot::create_interaction(
            sentInteractionEmbeddedMessagingOmnetFederateClassHandle1,
            sentInteractionEmbeddedMessagingOmnetFederateSuppliedParameters1
    );

    // THE LOCAL INTERACTION INSTANCE SHOULD BE A TestOmnetFederate
    TestOmnetFederate::SP localEmbeddedMessagingOmnetFederateInteractionSP1 =
            boost::dynamic_pointer_cast<TestOmnetFederate>(localEmbeddedMessagingOmnetFederateInteractionRootSP1);
    CPPUNIT_ASSERT(localEmbeddedMessagingOmnetFederateInteractionSP1);

    TestOmnetFederate &localEmbeddedMessagingOmnetFederateInteraction1 =
            *localEmbeddedMessagingOmnetFederateInteractionSP1;

    std::istringstream jsonInputStream1(localEmbeddedMessagingOmnetFederateInteraction1.get_messagingJson());

    Json::Value sentInteractionJson1;
    jsonInputStream1 >> sentInteractionJson1;

    checkTestInteractionJson(senderTestInteraction, sentInteractionJson1, 0.5);

    // CLEAR THE AMBASSADOR PROXY FOR THE Receiver FEDERATE
    RTIAmbassadorTest2::clear();

    sender.iteration();

    // NUMBER OF INTERACTIONS SENT BY SENDER SHOULD BE 1
    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(sentInteractionDataSPList.size()));

    // GET THE DATA ASSOCIATED WITH THE PARAMETERS OF THE SENT INTERACTION
    RTIAmbassadorTest2::SentInteractionDataSP sentInteractionEmbeddedMessagingOmnetFederateDataSP2 =
            sentInteractionDataSPList.back();
    RTIAmbassadorTest2::SentInteractionData &sentInteractionEmbeddedMessagingOmnetFederateData2 =
            *sentInteractionEmbeddedMessagingOmnetFederateDataSP2;

    // THE CLASS HANDLE OF THE INTERACTION ASSOCIATED WITH THE SENT TESTINTERACTION SHOULD BE
    // THAT OF THE TestOmnetFederate-SPECIFIC EmbeddedMessaging INTERACTION
    int sentInteractionEmbeddedMessagingOmnetFederateClassHandle2 =
            sentInteractionEmbeddedMessagingOmnetFederateData2.getInteractionClassHandle();

    CPPUNIT_ASSERT_EQUAL(
            embeddedMessagingOmnetFederateInteractionClassHandle,
            sentInteractionEmbeddedMessagingOmnetFederateClassHandle2
    );

    // MUST PRESERVE THIS FOR LATER, SO CAN'T BE A REFERENCE -- THE DATA FROM
    // sentInteractionEmbeddedMessagingOmnetFederateData2.getParameterHandleValuePairSet()
    // CAN AND WILL CHANGE
    const PropertyHandleValuePairSetForTesting sentInteractionEmbeddedMessagingOmnetFederateSuppliedParameters2 =
            sentInteractionEmbeddedMessagingOmnetFederateData2.getParameterHandleValuePairSet();

    // SuppliedParameters SHOULD BE PRESENT IN THE SENT INTERACTION DATA, AND SHOULD
    // CONTAIN DATA FOR 6 PARAMETERS -- ALL THOSE PRESENT IN AN EMBEDDEDMESSAGING INTERACTION.
    CPPUNIT_ASSERT_EQUAL(4, static_cast<int>(sentInteractionEmbeddedMessagingOmnetFederateSuppliedParameters2.size()));


    // CREATE A LOCAL INTERACTION INSTANCE FROM THE INTERACTION-DATA THAT WAS SENT OUT FROM THE "sendInteraction"
    // CALL IN THE SENDER
    InteractionRoot::SP localEmbeddedMessagingOmnetFederateInteractionRootSP2 = InteractionRoot::create_interaction(
            sentInteractionEmbeddedMessagingOmnetFederateClassHandle2,
            sentInteractionEmbeddedMessagingOmnetFederateSuppliedParameters2
    );

    // THE LOCAL INTERACTION INSTANCE SHOULD BE A TestOmnetFederate
    TestOmnetFederate::SP localEmbeddedMessagingOmnetFederateInteractionSP2 =
            boost::dynamic_pointer_cast<TestOmnetFederate>(localEmbeddedMessagingOmnetFederateInteractionRootSP2);

    CPPUNIT_ASSERT(localEmbeddedMessagingOmnetFederateInteractionSP2);

    TestOmnetFederate &localEmbeddedMessagingOmnetFederateInteraction2 =
            *localEmbeddedMessagingOmnetFederateInteractionSP2;

    std::istringstream jsonInputStream2(localEmbeddedMessagingOmnetFederateInteraction2.get_messagingJson());

    Json::Value sentInteractionJson2;
    jsonInputStream2 >> sentInteractionJson2;

    checkTestInteractionJson(senderTestInteraction, sentInteractionJson2[0], 1.5);
    checkTestInteractionJson(senderTestInteraction, sentInteractionJson2[1], 1.6);

    sender.iteration();  // EMPTY THE ATRQUEUE

    RTIAmbassadorTest2::clear();
    rtiAmbassadorTest2.resetCurrentTime();

    //
    // CREATE THE RECEIVER FEDERATE
    //
    FederateConfigSP receiverFederateConfigSP = getNewFederateConfigSP("Receiver");
    Receiver receiver(receiverFederateConfigSP.get());
    rtiAmbassadorTest2.setSynchronizedFederate(receiver);

    // SEND THE TWO TEST-INTERACTIONS TO THE receiver
    receiver.receiveInteraction(
            sentInteractionEmbeddedMessagingOmnetFederateClassHandle1,
            sentInteractionEmbeddedMessagingOmnetFederateSuppliedParameters1,
            sentInteractionEmbeddedMessagingOmnetFederateData1.getRTIfedTime(),
            nullptr,
            RTI::EventRetractionHandle()
    );

    receiver.receiveInteraction(
            sentInteractionEmbeddedMessagingOmnetFederateClassHandle2,
            sentInteractionEmbeddedMessagingOmnetFederateSuppliedParameters2,
            sentInteractionEmbeddedMessagingOmnetFederateData2.getRTIfedTime(),
            nullptr,
            RTI::EventRetractionHandle()
    );

    Receiver::TestInteractionSPList &receiverTestInteractionSPList = receiver.getTestInteractionSPList();

    receiver.initialize();

    receiver.iteration();

    CPPUNIT_ASSERT_EQUAL(0, static_cast<int>(receiverTestInteractionSPList.size()));

    receiver.iteration();

    CPPUNIT_ASSERT_EQUAL(1, static_cast<int>(receiverTestInteractionSPList.size()));

    TestInteraction::SP receiverTestInteractionSP1 = receiverTestInteractionSPList.back();
    TestInteraction &receiverTestInteraction1 = *receiverTestInteractionSP1;

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, receiverTestInteraction1.getTime(), 0.001);

    // NOT SUBSCRIBED BY Receiver, SO receivedTestInteraction.get_BoolValue1() HAS DEFAULT VALUE OF false,
    // BUT localEmbeddedMessagingOmnetFederateInteraction1.get_BoolValue1 IS INCIDENTALLY false
    CPPUNIT_ASSERT_EQUAL(receiverTestInteraction1.get_BoolValue1(), senderTestInteraction.get_BoolValue1());
    CPPUNIT_ASSERT_EQUAL(receiverTestInteraction1.get_BoolValue2(), senderTestInteraction.get_BoolValue2());
    CPPUNIT_ASSERT_EQUAL(receiverTestInteraction1.get_ByteValue(), senderTestInteraction.get_ByteValue());
    CPPUNIT_ASSERT_EQUAL(receiverTestInteraction1.get_CharValue(), senderTestInteraction.get_CharValue());
    CPPUNIT_ASSERT_DOUBLES_EQUAL(receiverTestInteraction1.get_DoubleValue(), senderTestInteraction.get_DoubleValue(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(receiverTestInteraction1.get_FloatValue(), senderTestInteraction.get_FloatValue(), 0.001);
    CPPUNIT_ASSERT_EQUAL(receiverTestInteraction1.get_IntValue(), senderTestInteraction.get_IntValue());
    CPPUNIT_ASSERT_EQUAL(receiverTestInteraction1.get_LongValue(), senderTestInteraction.get_LongValue());
    CPPUNIT_ASSERT_EQUAL(receiverTestInteraction1.get_ShortValue(), senderTestInteraction.get_ShortValue());
    CPPUNIT_ASSERT_EQUAL(receiverTestInteraction1.get_StringValue(), senderTestInteraction.get_StringValue());
    CPPUNIT_ASSERT_EQUAL(receiverTestInteraction1.get_JSONValue(), senderTestInteraction.get_JSONValue());

    receiverTestInteractionSPList.clear();

    receiver.iteration();

    CPPUNIT_ASSERT_EQUAL(2, static_cast<int>(receiverTestInteractionSPList.size()));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.5, receiverTestInteractionSPList.front()->getTime(), 0.001);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.6, receiverTestInteractionSPList.back()->getTime(), 0.001);

    receiver.iteration();   // EMPTY THE ATRQUEUE
    RTIAmbassadorTest2::clear();
    rtiAmbassadorTest2.resetCurrentTime();

    std::cout << "ENDING \"EmbeddedMessagingInteractionTests::testInteractionNetworkPropagation\"" << std::endl;
    std::cout << std::endl;
}

CPPUNIT_TEST_SUITE_REGISTRATION( EmbeddedMessagingInteractionTests );
