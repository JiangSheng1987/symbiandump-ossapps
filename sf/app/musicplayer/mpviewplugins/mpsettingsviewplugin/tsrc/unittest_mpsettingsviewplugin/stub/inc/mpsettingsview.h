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
* Description: MpNowPlayingWidget stub for testing MpCollectionDocumentLoader
*
*/

#ifndef MPSETTINGSVIEW_H
#define MPSETTINGSVIEW_H

//includes
#include <QGraphicsWidget>

class MpSettingsView : public QGraphicsWidget
{
    Q_OBJECT

public:
    explicit MpSettingsView();
    virtual ~MpSettingsView();
    
    void initializeView();
    void activateView();
    void deactivateView();

    void emitCommand(int cmd);
    void resetCounters();
    
signals:
    void command(int cmd);

public:
    int mInitializeViewCount;
    int mActivateViewCount;
    int mDeactivateViewCount;
    
};

#endif    // MPSETTINGSVIEW_H
