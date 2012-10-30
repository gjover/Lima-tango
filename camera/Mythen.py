#----------------------------------------------------------------------------
# Plugins
#----------------------------------------------------------------------------
import PyTango
from Lima import Core
from Lima import Mythen


#==================================================================
# Mythenccd class definition
#==================================================================
class LimaMythen(PyTango.Device_4Impl):
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

    @Core.DEB_MEMBER_FUNCT
    def read_NrOfModules(self, attr):
        nr = _MythenInterface.getNrOfModules()
        attr.set_value(nr)

    @Core.DEB_MEMBER_FUNCT
    def write_NrOfModules(self, attr):
        nr = attr.get_write_value()
        _MythenInterface.setNrOfModules(nr)

    @Core.DEB_MEMBER_FUNCT
    def read_DynamicRange(self, attr):
        dr = _MythenInterface.getDynamicRange()
        attr.set_value(dr)

    @Core.DEB_MEMBER_FUNCT
    def write_DynamicRange(self, attr):
        dr = attr.get_write_value()
        _MythenInterface.setDynamicRange(dr)

    @Core.DEB_MEMBER_FUNCT
    def read_CalDir(self, attr):
        caldir = _MythenInterface.getCalDir()
        attr.set_value(caldir)

    @Core.DEB_MEMBER_FUNCT
    def write_CalDir(self, attr):
        caldir = attr.get_write_value()
        _MythenInterface.setCalDir(caldir)

    @Core.DEB_MEMBER_FUNCT
    def read_TrimDir(self, attr):
        trimdir = _MythenInterface.getTrimDir()
        attr.set_value(trimdir)

    @Core.DEB_MEMBER_FUNCT
    def write_TrimDir(self, attr):
        trimdir = attr.get_write_value()
        _MythenInterface.setTrimDir(trimdir)

    @Core.DEB_MEMBER_FUNCT
    def read_OutDir(self, attr):
        outdir = _MythenInterface.getOutDir()
        attr.set_value(outdir)

    @Core.DEB_MEMBER_FUNCT
    def write_OutDir(self, attr):
        outdir = attr.get_write_value()
        _MythenInterface.setOutDir(outdir)

    @Core.DEB_MEMBER_FUNCT
    def read_OutFile(self, attr):
        outfile = _MythenInterface.getOutFile()
        attr.set_value(outfile)

    @Core.DEB_MEMBER_FUNCT
    def write_OutFile(self, attr):
        outfile = attr.get_write_value()
        _MythenInterface.setOutDir(outfile)

    @Core.DEB_MEMBER_FUNCT
    def read_OutIndex(self, attr):
        index = _MythenInterface.getOutIndex()
        attr.set_value(index)

    @Core.DEB_MEMBER_FUNCT
    def write_OutIndex(self, attr):
        index = attr.get_write_value()
        _MythenInterface.setOutDir(index)

    @Core.DEB_MEMBER_FUNCT
    def read_Settings(self, attr):
        settings = _MythenInterface.getSettings()
        attr.set_value(settings)

    @Core.DEB_MEMBER_FUNCT
    def write_Settings(self, attr):
        settings = attr.get_write_value()
        _MythenInterface.setSettings(settings)

    @Core.DEB_MEMBER_FUNCT
    def read_Threshold(self, attr):
        threshold = _MythenInterface.getThreshold()
        #print "threshold: ", threshold, "type: " , type(threshold)
        attr.set_value(threshold)

    @Core.DEB_MEMBER_FUNCT
    def write_Threshold(self, attr):
        threshold = attr.get_write_value()
        _MythenInterface.setThreshold(threshold)


#==================================================================
# MarccdClass class definition
#==================================================================

class LimaMythenClass(PyTango.DeviceClass):

    #    Class Properties
    class_property_list = {
        }


    #    Device Properties
    device_property_list = {
        }


    #    Command definitions    
    cmd_list = {
        }


    #    Attribute definitions
    attr_list = {
        'NrOfModules':
            [[PyTango.DevShort,
              PyTango.SCALAR,
              PyTango.READ_WRITE]],
        'DynamicRange':
            [[PyTango.DevUShort,
              PyTango.SCALAR,
              PyTango.READ_WRITE]],
        'CalDir':
            [[PyTango.DevString,
              PyTango.SCALAR,
              PyTango.READ_WRITE]],
        'TrimDir':
            [[PyTango.DevString,
              PyTango.SCALAR,
              PyTango.READ_WRITE]],
        'OutDir':
            [[PyTango.DevString,
              PyTango.SCALAR,
              PyTango.READ_WRITE]],
        'OutFile':
            [[PyTango.DevString,
              PyTango.SCALAR,
              PyTango.READ_WRITE]],
        'OutIndex':
            [[PyTango.DevLong,
              PyTango.SCALAR,
              PyTango.READ_WRITE]],
        'Settings':
            [[PyTango.DevString,
              PyTango.SCALAR,
              PyTango.READ_WRITE]],
        'Threshold':
            [[PyTango.DevLong,
              PyTango.SCALAR,
              PyTango.READ_WRITE]],
        }

_MythenInterface = None

def get_control(**keys) :
    global _MythenInterface
    if _MythenInterface is None:
        #mythen = Mythen.Camera("bl04mythen", 1952, 1)
        mythen = Mythen.Camera("bl04mythen", 1953, 1)
        _MythenInterface = Mythen.Interface(mythen)
    _MythenInterface._ref_interface = mythen
    return Core.CtControl(_MythenInterface)

def close_interface() :
    global _MythenInterface
    if _MythenInterface is not None:
        del _MythenInterface

def get_tango_specific_class_n_device():
    return LimaMythenClass,LimaMythen