static const char *RcsId = "$Id $";
//+=============================================================================
//
// file :         PilatusPixelDetectorStateMachine.cpp
//
// description :  C++ source for the PilatusPixelDetector and its alowed 
//                methods for commands and attributes
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL: $
//
// CVS only:
// $Source:  $
// $Log:  $
//
// copyleft :     European Synchrotron Radiation Facility
//                BP 220, Grenoble 38043
//                FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================

#include <PilatusPixelDetector.h>
#include <PilatusPixelDetectorClass.h>

#include <tango.h>

/*====================================================================
 *	This file contains the methods to allow commands and attributes
 * read or write execution.
 *
 * If you wand to add your own code, add it between 
 * the "End/Re-Start of Generated Code" comments.
 *
 * If you want, you can also add your own methods.
 *====================================================================
 */

namespace PilatusPixelDetector_ns
{

//=================================================
//		Attributes Allowed Methods
//=================================================

//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::is_threshold_allowed
// 
// description : 	Read/Write allowed for threshold attribute.
//
//-----------------------------------------------------------------------------
bool PilatusPixelDetector::is_threshold_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::is_gain_allowed
// 
// description : 	Read/Write allowed for gain attribute.
//
//-----------------------------------------------------------------------------
bool PilatusPixelDetector::is_gain_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::is_imagePath_allowed
// 
// description : 	Read/Write allowed for imagePath attribute.
//
//-----------------------------------------------------------------------------
bool PilatusPixelDetector::is_imagePath_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::is_fileName_allowed
// 
// description : 	Read/Write allowed for fileName attribute.
//
//-----------------------------------------------------------------------------
bool PilatusPixelDetector::is_fileName_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::is_latency_allowed
// 
// description : 	Read/Write allowed for latency attribute.
//
//-----------------------------------------------------------------------------
bool PilatusPixelDetector::is_latency_allowed(Tango::AttReqType type)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::RUNNING && type==Tango::READ_REQ )
		{
           return true;
		}
		
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}

//=================================================
//		Commands Allowed Methods
//=================================================

//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::is_SetThresholdAndGain_allowed
// 
// description : 	Execution allowed for SetThresholdAndGain command.
//
//-----------------------------------------------------------------------------
bool PilatusPixelDetector::is_SetThresholdAndGain_allowed(const CORBA::Any &any)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::is_SetMxSettings_allowed
// 
// description : 	Execution allowed for SetMxSettings command.
//
//-----------------------------------------------------------------------------
bool PilatusPixelDetector::is_SetMxSettings_allowed(const CORBA::Any &any)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::is_SendAnyCommand_allowed
// 
// description : 	Execution allowed for SendAnyCommand command.
//
//-----------------------------------------------------------------------------
bool PilatusPixelDetector::is_SendAnyCommand_allowed(const CORBA::Any &any)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}
//+----------------------------------------------------------------------------
//
// method : 		PilatusPixelDetector::is_SetEnergy_allowed
// 
// description : 	Execution allowed for SetEnergy command.
//
//-----------------------------------------------------------------------------
bool PilatusPixelDetector::is_SetEnergy_allowed(const CORBA::Any &any)
{
	if (get_state() == Tango::INIT	||
		get_state() == Tango::FAULT	||
		get_state() == Tango::RUNNING)
	{
		//	End of Generated Code
		if ( get_state()==Tango::FAULT && is_device_initialized() )
		{
           return true;
		}
		//	Re-Start of Generated Code
		return false;
	}
	return true;
}

}	// namespace PilatusPixelDetector_ns
