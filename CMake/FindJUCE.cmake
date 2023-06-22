include(CPM)

if(${LEGACY})
    CPMAddPackage(
            NAME JUCE
            GITHUB_REPOSITORY kcoul/JUCE
            GIT_TAG origin/xcode8_elcap)
else()
    CPMAddPackage(
            NAME JUCE
            GITHUB_REPOSITORY kcoul/JUCE
            GIT_TAG origin/master)
endif()