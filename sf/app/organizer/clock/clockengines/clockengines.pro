#
# Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description:  Project definition file for project clockengine
#


TEMPLATE = subdirs
BLD_INF_RULES.prj_mmpfiles +="./clocktimezoneresolver/group/clocktimezoneresolver.mmp" \   
			      "./clocktimesourceinterface/group/clocktimesourceinterface.mmp" \   
			  "./clocknitzplugin/group/clocknitzplugin.mmp" \
			      "./utilities/clockecomlistener/group/clockecomlistener.mmp" \  
                 "./clockserver/client/group/clockserverclient.mmp" \
				  "./clockserver/server/group/clockserver.mmp"    
			    