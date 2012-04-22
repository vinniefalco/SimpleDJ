/* =========================================================================================

   This is an auto-generated file, created by The Introjucer 3.0.0
   Do not edit anything in this file!

*/

namespace BinaryData
{
    extern const char*   trans_cn;
    const int            trans_cnSize = 905;

    extern const char*   cpter_mp3;
    const int            cpter_mp3Size = 4925;

    extern const char*   human_mp3;
    const int            human_mp3Size = 3514;

    extern const char*   human_png;
    const int            human_pngSize = 20986;

    extern const char*   lost_mp3;
    const int            lost_mp3Size = 4612;

    extern const char*   remove_mp3;
    const int            remove_mp3Size = 4612;

    extern const char*   start_mp3;
    const int            start_mp3Size = 8373;

    extern const char*   win_mp3;
    const int            win_mp3Size = 15008;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();

    //==============================================================================
    // This class acts as an ImageProvider that will access the BinaryData images
    class ImageProvider  : public juce::ComponentBuilder::ImageProvider
    {
    public:
        ImageProvider() noexcept {}

        juce::Image getImageForIdentifier (const juce::var& imageIdentifier)
        {
            int dataSize = 0;
            const char* const data = getNamedResource (imageIdentifier.toString().toUTF8(), dataSize);

            if (data != nullptr)
                return juce::ImageCache::getFromMemory (data, dataSize);

            return juce::Image();
        }

        juce::var getIdentifierForImage (const juce::Image&)  { return juce::var(); }
    };
}
