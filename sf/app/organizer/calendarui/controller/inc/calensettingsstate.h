/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Calendar state machine
*
*/


#ifndef CALENSETTINGSSTATE_H
#define CALENSETTINGSSTATE_H

// INCLUDES
#include <e32base.h>
#include "calenstate.h"

// CLASS DEFINITIONS
/**
* Calendar settings state
*/
class CCalenSettingsState : public CCalenState
    {
    public:
        static CCalenSettingsState* NewLC( CCalenController& aController,
                                                    RHashSet<TCalenNotification>&aOutstandingNotifications );
        ~CCalenSettingsState();
        
    public:
        // From CCalenState
        TBool HandleCommandL( const TCalenCommand& aCommand,
                             CCalenStateMachine& aStateMachine );
        void HandleNotificationL(const TCalenNotification& aNotification,
                                  CCalenStateMachine& aStateMachine ); 
        
        void HandleStateActivationL();

    private:
        CCalenSettingsState( CCalenController& aController,
                                    RHashSet<TCalenNotification>& aOutstandingNotifications );
        void ConstructL();
    };


#endif // CALENSETTINGSSTATE_H

// end of file
