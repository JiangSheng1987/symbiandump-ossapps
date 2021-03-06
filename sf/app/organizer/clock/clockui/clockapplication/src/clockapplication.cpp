/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: Definition file for class ClockApplication.
*
*/


// User includes
#include "clockapplication.h"
#include "clockappcontroller.h"
#include "OstTraceDefinitions.h"
#ifdef OST_TRACE_COMPILER_IN_USE
#include "clockapplicationTraces.h"
#endif


/*!
	\class ClockApplication

	This class creates the ClockAppController object.
 */
/*!
	Constructor.
 */
ClockApplication::ClockApplication(int &argc, char *argv[]):
 HbApplication(argc, argv)
{
OstTraceFunctionEntry0( CLOCKAPPLICATION_CLOCKAPPLICATION_ENTRY );
OstTraceFunctionExit0( CLOCKAPPLICATION_CLOCKAPPLICATION_EXIT );
}

/*!
	Destructor.
 */
ClockApplication::~ClockApplication()
{
	OstTraceFunctionEntry0( DUP1_CLOCKAPPLICATION_CLOCKAPPLICATION_ENTRY );
	if (mController) {
		delete mController;
		mController = 0;
	}
OstTraceFunctionExit0( DUP1_CLOCKAPPLICATION_CLOCKAPPLICATION_EXIT );
}

/*!
	creates the ClockAppController object.
*/
void ClockApplication::createController()
{
	OstTraceFunctionEntry0( CLOCKAPPLICATION_CREATECONTROLLER_ENTRY );
	mController = new ClockAppController;
	connect(mController, SIGNAL(appReady()), this, SLOT(handleAppReady()));
OstTraceFunctionExit0( CLOCKAPPLICATION_CREATECONTROLLER_EXIT );
}

/*!
	Start the event loop for the application.
*/
bool ClockApplication::execution()
{
	OstTraceFunctionEntry0( CLOCKAPPLICATION_EXECUTION_ENTRY );
	int ret = 0;
	ret = exec();
	OstTraceFunctionExit0( CLOCKAPPLICATION_EXECUTION_EXIT );
	return ret;
}

/*!
	Emits the applicationReady signal.
 */
void ClockApplication::handleAppReady()
{
	OstTraceFunctionEntry0( CLOCKAPPLICATION_HANDLEAPPREADY_ENTRY );
	emit applicationReady();
	disconnect(mController, SIGNAL(appReady()), this, SLOT(handleAppReady()));
OstTraceFunctionExit0( CLOCKAPPLICATION_HANDLEAPPREADY_EXIT );
}

// End of file	--Don't remove this.
