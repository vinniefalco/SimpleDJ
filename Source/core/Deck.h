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

#ifndef DECK_HEADER
#define DECK_HEADER

#include "Mixer.h"
#include "Params.h"
#include "Playable.h"

/** A Mixer Source that streams a Playable.
*/
class Deck
  : public Mixer::Source
{
public:
  typedef Mixer::Levels Levels;

  /** Synchronizes the Deck state.
  */
  class Listener
  {
  public:
    /** Called when the output level changes.
    */
    virtual void onDeckLevels (Deck* deck, Levels level) { }

    /** Called when the Playable changes.
    */
    virtual void onDeckSelect (Deck* deck, Playable::Ptr playable) { }
  };

public:
  typedef ReferenceCountedObjectPtr <Deck> Ptr;

  static Deck::Ptr New (vf::CallQueue& mixerThread);

  /** Parameters.

      "vol"     [0...1]     Volume fader.
      "play"    0 or 1      Play state (off/on)
      "speed"   [-1...1]    Playback speed (0=normal)
  */
  Params const& param;

  /** Add or remove a Listener.
  */
  virtual void addListener (Listener* listener, vf::CallQueue& thread) = 0;
  virtual void removeListener (Listener* listener) = 0;

  /** Change the current Playable.

      Use nullptr to unload.
  */
  virtual void selectPlayable (Playable::Ptr playable) = 0;

protected:
  Deck (vf::CallQueue& mixerThread, Params& params);
};

#endif
