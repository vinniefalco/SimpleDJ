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

#ifndef PEAKDETECTOR_HEADER
#define PEAKDETECTOR_HEADER

// Peak level detector with decay time
template <int Channels = 2, typename ValueType = float>
class PeakDetector
{
private:
  double m_sampleRate;
  int m_millisecondsDecay;
  ValueType m_peak [Channels];

  static bool isnan (ValueType value)
  {
    volatile ValueType v = value;
    return v != v;
  }

public:
  PeakDetector ()
  {
    for (int i = 0; i < Channels; ++i)
      m_peak [i] = 0;
  }

  void setup (double sampleRate, int millisecondsDecay = 300)
  {
    m_sampleRate = sampleRate;
    m_millisecondsDecay = millisecondsDecay;
  }

  void process (int samples, ValueType const* const* src)
  {
    ValueType maxDeltaPeak = ValueType (1000 * samples) / ValueType (m_sampleRate * m_millisecondsDecay);

    for (int i = 0; i<Channels; i++)
    {
      ValueType peak = 0;
      const ValueType* cur = src[i];
      for (int n = samples; n; n--)
      {
        ValueType v = abs (*cur++);
        if (peak < v)
          peak = v;
      }

      if (peak>1)
        peak=1;

      ValueType minPeak = m_peak[i] - maxDeltaPeak;
      if (peak < minPeak)
        peak = minPeak;

      if (peak < 1e-8)
        peak = 0;

      m_peak[i] = peak;
    }
  }

  ValueType operator [] (const int channel) const
  {
    return m_peak [channel];
  }
};

#endif
