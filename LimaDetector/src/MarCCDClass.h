//=============================================================================
//
// file :         MarCCDClass.h
//
// description :  Include for the MarCCDClass root class.
//                This class is the singleton class for
//                the Pilatus device class.
//                It contains all properties and methods which the 
//                Pilatus requires only once e.g. the commands.
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
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================

#ifndef _MarCCDCLASS_H
#define _MarCCDCLASS_H


#include <MarCCD.h>
#include <tango.h>


namespace MarCCD_ns
{//=====================================
//	Define classes for attributes
//=====================================
//=========================================
//	Define classes for commands
//=========================================
//
// The MarCCDClass singleton definition
//

class
#ifdef WIN32
	__declspec(dllexport)
#endif
	MarCCDClass : public Tango::DeviceClass
{
public:
//	properties member data

//	add your own data members here
//------------------------------------

public:
	Tango::DbData	cl_prop;
	Tango::DbData	cl_def_prop;
	Tango::DbData	dev_def_prop;

//	Method prototypes
	static MarCCDClass *init(const char *);
	static MarCCDClass *instance();
	~MarCCDClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	MarCCDClass(string &);
	static MarCCDClass *_instance;
	void command_factory();
	void get_class_property();
	void write_class_property();
	void set_default_property();
	string get_cvstag();
	string get_cvsroot();

private:
	void device_factory(const Tango::DevVarStringArray *);
};


}	//	namespace MarCCD_ns

#endif // _MARCCDCLASS_H