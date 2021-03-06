// Copyright (c) 1999-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __HLPPANIC_H__
#define __HLPPANIC_H__

#include <e32std.h>


// Enums
enum THlpPanic
	{
	EHlpNoRowAtCursor,
	EHlpInvalidView,
	EHlpInvalidTDbCol,
	EHlpInvalidTDbKeyCol,
	EHlpInvalidColName,
	EHlpInvalidTableName,
	EHlpInvalidComparison,
	EHlpInvalidQuery,
	EHlpDatabaseInTransaction,
	EHlpDatabaseNotInTransaction,
	EHlpNoCriterion,
	EHlpNoCategoryList,
	EHlpNoPictureFactory,
	EHlpNoPictureStore,
	EHlpNoHelpList,
	EHlpNoItem,
	EHlpNoTopic,
	EHlpNoView,
	EHlpAsynchSearchError,
	EHlpTopicNoRowsInView,
	EHlpFault,
	EHlpUnlocatedHelpPicture,
	EHlpNotEnoughZoomRatios,
	EHlpNoHelpModelPointer,
	//
	EHlpLast
	};

GLDEF_C	void Panic(THlpPanic aReason);

#endif
