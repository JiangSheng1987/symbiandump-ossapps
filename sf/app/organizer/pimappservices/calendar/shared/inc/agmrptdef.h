// Copyright (c) 1997-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __AGMRPTDEF_H__
#define __AGMRPTDEF_H__

#include "agmcalendartime.h"

class TAgnRpt;
class TAgnDailyRpt;
class TAgnWeeklyRpt;
class TAgnMonthlyByDatesRpt;
class TAgnMonthlyByDaysRpt;
class TAgnYearlyByDateRpt;
class TAgnYearlyByDayRpt;
class CAgnRptDef;
class CAgnSimpleEntry;
class CAgnTlsProxy;
class CTzRules;
class CAgnTzRules;

const TInt KMonthlyByDaysArraySize = 5;

NONSHARABLE_CLASS(TAgnRpt)
/** Abstract base class for the agenda model repeat types.

Stores the repeat details common to all agenda model repeat types. The common 
repeat details are the until time of the repeat and the interval between 
repeats.
If an instance repeats forever, then its end date will be TCalTime::MaxTime()..
An instance of a TAgnRpt-derived class is owned by a repeat definition (CAgnRptDef), 
which also contains the repeat exceptions list. It is set using 
CAgnRptDef::SetDaily(), SetWeekly() etc. 
@internalComponent
@released
*/
	{
public:
	enum TType 
		{
		/** Repeat every x days */
		EDaily=1,
		/** Repeat every x weeks on days, e.g. every Monday and Thursday every other week - first day of week affects this*/
		EWeekly,
		/** Repeat every x months, e.g. on the 3rd, 5th and 9th */
		EMonthlyByDates,
		/** Repeat every x months, e.g. on the 1st Tuesday of the month and 3rd Wednesday */
		EMonthlyByDays,
		/** Repeat every x years, e.g on the 3rd of October */
		EYearlyByDate,
		/** Repeat every x years, e.g. on the 4th Wednesday of November */
		EYearlyByDay,
		};
		
	/**
	@internalComponent
	@released
	*/
	enum TWeekInMonth
		{
		/** The first week in the month. Implementation requires this to be 0. */
		EFirst=0,
		/** The second week in the month */
		ESecond,
		/** The third week in the month */
		EThird,
		/** The fourth week in the month */
		EFourth,
		/** The last week in the month */
		ELast,
		};

	IMPORT_C const TAgnCalendarTime& UntilTimeL() const;
	IMPORT_C TTime FindRptUntilTimeLocalL(TUint aCount) const; // Calculates the repeat end date from the number of instances
	IMPORT_C TUint16 Interval() const;
	IMPORT_C void SetCount(TInt aRepCount);
	IMPORT_C TInt Count() const;

	TAgnRpt(CAgnRptDef& aOwningRptDef);
	TAgnRpt(const TAgnRpt& aRpt, CAgnRptDef& aOwningRptDef);

	const TAgnCalendarTime& StartTime() const;
	
	void SetUntilTime(const TAgnCalendarTime& aUntilTime);
	IMPORT_C void SetInterval(TUint16 aInterval);
	void ClearAll();
	
	void ResetCachedStartTimeOffset();
	void ResetCachedUntilTimeOffset();
		
	TTime StartTimeAsRptLocalL() const;
	TTime UntilTimeAsRptLocalL() const;
	
	TBool operator==(const TAgnRpt& aRpt) const;
	TBool operator!=(const TAgnRpt& aRpt) const;
	
	virtual void InternalizeL(RReadStream& aStream);
	virtual void ExternalizeL(RWriteStream& aStream) const;

	virtual TInt InvariantL() const;

	virtual TType Type() const = 0;
	virtual TTime FindRptUntilTimeRptLocalL(TUint aCount) const = 0;
	virtual TUint InstanceCountL() const = 0; // Returns the number of instances generated by the repeat algorithm

	virtual TBool IsAlignedRptLocalL(const TTime& aRptLocalDate) const = 0;
	virtual TBool IsAlignedUtcL(const TTime& aUtcDate) const = 0;
	virtual TTime NudgeNextInstanceUtcL(const TTime& aDay) const = 0;
	virtual TTime NudgePreviousInstanceUtcL(const TTime& aDay) const = 0;

protected:
	TTime ConvertFromRepeatLocalToUtcL(const TTime& aRptLocalDate) const;
	TTime ConvertFromUtcToRepeatLocalL(const TTime& aUtcDate) const;
	TTime ConvertFromRepeatLocalToSystemLocalL(const TTime& aRptLocalTime) const;
	TTime ConvertFromSystemLocalToRepeatLocalL(const TTime& aSysLocalTime) const;
	
	TUint MapDayToBits(TDay aDay) const;
	TUint MapDateToBits(TUint aDate) const;

	TTime NudgeNextAlignedStartTimeL(const TTime& aRptLocalDate) const;
	TTime NudgePreviousAlignedStartTimeL(const TTime& aRptLocalDate) const;

	TBool HourAndMinutesDifferentFromStartTimeL(const TTime& aDate) const;
	void GetTimeAsRptLocalL(const TAgnCalendarTime& aCalendarTime, TTime& aTimeAsRptLocal, TInt16& aCachedOffset) const;

	MAgnCalendarTimeMode::TTimeMode TimeMode() const;

private:
	TAgnRpt(const TAgnRpt&); // not implemented 
	void operator=(const TAgnRpt&); // not implemented 

protected:
	CAgnRptDef&			iOwningRptDef;
	mutable TAgnCalendarTime	iUntilTime;
	TUint16				iInterval;
	
	mutable TInt16		iStartTimeRptLocalOffset;
	mutable TInt16		iUntilTimeRptLocalOffset;
	TInt 				iCount;
	mutable TBool		iUntiltimeHasBeenSet;
	};



