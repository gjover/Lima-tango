static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         XpadPixelDetector.cpp
//
// description :  C++ source for the XpadPixelDetector and its commands. 
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                XpadPixelDetector are implemented in this file.
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
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
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================



//===================================================================
//
//	The following table gives the correspondence
//	between commands and method name.
//
//  Command name    |  Method name
//	----------------------------------------
//  State           |  dev_state()
//  Status          |  dev_status()
//  LoadFlatConfig  |  load_flat_config()
//  LoadAllConfigG  |  load_all_config_g()
//  SaveConfigL     |  save_config_l()
//  SaveConfigG     |  save_config_g()
//  LoadConfig      |  load_config()
//  Reset           |  reset()
//  GetModConfig    |  get_mod_config()
//
//===================================================================



#include <XpadPixelDetector.h>
#include <XpadPixelDetectorClass.h>
#include <tango.h>
#include <PogoHelper.h>

namespace XpadPixelDetector_ns
{

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::XpadPixelDetector(string &s)
// 
// description : 	constructor for simulated XpadPixelDetector
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name 
//
//-----------------------------------------------------------------------------
XpadPixelDetector::XpadPixelDetector(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
	init_device();
}

XpadPixelDetector::XpadPixelDetector(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
	init_device();
}

XpadPixelDetector::XpadPixelDetector(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
	init_device();
}
//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::delete_device()
// 
// description : 	will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::delete_device()
{
	//	Delete device allocated objects
	INFO_STREAM << "XpadPixelDetector::delete_device() " << device_name << endl;

	DELETE_SCALAR_ATTRIBUTE(attr_deadTime_read);
	DELETE_SCALAR_ATTRIBUTE(attr_init_read);
	DELETE_SCALAR_ATTRIBUTE(attr_shutter_read);
	DELETE_SCALAR_ATTRIBUTE(attr_ovf_read);
	DELETE_SCALAR_ATTRIBUTE(attr_mode_read);
	DELETE_SCALAR_ATTRIBUTE(attr_n_read);
	DELETE_SCALAR_ATTRIBUTE(attr_p_read);
	DELETE_SCALAR_ATTRIBUTE(attr_gp1_read);
	DELETE_SCALAR_ATTRIBUTE(attr_gp2_read);
	DELETE_SCALAR_ATTRIBUTE(attr_gp3_read);
	DELETE_SCALAR_ATTRIBUTE(attr_gp4_read);

	/*DELETE_IMAGE_ATTRIBUTE(attr_dacl_read);
	DELETE_IMAGE_ATTRIBUTE(attr_ithl_read);
	DELETE_IMAGE_ATTRIBUTE(my_attr_dacl_write);
	DELETE_IMAGE_ATTRIBUTE(my_attr_ithl_write);*/
	
	//!!!! ONLY LimaDetector device can do this !!!!
	//if(m_ct!=0)
	//{
	//	ControlFactory::instance().reset("XpadPixelDetector");
	//	m_ct = 0;
	//}
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::init_device()
// 
// description : 	will be called at device initialization.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::init_device()
{
	INFO_STREAM << "XpadPixelDetector::XpadPixelDetector() create device " << device_name << endl;

	// Initialise variables to default values
	//--------------------------------------------
	get_device_property();

	CREATE_SCALAR_ATTRIBUTE(attr_deadTime_read);
	CREATE_SCALAR_ATTRIBUTE(attr_init_read);
	CREATE_SCALAR_ATTRIBUTE(attr_shutter_read);
	CREATE_SCALAR_ATTRIBUTE(attr_ovf_read);
	CREATE_SCALAR_ATTRIBUTE(attr_mode_read);
	CREATE_SCALAR_ATTRIBUTE(attr_n_read);
	CREATE_SCALAR_ATTRIBUTE(attr_p_read);
	CREATE_SCALAR_ATTRIBUTE(attr_gp1_read);
	CREATE_SCALAR_ATTRIBUTE(attr_gp2_read);
	CREATE_SCALAR_ATTRIBUTE(attr_gp3_read);
	CREATE_SCALAR_ATTRIBUTE(attr_gp4_read);

	m_is_device_initialized = true;
	set_state(Tango::INIT);		
	m_status_message.str("");

	attr_deadTime_write = 0;
	attr_init_write = 0;
	attr_shutter_write = 0;
	attr_ovf_write = 0;
	attr_mode_write = 0;
	attr_n_write = 0;
	attr_p_write = 0;
	attr_gp1_write = 0;
	attr_gp2_write = 0;
	attr_gp3_write = 0;
	attr_gp4_write = 0;

	try
	{
		//- get the main object used to pilot the lima framework
		//in fact LimaDetector is create the singleton control objet
		//so this call, will only return existing object, no need to give it the ip !!
		m_ct = ControlFactory::instance().get_control("XpadPixelDetector");		
		if(m_ct==0)
		{
			INFO_STREAM<<"Initialization Failed : Unable to get the lima control object !"<<endl;
			m_status_message <<"Initialization Failed : Unable to get the lima control object !"<< endl;
			m_is_device_initialized = false;
			set_state(Tango::INIT);		
			return;			
		}
		
		//- get interface to specific detector
		m_interface = dynamic_cast<Xpad::Interface*>(m_ct->hwInterface());
		if(m_interface==0)
		{
			INFO_STREAM<<"Initialization Failed : Unable to get the interface of camera plugin !"<<endl;
			m_status_message <<"Initialization Failed : Unable to get the interface of camera plugin !"<< endl;
			m_is_device_initialized = false;
			set_state(Tango::INIT);		
			return;			
		}

        //- get camera to specific detector
		m_camera = &(m_interface->getCamera());
		if(m_camera == 0)
		{
			INFO_STREAM<<"Initialization Failed : Unable to get the camera of plugin !"<<endl;
			m_status_message <<"Initialization Failed : Unable to get the camera object !"<< endl;
			m_is_device_initialized = false;
			set_state(Tango::INIT);		
			return;			
		}
	}
	catch(Exception& e)
	{
		INFO_STREAM<<"Initialization Failed : "<<e.getErrMsg()<<endl;
		m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
		m_is_device_initialized = false;
		set_state(Tango::INIT);		
		return;	
	}

	//- Xpad specific stuff:
	try
	{
		INFO_STREAM << "acquisitionType = " << acquisitionType <<endl;
        m_camera->setAcquisitionType(acquisitionType);
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg()<<endl;
		m_status_message <<e.getErrMsg( )<< endl;
		m_is_device_initialized = false;
		set_state(Tango::INIT);		
		return;		
	}

	set_state(Tango::STANDBY);	
	this->dev_state();		
}


//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::get_device_property()
// 
// description : 	Read the device properties from database.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::get_device_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read device properties from database.(Automatic code generation)
	//------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("AcquisitionType"));
	dev_prop.push_back(Tango::DbDatum("AllConfigG"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	XpadPixelDetectorClass	*ds_class =
		(static_cast<XpadPixelDetectorClass *>(get_device_class()));
	int	i = -1;

	//	Try to initialize AcquisitionType from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  acquisitionType;
	else {
		//	Try to initialize AcquisitionType from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  acquisitionType;
	}
	//	And try to extract AcquisitionType value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  acquisitionType;

	//	Try to initialize AllConfigG from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  allConfigG;
	else {
		//	Try to initialize AllConfigG from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  allConfigG;
	}
	//	And try to extract AllConfigG value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  allConfigG;



	//	End of Automatic code generation
	//------------------------------------------------------------------

}
//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::always_executed_hook()
// 
// description : 	method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::always_executed_hook()
{
    try
    {
    	//- get the singleton control objet used to pilot the lima framework
        m_ct = ControlFactory::instance().get_control("XpadPixelDetector");

        //- get interface to specific detector
        if(m_ct != 0)
        {
            m_interface = dynamic_cast<Xpad::Interface*>(m_ct->hwInterface());
            m_camera = &(m_interface->getCamera());
        }
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        Tango::Except::throw_exception(
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("XpadPixelDetector::always_executed_hook"));
    }
}
//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_attr_hardware
// 
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_attr_hardware(vector<long> &attr_list)
{
	DEBUG_STREAM << "XpadPixelDetector::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
	//	Add your own code here
}
//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_gp2
// 
// description : 	Extract real attribute values for gp2 acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_gp2(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_gp2(Tango::Attribute &attr) entering... "<< endl;

	*attr_gp2_read = attr_gp2_write;
	attr.set_value(attr_gp2_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_gp2
// 
// description : 	Write gp2 attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_gp2(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_gp2(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_gp2_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_gp3
// 
// description : 	Extract real attribute values for gp3 acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_gp3(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_gp3(Tango::Attribute &attr) entering... "<< endl;

	*attr_gp3_read = attr_gp3_write;
	attr.set_value(attr_gp3_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_gp3
// 
// description : 	Write gp3 attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_gp3(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_gp3(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_gp3_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_gp4
// 
// description : 	Extract real attribute values for gp4 acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_gp4(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_gp4(Tango::Attribute &attr) entering... "<< endl;

	*attr_gp4_read = attr_gp4_write;
	attr.set_value(attr_gp4_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_gp4
// 
// description : 	Write gp4 attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_gp4(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_gp4(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_gp4_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_deadTime
// 
// description : 	Extract real attribute values for deadTime acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_deadTime(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_deadTime(Tango::Attribute &attr) entering... "<< endl;

	*attr_deadTime_read = attr_deadTime_write;
	attr.set_value(attr_deadTime_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_deadTime
// 
// description : 	Write deadTime attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_deadTime(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_deadTime(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_deadTime_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_init
// 
// description : 	Extract real attribute values for init acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_init(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_init(Tango::Attribute &attr) entering... "<< endl;

	*attr_init_read = attr_init_write;
	attr.set_value(attr_init_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_init
// 
// description : 	Write init attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_init(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_init(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_init_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_shutter
// 
// description : 	Extract real attribute values for shutter acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_shutter(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_shutter(Tango::Attribute &attr) entering... "<< endl;

	*attr_shutter_read = attr_shutter_write;
	attr.set_value(attr_shutter_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_shutter
// 
// description : 	Write shutter attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_shutter(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_shutter(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_shutter_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_ovf
// 
// description : 	Extract real attribute values for ovf acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_ovf(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_ovf(Tango::Attribute &attr) entering... "<< endl;

	*attr_ovf_read = attr_ovf_write;
	attr.set_value(attr_ovf_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_ovf
// 
// description : 	Write ovf attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_ovf(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_ovf(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_ovf_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_mode
// 
// description : 	Extract real attribute values for mode acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_mode(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_mode(Tango::Attribute &attr) entering... "<< endl;

	*attr_mode_read = attr_mode_write;
	attr.set_value(attr_mode_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_mode
// 
// description : 	Write mode attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_mode(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_mode(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_mode_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_n
// 
// description : 	Extract real attribute values for n acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_n(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_n(Tango::Attribute &attr) entering... "<< endl;

	*attr_n_read = attr_n_write;
	attr.set_value(attr_n_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_n
// 
// description : 	Write n attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_n(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_n(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_n_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_p
// 
// description : 	Extract real attribute values for p acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_p(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_p(Tango::Attribute &attr) entering... "<< endl;

	*attr_p_read = attr_p_write;
	attr.set_value(attr_p_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_p
// 
// description : 	Write p attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_p(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_p(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_p_write);
	set_all_f_parameters();
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::read_gp1
// 
// description : 	Extract real attribute values for gp1 acquisition result.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::read_gp1(Tango::Attribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::read_gp1(Tango::Attribute &attr) entering... "<< endl;

	*attr_gp1_read = attr_gp1_write;
	attr.set_value(attr_gp1_read);
}

//+----------------------------------------------------------------------------
//
// method : 		XpadPixelDetector::write_gp1
// 
// description : 	Write gp1 attribute values to hardware.
//
//-----------------------------------------------------------------------------
void XpadPixelDetector::write_gp1(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "XpadPixelDetector::write_gp1(Tango::WAttribute &attr) entering... "<< endl;

	attr.get_write_value(attr_gp1_write);
	set_all_f_parameters();
}

//+------------------------------------------------------------------
/**
 *	method:	XpadPixelDetector::load_flat_config
 *
 *	description:	method to execute "LoadFlatConfig"
 *	Load a Flat config, for each pixel
 *
 * @param	argin	Flat value to be loaded
 *
 */
//+------------------------------------------------------------------
void XpadPixelDetector::load_flat_config(Tango::DevULong argin)
{
	DEBUG_STREAM << "XpadPixelDetector::load_flat_config(): entering... !" << endl;

	//	Add your own code to control device here

	try
	{
		m_camera->loadFlatConfig(argin);
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		Tango::Except::throw_exception(
					static_cast<const char*> ("TANGO_DEVICE_ERROR"),
					static_cast<const char*> (e.getErrMsg().c_str()),
					static_cast<const char*> ("XpadPixelDetector::load_flat_config"));
	}
}

//+------------------------------------------------------------------
/**
 *	method:	XpadPixelDetector::set_all_f_parameters
 *
 */
//+------------------------------------------------------------------
void XpadPixelDetector::set_all_f_parameters()
{
	DEBUG_STREAM << "XpadPixelDetector::set_all_f_parameters(): entering... !" << endl;

	try
	{
		m_camera->setFParameters(	attr_deadTime_write,attr_init_write,
								    attr_shutter_write,attr_ovf_write,attr_mode_write,
								    attr_n_write,attr_p_write,
								    attr_gp1_write,attr_gp2_write,attr_gp3_write,attr_gp4_write);
	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		Tango::Except::throw_exception(
					static_cast<const char*> ("TANGO_DEVICE_ERROR"),
					static_cast<const char*> (e.getErrMsg().c_str()),
					static_cast<const char*> ("XpadPixelDetector::set_all_f_parameters"));
	}
}

//+------------------------------------------------------------------
/**
 *	method:	XpadPixelDetector::dev_state
 *
 *	description:	method to execute "State"
 *	This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return	State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState XpadPixelDetector::dev_state()
{
	Tango::DevState	argout = DeviceImpl::dev_state();
	DEBUG_STREAM << "XpadPixelDetector::dev_state(): entering... !" << endl;

	//	Add your own code to control device here

	stringstream    DeviceStatus;
	DeviceStatus 	<< "";
	Tango::DevState DeviceState	= Tango::STANDBY;
	if(!m_is_device_initialized )
	{
		DeviceState			= Tango::INIT;
		DeviceStatus		<< m_status_message.str();		
	}
	else if (m_ct==0)
	{
		DeviceState			= Tango::INIT;
		DeviceStatus		<<"Initialization Failed : Unable to get the lima control object !\n\n";				
	}
	else
	{
		CtControl::Status status;
		m_ct->getStatus(status);
		if (status.AcquisitionStatus == lima::AcqReady)
		{
			HwInterface::StatusType state;
			m_interface->getStatus(state);
			if(state.acq == AcqRunning && state.det == DetExposure)
			{
				DeviceState=Tango::RUNNING;
				DeviceStatus<<"Acquisition is Running ...\n"<<endl;
			}
			else if(state.acq == AcqFault && state.det == DetFault)
			{
				DeviceState=Tango::INIT;//INIT
				DeviceStatus<<"Acquisition is in Init\n"<<endl;
			}
			else if(state.acq == AcqFault && state.det == DetIdle)
			{
				DeviceState=Tango::FAULT;//FAULT
				DeviceStatus<<"Acquisition is in Fault\n"<<endl;
			}
			else
			{
				DeviceState=Tango::STANDBY;
				DeviceStatus<<"Waiting for Request ...\n"<<endl;
			}
		}
		else if(status.AcquisitionStatus == lima::AcqRunning)
		{
			DeviceState=Tango::RUNNING;
			DeviceStatus<<"Acquisition is Running ...\n"<<endl;
		}
		else
		{
			HwInterface::StatusType state;
			m_interface->getStatus(state);
			if(state.acq == AcqFault && state.det == DetFault)
			{
				DeviceState=Tango::INIT;//INIT
				DeviceStatus<<"Acquisition is in Init\n"<<endl;
			}
			else
			{
			  DeviceState=Tango::FAULT;//FAULT
			  DeviceStatus<<"Acquisition is in Fault\n"<<endl;
			}
		}
	}
	
	set_state(DeviceState);
	set_status(DeviceStatus.str());
	
	argout = DeviceState;
	return argout;
}


//+------------------------------------------------------------------
/**
 *	method:	XpadPixelDetector::save_config_l
 *
 *	description:	method to execute "SaveConfigL"
 *	The�function�loads/stores�a�line�of�calibration�data�at�the�line�index�curRow�in�the�
 *	memory�buffer�identified�by�calibId�of�the�chip�identified�by�chipId�of�the�modules�
 *	selected�by� modNum. �The�80�calibration�data�values�that�are�stored�starting�at�
 *	address�value.�Calibration�data�(80�words�16�bits)�for�one�row�of�one�chip�(9�bits)
 *
 * @param	argin	modNum(1..8), calibId(0..6), chipId(0..7), curRow (0..119), values (80 values)
 *
 */
//+------------------------------------------------------------------
void XpadPixelDetector::save_config_l(const Tango::DevVarULongArray *argin)
{
	DEBUG_STREAM << "XpadPixelDetector::save_config_l(): entering... !" << endl;

	//	Add your own code to control device here

    //- TODO: parameter checking ? or done in xpix?
    //- argin length doit etre de taille 4 + 80 = 84
    try
    {
        m_camera->saveConfigL((*argin)[0],(*argin)[1],(*argin)[2],(*argin)[3],(unsigned long*) &((*argin)[4]));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("XpadPixelDetector::save_config_l"));
    }
}

//+------------------------------------------------------------------
/**
 *	method:	XpadPixelDetector::save_config_g
 *
 *	description:	method to execute "SaveConfigG"
 *	The � function � loads/store � the � global � register �reg� (see � paragraph � 3.4) � in � the�
 *	memory�buffer�identified�by�calibId.
 *
 * @param	argin	modNum(1..8), calibId(0..6), reg, values (7 values)
 *
 */
//+------------------------------------------------------------------
void XpadPixelDetector::save_config_g(const Tango::DevVarULongArray *argin)
{
	DEBUG_STREAM << "XpadPixelDetector::save_config_g(): entering... !" << endl;

	//	Add your own code to control device here

    //- TODO: parameter checking ? or done in xpix?
    //- argin length doit etre de taille: 3 + 11 = 14
    try
    {
        m_camera->saveConfigG((*argin)[0],(*argin)[1],(*argin)[2],(unsigned long*) &((*argin)[3]));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("XpadPixelDetector::save_config_g"));
    }
}

//+------------------------------------------------------------------
/**
 *	method:	XpadPixelDetector::load_config
 *
 *	description:	method to execute "LoadConfig"
 *	This�function�activate� the�copy�of � the�calibration�data�stored� into� the�memory�
 *	buffer�identified�by�calibId�of�all�the�chips�of�the�modules�selected�by�modNum �
 *	into�the�config�registers.
 *
 * @param	argin	modNum(1..8), calibId(0..6)
 *
 */
//+------------------------------------------------------------------
void XpadPixelDetector::load_config(const Tango::DevVarULongArray *argin)
{
	DEBUG_STREAM << "XpadPixelDetector::load_config(): entering... !" << endl;

	//	Add your own code to control device here

    //- TODO: parameter checking ? or done in xpix?
    try
    {
        m_camera->loadConfig((*argin)[0],(*argin)[1]);
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("XpadPixelDetector::load_config"));
    }
}


//+------------------------------------------------------------------
/**
 *	method:	XpadPixelDetector::reset
 *
 *	description:	method to execute "Reset"
 *	Reset the Xpad : call the xpci_hubModRebootNIOS(modMask) xpix function
 *
 *
 */
//+------------------------------------------------------------------
void XpadPixelDetector::reset()
{
	DEBUG_STREAM << "XpadPixelDetector::reset(): entering... !" << endl;

	//	Add your own code to control device here

    try
    {
        m_camera->reset();
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("XpadPixelDetector::reset"));
    }
}

//+------------------------------------------------------------------
/**
 *	method:	XpadPixelDetector::get_mod_config
 *
 *	description:	method to execute "GetModConfig"
 *	This�fonction�read�the�values�of�the�local�configuration�registers�currently�loaded�
 *	in�the�detector�for�all�the�chips�on�all�the�modules.�Data�are�received�in�the�format�of�2�bytes�per�pixel�with�
 *	the�following�format.<BR>
 *	� bit[0]�enable�counters<BR>
 *	� bit[1]�enable�ampli�(validated�at�0)<BR>
 *	� bit[2]�enable�test�pulse<BR>
 *	� bit[8:3]�DACL�registers<BR>
 *	� bit[15:9]�reserved�(tied�to�0)
 *
 * @return	array of data
 *
 */
//+------------------------------------------------------------------
Tango::DevVarUShortArray *XpadPixelDetector::get_mod_config()
{
	//	POGO has generated a method core with argout allocation.
	//	If you would like to use a static reference without copying,
	//	See "TANGO Device Server Programmer's Manual"
	//		(chapter : Writing a TANGO DS / Exchanging data)
	//------------------------------------------------------------
	Tango::DevVarUShortArray	*argout  = new Tango::DevVarUShortArray();
	argout->length(1);
	(*argout)[0] = 0;
	DEBUG_STREAM << "XpadPixelDetector::get_mod_config(): entering... !" << endl;

	//	Add your own code to control device here

    try
    {
        //- get the DACLs size, which is the same size of the image
        HwDetInfoCtrlObj *hw_det_info;
        m_interface->getHwCtrlObj(hw_det_info);
        Size image_size;
        hw_det_info->getDetectorImageSize(image_size);
    
        cout << "########### 1 "<<endl;
        //- resize the argout
        argout->length(image_size.getWidth() * image_size.getHeight());

        cout << "########### 2 "<<endl;

        //- Get the DACLs
        unsigned short*& dacl = m_camera->getModConfig();

        cout << "########### 3 "<<endl;

        //(*argout) = dacl;

        //- store input data in attribute Theta2Constants
	    for (int i = 0;i < argout->length(); i++)
	    {
            cout << "dacl # " << i << "= " << dacl[i];
	    }
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("XpadPixelDetector::get_mod_config"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("XpadPixelDetector::get_mod_config"));
    }

	return argout;
}

//+------------------------------------------------------------------
/**
 *	method:	XpadPixelDetector::load_all_config_g
 *
 *	description:	method to execute "LoadAllConfigG"
 *	This�function�loads�in�all�the�global�registers�the�value�passed�as�parameters.
 *	the order if the configG is as follow: CMOS_DSBL ; AMP_TP;ITHH;VADJ;VREF;IMFP;IOTA;IPRE;ITHL;ITUNE;IBUFFER
 *
 * @param	argin	modNum(1..8), chipId(0..6), config_values (11 values)
 *
 */
//+------------------------------------------------------------------
void XpadPixelDetector::load_all_config_g(const Tango::DevVarULongArray *argin)
{
	DEBUG_STREAM << "XpadPixelDetector::load_all_config_g(): entering... !" << endl;

	//	Add your own code to control device here

    //- TODO: parameter checking ? or done in xpix?
    //- argin length doit etre de taille: 2 + 11 = 13
    try
    {
        m_camera->loadAllConfigG((*argin)[0],(*argin)[1],(unsigned long*) &((*argin)[2]));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        Tango::Except::throw_exception(
                    static_cast<const char*> ("LIMA_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("XpadPixelDetector::load_all_config_g"));
    }
}

}	//	namespace
