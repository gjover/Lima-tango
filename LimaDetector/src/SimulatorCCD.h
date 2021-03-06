//=============================================================================
//
// file :        SimulatorCCD.h
//
// description : Include for the SimulatorCCD class.
//
// project :	
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
// copyleft :    Synchrotron SOLEIL 
//               L'Orme des merisiers - Saint Aubin
//         BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//=============================================================================
//
//          This file is generated by POGO
//    (Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifndef _SIMULATORCCD_H
#define _SIMULATORCCD_H


//using namespace Tango;

/**
 * @author    $Author:  $
 * @version    $Revision:  $
 */

 //    Add your own constant definitions here.
 //-----------------------------------------------

#ifdef WIN32
#include <tango.h>
#include "Factory.h"
#endif

#include "HwInterface.h"
#include "CtControl.h"
#include "CtAcquisition.h"
#include "CtImage.h"

#include <SimulatorInterface.h>

#ifndef WIN32
#include <tango.h>
#include "Factory.h"
#endif



using namespace lima;
using namespace std;

namespace SimulatorCCD_ns
{

/**
 * Class Description:
 * 
 */

/*
 *	Device States Description:
*  Tango::INIT :
*  Tango::STANDBY :
*  Tango::FAULT :
*  Tango::RUNNING :
 */


class SimulatorCCD: public Tango::Device_4Impl
{
public :
    //    Add your own data members here
    //-----------------------------------------


    //    Here is the Start of the automatic code generation part
    //-------------------------------------------------------------    
/**
 *    @name attributes
 *    Attribute member data.
 */
//@{
		Tango::DevDouble	*attr_exposureTime_read;
		Tango::DevDouble	attr_exposureTime_write;
//@}

/**
 * @name Device properties
 * Device properties member data.
 */
//@{
//@}

/**
 *    @name Device properties
 *    Device property member data.
 */
//@{
//@}

/**@name Constructors
 * Miscellaneous constructors */
//@{
/**
 * Constructs a newly allocated Command object.
 *
 *    @param cl    Class.
 *    @param s     Device Name
 */
    SimulatorCCD(Tango::DeviceClass *cl,string &s);
/**
 * Constructs a newly allocated Command object.
 *
 *    @param cl    Class.
 *    @param s     Device Name
 */
    SimulatorCCD(Tango::DeviceClass *cl,const char *s);
/**
 * Constructs a newly allocated Command object.
 *
 *    @param cl    Class.
 *    @param s     Device name
 *    @param d    Device description.
 */
    SimulatorCCD(Tango::DeviceClass *cl,const char *s,const char *d);
//@}

/**@name Destructor
 * Only one destructor is defined for this class */
//@{
/**
 * The object destructor.
 */    
    ~SimulatorCCD() {delete_device();};
/**
 *    will be called at device destruction or at init command.
 */
    void delete_device();
//@}

    
/**@name Miscellaneous methods */
//@{
/**
 *    Initialize the device
 */
    virtual void init_device();
/**
 *    Always executed method before execution command method.
 */
    virtual void always_executed_hook();

//@}

/**
 * @name SimulatorCCD methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for exposureTime acquisition result.
 */
	virtual void read_exposureTime(Tango::Attribute &attr);
/**
 *	Write exposureTime attribute values to hardware.
 */
	virtual void write_exposureTime(Tango::WAttribute &attr);
/**
 *	Read/Write allowed for exposureTime attribute.
 */
	virtual bool is_exposureTime_allowed(Tango::AttReqType type);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

    //    Here is the end of the automatic code generation part
    //-------------------------------------------------------------    
	// return true if the device is correctly initialized in init_device
	bool is_device_initialized(){return m_is_device_initialized;};


protected :    
    //    Add your own data members here
    //-----------------------------------------
    
    bool                 m_is_device_initialized ;
    stringstream        m_status_message;
    
    //LIMA objects
    Simulator::Interface*     m_hw;
    CtControl*            m_ct;    
};

}    // namespace_ns

#endif    // _SIMULATORCCD_H
