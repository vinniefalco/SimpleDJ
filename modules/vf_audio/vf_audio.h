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

/** Include this to get the @ref vf_audio module.

    @file vf_audio.h
    @ingroup vf_audio
*/

#ifndef VF_AUDIO_VFHEADER
#define VF_AUDIO_VFHEADER

/*============================================================================*/
/**
    Audio signal processing utilities.

    This is a small collection of classes for performing audio signal
    processing.

    @defgroup vf_audio vf_audio
*/

#include "../vf_core/vf_core.h"

#include "modules/juce_audio_basics/juce_audio_basics.h"

namespace vf
{

#include "buffers/vf_AudioBufferPool.h"
#include "buffers/vf_AudioSampleBufferArray.h"
#include "sources/vf_NoiseAudioSource.h"
#include "buffers/vf_ScopedAudioSampleBuffer.h"

}

#endif