NONSHARABLE_CLASS(TAgnDailyRpt) : public TAgnRpt
/** Daily repeating class. 

@internalComponent
@released
*/
	{
public:
	IMPORT_C TAgnDailyRpt(CAgnRptDef& aOwningRptDef);
	
	TAgnDailyRpt(const TAgnDailyRpt& aRpt, CAgnRptDef& aOwningRptDef);
	TType Type() const;
	
	// from TAgnRpt
	TUint InstanceCountL() const;
	
private:
	TTime FindRptUntilTimeRptLocalL(TUint aCount) const;

	TAgnDailyRpt(const TAgnDailyRpt& ); // not implemented
	void operator=(const TAgnDailyRpt& ); // not implemented
	
	// from TAgnRpt
	TBool IsAlignedRptLocalL(const TTime& aRptLocalDate) const;
	TBool IsAlignedUtcL(const TTime& aUtcDate) const;
	TTime NudgeNextInstanceUtcL(const TTime& aDay) const;
	TTime NudgePreviousInstanceUtcL(const TTime& aDay) const;
	};
	


NONSHARABLE_CLASS(TAgnWeeklyRpt)	: public TAgnRpt
/** Weekly repeat class. 

In addition to the common repeat information inherited from TAgnRpt, this 
class stores the days in the week on which the repeat occurs (using a set 
of flags), and the day which is the start of the week. The repeat details 
are used by the CAgnRptDef class, which also stores a list of any exceptions 
to the repeat. 
@internalComponent
@released
*/
	{	
public:
	IMPORT_C TAgnWeeklyRpt(CAgnRptDef& aOwningRptDef);

	IMPORT_C void SetDay(TDay aDay);
	IMPORT_C void SetFirstDayOfWeek(TDay aDay);//this function is for testing purposes - the start day is

	IMPORT_C TBool IsDaySet(TDay aDay) const;
	IMPORT_C TDay FirstDayOfWeek() const;	 	// set automatically from the operating system
	
	TAgnWeeklyRpt(const TAgnWeeklyRpt& aRpt, CAgnRptDef& aOwningRptDef);
	
	TType Type() const;
	TBool operator==(const TAgnWeeklyRpt& aRpt) const;
	TUint NumDaysSet() const;

	// from TAgnRpt
	TUint InstanceCountL() const;
	TInt InvariantL() const;	  // self testing
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	
private:
	TTime DayAtStartOfWeek(const TTime& aDay) const;
	TInt IsDateInValidWeekRptLocalL(const TTime& aDate) const;
	TInt WeekNumRptLocalL(const TTime& aDate) const;
	TTime FindRptUntilTimeRptLocalL(TUint aCount) const;
	
	TAgnWeeklyRpt(const TAgnWeeklyRpt& ); // not implemented
	void operator=(const TAgnWeeklyRpt& ); // not implemented

	// from TAgnRpt
	TBool IsAlignedRptLocalL(const TTime& aRptLocalDate) const;
	TBool IsAlignedUtcL(const TTime& aUtcDate) const;
	TTime NudgeNextInstanceUtcL(const TTime& aDay) const;
	TTime NudgeNextInstanceRptLocalL(const TTime& aRptLocalDate) const;
	TTime NudgePreviousInstanceUtcL(const TTime& aDay) const;
	TTime NudgePreviousInstanceRptLocalL(const TTime& aRptLocalDate) const;
private:
	TUint8 	iWeeklyRptDays; //stores the days of the week in the lowest 7 bits (bit 1 = Monday)
	TUint8 	iFirstDayOfWeek; // stores the start day of the week in the lowest 7 bits
	};

