static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         MarCCD.cpp
//
// description :  C++ source for the MarCCD and its commands. 
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                MarCCD are implemented in this file.
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
//  TakeBackground  |  take_background()
//
//===================================================================
#ifdef WIN32
#include <tango.h>
#include <PogoHelper.h>
#endif

#include <MarCCD.h>
#include <MarCCDClass.h>

#ifndef WIN32
#include <tango.h>
#include <PogoHelper.h>
#endif

const size_t MAX_STRING_LENGTH = 256;

namespace MarCCD_ns
{

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::MarCCD(string &s)
// 
// description : 	constructor for simulated MarCCD
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name 
//
//-----------------------------------------------------------------------------
MarCCD::MarCCD(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
	init_device();
}

MarCCD::MarCCD(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
	init_device();
}

MarCCD::MarCCD(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
	init_device();
}
//+----------------------------------------------------------------------------
//
// method : 		MarCCD::delete_device()
// 
// description : 	will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void MarCCD::delete_device()
{
	//	Delete device allocated objects
	DELETE_DEVSTRING_ATTRIBUTE(attr_imageName_read);   
	DELETE_SCALAR_ATTRIBUTE(attr_imageIndex_read);

    //!!!! ONLY LimaDetector device can do this !!!!
    //if(m_ct!=0)
    //{
    //    ControlFactory::instance().reset("MarCCD");
    //    m_ct = 0;
    //}    
}

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::init_device()
// 
// description : 	will be called at device initialization.
//
//-----------------------------------------------------------------------------
void MarCCD::init_device()
{
	INFO_STREAM << "MarCCD::MarCCD() create device " << device_name << endl;

	// Initialise variables to default values
	//--------------------------------------------
	CREATE_DEVSTRING_ATTRIBUTE(attr_imageName_read, MAX_STRING_LENGTH);   
	CREATE_SCALAR_ATTRIBUTE(attr_imageIndex_read);

	get_device_property();

    //By default INIT, need to ensure that all objets are OK before set the device to STANDBY
    set_state(Tango::INIT);
	m_is_device_initialized = false;
	m_status_message.str("");
	
	try
	{
		//- get the main object used to pilot the lima framework
		//in fact LimaDetector is create the singleton control objet
		//so this call, will only return existing object, no need to give it the ip !!
		m_ct = ControlFactory::instance().get_control("MarCCD");

		//- get interface to specific camera
		m_hw = dynamic_cast<Marccd::Interface*>(m_ct->hwInterface());
		if( m_hw==0 )
		{
			INFO_STREAM<<"Initialization Failed : Unable to get the interface of camera plugin !" << std::endl;
			m_status_message <<"Initialization Failed : Unable to get the interface of camera plugin !" << std::endl;
			m_is_device_initialized = false;
			set_state(Tango::FAULT);
			return;			
		}
		
	}
	catch(Exception& e)
	{
		INFO_STREAM<<"Initialization Failed : " << e.getErrMsg() << std::endl;
		m_status_message <<"Initialization Failed : " << e.getErrMsg( ) << std::endl;
		m_is_device_initialized = false;
		set_state(Tango::FAULT);
		return;
	}
	catch(...)
	{
		INFO_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
		m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
	m_is_device_initialized = true;
	set_state(Tango::STANDBY);	
	this->dev_state();	
}


//+----------------------------------------------------------------------------
//
// method : 		MarCCD::get_device_property()
// 
// description : 	Read the device properties from database.
//
//-----------------------------------------------------------------------------
void MarCCD::get_device_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read device properties from database.(Automatic code generation)
	//------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("DetectorIP"));
	dev_prop.push_back(Tango::DbDatum("DetectorPort"));
	dev_prop.push_back(Tango::DbDatum("DetectorTargetPath"));
	dev_prop.push_back(Tango::DbDatum("ReaderTimeout"));
	dev_prop.push_back(Tango::DbDatum("UseReader"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	MarCCDClass	*ds_class =
		(static_cast<MarCCDClass *>(get_device_class()));
	int	i = -1;

	//	Try to initialize DetectorIP from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorIP;
	else {
		//	Try to initialize DetectorIP from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorIP;
	}
	//	And try to extract DetectorIP value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorIP;

	//	Try to initialize DetectorPort from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorPort;
	else {
		//	Try to initialize DetectorPort from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorPort;
	}
	//	And try to extract DetectorPort value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorPort;

	//	Try to initialize DetectorTargetPath from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorTargetPath;
	else {
		//	Try to initialize DetectorTargetPath from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorTargetPath;
	}
	//	And try to extract DetectorTargetPath value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorTargetPath;

	//	Try to initialize ReaderTimeout from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  readerTimeout;
	else {
		//	Try to initialize ReaderTimeout from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  readerTimeout;
	}
	//	And try to extract ReaderTimeout value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  readerTimeout;

	//	Try to initialize UseReader from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  useReader;
	else {
		//	Try to initialize UseReader from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  useReader;
	}
	//	And try to extract UseReader value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  useReader;



	//	End of Automatic code generation
	//------------------------------------------------------------------
	create_property_if_empty(dev_prop,"127.0.0.1","DetectorIP");
	create_property_if_empty(dev_prop,"-1","DetectorPort");
	create_property_if_empty(dev_prop,"/no/path/defined/","DetectorTargetPath");
	create_property_if_empty(dev_prop,"10000","ReaderTimeout");
	create_property_if_empty(dev_prop,"true","UseReader");
}
//+----------------------------------------------------------------------------
//
// method : 		MarCCD::always_executed_hook()
// 
// description : 	method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void MarCCD::always_executed_hook()
{
	DEBUG_STREAM << "MarCCD::always_executed_hook() entering... "<< endl;
	try
	{
	    m_status_message.str("");
		//- get the singleton control objet used to pilot the lima framework
		m_ct = ControlFactory::instance().get_control("MarCCD");

		//- get interface to specific detector
		if(m_ct!=0)
			m_hw = dynamic_cast<Marccd::Interface*>(m_ct->hwInterface());

	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
		//- throw exception
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
	catch(...)
	{
		ERROR_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
		m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
		//- throw exception
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
}
//+----------------------------------------------------------------------------
//
// method : 		MarCCD::read_attr_hardware
// 
// description : 	Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void MarCCD::read_attr_hardware(vector<long> &attr_list)
{
	DEBUG_STREAM << "MarCCD::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
	//	Add your own code here
}

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::read_imageName
// 
// description : 	Extract real attribute values for imageName acquisition result.
//
//-----------------------------------------------------------------------------
void MarCCD::read_imageName(Tango::Attribute &attr)
{
	DEBUG_STREAM << "MarCCD::read_imageName(Tango::Attribute &attr) entering... "<< endl;
	std::string imgName("");

	try
	{
		imgName = m_hw->getImageFileName();
		::strcpy( *attr_imageName_read, imgName.c_str() );
		attr.set_value(attr_imageName_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
			static_cast<const char*> ("TANGO_DEVICE_ERROR"),
			static_cast<const char*> (string(df.errors[0].desc).c_str()),
			static_cast<const char*> ("MarCCD::read_imageName"));
	}
	catch(...)
	{
		Tango::Except::throw_exception(
			static_cast<const char*> ("TANGO_DEVICE_ERROR"),
			static_cast<const char*> ("Unknown exception caught."),
			static_cast<const char*> ("MarCCD::read_imageName"));
	}
}

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::write_imageName
// 
// description : 	Write imageName attribute values to hardware.
//
//-----------------------------------------------------------------------------
void MarCCD::write_imageName(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "MarCCD::write_imageName(Tango::WAttribute &attr) entering... "<< endl;
	std::string imgName("");

	try
	{
		attr.get_write_value(attr_imageName_write);
		m_hw->setImageFileName(attr_imageName_write);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
			static_cast<const char*> ("TANGO_DEVICE_ERROR"),
			static_cast<const char*> (string(df.errors[0].desc).c_str()),
			static_cast<const char*> ("MarCCD::write_imageName"));
	}
	catch(...)
	{
		Tango::Except::throw_exception(
			static_cast<const char*> ("TANGO_DEVICE_ERROR"),
			static_cast<const char*> ("Unknown exception caught."),
			static_cast<const char*> ("MarCCD::write_imageName"));
	}
}

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::read_imageIndex
// 
// description : 	Extract real attribute values for imageIndex acquisition result.
//
//-----------------------------------------------------------------------------
void MarCCD::read_imageIndex(Tango::Attribute &attr)
{
	DEBUG_STREAM << "MarCCD::read_imageIndex(Tango::Attribute &attr) entering... "<< endl;
	try
	{
		*attr_imageIndex_read = m_hw->getImageIndex();
		attr.set_value(attr_imageIndex_read);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
			static_cast<const char*> ("TANGO_DEVICE_ERROR"),
			static_cast<const char*> (string(df.errors[0].desc).c_str()),
			static_cast<const char*> ("MarCCD::read_imageIndex"));
	}
	catch(...)
	{
		Tango::Except::throw_exception(
			static_cast<const char*> ("TANGO_DEVICE_ERROR"),
			static_cast<const char*> ("Unknown exception caught."),
			static_cast<const char*> ("MarCCD::read_imageIndex"));
	}
}

//+----------------------------------------------------------------------------
//
// method : 		MarCCD::write_imageIndex
// 
// description : 	Write imageIndex attribute values to hardware.
//
//-----------------------------------------------------------------------------
void MarCCD::write_imageIndex(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "MarCCD::write_imageIndex(Tango::WAttribute &attr) entering... "<< endl;
	try
	{
		attr.get_write_value(attr_imageIndex_write);
		m_hw->setImageIndex(attr_imageIndex_write);
	}
	catch(Tango::DevFailed& df)
	{
		ERROR_STREAM << df << endl;
		//- rethrow exception
		Tango::Except::re_throw_exception(df,
			static_cast<const char*> ("TANGO_DEVICE_ERROR"),
			static_cast<const char*> (string(df.errors[0].desc).c_str()),
			static_cast<const char*> ("MarCCD::write_imageIndex"));
	}
	catch(...)
	{
		Tango::Except::throw_exception(
			static_cast<const char*> ("TANGO_DEVICE_ERROR"),
			static_cast<const char*> ("Unknown exception caught."),
			static_cast<const char*> ("MarCCD::write_imageIndex"));
	}
}

//+------------------------------------------------------------------
/**
 *	method:	MarCCD::take_background
 *
 *	description:	method to execute "TakeBackground"
 *	Command to force the MarCCD detector to get a background frame.
 *
 *
 */
//+------------------------------------------------------------------
void MarCCD::take_background()
{
	DEBUG_STREAM << "MarCCD::take_background(): entering... !" << endl;

	//	Add your own code to control device here
	if(m_ct!=0)
	{
		try
		{
			if(m_hw!=0)
				m_hw->takeBackgroundFrame();
		}
		catch(Tango::DevFailed& df)
		{
			ERROR_STREAM << df << endl;
			//- rethrow exception
			Tango::Except::re_throw_exception(df,
				static_cast<const char*> ("TANGO_DEVICE_ERROR"),
				static_cast<const char*> (string(df.errors[0].desc).c_str()),
				static_cast<const char*> ("MarCCD::take_background"));
		}
		catch(Exception& e)
		{
			ERROR_STREAM << e.getErrMsg() << endl;
			//- throw exception
			Tango::Except::throw_exception(
				static_cast<const char*> ("TANGO_DEVICE_ERROR"),
				static_cast<const char*> (e.getErrMsg().c_str()),
				static_cast<const char*> ("MarCCD::take_background"));
		}
		catch(...)
		{
			ERROR_STREAM << "MarCCD::read_binnig -> caught [...]" << endl;
			//- throw exception
			Tango::Except::throw_exception(
				static_cast<const char*> ("UNKNOWN_ERROR"),
				static_cast<const char*> ("MarCCD::take_background -> caught [...]"),
				static_cast<const char*> ("MarCCD::take_background"));
		}
	}

}

//+------------------------------------------------------------------
/**
 *	method:	MarCCD::dev_state
 *
 *	description:	method to execute "State"
 *	This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return	State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState MarCCD::dev_state()
{
	Tango::DevState	argout = DeviceImpl::dev_state();
	DEBUG_STREAM << "MarCCD::dev_state(): entering... !" << endl;	
	//	Add your own code to control device here
	stringstream    DeviceStatus;
	DeviceStatus 	<< "";
	Tango::DevState DeviceState	= Tango::STANDBY;
    if(!m_is_device_initialized )
    {
        DeviceState            = Tango::FAULT;
        DeviceStatus        << m_status_message.str();
    }
    else
	{
		//state&status are retrieved from specific device
		DeviceState = ControlFactory::instance().get_state();
		DeviceStatus << ControlFactory::instance().get_status();		
    }
	
	set_state(DeviceState);
	set_status(DeviceStatus.str());

	argout = DeviceState;
	return argout;
}

/*-------------------------------------------------------------------------
//       MarCCD::store_value_as_property
/-------------------------------------------------------------------------*/
template <class T>
void MarCCD::store_value_as_property (T value, string property_name)
{
    Tango::DbDatum current_value(property_name);
    current_value << value;
    Tango::DbData db_data;
    db_data.push_back(current_value);
    try
    {
        get_db_device()->put_property(db_data);
    }
    catch(Tango::DevFailed &df)
    {
        string message= "Error in storing " + property_name + " in Configuration DataBase ";
        LOG_ERROR((message));
        ERROR_STREAM<<df<<endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("MarCCD::store_value_as_property"));
    }

}

/*-------------------------------------------------------------------------
//       MarCCD::create_property_if_empty
/-------------------------------------------------------------------------*/
template <class T>
void MarCCD::create_property_if_empty(Tango::DbData& dev_prop,T value,string property_name)
{
    int iPropertyIndex = FindIndexFromPropertyName(dev_prop,property_name);
    if (iPropertyIndex == -1) return;
    if (dev_prop[iPropertyIndex].is_empty())
    {
        Tango::DbDatum current_value(dev_prop[iPropertyIndex].name);
        current_value << value;
        Tango::DbData db_data;
        db_data.push_back(current_value);

        try
        {
            get_db_device()->put_property(db_data);
        }
        catch(Tango::DevFailed &df)
        {
            string message= "Error in storing " + property_name + " in Configuration DataBase ";
            LOG_ERROR((message));
            ERROR_STREAM<<df<<endl;
            //- rethrow exception
            Tango::Except::re_throw_exception(df,
                        static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                        static_cast<const char*> (string(df.errors[0].desc).c_str()),
                        static_cast<const char*> ("MarCCD::create_property_if_empty"));
        }
    }
}

/*-------------------------------------------------------------------------
//       MarCCD::FindIndexFromPropertyName
/-------------------------------------------------------------------------*/
int MarCCD::FindIndexFromPropertyName(Tango::DbData& dev_prop, string property_name)
{
    size_t iNbProperties = dev_prop.size();
    unsigned int i;
    for (i=0;i<iNbProperties;i++)
    {
        string sPropertyName(dev_prop[i].name);
        if (sPropertyName == property_name) return i;
    }
    if (i == iNbProperties) return -1;
    return i;
}





}	//	namespace
