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
import PyTango
from Lima import Core
from Lima import Marccd

#==================================================================
# Marccd class definition
#==================================================================
class LimaMarccd(PyTango.Device_4Impl):
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
#   
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def takeBackgroundFrame(self):
        _MarccdInterface.takeBackgroundFrame()
        pass

#------------------------------------------------------------------
#   
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def getCamState(self):
        return _MarccdInterface.getCamState()

#------------------------------------------------------------------
#    Attrubute read/write methods
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def read_cam_state(self, attr):
        state = _MarccdInterface.getCamState()
        attr.set_value(state)
    
#     @Core.DEB_MEMBER_FUNCT
#     def read_binning(self, attr):
#         Id = _MarccdInterface.getBinning()
#         attr.set_value(Id)
    
#     @Core.DEB_MEMBER_FUNCT
#     def write_binning(self, attr):
#         data = []
#         attr.get_write_value(data)
#         Id = data[0]
#         _MarccdInterface.setBinning(Id)
    
#     @Core.DEB_MEMBER_FUNCT
#     def read_conf_file1(self, attr):
#         self.__calfile1, self.__calfile2 = _MarccdInterface.getCalFiles()
#         attr.set_value(self.__calfile1)
    
#     @Core.DEB_MEMBER_FUNCT
#     def write_conf_file1(self, attr):
#         data = []
#         attr.get_write_value(data)
#         self.__calfile1 = data[0]
#         _MarccdInterface.setCalFiles(self.__calfile1, self.__calfile2)
    
#     @Core.DEB_MEMBER_FUNCT
#     def read_conf_file2(self, attr):
#         self.__calfile1, self.__calfile2 = _MarccdInterface.getCalFiles()
#         attr.set_value(self.__calfile2)
    
#     @Core.DEB_MEMBER_FUNCT
#     def write_conf_file2(self, attr):
#         data = []
#         attr.get_write_value(data)
#         self.__calfile2 = data[0]
#        _MarccdInterface.setCalFiles(self.__calfile1, self.__calfile2)
    
#==================================================================
# MarccdClass class definition
#==================================================================

class LimaMarccdClass(PyTango.DeviceClass):

    #    Class Properties
    class_property_list = {
        }


    #    Device Properties
    device_property_list = {
        }


    #    Command definitions    
    cmd_list = {
        'takeBackgroundFrame':
        [[PyTango.DevVoid, ""],
         [PyTango.DevVoid, ""]],
        }


    #    Attribute definitions
    attr_list = {
        'cam_state':
            [[PyTango.DevUShort,
              PyTango.SCALAR,
              PyTango.READ]],
#         'binning':
#             [[PyTango.DevUShort,
#               PyTango.SCALAR,
#               PyTango.READ_WRITE]],
        }

#----------------------------------------------------------------------------
# Plugins
#----------------------------------------------------------------------------
from Lima import Marccd

_MarccdInterface = None

def get_control(**keys) :
    global _MarccdInterface
    if _MarccdInterface is None:
        marccd = Marccd.Camera('bl04rayonix', 2222, '/buffer/rayonix/')
        _MarccdInterface = Marccd.Interface(marccd)
    _MarccdInterface._ref_interface = marccd
    return Core.CtControl(_MarccdInterface)

def close_interface() :
    global _MarccdInterface
    if _MarccdInterface is not None:
        del _MarccdInterface

def get_tango_specific_class_n_device() :
    return LimaMarccdClass,LimaMarccd
