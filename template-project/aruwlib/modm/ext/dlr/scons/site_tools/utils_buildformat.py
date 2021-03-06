#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2013-2014, 2016-2017, German Aerospace Center (DLR)
# Copyright (c) 2018, Niklas Hauser
# Copyright (c) 2018, Fabian Greif
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# Authors:
# - 2013-2014, 2016-2017, Fabian Greif (DLR RY-AVS)
# - 2018, Niklas Hauser
# - 2018, Fabian Greif

import sys
import os

from SCons.Script import *

# -----------------------------------------------------------------------------
def generate(env, **kw):
    colors = {
        'cyan':         '\033[;0;36m',
        'purple':       '\033[;0;35m',
        'blue':         '\033[;0;34m',
        'green':        '\033[;0;32m',
        'boldgreen':    '\033[;1;32m',
        'lightgreen':   '\033[;0;92m',
        'yellow':       '\033[;0;33m',
        'boldyellow':   '\033[;1;33m',
        'lightyellow':  '\033[;0;93m',
        'red':          '\033[;0;31m',
        'boldred':      '\033[;1;31m',
        'end':          '\033[;0;0m',
    }

    # If the output is not a terminal, remove the colors
    if not sys.stdout.isatty():
        for key, value in colors.items():
            colors[key] = ''

    default = (colors['green'], colors['yellow'], colors['end'])
    library = (colors['boldgreen'], colors['yellow'], colors['end'])
    linking = (colors['boldgreen'], colors['boldyellow'], colors['end'])
    install = (colors['green'], colors['yellow'], colors['green'], colors['boldyellow'], colors['end'])

    # build messages
    if ARGUMENTS.get('verbose') != '1':
        # Warning: Due to an inconsistency in SCons these ASCII-art arrow are
        #          necessary to keep the indentation. Spaces would be removed.
        #
        # See also:
        # http://scons.tigris.org/ds/viewMessage.do?dsForumId=1268&dsMessageId=2425232
        env['CXX_PREPARE_COMSTR'] = \
                                '%sPrepare C++ยทยทยทยท %s$TARGET%s' % default
        env['LOG_PREPROCESSOR_COMSTR'] = \
                                '%sExtract Logยทยทยทยท %s$TARGET%s' % default
        env['CCCOMSTR'] =       '%sCompiling Cยทยทยทยท %s$TARGET%s' % default
        env['CXXCOMSTR'] =      '%sCompiling C++ยทยท %s$TARGET%s' % default
        env['ASCOMSTR'] =       '%sAssemblingยทยทยทยทยท %s$TARGET%s' % default
        env['ASPPCOMSTR'] =     '%sAssemblingยทยทยทยทยท %s$TARGET%s' % default
        env['LINKCOMSTR'] =     '%sLinkingยทยทยทยทยทยทยทยท %s$TARGET%s' % linking
        env['RANLIBCOMSTR'] =   '%sIndexingยทยทยทยทยทยทยท %s$TARGET%s' % library
        env['ARCOMSTR'] =       '%sCreate Libraryยท %s$TARGET%s' % library

        # for shared libraries
        env['SHCCCOMSTR'] =     '%sCompiling C (shared)ยทยทยท %s$TARGET%s' % default
        env['SHCXXCOMSTR'] =    '%sCompiling C++ (shared)ยท %s$TARGET%s' % default
        env['SHLINKCOMSTR'] =   '%sLinking (shared)ยทยทยทยทยทยทยท %s$TARGET%s' % linking

        env['INSTALLSTR'] =     "%s.----Install--- %s$SOURCE\n" \
                                "%s'-------------> %s$TARGET%s" % install

        env['STRIPCOMSTR'] =    '%sStrippingยทยทยทยทยทยท %s$TARGET%s' % linking

        env['SIZECOMSTR'] =     '%sMemory usageยทยทยท %s$SOURCE%s' % default
        env['HEXCOMSTR'] =      '%sIntel-Hex Fileยท %s$TARGET%s' % default
        env['BINCOMSTR'] =      '%sBinary Fileยทยทยทยท %s$TARGET%s' % default
        env['LSSCOMSTR'] =      '%sExt. Listingยทยทยท %s$TARGET%s' % default
        env['SYMBOLSCOMSTR'] =  '%sSymbolsยทยทยทยทยทยทยทยท %s$SOURCE%s' % default


def exists(env):
    return True
