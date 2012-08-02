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
from Lima import Adsc

#==================================================================
# Adsc class definition
#==================================================================
class Adsc(PyTango.Device_4Impl):
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
    def takeDarks(self,Texp):
         _AdscInterface.takeDarks(Texp)

#------------------------------------------------------------------
#    Attrubute read/write methods
#------------------------------------------------------------------
    
#==================================================================
# AdscClass class definition
#==================================================================

class AdscClass(PyTango.DeviceClass):

    #    Class Properties
    class_property_list = {
        }


    #    Device Properties
    device_property_list = {
        }


    #    Command definitions    
    cmd_list = {
        'takeDarks':
        [[PyTango.DevFloat, "Exposure time"],
         [PyTango.DevVoid, ""]]
        }


    #    Attribute definitions
    attr_list = {
        }

#==================================================================
# Plugins
#==================================================================
from Lima.Adsc.Interface import Interface

_AdscInterface = None


def get_control(**keys) :
    global _AdscInterface
    if _AdscInterface is None:
        _AdscInterface = Interface()
    return Core.CtControl(_AdscInterface)

def close_interface() :
    global _AdscInterface
    if _AdscInterface is not None:
        del _AdscInterface

def get_tango_specific_class_n_device() :
    return AdscClass,Adsc

