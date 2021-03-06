// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#include "TestCalInterimApiDeleteEntryByTimeRangeAsync.h"
#include <calsession.h>
#include <calinstance.h>
#include <calinstanceview.h>
#include <calentry.h>
#include <calentryview.h>
#include <hal.h>
#include <hal_data.h>

_LIT(KFilterStartDateTime,	"starttime");
_LIT(KFilterEndDateTime,	"endtime");
_LIT(KFilterType,			"filter");
_LIT(KTimeMode,				"timemode");


CTestCalInterimApiDeleteEntryByTimeRangeAsync::CTestCalInterimApiDeleteEntryByTimeRangeAsync()
:	CTestCalInterimApiSuiteStepBase()
	{
	// **MUST** call SetTestStepName in the constructor as the controlling
	// framework uses the test step name immediately following construction to set
	// up the step's unique logging ID.
	SetTestStepName( KTestCalInterimApiDeleteEntryByTimeRangeAsync );
	}

/**
 * Destructor
 */
CTestCalInterimApiDeleteEntryByTimeRangeAsync::~CTestCalInterimApiDeleteEntryByTimeRangeAsync()
	{
	}

/**
Base class pure virtual.
@return		EPass or EFail indicating the result of the test step.
*/
TVerdict CTestCalInterimApiDeleteEntryByTimeRangeAsync::doTestStepL()
	{
	TPtrC	startTime;
	TPtrC	endTime;
	TInt	filter;
	TPtrC	timeMode;
	
	TESTL( GetStringFromConfig(ConfigSection(),  KFilterStartDateTime,  startTime) );
	TESTL( GetStringFromConfig(ConfigSection(),  KFilterEndDateTime,  endTime) );
	TESTL( GetIntFromConfig(ConfigSection(),  KFilterType, filter) );
	// Dont mind if it is not given in the ini file
	GetStringFromConfig(ConfigSection(), KTimeMode, timeMode);
	
	CCalEntryView*	entryView = CCalEntryView::NewL(GetSession(), *this);
	CleanupStack::PushL(entryView);
	CActiveScheduler::Start();

	// To convert TPtrc to TTime
	TTime	filterStartDateTime;
	filterStartDateTime.Set(startTime);
	TTime	filterEndDateTime;
	filterEndDateTime.Set(endTime);

	// To change TTime as TCalTime
	TCalTime	calStartDateTime;
	// Sets the time mode to floating or Utc based on the time mode given
	SetCalTimeL(filterStartDateTime, calStartDateTime, SetTimeMode(timeMode));
	TCalTime	calEndDateTime;
	SetCalTimeL(filterEndDateTime, calEndDateTime, SetTimeMode(timeMode));
	
	CalCommon::TCalTimeRange	calTimeRange(calStartDateTime, calEndDateTime);

	// When we run multiple instances of this test step concurrently for
	// testing asynchronous operations, the server returns KErrServerBusy.
	// If so we try again and again. 
	TInt numOfTimes = 0;
	TInt err = KErrNone;
	do
		{
		SetTestStepError(KErrNone);
		TRAP( err, entryView->DeleteL( calTimeRange, CalCommon::TCalViewFilter(filter), *this) );
		CActiveScheduler::Start();
		++numOfTimes;
		}
	while (TestStepError() == KErrServerBusy);
	
    // Set the test result.
	if (err == KErrNone)
	    {
	    SetTestStepResult( EPass );
	    }
	else
	    {
	    SetTestStepResult( EFail );
	    SetTestStepError( err );
	    }
	
	CleanupStack::PopAndDestroy(entryView);
	return TestStepResult();
	}
