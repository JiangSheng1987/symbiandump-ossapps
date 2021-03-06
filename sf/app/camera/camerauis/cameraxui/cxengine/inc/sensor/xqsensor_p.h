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
* Description:
*
*/
#ifndef XQSENSORPRIVATE_H
#define XQSENSORPRIVATE_H

// INCLUDES
#include "xqsensor.h"
#include <sensrvdatalistener.h>

// FORWARD DECLARATIONS
class CSensrvChannelFinder;

// CLASS DECLARATION
class XQSensorPrivate: public QObject, public CBase,
    public MSensrvDataListener
{
protected:
    XQSensorPrivate(XQSensor& qq);
    virtual ~XQSensorPrivate();
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void startReceiving() = 0;
    virtual void stopReceiving() = 0;
    virtual XQSensor::Error error() const = 0;

protected:
    CSensrvChannel* CreateChannelL(TSensrvChannelTypeId aType);

protected:  //from MSensrvDataListener
    virtual void DataError(CSensrvChannel& aChannel, TSensrvErrorSeverity aError);
    virtual void GetDataListenerInterfaceL(TUid /*aInterfaceUid*/,
        TAny*& aInterface) { aInterface = NULL; }

private:
    void FindChannelL(TSensrvChannelTypeId aType, TSensrvChannelInfo& aChannelInfo);

protected:
    friend class XQSensor;
    XQSensor& q;

protected:
    CSensrvChannelFinder* iSensrvChannelFinder;
};

#endif /*XQSENSORPRIVATE_H*/

// End of file
