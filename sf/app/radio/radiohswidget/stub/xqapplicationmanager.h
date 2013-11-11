/*
* Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Stub for FM Radio home screen widget unit testing.
*
*/

#ifndef XQAPPLICATIONMANAGER_H
#define XQAPPLICATIONMANAGER_H

// System includes
#include <QObject>

// User includes
#include "xqaiwrequest.h"

class XQApplicationManager : public QObject
{
    Q_OBJECT

public:

    XQApplicationManager();
    ~XQApplicationManager();
    
    XQAiwRequest* create(const QString& interface, const QString& operation, bool embedded = true);

};

#endif // XQAPPLICATIONMANAGER_H