/*============================================================================*/
/*
  Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
  See the file GNU_GPL_v2.txt for full licensing terms.

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 51
  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
/*============================================================================*/

#ifndef VF_BIND_VFHEADER
#define VF_BIND_VFHEADER

#if JUCE_MSVC
using std::bind;
using std::placeholders::_1;

#elif JUCE_IOS || JUCE_MAC
#if VF_USE_BOOST
using boost::bind;
using boost::function;
using ::_1;
using ::_2;
#else
using std::tr1::bind;
using std::tr1::function;
using std::tr1::placeholders::_1;
using std::tr1::placeholders::_2;
#endif

#else
#error Unknown platform in vf_Bind.h

#endif

#endif
