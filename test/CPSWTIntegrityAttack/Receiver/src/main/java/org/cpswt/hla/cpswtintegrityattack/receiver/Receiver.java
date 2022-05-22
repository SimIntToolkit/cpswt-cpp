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

package org.cpswt.hla.cpswtintegrityattack.receiver;

import org.cpswt.config.FederateConfig;
import org.cpswt.config.FederateConfigParser;
import org.cpswt.hla.InteractionRoot;
import org.cpswt.hla.base.AdvanceTimeRequest;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.TestInteraction;
import org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.StartIntegrityAttack;

// Define the  type of federate for the federation.

@SuppressWarnings("unused")
public class Receiver extends ReceiverBase {
    private final static Logger log = LogManager.getLogger();

    private double currentTime = 0;

    public Receiver(FederateConfig params) throws Exception {
        super(params);
    }

    private void checkReceivedSubscriptions() {
        InteractionRoot interactionRoot;
        while ((interactionRoot = getNextInteractionNoWait()) != null) {

            System.err.println(
                    "State " + state + ": Received \"" + interactionRoot.getInstanceHlaClassName() + "\" interaction"
            );

            if (interactionRoot.isInstanceHlaClassDerivedFromHlaClass("InteractionRoot.C2WInteractionRoot.TestInteraction.Receiver")) {

                handleInteractionClass_InteractionRoot_C2WInteractionRoot_TestInteraction_Receiver(interactionRoot);
                continue;
            }
            if (interactionRoot.isInstanceHlaClassDerivedFromHlaClass("InteractionRoot.C2WInteractionRoot.TestInteraction")) {

                handleInteractionClass_InteractionRoot_C2WInteractionRoot_TestInteraction(interactionRoot);
                continue;
            }
            if (interactionRoot.isInstanceHlaClassDerivedFromHlaClass("InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StopIntegrityAttack")) {

                handleInteractionClass_InteractionRoot_C2WInteractionRoot_ActionBase_OmnetCommand_StopIntegrityAttack(interactionRoot);
                continue;
            }
            if (interactionRoot.isInstanceHlaClassDerivedFromHlaClass("InteractionRoot.C2WInteractionRoot.ActionBase.OmnetCommand.StartIntegrityAttack")) {

                handleInteractionClass_InteractionRoot_C2WInteractionRoot_ActionBase_OmnetCommand_StartIntegrityAttack(interactionRoot);
                continue;
            }

            log.debug("unhandled interaction: {}", interactionRoot.getJavaClassName());
        }
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

        while (!exitCondition) {
            atr.requestSyncStart();
            enteredTimeGrantedState();

            checkReceivedSubscriptions();

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

    static class IntegrityAttackTest {
        private TestInteraction _testInteraction1;
        private TestInteraction _testInteraction2;
        private StartIntegrityAttack _startIntegrityAttack;

        void setTestInteraction1(TestInteraction testInteraction) {
            _testInteraction1 = testInteraction;
        }

        void setTestInteraction2(TestInteraction testInteraction) {
            _testInteraction2 = testInteraction;
        }

        void setStartIntegrityAttack(StartIntegrityAttack startIntegrityAttack) {
            _startIntegrityAttack = startIntegrityAttack;
        }

        boolean testBooleanValue1() {
            boolean firstValue = _testInteraction1.get_BooleanValue1();
            if (_startIntegrityAttack != null && _startIntegrityAttack.get_booleanEnableFlip()) {
                firstValue = !firstValue;
            }
            return firstValue == _testInteraction2.get_BooleanValue1();
        }

        boolean testBooleanValue2() {
            boolean firstValue = _testInteraction1.get_BooleanValue2();
            if (_startIntegrityAttack != null && _startIntegrityAttack.get_booleanEnableFlip()) {
                firstValue = !firstValue;
            }
            return firstValue == _testInteraction2.get_BooleanValue2();
        }

        boolean testByteValues() {
            return _testInteraction1.get_ByteValue() == _testInteraction2.get_ByteValue();
        }

        boolean testCharValues() {
            return _testInteraction1.get_CharValue() == _testInteraction2.get_CharValue();
        }

        boolean testShortValues() {
            return _testInteraction1.get_ShortValue() == _testInteraction2.get_ShortValue();
        }

        boolean testIntValues() {
            int firstValue = _testInteraction1.get_IntValue();
            if (_startIntegrityAttack != null) {
                firstValue = firstValue * _startIntegrityAttack.get_intMultiplier() +
                        _startIntegrityAttack.get_intAdder();
            }
            return firstValue == _testInteraction2.get_IntValue();
        }

        boolean testLongValues() {
            long firstValue = _testInteraction1.get_LongValue();
            if (_startIntegrityAttack != null) {
                firstValue = firstValue * _startIntegrityAttack.get_longMultiplier() +
                        _startIntegrityAttack.get_longAdder();
                return firstValue == _testInteraction2.get_LongValue();
            }
            return firstValue == _testInteraction2.get_LongValue();
        }

        boolean testFloatValues() {
            return _testInteraction1.get_FloatValue() == _testInteraction2.get_FloatValue();
        }

        boolean testDoubleValues() {
            double firstValue = _testInteraction1.get_DoubleValue();
            if (_startIntegrityAttack != null) {
                firstValue = firstValue * _startIntegrityAttack.get_doubleMultiplier() +
                        _startIntegrityAttack.get_doubleAdder();
            }
            return Math.abs(firstValue - _testInteraction2.get_DoubleValue()) < 0.00001;
        }

        boolean testStringValues() {
            String firstValue = _startIntegrityAttack == null ?
                    _testInteraction1.get_StringValue() : _startIntegrityAttack.get_stringReplacement();
            return firstValue.equals(_testInteraction2.get_StringValue());
        }

        void testIntegrity() {
            if (!testBooleanValue1()) {
                System.err.println("Boolean1 values do not match");
            }
            if (!testBooleanValue2()) {
                System.err.println("Boolean2 values do not match");
            }
            if (!testByteValues()) {
                System.err.println("Byte values do not match");
                System.err.println(
                        _testInteraction1.get_ByteValue() + " != " + _testInteraction2.get_ByteValue()
                );
            }
            if (!testCharValues()) {
                System.err.println("Char values do not match");
                System.err.println(
                        "'" + _testInteraction1.get_CharValue() + "' != '" + _testInteraction2.get_CharValue() + "'"
                );
            }
            if (!testShortValues()) {
                System.err.println("Short values do not match");
            }
            if (!testIntValues()) {
                System.err.println("Int values do not match");
            }
            if (!testLongValues()) {
                System.err.println("Long values do not match");
            }
            if (!testFloatValues()) {
                System.err.println("Float values do not match");
            }
            if (!testDoubleValues()) {
                System.err.println("Double values do not match");
            }
            if (!testStringValues()) {
                System.err.println("String values do not match");
            }
        }
    }

    private int state = 0;

    private IntegrityAttackTest integrityAttackTest;

    private void handleInteractionClass_InteractionRoot_C2WInteractionRoot_ActionBase_OmnetCommand_StartIntegrityAttack(InteractionRoot interactionRoot) {
        org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.StartIntegrityAttack startIntegrityAttack =
            (org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.StartIntegrityAttack)interactionRoot;

        if (state == 2) {
            if (integrityAttackTest != null) {
                System.err.println("integrateAttackTest variable should be null for startIntegrityAttack (state 2)");
            }
            integrityAttackTest = new IntegrityAttackTest();
            integrityAttackTest.setStartIntegrityAttack(startIntegrityAttack);
        } else {
            System.err.println("Bad state " + state + " for startIntegrityAttack");
        }
        ++state;
    }

    private void handleInteractionClass_InteractionRoot_C2WInteractionRoot_ActionBase_OmnetCommand_StopIntegrityAttack(InteractionRoot interactionRoot) {
        org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.StopIntegrityAttack stopIntegrityAttack =
            (org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.ActionBase_p.OmnetCommand_p.StopIntegrityAttack)interactionRoot;

        if (state == 5) {
            if (integrityAttackTest != null) {
                System.err.println("integrateAttackTest variable should be null for stopIntegrityAttack (state 5)");
            }
        } else {
            System.err.println("Bad state " + state + " for stopIntegrityAttack");
        }
        ++state;
    }

    private void handleInteractionClass_InteractionRoot_C2WInteractionRoot_TestInteraction(InteractionRoot interactionRoot) {
        org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.TestInteraction testInteraction =
            (org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.TestInteraction)interactionRoot;

        if (state == 0 || state == 3 || state == 6) {
            if ((state == 0 || state == 6)) {
                if (integrityAttackTest != null) {
                    System.err.println("integrateAttackTest variable should be null for testInteraction1 for states 0 and 6");
                }
                integrityAttackTest = new IntegrityAttackTest();
            }
            integrityAttackTest.setTestInteraction1(testInteraction);
        } else {
            System.err.println("Bad state " + state + " for testInteraction1");
        }
        ++state;
    }

    private void handleInteractionClass_InteractionRoot_C2WInteractionRoot_TestInteraction_Receiver(InteractionRoot interactionRoot) {
        org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.TestInteraction_p.Receiver receiver =
            (org.cpswt.hla.InteractionRoot_p.C2WInteractionRoot_p.TestInteraction_p.Receiver)interactionRoot;

        if (state == 1 || state == 4 || state == 7) {
            if (integrityAttackTest == null) {
                System.err.println("integrateAttackTest variable should not be null for testInteraction2");
            } else {
                integrityAttackTest.setTestInteraction2(receiver);
                integrityAttackTest.testIntegrity();
                integrityAttackTest = null;
            }
        } else {
            System.err.println("Bad state " + state + " for testInteraction2");
        }
        ++state;
    }

    public static void main(String[] args) {
        try {
            FederateConfigParser federateConfigParser = new FederateConfigParser();
            FederateConfig federateConfig = federateConfigParser.parseArgs(args, FederateConfig.class);
            Receiver federate = new Receiver(federateConfig);
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
