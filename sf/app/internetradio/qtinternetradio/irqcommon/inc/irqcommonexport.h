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

#ifndef IRQCOMMMONEXPORT_H_
#define IRQCOMMMONEXPORT_H_

#include <QtGlobal>

#ifdef BUILD_IRQCOMMMON_DLL
    #define IRQCOMMMON_DLL_EXPORT Q_DECL_EXPORT
#else
    #define IRQCOMMMON_DLL_EXPORT Q_DECL_IMPORT
#endif

#endif /* IRQCOMMMONEXPORT_H_ */
