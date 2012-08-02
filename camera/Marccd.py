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
#----------------------------------------------------------------------------
# Plugins
#----------------------------------------------------------------------------
from Lima import Core
from Lima import Marccd
#from Lima.Marccd.Interface import Interface

_MarccdInterface = None


def get_control(**keys) :
    global _MarccdInterface
    if _MarccdInterface is None:
        marccd = Marccd.Camera('bl04rayonix', 2222, '/beamlines/bl04/controls/rayonix_buffer/buffer')
        _MarccdInterface = Marccd.Interface(marccd)
    _MarccdInterface._ref_interface = marccd
    return Core.CtControl(_MarccdInterface)

def close_interface() :
    global _MarccdInterface
    if _MarccdInterface is not None:
        del _MarccdInterface


