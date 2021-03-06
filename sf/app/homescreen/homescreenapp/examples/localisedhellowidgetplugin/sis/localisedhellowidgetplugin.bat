@rem
@rem Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
@rem All rights reserved.
@rem This component and the accompanying materials are made available
@rem under the terms of "Eclipse Public License v1.0"
@rem which accompanies this distribution, and is available
@rem at the URL "http://www.eclipse.org/legal/epl-v10.html".
@rem
@rem Initial Contributors:
@rem Nokia Corporation - initial contribution.
@rem
@rem Contributors:
@rem
@rem Description:
@rem
@echo off

if exist localisedhellowidgetplugin.sisx del localisedhellowidgetplugin.sisx

makesis localisedhellowidgetplugin.pkg
signsis localisedhellowidgetplugin.sis localisedhellowidgetplugin.sisx ../../../internal/sis/rd.cer ../../../internal/sis/rd-key.pem

if exist localisedhellowidgetplugin.sisx (
echo localisedhellowidgetplugin.sisx creation SUCCEEDED
del localisedhellowidgetplugin.sis
)

if not exist localisedhellowidgetplugin.sisx (
echo localisedhellowidgetplugin.sisx creation FAILED
)