NONSHARABLE_CLASS(TAgnMonthlyRpt) : public TAgnRpt
/** Abstract base class for the monthly repeat types TAgnMonthlyByDaysRpt and 
TAgnMonthlyByDatesRpt. 
@internalComponent
@released
*/
	{ 		
public:
	// from TAgnRpt
	TUint InstanceCountL() const;
	
protected:
	TAgnMonthlyRpt(CAgnRptDef& aOwningRptDef);
	TAgnMonthlyRpt(const TAgnRpt& aRpt, CAgnRptDef& aOwningRptDef);
	TBool DateFallsInAlignedMonthL(const TDateTime& aDate) const;
private:
	void NudgeNextMonthL(TTime& aDate) const; // repeat local
	void NudgePreviousMonthL(TTime& aDate) const; // repeat local
	TTime FindRptUntilTimeRptLocalL(TUint aCount) const;

	virtual TTimeIntervalDays NumDaysToNextInstanceFrom(const TTime& aDate) const = 0;
	virtual TInt NumInstancesPerMonth() const = 0;

	// from TAgnRpt
	TTime NudgeNextInstanceUtcL(const TTime& aDay) const;
	TTime NudgeNextInstanceRptLocalL(const TTime& aDay) const;
	TTime NudgePreviousInstanceUtcL(const TTime& aDay) const;
	TTime NudgePreviousInstanceRptLocalL(const TTime& aDay) const;
	};


NONSHARABLE_CLASS(TAgnMonthlyByDaysRpt) : public TAgnMonthlyRpt
/** Stores the days in a month on which a repeat can occur, for instance Tuesday 
in the first week, Sunday in the last week. 
@internalComponent
@released
*/
	{
public:
	IMPORT_C TAgnMonthlyByDaysRpt(CAgnRptDef& aOwningRptDef);
	IMPORT_C void SetDay(TDay aDay,TWeekInMonth aWeek);
	IMPORT_C TBool IsDaySet(TDay aDay,TWeekInMonth aWeek) const;
	
	TAgnMonthlyByDaysRpt(const TAgnMonthlyByDaysRpt& aRpt, CAgnRptDef& aOwningRptDef);
	TType Type() const;
	void ClearAllDays();
	TBool operator==(const TAgnMonthlyByDaysRpt& aRpt) const;
	TInt NumDaysSet() const;
	
	// from TAgnRpt
	TInt InvariantL() const;	  // self testing
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;

private:
	TWeekInMonth GetWeekToCheckRptLocal(const TTime& aTime) const;
	TTime FindLastEventOnSpecifiedMonthRptLocal(const TTime& aTime) const;
	TBool CheckLastWeekRptLocal(const TTime& aTime) const;
	TBool EventOnDateRptLocal( const TTime& aTime ) const;

	TAgnMonthlyByDaysRpt(const TAgnMonthlyByDaysRpt& ); // not implemented
	void operator=(const TAgnMonthlyByDaysRpt& ); // not implemented
	
	// from TAgnRpt
	TBool IsAlignedRptLocalL(const TTime& aDate) const;
	TBool IsAlignedUtcL(const TTime& aUtcDate) const;
	
	// from TAgnMonthlyRpt
	TTimeIntervalDays NumDaysToNextInstanceFrom(const TTime& aDate) const;
	TInt NumInstancesPerMonth() const;

private:
	TUint8 iMonthlyRptDays[KMonthlyByDaysArraySize]; // stores the days of the week for 5 weeks - EFirst to ELast. 
	};



