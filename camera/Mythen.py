#----------------------------------------------------------------------------
# Plugins
#----------------------------------------------------------------------------
from Lima import Core
from Lima import Mythen

_MythenInterface = None


def get_control(**keys) :
    global _MythenInterface
    if _MythenInterface is None:
        mythen = Mythen.Camera("bl04mythen", 1952, 1)
        _MythenInterface = Mythen.Interface(mythen)
    _MythenInterface._ref_interface = mythen
    return Core.CtControl(_MythenInterface)

def close_interface() :
    global _MythenInterface
    if _MythenInterface is not None:
        del _MythenInterface
