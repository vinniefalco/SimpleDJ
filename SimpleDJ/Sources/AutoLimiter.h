// Uses an envelope follower to scale the audio signal into range
// and prevent clipping. If audio signal is already between 0..1, does
// nothing. 
//
// For musical purposes attack=10ms and release=500ms seems to work well.
//
template <int Channels=2, typename Value=float>
class AutoLimiter
{
public:
  void Setup (double sampleRate, double attackMs = 10, double releaseMs = 500)
  {
    m_a = Value (pow (0.01, 1.0 / (attackMs * sampleRate * 0.001)));
    m_r = Value (pow (0.01, 1.0 / (releaseMs * sampleRate * 0.001)));

    for (int i=0; i<Channels; i++)
      m_env[i] = 1;
  }

  // bias the input stream to prevent denormals
  static Value with_dc (Value val)
  {
    static const Value anti_denormal = Value(1e-20);
    return val + anti_denormal;
  }

  void Process (int samples, Value* const* dest)
  {
    for (int i=0; i<Channels; i++)
    {
      Value* cur = dest [i];

      Value e = m_env [i];
      
      for (int n = samples; n; n--)
      {
        Value v = with_dc (std::abs (*cur));

        if (v > e)
          e = m_a * (e - v) + v;
        else
          e = m_r * (e - v) + v;

        if (e > 1)
          *cur = *cur / e;

        cur++;
      }

      m_env[i] = e;
    }
  }

public:
  Value m_a;
  Value m_r;
  Value m_env [Channels];
};
