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
* Description:  stub tn manager
 *
*/

// Version : %version:  1 %

#include <qsize.h>
#include "thumbnailmanager_qt.h"
 
QMap<int, ThumbnailManager::TnRequest> ThumbnailManager::mRequests = QMap<int, ThumbnailManager::TnRequest>();

ThumbnailManager::ThumbnailManager( QObject* parentPtr ) :
QObject( parentPtr ),
mGetThumbFails(false),
mThumbnailReadyError(0)
{
}

ThumbnailManager::~ThumbnailManager()
{
}

ThumbnailManager::QualityPreference ThumbnailManager::qualityPreference() const
{
    return mQuality;
}

bool ThumbnailManager::setQualityPreference( QualityPreference
    qualityPreference )
{
    mQuality = qualityPreference;
    return true;
}
 
ThumbnailManager::DisplayMode ThumbnailManager::displayMode() const
{
    return Color16MAP;
}

bool ThumbnailManager::setDisplayMode( ThumbnailManager::DisplayMode displayMode )
{
    Q_UNUSED(displayMode);
    return true;
}

QSize ThumbnailManager::thumbnailSize() const
{
    return QSize(128, 128); // ThumbnailMedium?
}

bool ThumbnailManager::setThumbnailSize( const QSize& thumbnailSize )
{
    Q_UNUSED(thumbnailSize);
    return true;
}

bool ThumbnailManager::setThumbnailSize( ThumbnailSize thumbnailSize )
{
    mThumbSize = thumbnailSize;
    return true;
}

ThumbnailManager::ThumbnailMode ThumbnailManager::mode() const
{
    return Default;
}

bool ThumbnailManager::setMode( ThumbnailMode mode )
{
    Q_UNUSED(mode);
    return true;
}

int ThumbnailManager::getThumbnail( const QString& fileName, void * clientData, 
        int priority )
{
    Q_UNUSED(fileName);
    Q_UNUSED(clientData);
    Q_UNUSED(priority);
    return 0;    
}

int ThumbnailManager::getThumbnail( unsigned long int thumbnailId, void * clientData, 
        int priority )
{
    Q_UNUSED(thumbnailId);
    Q_UNUSED(clientData);
    Q_UNUSED(priority);
    return 0;
}    

int ThumbnailManager::setThumbnail( const QPixmap& source, const QString& filename,
        void * clientData , Priority priority )
{
    Q_UNUSED(source);
    Q_UNUSED(filename);
    Q_UNUSED(clientData);
    Q_UNUSED(priority);
    return 0;
}

void ThumbnailManager::deleteThumbnails( const QString& fileName )
{
    Q_UNUSED(fileName);
}

void ThumbnailManager::deleteThumbnails( unsigned long int thumbnailId )
{
    Q_UNUSED(thumbnailId);
}

bool ThumbnailManager::cancelRequest( int id )
{
    if(mRequests.contains(id)) {
        mRequests[id].cancelled = true;
    }
    return true;
}

bool ThumbnailManager::changePriority( int id, Priority newPriority )
{
    if(mRequests.contains(id)) {
        mRequests[id].priority = newPriority;
    }
    return true;
}

void ThumbnailManager::emitThumbnailReady(int tnId )
{
    QPixmap pixmap(100,100);
    pixmap.fill(Qt::white);
    void* internal = 0;
    
    if(mRequests.contains(tnId)) {
        internal = mRequests[tnId].id;
        mRequests.remove(tnId);
    }
    
    emit thumbnailReady(pixmap, internal, tnId, mThumbnailReadyError);
}