NONSHARABLE_CLASS(TAgnMonthlyByDatesRpt) : public TAgnMonthlyRpt
/** Stores the dates in a month on which a repeat can occur. 
@internalComponent
@released
*/
	{
public:
	IMPORT_C TAgnMonthlyByDatesRpt(CAgnRptDef& aOwningRptDef);
	IMPORT_C void SetDate(TUint aDateInMonth);
	IMPORT_C TBool IsDateSet(TUint aDateInMonth) const;
	
	TAgnMonthlyByDatesRpt(const TAgnMonthlyByDatesRpt& aRpt, CAgnRptDef& aOwningRptDef);
	
	TType Type() const;
	TInt NumDatesSet() const;
	TBool operator==(const TAgnMonthlyByDatesRpt& aRpt) const;

	// from TAgnRpt
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	TInt InvariantL() const; // self testing
private:
	TTime FindLastEventOnSpecifiedMonthRptLocal(const TTime& aTime) const;
	
	TAgnMonthlyByDatesRpt(const TAgnMonthlyByDatesRpt& ); // not implemented
	void operator=(const TAgnMonthlyByDatesRpt& ); // not implemented
	
	// from TAgnRpt
	TBool IsAlignedRptLocalL(const TTime& aRptLocalDate) const;
	TBool IsAlignedUtcL(const TTime& aUtcDate) const;

	// from TAgnMonthlyRpt
	TTimeIntervalDays NumDaysToNextInstanceFrom(const TTime& aDate) const;
	TInt NumInstancesPerMonth() const;
	
private:
	TUint32 iMonthlyRptDates;// stores the dates of a month i.e. bit 2 = the 2nd 
	};

NONSHARABLE_CLASS(TAgnYearlyByDateRpt) : public TAgnRpt
/** A yearly by date repeat, for example 3rd October each year. 
@internalComponent
@released
*/
	{
public:
	IMPORT_C TAgnYearlyByDateRpt(CAgnRptDef& aOwningRptDef);
	
	TAgnYearlyByDateRpt(const TAgnYearlyByDateRpt& aRpt, CAgnRptDef& aOwningRptDef);
	TType Type() const;
	
	// from TAgnRpt
	TUint InstanceCountL() const;
private:
	TTime FindRptUntilTimeRptLocalL(TUint aCount) const;

	TAgnYearlyByDateRpt(const TAgnYearlyByDateRpt& ); // not implemented
	void operator=(const TAgnYearlyByDateRpt& ); // not implemented
	
	// from TAgnRpt
	TBool IsAlignedRptLocalL(const TTime& aRptLocalDate) const;
	TBool IsAlignedUtcL(const TTime& aUtcDate) const;
	TTime NudgeNextInstanceUtcL(const TTime& aDay) const;
	TTime NudgePreviousInstanceUtcL(const TTime& aDay) const;
	TTime NudgeNextInstanceRptLocalL(const TTime& aDay) const;
	TTime NudgePreviousInstanceRptLocalL(const TTime& aDay) const;	
	};

