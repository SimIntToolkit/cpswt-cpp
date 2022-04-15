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

#include "RTITest.hh"

const char *RTI::ArrayIndexOutOfBounds::_ex = nullptr;
const char *RTI::AsynchronousDeliveryAlreadyDisabled::_ex = nullptr;
const char *RTI::AsynchronousDeliveryAlreadyEnabled::_ex = nullptr;
const char *RTI::AttributeAcquisitionWasNotRequested::_ex = nullptr;
const char *RTI::AttributeAcquisitionWasNotCanceled::_ex = nullptr;
const char *RTI::AttributeAlreadyBeingAcquired::_ex = nullptr;
const char *RTI::AttributeAlreadyBeingDivested::_ex = nullptr;
const char *RTI::AttributeAlreadyOwned::_ex = nullptr;
const char *RTI::AttributeDivestitureWasNotRequested::_ex = nullptr;
const char *RTI::AttributeNotDefined::_ex = nullptr;
const char *RTI::AttributeNotKnown::_ex = nullptr;
const char *RTI::AttributeNotOwned::_ex = nullptr;
const char *RTI::AttributeNotPublished::_ex = nullptr;
const char *RTI::ConcurrentAccessAttempted::_ex = nullptr;
const char *RTI::CouldNotDiscover::_ex = nullptr;
const char *RTI::CouldNotOpenFED::_ex = nullptr;
const char *RTI::CouldNotRestore::_ex = nullptr;
const char *RTI::DeletePrivilegeNotHeld::_ex = nullptr;
const char *RTI::DimensionNotDefined::_ex = nullptr;
const char *RTI::EnableTimeConstrainedPending::_ex = nullptr;
const char *RTI::EnableTimeConstrainedWasNotPending::_ex = nullptr;
const char *RTI::EnableTimeRegulationPending::_ex = nullptr;
const char *RTI::EnableTimeRegulationWasNotPending::_ex = nullptr;
const char *RTI::ErrorReadingFED::_ex = nullptr;
const char *RTI::EventNotKnown::_ex = nullptr;
const char *RTI::FederateAlreadyExecutionMember::_ex = nullptr;
const char *RTI::FederateInternalError::_ex = nullptr;
const char *RTI::FederateLoggingServiceCalls::_ex = nullptr;
const char *RTI::FederateNotExecutionMember::_ex = nullptr;
const char *RTI::FederateOwnsAttributes::_ex = nullptr;
const char *RTI::FederateWasNotAskedToReleaseAttribute::_ex = nullptr;
const char *RTI::FederatesCurrentlyJoined::_ex = nullptr;
const char *RTI::FederationExecutionAlreadyExists::_ex = nullptr;
const char *RTI::FederationExecutionDoesNotExist::_ex = nullptr;
const char *RTI::FederationTimeAlreadyPassed::_ex = nullptr;
const char *RTI::HandleValuePairMaximumExceeded::_ex = nullptr;
const char *RTI::InteractionClassNotDefined::_ex = nullptr;
const char *RTI::InteractionClassNotKnown::_ex = nullptr;
const char *RTI::InteractionClassNotPublished::_ex = nullptr;
const char *RTI::InteractionClassNotSubscribed::_ex = nullptr;
const char *RTI::InteractionParameterNotDefined::_ex = nullptr;
const char *RTI::InteractionParameterNotKnown::_ex = nullptr;
const char *RTI::InvalidExtents::_ex = nullptr;
const char *RTI::InvalidFederationTime::_ex = nullptr;
const char *RTI::InvalidHandleValuePairSetContext::_ex = nullptr;
const char *RTI::InvalidLookahead::_ex = nullptr;
const char *RTI::InvalidOrderingHandle::_ex = nullptr;
const char *RTI::InvalidRegionContext::_ex = nullptr;
const char *RTI::InvalidResignAction::_ex = nullptr;
const char *RTI::InvalidRetractionHandle::_ex = nullptr;
const char *RTI::InvalidTransportationHandle::_ex = nullptr;
const char *RTI::MemoryExhausted::_ex = nullptr;
const char *RTI::NameNotFound::_ex = nullptr;
const char *RTI::ObjectClassNotDefined::_ex = nullptr;
const char *RTI::ObjectClassNotKnown::_ex = nullptr;
const char *RTI::ObjectClassNotPublished::_ex = nullptr;
const char *RTI::ObjectClassNotSubscribed::_ex = nullptr;
const char *RTI::ObjectNotKnown::_ex = nullptr;
const char *RTI::ObjectAlreadyRegistered::_ex = nullptr;
const char *RTI::OwnershipAcquisitionPending::_ex = nullptr;
const char *RTI::RegionInUse::_ex = nullptr;
const char *RTI::RegionNotKnown::_ex = nullptr;
const char *RTI::RestoreInProgress::_ex = nullptr;
const char *RTI::RestoreNotRequested::_ex = nullptr;
const char *RTI::RTIinternalError::_ex = nullptr;
const char *RTI::SpaceNotDefined::_ex = nullptr;
const char *RTI::SaveInProgress::_ex = nullptr;
const char *RTI::SaveNotInitiated::_ex = nullptr;
const char *RTI::SpecifiedSaveLabelDoesNotExist::_ex = nullptr;
const char *RTI::SynchronizationPointLabelWasNotAnnounced::_ex = nullptr;
const char *RTI::TimeAdvanceAlreadyInProgress::_ex = nullptr;
const char *RTI::TimeAdvanceWasNotInProgress::_ex = nullptr;
const char *RTI::TimeConstrainedAlreadyEnabled::_ex = nullptr;
const char *RTI::TimeConstrainedWasNotEnabled::_ex = nullptr;
const char *RTI::TimeRegulationAlreadyEnabled::_ex = nullptr;
const char *RTI::TimeRegulationWasNotEnabled::_ex = nullptr;
const char *RTI::UnableToPerformSave::_ex = nullptr;
const char *RTI::ValueCountExceeded::_ex = nullptr;
const char *RTI::ValueLengthExceeded::_ex = nullptr;

