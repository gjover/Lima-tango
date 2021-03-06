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
# file :        Pilatus.py
#
# description : Python source for the Pilatus and its commands. 
#                The class is derived from Device. It represents the
#                CORBA servant object which will be accessed from the
#                network. All commands which can be executed on the
#                Pilatus are implemented in this file.
#
# project :     TANGO Device Server
#
# copyleft :    European Synchrotron Radiation Facility
#               BP 220, Grenoble 38043
#               FRANCE
#
#=============================================================================
#          This file is generated by POGO
#    (Program Obviously used to Generate tango Object)
#
#         (c) - Software Engineering Group - ESRF
#=============================================================================
#


import PyTango
import sys

from Lima import Core

#==================================================================
#   Pilatus Class Description:
#
#
#==================================================================


class Pilatus(PyTango.Device_4Impl):

#--------- Add you global variables here --------------------------
    Core.DEB_CLASS(Core.DebModApplication, 'LimaCCDs')

#------------------------------------------------------------------
#    Device constructor
#------------------------------------------------------------------
    def __init__(self,cl, name):
        PyTango.Device_4Impl.__init__(self,cl,name)
        self.init_device()

        self.__FillMode = {'ON':True,
                           'OFF':False}
        self.__ThresholdGain = {'LOW' : 0,
                                'MID' : 1,
                                'HIGH' : 2,
                                'ULTRA HIGH' : 3}

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

        if self.TmpfsSize:
            buffer = _PilatusIterface.buffer()
            buffer.setTmpfsSize(self.TmpfsSize * 1024 * 1024)
            
#------------------------------------------------------------------
#    getAttrStringValueList command:
#
#    Description: return a list of authorized values if any
#    argout: DevVarStringArray   
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def getAttrStringValueList(self, attr_name):
        valueList = []
        dict_name = '_' + self.__class__.__name__ + '__' + ''.join([x.title() for x in attr_name.split('_')])
        d = getattr(self,dict_name,None)
        if d:
            valueList = d.keys()
        return valueList

#------------------------------------------------------------------
#    sendCamserverCmd:
#
#    Description: sends any camserver command.
#
#    We need at least the mxsettings command to prepare the camserver:
#    Description: sets the mxsettings. Documentation from camserver:
#    Set crystallographic parameters reported in the image header.
#
#    mxsettings [param_name value] [param_name value] ...
#
#    List of availables param_name :
#    Wavelength, Energy_range, Detector_distance, Detector_Voffset, Beam_xy,
#    Beam_x, Beam_y, Flux, Filter_transmission, Start_angle, Angle_increment,
#    Detector_2theta, Polarization, Alpha, Kappa, Phi, Phi_increment, Chi,
#    Chi_increment, Oscillation_axis, N_oscillations, Start_position,
#    Position_increment, Shutter_time, CBF_template_file
#
#    Not settable with mxsettings, but provided to templates from detector
#    settings:
#    Timestamp, Exposure_period, Exposure_time, Count_cutoff,
#    Compression_type, X_dimension, Y_dimension
#
#    argin: DevString
#------------------------------------------------------------------
    @Core.DEB_MEMBER_FUNCT
    def sendCamserverCmd(self, cmd):
        communication = _PilatusIterface.communication()
        communication.send_CamserverCmd(cmd)

#==================================================================
#
#    Pilatus read/write attribute methods
#
#==================================================================

#------------------------------------------------------------------
#    Read threshold_gain attribute
#------------------------------------------------------------------
    def read_threshold_gain(self, attr):
        communication = _PilatusIterface.communication()
        gain = communication.gain()
        if gain is None:
            gain = "not set"
        else:
            gain = _getDictKey(self.__ThresholdGain,gain)
        attr.set_value(gain)


#------------------------------------------------------------------
#    Write threshold_gain attribute
#------------------------------------------------------------------
    def write_threshold_gain(self, attr):
        data = []
        attr.get_write_value(data)
        gain = _getDictValue(self.__ThresholdGain,data[0])
        communication = _PilatusIterface.communication()
        threshold = communication.threshold()
        communication.set_threshold_gain(threshold,gain)

