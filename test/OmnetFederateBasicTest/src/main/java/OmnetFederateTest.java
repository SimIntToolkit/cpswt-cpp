import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import org.cpswt.hla.InteractionRoot;
import org.cpswt.hla.SynchronizedFederate;
import org.cpswt.config.FederateConfig;
import org.cpswt.hla.base.AdvanceTimeRequest;

import java.util.concurrent.atomic.AtomicInteger;

public class OmnetFederateTest extends SynchronizedFederate {

    private final static Logger log = LogManager.getLogger();

    private static final String appName = "BasicUdpAppWrapper";
    public static String getAppName() {
        return appName;
    }

    private double currentTime = 0;
    private AdvanceTimeRequest atr = null;

    public OmnetFederateTest() throws Exception {
        super(new FederateConfig(
                "OmnetFederationTest",
                "OmnetFederateTest",
                false,
                0.1,
                1
        ));

        createLRC();
        joinFederation();

        NetworkPacket.publish(getLRC());
        NetworkPacket.subscribe(getLRC());

        enableTimeConstrained();
        enableTimeRegulation(getLookAhead());
        enableAsynchronousDelivery();
    }

    // CREATE AND INITIALIZE NETWORK PACKET
    private NetworkPacket getNetworkPacket() {

        NetworkPacket networkPacket = new NetworkPacket();

        networkPacket.set_packetType("NetworkPacket");
        networkPacket.set_data("1234");
        networkPacket.set_numBytes(5);

        networkPacket.set_senderHost("OmnetFederateTestNetwork.host1");
        networkPacket.set_senderHostApp(getAppName());
        networkPacket.set_senderAppIndex(0);

        networkPacket.set_receiverHost("OmnetFederateTestNetwork.host2");
        networkPacket.set_receiverHostApp(getAppName());
        networkPacket.set_receiverAppIndex(0);
        networkPacket.set_receiverAppInterface("eth");

        return networkPacket;
    }

    private void waitSimulationSeconds(Runnable runnable, double waitSeconds) {

        atr.requestSyncStart();

        runnable.run();

        currentTime += waitSeconds;
        AdvanceTimeRequest newAtr = new AdvanceTimeRequest(currentTime);
        putAdvanceTimeRequest(newAtr);

        atr.requestSyncEnd();
        atr = newAtr;
    }

    public void execute() throws Exception {
        atr = new AdvanceTimeRequest(currentTime);
        putAdvanceTimeRequest(atr);


        log.info("waiting on readyToPopulate...");
        readyToPopulate();
        log.info("...synchronized on readyToPopulate");

        log.info("waiting on readyToRun...");
        readyToRun();
        log.info("...synchronized on readyToRun");


        NetworkPacket networkPacket = getNetworkPacket();

        // START OF SIMULATION
        startAdvanceTimeThread();

        // WAIT 5 SECONDS
        waitSimulationSeconds(() -> {}, 2);

        Runnable sendNetworkPacket = () -> {
            System.out.println("Sending network packet");
            System.out.flush();
            networkPacket.sendInteraction(getLRC());
        };
        waitSimulationSeconds(sendNetworkPacket, 1);

        AtomicInteger numNetworkPackets = new AtomicInteger();
        Runnable getNetworkPackets = () -> {
            InteractionRoot interactionRoot = getNextInteractionNoWait();
            while(interactionRoot != null) {
                System.out.println("HERE");
                System.out.flush();
                if (interactionRoot instanceof NetworkPacket) {
                    System.out.println("Got network packet");
                    System.out.flush();
                    numNetworkPackets.incrementAndGet();
                }
                interactionRoot = getNextInteractionNoWait();
            }
        };

        int timeout = 10;
        while(--timeout >= 0 && numNetworkPackets.get() < 1) {
            waitSimulationSeconds(getNetworkPackets, 1);
        }

    }

    public static void main(String[] args) {
        try {
            OmnetFederateTest federate = new OmnetFederateTest();
            federate.execute();
            log.info("Done.");
            System.exit(0);
        }
        catch (Exception e) {
            log.error(e);
            System.exit(1);
        }
    }


}
