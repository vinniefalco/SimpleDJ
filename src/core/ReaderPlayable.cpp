/*
  ==============================================================================

  Copyright (c) 2012 by Vinnie Falco

  This file is provided under the terms of the MIT License:

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ==============================================================================
*/

#include "StandardIncludes.h"
#include "ReaderPlayable.h"

#include "vf_taglib/vf_taglib.h"

//==============================================================================

/** Quick and dirty interface to TagLib to retrieve metadata.
*/
class MetadataReader
{
public:
  MetadataReader (String path)
  {
#if (JUCE_MAC || JUCE_LINUX)
    TagLib::FileRef f (path.toUTF8 ());
#else
    TagLib::FileRef f (path.toWideCharPointer ());
#endif

    m_album = f.tag()->album().toWString ().c_str ();

    m_artist = f.tag()->artist().toWString ().c_str ();

    m_title = f.tag()->title().toWString ().c_str ();
  }

  String getAlbum () const { return m_album; }
  String getArtist () const { return m_artist; }
  String getTitle () const { return m_title; }

private:
  String m_album;
  String m_artist;
  String m_title;
};

//==============================================================================

ReaderPlayable::ReaderPlayable (String path, AudioFormatReader* formatReader)
  : m_source (new AudioFormatReaderSource (formatReader, true))
  , m_formatReader (*formatReader)
{
  // Extract metadata
  MetadataReader meta (path);
  m_meta.album =  meta.getAlbum ();
  m_meta.artist = meta.getArtist ();
  m_meta.title =  meta.getTitle ();
}

ReaderPlayable::~ReaderPlayable ()
{
}

double ReaderPlayable::getSampleRate ()
{
  return m_formatReader.sampleRate;
}

void ReaderPlayable::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
  m_source->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void ReaderPlayable::releaseResources()
{
  m_source->releaseResources ();
}

void ReaderPlayable::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
  m_source->getNextAudioBlock (bufferToFill);
}

Playable::Metadata ReaderPlayable::getMetadata ()
{
  return m_meta;
}

Playable::Ptr ReaderPlayable::openFromFile (String path, AudioFormat* format)
{
  Playable::Ptr playable;

  InputStream* inputStream = new FileInputStream (path);

  if (inputStream != nullptr)
  {
    AudioFormatReader* formatReader = format->createReaderFor (inputStream, true);

    if (formatReader != nullptr)
    {
      playable = new ReaderPlayable (path, formatReader);
    }
  }

  return playable;
}
