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
#     @Core.DEB_MEMBER_FUNCT
#     def getHeader(self, i):
#         value = _MarccdInterface.getHeader()
#         return str(type(value))
    
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
#         if (data[0] == 1):
#             data[0] = 2;
#         Id = data[0]
#         _MarccdInterface.setBinning(Id)
    
    @Core.DEB_MEMBER_FUNCT
    def write_source_beam_x(self, attr):
        data = []
        attr.get_write_value(data)
        X = data[0]
        _MarccdInterface.setBeamX(X)
    
    @Core.DEB_MEMBER_FUNCT
    def write_source_beam_y(self, attr):
        data = []
        attr.get_write_value(data)
        Y = data[0]
        _MarccdInterface.setBeamY(Y)
    
    @Core.DEB_MEMBER_FUNCT
    def write_source_distance(self, attr):
        data = []
        attr.get_write_value(data)
        D = data[0]
        _MarccdInterface.setDistance(D)
    
    @Core.DEB_MEMBER_FUNCT
    def write_source_wavelength(self, attr):
        data = []
        attr.get_write_value(data)
        W = data[0]
        _MarccdInterface.setWavelength(W)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_beam_x(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["beam_x"]/1000.0
        attr.set_value(val)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_beam_y(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["beam_y"]/1000.0
        attr.set_value(val)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_distance(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["distance"]/1000.0
        attr.set_value(val)
    
    def read_header_pixelsize_x(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["pixelsize_x"]/1000.0
        attr.set_value(val)
    
    def read_header_pixelsize_y(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["pixelsize_y"]/1000.0
        attr.set_value(val)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_integration_time(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["integration_time"]/1000.0
        attr.set_value(val)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_exposure_time(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["exposure_time"]/1000.0
        attr.set_value(val)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_readout_time(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["readout_time"]/1000.0
        attr.set_value(val)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_wavelength(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["source_wavelength"]/100000.0
        attr.set_value(val)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_acquire_timestamp(self, attr):
        header = _MarccdInterface.getHeader()
        str = header["acquire_timestamp"]
        val = "%s/%s/%s %s:%s:%s" % (str[2:4],str[0:2],str[8:12],str[4:6],str[6:8],str[13:15])
        attr.set_value(val)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_header_timestamp(self, attr):
        header = _MarccdInterface.getHeader()
        str = header["header_timestamp"]
        val = "%s/%s/%s %s:%s:%s" % (str[2:4],str[0:2],str[8:12],str[4:6],str[6:8],str[13:15])
        attr.set_value(val)
    
    @Core.DEB_MEMBER_FUNCT
    def read_header_save_timestamp(self, attr):
        header = _MarccdInterface.getHeader()
        str = header["save_timestamp"]
        val = "%s/%s/%s %s:%s:%s" % (str[2:4],str[0:2],str[8:12],str[4:6],str[6:8],str[13:15])
        attr.set_value(val)

    @Core.DEB_MEMBER_FUNCT
    def read_header_mean_bias(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["mean_bias"]/1000.0
        attr.set_value(val)
        
    @Core.DEB_MEMBER_FUNCT
    def read_header_photons_per_100adu(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["photons_per_100adu"]
        attr.set_value(val)
        
    @Core.DEB_MEMBER_FUNCT
    def read_header_mean(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["mean"]
        attr.set_value(val)
        
    @Core.DEB_MEMBER_FUNCT
    def read_header_rms(self, attr):
        header = _MarccdInterface.getHeader()
        val = header["rms"]
        attr.set_value(val)
        
    @Core.DEB_MEMBER_FUNCT
    def read_header_temperature(self, attr):
        header = _MarccdInterface.getHeader()
        val = [header["temperature_0"]/1000.0,
               header["temperature_1"]/1000.0,
               header["temperature_2"]/1000.0,
               header["temperature_3"]/1000.0,
               header["temperature_4"]/1000.0,
               header["temperature_5"]/1000.0,
               header["temperature_6"]/1000.0,
               header["temperature_7"]/1000.0,
               header["temperature_8"]/1000.0]
        attr.set_value(val)
        
    @Core.DEB_MEMBER_FUNCT
    def read_header_pressure(self, attr):
        header = _MarccdInterface.getHeader()
        val = [header["pressure_0"]/1000000.0,
               header["pressure_1"]/1000000.0,
               header["pressure_2"]/1000000.0,
               header["pressure_3"]/1000000.0,
               header["pressure_4"]/1000000.0,
               header["pressure_5"]/1000000.0,
               header["pressure_6"]/1000000.0,
               header["pressure_7"]/1000000.0,
               header["pressure_8"]/1000000.0]
        attr.set_value(val)
        

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
#         'getHeader':
#         [[PyTango.DevLong, ""],
#          [PyTango.DevString, ""]],
        }


    #    Attribute definitions
    attr_list = {
        'cam_state':
            [[PyTango.DevULong,
              PyTango.SCALAR,
              PyTango.READ]],
#          'binning':
#              [[PyTango.DevUShort,
#                PyTango.SCALAR,
#                PyTango.WRITE]],
         'source_beam_x':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.WRITE]],
         'source_beam_y':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.WRITE]],
         'source_distance':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.WRITE]],
         'source_wavelength':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.WRITE]],
         'header_beam_x':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_beam_y':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_distance':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_pixelsize_x':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_pixelsize_y':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_integration_time':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_exposure_time':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_readout_time':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_wavelength':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_acquire_timestamp':
             [[PyTango.DevString,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_header_timestamp':
             [[PyTango.DevString,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_save_timestamp':
             [[PyTango.DevString,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_mean_bias':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_photons_per_100adu':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_mean':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_rms':
             [[PyTango.DevFloat,
               PyTango.SCALAR,
               PyTango.READ]],
         'header_temperature':
             [[PyTango.DevFloat,
               PyTango.SPECTRUM,
               PyTango.READ,9]],
         'header_pressure':
             [[PyTango.DevFloat,
               PyTango.SPECTRUM,
               PyTango.READ,9]],
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