NONSHARABLE_CLASS(TAgnYearlyByDayRpt) : public TAgnRpt
/** A yearly by day repeat. 

In addition to a start date, this class stores the day in the week and the 
week in the month on which the repeat should occur, e.g. Wednesday of the 
third week of November every year. 
@internalComponent
@released
*/
	{
public:
	IMPORT_C TAgnYearlyByDayRpt(CAgnRptDef& aOwningRptDef);
	IMPORT_C TTime FindStartDayL(TDay aDay,TWeekInMonth aWeek,TMonth aMonth,TInt aYear);	
	IMPORT_C void GetStartDayL(TDay& aDay,TWeekInMonth& aWeek,TMonth& aMonth,TInt& aYear) const;
	
	TAgnYearlyByDayRpt(const TAgnYearlyByDayRpt& aRpt, CAgnRptDef& aOwningRptDef);
	TType Type() const;
	
	// from TAgnRpt
	TUint InstanceCountL() const;
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	TInt InvariantL() const;
private:
	TInt GetFirstDayInWeekRptLocal(TWeekInMonth aWeekInMonth,TMonth aMonth,TInt aYear) const;
	void SetDateAccordingToDayRptLocal(TTime& aDate,TDay aDay,TWeekInMonth aWeekInMonth) const;
	TTime FindRptUntilTimeRptLocalL(TUint aCount) const;

	TAgnYearlyByDayRpt(const TAgnYearlyByDayRpt& ); // not implemented
	void operator=(const TAgnYearlyByDayRpt& ); // not implemented
	
	// from TAgnRpt
	TBool IsAlignedRptLocalL(const TTime& aRptLocalDate) const;
	TBool IsAlignedUtcL(const TTime& aUtcDate) const;
	TTime NudgeNextInstanceUtcL(const TTime& aDay) const;
	TTime NudgePreviousInstanceUtcL(const TTime& aDay) const;
	TTime NudgeNextInstanceRptLocalL(TTime aDay) const;
	TTime NudgePreviousInstanceRptLocalL(TTime aDay) const;	
private:
	TWeekInMonth	iWeekInMonth;
	TDay			iDay;
	};

