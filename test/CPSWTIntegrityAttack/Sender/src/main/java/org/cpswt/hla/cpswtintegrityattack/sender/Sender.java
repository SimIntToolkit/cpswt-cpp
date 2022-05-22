/*
 * Certain portions of this software are Copyright (C) 2006-present
 * Vanderbilt University, Institute for Software Integrated Systems.
 *
 * Certain portions of this software are contributed as a public service by
 * The National Institute of Standards and Technology (NIST) and are not
 * subject to U.S. Copyright.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above Vanderbilt University copyright notice, NIST contribution
 * notice and this permission and disclaimer notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. THE AUTHORS OR COPYRIGHT HOLDERS SHALL NOT HAVE
 * ANY OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,
 * OR MODIFICATIONS.
 */

package org.cpswt.hla.cpswtintegrityattack.sender;

import org.cpswt.config.FederateConfig;
import org.cpswt.config.FederateConfigParser;
import org.cpswt.hla.base.AdvanceTimeRequest;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.Arrays;
import java.util.List;

import org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.TestInteraction;
import org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.StartIntegrityAttack;
import org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.StopIntegrityAttack;

// Define the  type of federate for the federation.

@SuppressWarnings("unused")
public class Sender extends SenderBase {
    private final static Logger log = LogManager.getLogger();

    private double currentTime = 0;

    public Sender(FederateConfig params) throws Exception {
        super(params);
    }

    private void execute() throws Exception {
        if(super.isLateJoiner()) {
            log.info("turning off time regulation (late joiner)");
            currentTime = super.getLBTS() - super.getLookAhead();
            super.disableTimeRegulation();
        }

        /////////////////////////////////////////////
        // TODO perform basic initialization below //
        /////////////////////////////////////////////

        AdvanceTimeRequest atr = new AdvanceTimeRequest(currentTime);
        putAdvanceTimeRequest(atr);

        if(!super.isLateJoiner()) {
            log.info("waiting on readyToPopulate...");
            readyToPopulate();
            log.info("...synchronized on readyToPopulate");
        }

        ///////////////////////////////////////////////////////////////////////
        // TODO perform initialization that depends on other federates below //
        ///////////////////////////////////////////////////////////////////////

        if(!super.isLateJoiner()) {
            log.info("waiting on readyToRun...");
            readyToRun();
            log.info("...synchronized on readyToRun");
        }

        startAdvanceTimeThread();
        log.info("started logical time progression");

        TestInteraction testInteraction = create_InteractionRoot_C2WInteractionRoot_TestInteraction();
        testInteraction.set_BooleanValue1(true);
        testInteraction.set_BooleanValue2(false);
        testInteraction.set_ByteValue((byte)-7);
        testInteraction.set_CharValue('G');
        testInteraction.set_DoubleValue(3.14);
        testInteraction.set_FloatValue((float)2.718);
        testInteraction.set_IntValue( 42 );
        testInteraction.set_LongValue(9344255L);
        testInteraction.set_ShortValue((short)-354);
        testInteraction.set_StringValue("TestString");
        testInteraction.set_actualLogicalGenerationTime( currentTime );
        testInteraction.set_federateFilter("");

        final String nodeFullPath = "OmnetFederateTestNetwork.host1";

        int state = 0;
        List<Integer> sendTimesList = Arrays.asList(1, 2, 3, 4, 5);

        while (!exitCondition) {
            atr.requestSyncStart();
            enteredTimeGrantedState();

            if (state == 0 && currentTime >= sendTimesList.get(state) - getLookAhead()) {

                System.out.println("Sending initial TestInteraction.");
                sendInteraction(testInteraction, currentTime + getLookAhead());

                ++state;
            }

            if (state == 1 && currentTime >= sendTimesList.get(state) - getLookAhead()) {

                System.out.println("Sending StartIntegrityAttack");
                StartIntegrityAttack startIntegrityAttack = create_InteractionRoot_C2WInteractionRoot_ActionBase_OmnetCommand_StartIntegrityAttack();
                startIntegrityAttack.set_booleanEnableFlip( true );
                startIntegrityAttack.set_doubleAdder( 15.3 );
                startIntegrityAttack.set_doubleMultiplier( -2.1 );
                startIntegrityAttack.set_intAdder( -6 );
                startIntegrityAttack.set_intMultiplier( 21 );
                startIntegrityAttack.set_longAdder( 95L );
                startIntegrityAttack.set_longMultiplier( 11L );
                startIntegrityAttack.set_nodeFullPath( nodeFullPath );
                startIntegrityAttack.set_stringReplacement( "GARBAGE" );
                startIntegrityAttack.set_uniqueCommandID( "IntegrityAttack1" );
                startIntegrityAttack.set_actualLogicalGenerationTime( currentTime );
                startIntegrityAttack.set_federateFilter( "" );
                sendInteraction(startIntegrityAttack, currentTime + getLookAhead());

                ++state;
            }

            if (state == 2 && currentTime >= sendTimesList.get(state) - getLookAhead()) {

                System.out.println("Sending TestInteraction that should be modified by Integrity Attack");
                sendInteraction(testInteraction, currentTime + getLookAhead());

                ++state;
            }

            if (state == 3 && currentTime >= sendTimesList.get(state) - getLookAhead()) {

                System.out.println("Sending StopIntegrityAttack");
                StopIntegrityAttack stopIntegrityAttack = create_InteractionRoot_C2WInteractionRoot_ActionBase_OmnetCommand_StopIntegrityAttack();
                stopIntegrityAttack.set_nodeFullPath( nodeFullPath );
                stopIntegrityAttack.set_uniqueCommandID( "IntegrityAttack2" );
                stopIntegrityAttack.set_actualLogicalGenerationTime(currentTime);
                stopIntegrityAttack.set_federateFilter("");
                sendInteraction(stopIntegrityAttack, currentTime + getLookAhead());

                ++state;
            }

            if (state == 4 && currentTime >= sendTimesList.get(state) - getLookAhead()) {

                System.out.println("Sending TestInteraction");
                sendInteraction(testInteraction, currentTime + getLookAhead());

                ++state;
            }

            ////////////////////////////////////////////////////////////////////
            // TODO break here if ready to resign and break out of while loop //
            ////////////////////////////////////////////////////////////////////

            if (!exitCondition) {
                currentTime += super.getStepSize();
                AdvanceTimeRequest newATR = new AdvanceTimeRequest(currentTime);
                putAdvanceTimeRequest(newATR);
                atr.requestSyncEnd();
                atr = newATR;
            }
        }

        // call exitGracefully to shut down federate
        exitGracefully();

        //////////////////////////////////////////////////////////////////////
        // TODO Perform whatever cleanups are needed before exiting the app //
        //////////////////////////////////////////////////////////////////////
    }

    public static void main(String[] args) {
        try {
            FederateConfigParser federateConfigParser = new FederateConfigParser();
            FederateConfig federateConfig = federateConfigParser.parseArgs(args, FederateConfig.class);
            Sender federate = new Sender(federateConfig);
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
