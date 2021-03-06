/*
* Copyright (c) 2002-2004 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:  This module contains the implementation of phone engine panic function
*
*/


// INCLUDE FILES
#include <e32std.h>
#include "pepanic.pan"


// EXTERNAL DATA STRUCTURES
// None.

// EXTERNAL FUNCTION PROTOTYPES  
// None.

// CONSTANTS
// None.

// MACROS
// None.

// LOCAL CONSTANTS AND MACROS
// None.

// MODULE DATA STRUCTURES
// None.

// LOCAL FUNCTION PROTOTYPES
// None.

// ==================== LOCAL FUNCTIONS ====================

// -----------------------------------------------------------------------------
// Panic
// Creates PhoneEngine panic.
// Returns: None.
// -----------------------------------------------------------------------------
//
GLDEF_C void Panic( TPEPanic aPanic )
    {
    User::Panic( KPEPhoneEnginePanic, aPanic );
    }

// ===================== MEMBER FUNCTIONS ==================
// None.

// ================= OTHER EXPORTED FUNCTIONS ==============
// None.

// End of File