#------------------------------------------------------------------
#    Read threshold attribute
#------------------------------------------------------------------
    def read_threshold(self, attr):
        communication = _PilatusIterface.communication()
        threshold = communication.threshold()
        if threshold == None:           # Not set
            threshold = -1
        attr.set_value(threshold)

#------------------------------------------------------------------
#    Write threshold attribute
#------------------------------------------------------------------
    def write_threshold(self, attr):
        data = []
        attr.get_write_value(data)
        communication = _PilatusIterface.communication()
        communication.set_threshold_gain(data[0])

#------------------------------------------------------------------
#    Read energy_threshold attribute
#------------------------------------------------------------------
    def read_energy_threshold(self, attr):
        communication = _PilatusIterface.communication()
        threshold = communication.threshold()
        if threshold == None:           # Not set
            energy = -1
        else:
            energy = threshold * 2.    # threshold is 60% of working energy
        attr.set_value(energy)

#------------------------------------------------------------------
#    Write energy_threshold attribute
#------------------------------------------------------------------
    def write_energy_threshold(self, attr):
        data = []
        attr.get_write_value(data)
        energy = data[0]
        communication = _PilatusIterface.communication()
        communication.set_energy(energy)

        # threshold = energy * 600  # 60% of working energy
        # if energy > 12 :
        #     gain = 0                    # Low gain
        # elif energy > 8 and energy <= 12 :
        #     gain = 1                    # Mid gain
        # elif energy >= 6 and energy <= 8:
        #     gain = 2                    # high gain
        # else:
        #     gain = 3                    # Ultra high gain
        
        # communication = _PilatusIterface.communication()
        # communication.set_threshold_gain(threshold,gain)
#----------------------------------------------------------------------------
#     Read delay attribute
#----------------------------------------------------------------------------
    def read_trigger_delay(self,attr) :
        communication = _PilatusIterface.communication()
        delay = communication.hardware_trigger_delay()
        attr.set_value(delay)

#----------------------------------------------------------------------------
#     Write delay attribute
#----------------------------------------------------------------------------
    def write_trigger_delay(self,attr) :
        data = []
        attr.get_write_value(data)
        delay = data[0]
        
        communication = _PilatusIterface.communication()
        communication.set_hardware_trigger_delay(delay)

#----------------------------------------------------------------------------
#     Read nb exposure per frame attribute
#----------------------------------------------------------------------------
    def read_nb_exposure_per_frame(self,attr) :
        communication = _PilatusIterface.communication()
        nb_frames = communication.nb_exposure_per_frame()
        attr.set_value(nb_frames)

#----------------------------------------------------------------------------
#     Write nb exposure per frame attribute
#----------------------------------------------------------------------------
    def write_nb_exposure_per_frame(self,attr) :
        data = []
        attr.get_write_value(data)
        nb_frames = data[0]
        
        communication = _PilatusIterface.communication()
        communication.set_nb_exposure_per_frame(nb_frames)


#----------------------------------------------------------------------------
#     Read nb exposure per frame attribute
#----------------------------------------------------------------------------
    def read_nb_first_image(self,attr) :
        communication = _PilatusIterface.communication()
        first = communication.getFirstImgNumber()
        attr.set_value(first)

#----------------------------------------------------------------------------
#     Write nb exposure per frame attribute
#----------------------------------------------------------------------------
    def write_nb_first_image(self,attr) :
        data = []
        attr.get_write_value(data)
        first = data[0]
        
        communication = _PilatusIterface.communication()
        communication.setFirstImgNumber(first)



#------------------------------------------------------------------
#    Read gapfill attribute
#------------------------------------------------------------------
    def read_fill_mode(self, attr):
        communication = _PilatusIterface.communication()
        gapfill = communication.gapfill()
        gapfill = _getDictKey(self.__FillMode,gapfill)
        attr.set_value(gapfill)

