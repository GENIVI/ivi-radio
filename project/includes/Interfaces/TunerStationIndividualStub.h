////////////////////////////////////////////////////////////
//  TunerStationIndividualStub.h
//  Implementation of the Class TunerStationIndividualStub
//  Created on:      17-Jul-2013 10:25:51
//  Original author: qx92858
///////////////////////////////////////////////////////////

#if !defined(EA_A94F8AD3_5E3B_4e39_B8A5_BFE4E91089B1__INCLUDED_)
#define EA_A94F8AD3_5E3B_4e39_B8A5_BFE4E91089B1__INCLUDED_

#include "IVIRadio/Station/StationStubDefault.h"
#include "../TerminalIO.h"
#include "../Middleware.h"
#include <pthread.h>


class TunerStationIndividualStub;

/**
 * \struct arg_ThreadDataStartTune
 */
struct arg_ThreadDataStartTune {
	TunerStationIndividualStub 						*pThis;
	IVIRadio::Types::Types::StationSelector 		station;
	IVIRadio::Station::StationTypes::SelectionMode  selectionMode;
	uint32_t  										handle_out;
	uint32_t  										handle;
};

/**
 * \struct arg_ThreadDataStartSeek
 */
struct arg_ThreadDataStartSeek {
	TunerStationIndividualStub 						*pThis;
	IVIRadio::Types::Types::DeviceType 				device;
	IVIRadio::Station::StationTypes::SeekMode 		seekMode;
	uint32_t  										handle;
};

