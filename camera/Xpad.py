############################################################################
# This file is part of LImA, a Library for Image Acquisition
#
# Copyright (C) : 2009-2011
# European Synchrotron Radiation Facility
# BP 220, Grenoble 38043
# FRANCE
#
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
############################################################################
#=============================================================================
#
# file :        XPad.py
#
# description : Python source of the device server for XPad specific
#               functionalities.  The class is derived from Pytango device
#               as the XPad class is derived from Pythango device class.
#
# project :     TANGO Device Server
#
# copyleft :    CELLS, Sincrotron ALBA
#               08290 Cerdanyola del Valles
#               SPAIN
#
#=============================================================================

import PyTango
from Lima import Core
from Lima import XPad

#==================================================================
# XPad class definition
#==================================================================
class XPad(PyTango.Device_4Impl):
    Core.DEB_CLASS(Core.DebModApplication, 'LimaCCDs')

#------------------------------------------------------------------
#    Device constructor
#------------------------------------------------------------------
    def __init__(self,cl, name):
        PyTango.Device_4Impl.__init__(self,cl,name)
        self.init_device()

#------------------------------------------------------------------
#    Device destructor
#------------------------------------------------------------------
    def delete_device(self):
        pass

#------------------------------------------------------------------
#    Device initialization
#------------------------------------------------------------------
    def init_device(self):
        self.set_state(PyTango.DevState.ON)
        self.get_device_properties(self.get_device_class())

#------------------------------------------------------------------
#    LoadConfiguration command
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def loadConfiguration(self,filearr):
         _XPadInterface.loadConfig(filearr[0],filearr[1])

#------------------------------------------------------------------
#    Attrubute read/write methods
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def read_config_id(self, attr):
        Id = _XPadInterface.getConfigId()
        attr.set_value(Id)
    
    @Core.DEB_MEMBER_FUNCT
    def write_config_id(self, attr):
        data = []
        attr.get_write_value(data)
        Id = data[0]
        _XPadInterface.setConfigId(Id)
    
    @Core.DEB_MEMBER_FUNCT
    def read_ITHLoffset(self, attr):
        th = _XPadInterface.getITHLoffset()
        attr.set_value(th)
    
    @Core.DEB_MEMBER_FUNCT
    def write_ITHLoffset(self, attr):
        data = []
        attr.get_write_value(data)
        th = data[0]
        _XPadInterface.getITHLoffset(th)
    
#     @Core.DEB_MEMBER_FUNCT
#     def read_conf_file1(self, attr):
#         self.__calfile1, self.__calfile2 = _XPadInterface.getCalFiles()
#         attr.set_value(self.__calfile1)
    
#     @Core.DEB_MEMBER_FUNCT
#     def write_conf_file1(self, attr):
#         data = []
#         attr.get_write_value(data)
#         self.__calfile1 = data[0]
#         _XPadInterface.setCalFiles(self.__calfile1, self.__calfile2)
    
#     @Core.DEB_MEMBER_FUNCT
#     def read_conf_file2(self, attr):
#         self.__calfile1, self.__calfile2 = _XPadInterface.getCalFiles()
#         attr.set_value(self.__calfile2)
    
#     @Core.DEB_MEMBER_FUNCT
#     def write_conf_file2(self, attr):
#         data = []
#         attr.get_write_value(data)
#         self.__calfile2 = data[0]
#        _XPadInterface.setCalFiles(self.__calfile1, self.__calfile2)
    
#==================================================================
# XPadClass class definition
#==================================================================

class XPadClass(PyTango.DeviceClass):

    #    Class Properties
    class_property_list = {
        }


    #    Device Properties
    device_property_list = {
        }


    #    Command definitions    
    cmd_list = {
        'loadConfiguration':
        [[PyTango.DevVarStringArray, "Calibration files"],
         [PyTango.DevVoid, ""]]
        }


    #    Attribute definitions
    attr_list = {
        'config_id':
            [[PyTango.DevLong,
            PyTango.SCALAR,
            PyTango.READ_WRITE]],
        'ITHLoffset':
            [[PyTango.DevLong,
            PyTango.SCALAR,
            PyTango.READ_WRITE]],
        }


#==================================================================
# Plugins
#==================================================================
from Lima.XPad.Interface import Interface

_XPadInterface = None

def get_control(**keys) :
    global _XPadInterface
    if _XPadInterface is None:
        _XPadInterface = Interface()
    return Core.CtControl(_XPadInterface)

def close_interface() :
    global _XPadInterface
    if _XPadInterface is not None:
        del _XPadInterface

def get_tango_specific_class_n_device() :
    return XPadClass,XPad

