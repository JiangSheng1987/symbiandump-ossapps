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
# Description: 
#
#include ../../../../../../../../../build/ant_s60.mk

build_java : 
	call ant

FREEZE : 
	rem do_nothing

LIB : 
	rem do_nothing

MAKMAKE : 
	rem do_nothing

RESOURCE : 
	rem do_nothing

BLD : build_java

SAVESPACE : 
	rem do_nothing

FINAL :
	rem do_nothing

CLEAN : 
	ant clean

RELEASABLES : 
	rem do_nothing