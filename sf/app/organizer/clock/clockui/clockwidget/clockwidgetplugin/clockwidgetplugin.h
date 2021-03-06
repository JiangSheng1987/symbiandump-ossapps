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
* Description: Clockwidget custom document loader plugin.
*
*/

#ifndef CLOCKWIDGETDPLUGIN_H    
#define CLOCKWIDGETDPLUGIN_H

// System includes
#include <hbdocumentloaderplugin.h>
#include <qplugin.h>


class ClockWidgetPlugin : public HbDocumentLoaderPlugin
{

private:
    virtual QObject *createObject(const QString &type, const QString &name);
    virtual QList<const QMetaObject *> supportedObjects();
    
};
Q_EXPORT_PLUGIN(ClockWidgetPlugin) 

#endif // CLOCKWIDGETDPLUGIN_H

// End of file  --Don't remove this.