/*
 * \class TunerStationIndividualStub
 * \brief the class TunerStationIndividualStub overrides the methods from TunerStationStubDefault;\n
 * 		  practically all the calls from the client for station managements are ending here; this is the first part
 * 		  where individual logic (independent from Common API logic) needs to be implemented. \n
 * 		  this class starts threads to simulate functionality in the middleware as well as sends broadcast containing the requested information\n
 *		  class inherits IVIRadio::Station::StationStubDefault\n
 *
 * \author (last to touch it)  Bernhard Singer
 *
 * \version 2.0
 *
 * \date 2013/06/16 14:16:20
 *
 * Contact: bernhard.singer@partner.bmw.de
 *
  * Copyright
 * Copyright (C) 2013, GENIVI Alliance, Inc.
 * Copyright (C) 2013, BMW AG
 *
 * Contributions are licensed to the GENIVI Alliance under one or more
 * Contribution License Agreements or MPL 2.0 .
 *
 * (C) Copyright
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with
 * this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#define LOG( a, b ) m_TerminalIO->Log( a, b )

class TunerStationIndividualStub : public IVIRadio::Station::StationStubDefault
{

public:
	TunerStationIndividualStub();
	virtual ~TunerStationIndividualStub();

	/**
	* \brief Starts tuning a frequency or selecting a station.
	* \param [in] station an StationSelector The requested frequency/station
	* \param [in] selectionMode The required selection mode
	* \param [in] handle an UIn32  an optional handle for identifying the request
	* \param [out] handle_out an UInt32  the handle of the corresponding request
	* \param [out] feedback a Feedback the result of the request
	*/
	virtual void startTune(
			IVIRadio::Types::Types::StationSelector station,
	       IVIRadio::Station::StationTypes::SelectionMode selectionMode,
	       uint32_t handle,
	       uint32_t& handle_out,
	       IVIRadio::Types::Types::Feedback& feedback
	   );

	/**
	* \brief Aborts a running tune or station selection process
	* \param [in] device an DeviceType Device on which tune process shall be aborted.
	* \param [in] handle an UIn32  an optional handle for identifying the request
	* \param [out] handle_out an UInt32  the handle of the corresponding request
	* \param [out] feedback a Feedback the result of the request
	*/
   virtual void abortTune(
		   IVIRadio::Types::Types::DeviceType device,
	   uint32_t handle,
	   uint32_t& handle_out,
	   IVIRadio::Types::Types::Feedback& feedback
   );

	/**
	* \brief Starts/Stops a seek process
	* \param [in] device an DeviceType Device on which search shall run
	* \param [in] seekMode The requested seek mode and genre/PTY mask
	* \param [in] genre an UIn8 Consider only stations of this genre
	* \param [in] flags Additional flags to be considered (device and project dependent)
	* \param [in] handle An optional handle for identifying the request
	* \param [out] handle_out an UInt32  the handle of the corresponding request
	* \param [out] feedback a Feedback the result of the request
	*/
   virtual void seek(
		   IVIRadio::Types::Types::DeviceType device,
	   IVIRadio::Station::StationTypes::SeekMode seekMode,
	   uint8_t genre,
	   IVIRadio::Types::Types::UInt32s flags,
	   uint32_t handle,
	   uint32_t& handle_out,
	   IVIRadio::Types::Types::Feedback& feedback
   );

	/**
	* \brief Make station permanent (tuning information will not be removed from middleware even if station is not receivable any more)
	* \param [in] station an The requested frequency/station
	* \param [in] permanent an boolean an Enable / disable the permanent flag
	* \param [in] handle An optional handle for identifying the request
	* \param [out] handle_out an UInt32  the handle of the corresponding request
	* \param [out] feedback a Feedback the result of the request
	*/
   virtual void makePermanent(
		   IVIRadio::Types::Types::StationSelector station,
	   bool permanent,
	   uint32_t handle,
	   uint32_t& handle_out,
	   IVIRadio::Types::Types::Feedback& feedback
   );

	/**
	* \brief Controls the update of currentStation or stationList information. It is possible to enable continuous updates or to request one single update e.g. necessary for synchronization after startup.
	* \param [in] updateElement Update element: seek data, current station, station list
	* \param [in] updateType an Update type: One single update or continuously
	* \param [in] sourceType The source type of interest (e. g. UNDEF, FM, AMFM)
	* \param [in] stationType The station type of interest (e. g. RECEIVABLE, AUTOSTORE, PERMANENT)
	* \param [in] handle An optional handle for identifying the request
	* \param [out] handle_out an UInt32  the handle of the corresponding request
	* \param [out] feedback a Feedback the result of the request
	*/
   virtual void controlUpdate(
	  IVIRadio::Station::StationTypes::UpdateElement updateElement,
	  IVIRadio::Types::Types::UpdateType updateType,
	  uint32_t sourceType,
	  uint32_t stationType,
	  uint32_t handle,
	  uint32_t& handle_out,
	  IVIRadio::Types::Types::Feedback& feedback
   );

	/**
	* \brief method sets the middleware instance to a member
	* \param [in] Pointer to the Middleware instance is needed to invoke simulations in the middleware class
	*/
   void setMiddleware(Middleware *middleware){
	   m_MW = middleware;
	   pthread_create(&m_thread_sendCurrStation, NULL, InternalThreadEntryFunc_SendCurrentStation, this);
   }

   static void * InternalThreadEntryFunc_JobSeek(void * _arg) {
	   ((arg_ThreadDataStartSeek *)_arg)->pThis->InternalThreadEntry_JobSeek( _arg ); return NULL;
   }

   static void * InternalThreadEntryFunc_SeekEvent(void * _arg) {
	   ((arg_ThreadDataStartSeek *)_arg)->pThis->InternalThreadEntry_SeekEvent( _arg ); return NULL;
   }

   static void * InternalThreadEntryFunc_JobStartTune( void * threadData ) {
	   ((arg_ThreadDataStartTune*)threadData)->pThis->InternalThreadEntry_JobStartTune( threadData ); return NULL;
   }

   static void * InternalThreadEntryFunc_SendCurrentStation(void * This) {
	   ((TunerStationIndividualStub *)This)->InternalThreadEntry_SendCurrentStation(); return NULL;
   }

   void InternalThreadEntry_SendCurrentStation	(					);
   void InternalThreadEntry_JobSeek  			( void * _args 		);
   void InternalThreadEntry_SeekEvent			( void * _args 		);
   void InternalThreadEntry_JobStartTune		( void * threadData );

private:

   	TerminalIO 	*m_TerminalIO;

	/*
	 * \brief m_MW is a pointer to the instance of middleware which is currently running
	 */
	Middleware 	*m_MW;
	pthread_t m_thread_JobSeek ;
	pthread_t m_thread_SeekData;
	pthread_t m_thread_startTune;
	pthread_t m_thread_sendCurrStation;

	bool m_thread_JobSeek_completed;
};
#endif // !defined(EA_A94F8AD3_5E3B_4e39_B8A5_BFE4E91089B1__INCLUDED_)
