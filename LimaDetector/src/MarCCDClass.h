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
class binnigAttrib: public Tango::Attr
{
public:
	binnigAttrib():Attr("binnig", Tango::DEV_USHORT, Tango::READ_WRITE) {};
	~binnigAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<MarCCD *>(dev))->read_binnig(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<MarCCD *>(dev))->write_binnig(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<MarCCD *>(dev))->is_binnig_allowed(ty);}
};

//=========================================
//	Define classes for commands
//=========================================
class TakeBackgroundClass : public Tango::Command
{
public:
	TakeBackgroundClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	TakeBackgroundClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~TakeBackgroundClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<MarCCD *>(dev))->is_TakeBackground_allowed(any);}
};



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
	void attribute_factory(vector<Tango::Attr *> &);
	void write_class_property();
	void set_default_property();
	string get_cvstag();
	string get_cvsroot();

private:
	void device_factory(const Tango::DevVarStringArray *);
};


}	//	namespace MarCCD_ns

#endif // _MARCCDCLASS_H