#------------------------------------------------------------------
#    Write gapfill attribute
#------------------------------------------------------------------
    def write_fill_mode(self, attr):
        data = []
        attr.get_write_value(data)
        gapfill = _getDictValue(self.__FillMode,data[0])
        communication = _PilatusIterface.communication()
        communication.set_gapfill(gapfill)

#------------------------------------------------------------------
#    Read camstatus attribute
#------------------------------------------------------------------
    def read_cam_state(self, attr):
        StateDict = {0:"ERROR",1:"DISCONNECTED",2:"OK",3:"SETTING_THRESHOLD",4:"SETTING_EXPOSURE",5:"SETTING_NB_IMAGE_IN_SEQUENCE",6:"SETTING_EXPOSURE_PERIOD",7:"SETTING_HARDWARE_TRIGGER_DELAY",8:"SETTING_EXPOSURE_PER_FRAME",9:"KILL_ACQUISITION",10:"RUNNING"}

        communication = _PilatusIterface.communication()
        status = communication.status()
        attr.set_value(StateDict[status])

#==================================================================
#
#    Pilatus command methods
#
#==================================================================

#==================================================================
#
#    PilatusClass class definition
#
#==================================================================
class PilatusClass(PyTango.DeviceClass):

    #    Class Properties
    class_property_list = {
        }


    #    Device Properties
    device_property_list = {
        'TmpfsSize' :
        [PyTango.DevInt,
         "Size of communication temp. filesystem (in MB)",0],
        }


    #    Command definitions
    cmd_list = {
        'getAttrStringValueList':
        [[PyTango.DevString, "Attribute name"],
         [PyTango.DevVarStringArray, "Authorized String value list"]],
        'sendCamserverCmd':
        [[PyTango.DevString, "Camserver command to send"],
         [PyTango.DevVoid, "No answer"]],
         }


    #    Attribute definitions
    attr_list = {
        'threshold_gain':
            [[PyTango.DevString,
            PyTango.SCALAR,
            PyTango.READ_WRITE]],
        'threshold':
            [[PyTango.DevFloat,
            PyTango.SCALAR,
            PyTango.READ_WRITE]],
        'energy_threshold':
            [[PyTango.DevFloat,
            PyTango.SCALAR,
            PyTango.READ_WRITE]],
        'fill_mode':
            [[PyTango.DevString,
            PyTango.SCALAR,
            PyTango.READ_WRITE]],
        'trigger_delay':
            [[PyTango.DevDouble,
            PyTango.SCALAR,
            PyTango.READ_WRITE]],
        'nb_exposure_per_frame':
            [[PyTango.DevLong,
            PyTango.SCALAR,
            PyTango.READ_WRITE]],
        'nb_first_image':
            [[PyTango.DevLong,
            PyTango.SCALAR,
            PyTango.READ_WRITE]],
        'cam_state':
            [[PyTango.DevString,
            PyTango.SCALAR,
            PyTango.READ]],
        }


#------------------------------------------------------------------
#    PilatusClass Constructor
#------------------------------------------------------------------
    def __init__(self, name):
        PyTango.DeviceClass.__init__(self, name)
        self.set_type(name)

def _getDictKey(dict, value):
    try:
        ind = dict.values().index(value)                            
    except ValueError:
        return None
    return dict.keys()[ind]

def _getDictValue(dict, key):
    try:
        value = dict[key.upper()]
    except KeyError:
        return None
    return value

#----------------------------------------------------------------------------
# Plugins
#----------------------------------------------------------------------------
from Lima.Pilatus import Interface

_PilatusIterface = None

def get_control(**keys) :
    global _PilatusIterface
    if _PilatusIterface is None:
        _PilatusIterface = Interface.Interface()
    ct = Core.CtControl(_PilatusIterface)
    _PilatusIterface.setCtSavingLink(ct.saving())
    return ct

def close_interface() :
    global _PilatusIterface
    if _PilatusIterface is not None:
        _PilatusIterface.quit()
        _PilatusIterface = None


def get_tango_specific_class_n_device() :
    return PilatusClass,Pilatus
