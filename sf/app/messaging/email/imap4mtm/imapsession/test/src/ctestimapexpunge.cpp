// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
//

#include "ctestimapexpunge.h"

#include "cfakeinputstream.h"
#include "cfakeoutputstream.h"
#include "cactivewaiter.h"
#include "moutputstream.h"
#include "cimapsession.h"
#include "cimaputils.h"
#include "cimapfolderinfo.h"

CTestImapExpunge::CTestImapExpunge()
	: iInputStream(NULL)
	, iOutputStream(NULL)
	, iActiveWaiter(NULL)
	, iImapSession(NULL)
	{}

CTestImapExpunge::~CTestImapExpunge()
	{
	delete iImapSession;
	delete iActiveWaiter;
	delete iOutputStream;
	delete iInputStream;
	CImapUtils::Delete();
	}

void CTestImapExpunge::SetupL()
	{
	ASSERT(iInputStream == NULL);
	ASSERT(iOutputStream == NULL);
	ASSERT(iActiveWaiter == NULL);
	ASSERT(iImapSession == NULL);

	CImapUtils::CreateL();
	iInputStream = CFakeInputStream::NewL(Logger());
	iOutputStream = CFakeOutputStream::NewL(Logger());
	iActiveWaiter = new(ELeave)CActiveWaiter(Logger());
	
	CImapSettings* imapSettings=NULL; 
	CImapMailStore* imapMailStore=NULL;
	
	iImapSession = CImapSession::NewL(*imapSettings,*imapMailStore,*iInputStream, *iOutputStream);

	INFO_PRINTF1(_L("Setup: ServerGreeting"));
	iInputStream->ResetInputStrings();
	iInputStream->AppendInputStringL(_L8("* OK Microsoft Exchange 2000 IMAP4rev1 server version 6.0.6249.0 (lon-cn-exchng2k.msexchange2k.closedtest.intra) ready.\r\n"));
	
	ASSERT_EQUALS(CImapSession::EServerStateNone, iImapSession->ServerState());
	
	iImapSession->ReadServerGreetingL(iActiveWaiter->iStatus);
	iActiveWaiter->WaitActive();
	
	INFO_PRINTF1(_L("...Login"));
	iInputStream->ResetInputStrings();
	iInputStream->AppendInputStringL(_L8("1 OK LOGIN completed\r\n"));
			
	iImapSession->LoginL(iActiveWaiter->iStatus, _L8("username"), _L8("password"));
	iActiveWaiter->WaitActive();

	ASSERT_EQUALS(CImapSession::EServerStateAuthenticated, iImapSession->ServerState());


	INFO_PRINTF1(_L("...Select inbox"));
	iInputStream->ResetInputStrings();
	iInputStream->AppendInputStringL(_L8("* 23 EXISTS\r\n"));
	iInputStream->AppendInputStringL(_L8("* 1 RECENT\r\n"));
	iInputStream->AppendInputStringL(_L8("2 OK [READ-WRITE] SELECT completed\r\n"));
		
	CImapFolderInfo* folderInfo = CImapFolderInfo::NewL();
	CleanupStack::PushL(folderInfo);
	
	folderInfo->SetNameL(_L16("inbox"));
	CleanupStack::Pop(folderInfo);
	iImapSession->SelectL(iActiveWaiter->iStatus, folderInfo);
	iActiveWaiter->WaitActive();

	ASSERT_EQUALS(CImapSession::EServerStateSelected, iImapSession->ServerState());
	ASSERT_EQUALS(folderInfo, iImapSession->SelectedFolderInfo());
	
	INFO_PRINTF1(_L("Setup: Complete"));
	}
	
void CTestImapExpunge::TearDownL()
	{
	delete iImapSession;
	iImapSession = NULL;
	
	delete iActiveWaiter;
	iActiveWaiter = NULL;
	
	delete iOutputStream;
	iOutputStream = NULL;
	
	delete iInputStream;
	iInputStream = NULL;

	CImapUtils::Delete();
	}

// Tests
void CTestImapExpunge::TestExpungeL()
	{
	INFO_PRINTF1(_L("TestExpungeL"));
	iInputStream->ResetInputStrings();
	
	iInputStream->AppendInputStringL(_L8("* 3 EXPUNGE\r\n"));
	iInputStream->AppendInputStringL(_L8("* 3 EXPUNGE\r\n"));
	iInputStream->AppendInputStringL(_L8("* 5 EXPUNGE\r\n"));
	iInputStream->AppendInputStringL(_L8("3 OK Expunge completed\r\n"));
		
	iImapSession->ExpungeL(iActiveWaiter->iStatus);
	iActiveWaiter->WaitActive();
	
	CImapFolderInfo* folderInfo = iImapSession->SelectedFolderInfo();
	ASSERT_NOT_NULL(folderInfo);
	
	RArray<TUint> expungedMessages = folderInfo->ExpungedMessages();

	ASSERT_EQUALS(expungedMessages.Count(), 3);
	ASSERT_EQUALS(expungedMessages[0], 3u); // unsigned 3 (etc)
	ASSERT_EQUALS(expungedMessages[1], 3u);
	ASSERT_EQUALS(expungedMessages[2], 5u);
	
	INFO_PRINTF1(_L("Complete"));
	}
	
CTestSuite* CTestImapExpunge::CreateSuiteL(const TDesC& aName)
// static
	{
	SUB_SUITE;
	ADD_ASYNC_TEST_STEP(TestExpungeL);
	END_SUITE;
	}
