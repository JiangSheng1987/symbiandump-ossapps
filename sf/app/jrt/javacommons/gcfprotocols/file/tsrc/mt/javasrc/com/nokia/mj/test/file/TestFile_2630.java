/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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


package com.nokia.mj.test.file;

import j2meunit.framework.Test;
import j2meunit.framework.TestCase;
import j2meunit.framework.TestMethod;
import j2meunit.framework.TestSuite;

import java.util.*;
import java.io.*;

import java.io.IOException;
import javax.microedition.io.file.*;
import javax.microedition.io.*;

import com.nokia.mj.test.file.utils.FileTestUtils;
import com.nokia.mj.test.file.utils.FileTestBase;
import com.nokia.mj.test.file.utils.TestFailedException;
import com.nokia.mj.impl.installer.utils.InstallerMain;

public class TestFile_2630 extends FileTestBase
{
    public TestFile_2630()
    {
    }

    public TestFile_2630(String aTestName, TestMethod aTestMethod)
    {
        super(aTestName, aTestMethod);
    }

    public void assertFalse(String aMsg, boolean aCondition)
    {
        assertTrue(aMsg, !aCondition);
    }

    public static void registerTests(TestSuite suite)
    {
        suite.addTest(new TestFile_2630("run_2630", new TestMethod()
        {
            public void run(TestCase tc)
            {
                ((TestFile_2630) tc).run_2630();
            }
        }));
    }


    // Begin j2meunit test framework setup
    public void installerMain(String[] args)
    {
        TestSuite suite = new TestSuite(this.getClass().getName());
        registerTests(suite);

        com.nokia.mj.impl.utils.OmjTestRunner.run(suite);
    }

    public void run_2630()
    {
        FileConnection conn1 = null;
        int counter = 0;
        try
        {
            // File does not exists.
            conn1 = (FileConnection) Connector.open("file:///" + iRoot
                                                    + "mainTestDir/test100/gdfgggr", Connector.READ_WRITE);
            counter = 1;
            if (conn1.exists())
                throw new TestFailedException();
            try
            {
                conn1.truncate(30);
                throw new TestFailedException();
            }
            catch (IOException ex)
            {
            }
            counter = 2;
            conn1.close();
            counter = 3;

            // "Connection closed" error case.
            conn1 = (FileConnection) Connector.open("file:///" + iRoot
                                                    + "mainTestDir/test260/file260b.txt", Connector.READ_WRITE);
            counter = 4;
            if (!conn1.exists())
                throw new TestFailedException();
            conn1.close();
            try
            {
                conn1.truncate(1);
                throw new TestFailedException();
            }
            catch (ConnectionClosedException ex)
            {
            }
            counter = 5;
            conn1.close();
            counter = 6;

            // "Connection has been opened in the READ mode" error case.
            conn1 = (FileConnection) Connector.open("file:///" + iRoot
                                                    + "mainTestDir/test260/file260b.txt", Connector.READ);
            counter = 7;
            if (!conn1.exists())
                throw new TestFailedException();
            try
            {
                conn1.truncate(1);
                throw new TestFailedException();
            }
            catch (IllegalModeException ex)
            {
            }
            counter = 8;
            conn1.close();
            counter = 9;

            // "Negative argument value" error case.
            conn1 = (FileConnection) Connector.open("file:///" + iRoot
                                                    + "mainTestDir/test260/file260b.txt", Connector.READ_WRITE);
            counter = 10;
            if (!conn1.exists())
                throw new TestFailedException();
            counter = 11;
            try
            {
                conn1.truncate(-1);
                throw new TestFailedException();
            }
            catch (IllegalArgumentException ex)
            {
            }
            counter = 12;
            conn1.close();

            // WRITE access test for read-only file.
            conn1 = (FileConnection) Connector.open("file:///" + iRoot
                                                    + "mainTestDir/test020/binaryFile2.dat", Connector.WRITE);
            counter = 14;
            try
            {
                conn1.truncate(4);
                throw new TestFailedException();
            }
            catch (IOException ex)
            {
            }
            counter = 15;
            conn1.close();

            assertTrue(" run_2630() ok ", true);
            System.out.println(" run_2630() ok \n");
        }
        catch (Exception ex)
        {
            append(ex.toString());
            append("TEST FAILED!!! Case: run_2630() counter: " + counter + "\n");
            assertTrue(" run_2630() FAILED!!! Counter: " + counter, false);
        }
    }//end run_2630()

}