NONSHARABLE_CLASS(CAgnRptDef) : public CBase
/** A repeat definition, including exceptions and sporadic dates, which is owned by an agenda entry. 

The object is set using CAgnEntry::SetRptDefL() and is returned using CAgnSimpleEntry::RptDef().

The repeat definition has a type (daily, weekly etc.) and stores a set of 
repeat details (e.g. until time, interval between repeats). The repeat 
details are stored using an instance of a TAgnRpt - derived class. They are 
set using SetDaily(), SetWeekly() etc. These functions also set the type. 
It may optionally store an exception list, which is a list of the dates on 
which the repeat should not occur.

@internalComponent
@released
*/
	{    
public:

	IMPORT_C static CAgnRptDef* NewL(const CAgnSimpleEntry& aOwningEntry);
	IMPORT_C ~CAgnRptDef();
		
	IMPORT_C void SetRRuleL(const TAgnRpt& aRpt);

	IMPORT_C void SetUntilTime(const TAgnCalendarTime& aUntilTime);
	IMPORT_C void SetInterval(TUint16 aInterval);
	
	IMPORT_C void AddExceptionL(const TAgnCalendarTime& aException);
	IMPORT_C void RemoveAllExceptions();
	IMPORT_C void PruneExceptionsL();
	
	IMPORT_C void AddSporadicDateL(const TAgnCalendarTime& aSporadicDate);  
	IMPORT_C void RemoveAllSporadicDates(); 
	
	// TZ rules handling
	IMPORT_C void SetTimeZoneL();
	IMPORT_C void SetTimeZoneL(const CTzRules& aTimeZone); // does not pass ownership
	IMPORT_C CTzRules* CloneTzRulesL();//Copy the rule and give the ownership
	
	IMPORT_C void ExternalizeL(RWriteStream& aStream, TBool aToBuffer=EFalse);
	IMPORT_C void InternalizeL(RReadStream& aStream, TBool aFromBuffer=EFalse);

	IMPORT_C TAgnRpt::TType Type() const;

	IMPORT_C const TAgnCalendarTime& FirstInstanceL() const;   
	IMPORT_C const TAgnCalendarTime& LastInstanceL() const;
	
	IMPORT_C const TAgnRpt* RRule() const;
	
	IMPORT_C TUint InstanceCountL() const; 
	
	IMPORT_C TBool NudgeNextInstanceL(const TTime& aDay,TTime& aNext,TBool aCheckUnexcepted) const;
	IMPORT_C TBool NudgePreviousUnexceptedInstanceL(const TTime& aDay,TTime& aPrev) const;
	IMPORT_C TBool IsAnUnexceptedInstanceL(const TTime& aDate) const; // means not just Rpt Instances
	IMPORT_C TBool IsAnInstanceL(const TTime& aDate) const; // means not just Rpt Instances

	IMPORT_C TBool NudgeNextInstanceUtcL(const TTime& aDayUtc, TTime& aNextUtc) const;
	IMPORT_C TBool NudgePreviousInstanceUtcL(const TTime& aDayUtc, TTime& aPrevUtc) const;

	IMPORT_C TBool FindException(const TAgnCalendarTime& aException) const;
	IMPORT_C const RArray<TAgnCalendarTime>* Exceptions() const;
	IMPORT_C const RArray<TAgnCalendarTime>* SporadicDateList() const;
	
	IMPORT_C TTime ConvertFromUtcToRepeatLocalL(const TTime& aUtcDate) const;
	IMPORT_C TTime ConvertFromRepeatLocalToUtcL(const TTime& aRptLocalDate) const;
	
	IMPORT_C void CopyL(const CAgnRptDef& aRpt);
	
	TBool operator==(const CAgnRptDef& aRpt) const;
	
	void RemoveSporadicDate(const TAgnCalendarTime& aException);
	
	void StartTimeChanged();
	void ClearRRule();
	
	TBool HasSporadicDates() const;
	TInt InvariantL() const;	// self testing
	
	MAgnCalendarTimeMode::TTimeMode TimeMode() const;
	const TAgnCalendarTime& StartTime() const;
	TBool HasRepeatRule() const;
	TBool IsARepeatRuleDateInstanceL(const TTime& aDate) const;  // local time
	
    void InternalizeRepeatRuleL(RReadStream& aStream);
    void InternalizeExceptionsL(RReadStream& aStream);
    void InternalizeSporadicDatesL(RReadStream& aStream);
    void InternalizeTimeZoneL(RReadStream& aStream, TBool aFromBuffer=EFalse);

    IMPORT_C CAgnTzRules* AgnTzRules() const;
private:
	
	CAgnRptDef(const CAgnSimpleEntry& aOwningEntry);
	CAgnRptDef(); // not implemented

	void CopyTimeArrayL(const RArray<TAgnCalendarTime>* aSource, RArray<TAgnCalendarTime>*& aDestination);
	void EnsureTimeArrayExistsL(RArray<TAgnCalendarTime>*& aTimeArray);
	void ClearTimeArray(RArray<TAgnCalendarTime>*& aTimeArray);
	
	void CreateRptObjectL(const TAgnRpt& aRpt);
	void CreateRptObjectL(TAgnRpt::TType aType);

	void ResetTimeZone();
	CAgnTlsProxy* TimeZoneAccessor();
	void TimeZoneChangedL();
	
	const CTzRules* TzRules() const;//Does not copy the Tz rules
	
	TInt FindSporadicDate(const TAgnCalendarTime& aException) const;   
	
	TBool NudgeInstanceForwardsUtcL(const TTime& aDate, TTime& aNext, TBool aCheckExcepted) const; 
	TBool NudgeInstanceBackwardsUtcL(const TTime& aDate, TTime& aNext, TBool aCheckExcepted) const;

	TBool NudgeNextRepeatInstanceUtcL(const TTime& aDate, TTime& aNext, TBool aCheckExcepted) const;
	TBool NudgeNextUnexceptedRepeatInstanceUtcL(const TTime& aDate, TTime& aNext) const;
	TBool NudgeNextSporadicInstanceUtcL(const TTime& aDate, TTime& aNext, TBool aCheckExcepted) const;
	TBool NudgeNextRepeatInstanceToNextValidInstanceUtcL(const TTime& aUtcDate, TTime& aUtcNext) const;
	
	TBool NudgePreviousRepeatInstanceUtcL(const TTime& aDay, TTime& aPrev, TBool aCheckExcepted) const;
	TBool NudgePreviousUnexceptedRepeatInstanceUtcL(const TTime& aDay, TTime& aPrev) const;
	TBool NudgePreviousSporadicInstanceUtcL(const TTime& aDay, TTime& aPrev, TBool aCheckExcepted) const;
	TBool NudgePreviousRepeatInstanceToPreviousValidInstanceUtcL(const TTime& aUtcDate, TTime& aUtcPrev) const;	  
		  
	TBool IsASporadicDateInstanceL(const TTime& aDate) const;  // local time 
	
private:
	TAgnRpt* 	iRRule;
	
	RArray<TAgnCalendarTime>* iExceptions;
	RArray<TAgnCalendarTime>* iSporadicDates;
	
	CAgnTzRules* iTimeZone; // the time zone where the repeat rule is defined, not owned
	const CAgnSimpleEntry&	iOwningEntry;
	};

#endif