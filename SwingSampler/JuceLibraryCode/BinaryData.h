/* =========================================================================================

   This is an auto-generated file, created by The Introjucer 3.0.0
   Do not edit anything in this file!

*/

namespace BinaryData
{
    extern const char*   trans_cn;
    const int            trans_cnSize = 932;

    extern const char*   piano_mp3;
    const int            piano_mp3Size = 31536;

    extern const char*   taiko_mp3;
    const int            taiko_mp3Size = 17744;

    extern const char*   violin_mp3;
    const int            violin_mp3Size = 52014;

    extern const char*   bg_jpg;
    const int            bg_jpgSize = 105451;

    extern const char*   icon_png;
    const int            icon_pngSize = 19523;

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
