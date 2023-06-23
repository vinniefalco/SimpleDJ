cmake_minimum_required(VERSION 3.17.3)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

# The policy uses the download time for timestamp, instead of the timestamp in the archive. This
# allows for proper rebuilds when a project's url changes
if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif ()

#
# 2. Project-wide setup
#
project(SimpleDJ)
set(SDJ_TAG "[SIMPLE-DJ]")
message("${SDJ_TAG} building for ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
set(TargetName ${PROJECT_NAME})

#
# 3. Dependencies
#
include(CPM)
find_package(JUCE)

juce_add_module(Extern/VFLib/modules/vf_audio ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_bzip2 ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_concurrent ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_core ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_db ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_freetype ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_gui ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_lua ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_luabridge ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_sqlite ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_taglib ALIAS_NAMESPACE vf)
juce_add_module(Extern/VFLib/modules/vf_unfinished ALIAS_NAMESPACE vf)

juce_add_gui_app(${TargetName}
        PRODUCT_NAME "SimpleDJ"
        VERSION 0.1
        BUNDLE_ID "com.kcoul.SimpleDJ"
        REQUIRES_FULL_SCREEN TRUE
        MICROPHONE_PERMISSION_ENABLED TRUE
        MICROPHONE_PERMISSION_TEXT "Microphone access may be required to use SimpleDJ"
        BACKGROUND_AUDIO_ENABLED TRUE
        BACKGROUND_BLE_ENABLED TRUE
        IPHONE_SCREEN_ORIENTATIONS UIInterfaceOrientationLandscape
        IPAD_SCREEN_ORIENTATIONS UIInterfaceOrientationLandscape)

juce_generate_juce_header(${TargetName})
target_compile_features(${TargetName} PUBLIC cxx_std_17)

target_sources(${TargetName} PRIVATE
        Source/core/AutoLimiter.h #Add headers so they show up in Xcode
        Source/core/Deck.cpp
        Source/core/Deck.h
        Source/core/FileManager.cpp
        Source/core/FileManager.h
        Source/core/Mixer.cpp
        Source/core/Mixer.h
        Source/core/Param.cpp
        Source/core/Param.h
        Source/core/ParamImp.cpp
        Source/core/ParamImp.h
        Source/core/Params.cpp
        Source/core/Params.h
        Source/core/PeakDetector.h
        Source/core/Playable.h
        Source/core/ReaderPlayable.cpp
        Source/core/ReaderPlayable.h
        Source/core/StandardIncludes.h
        Source/gui/CApp.cpp
        Source/gui/CApp.h
        Source/gui/CDeck.cpp
        Source/gui/CDeck.h
        Source/gui/CDeckFader.cpp
        Source/gui/CDeckFader.h
        Source/gui/CDeckLevelMeter.cpp
        Source/gui/CDeckLevelMeter.h
        Source/gui/CDeckMixer.cpp
        Source/gui/CDeckMixer.h
        Source/gui/CLevelMeter.cpp
        Source/gui/CLevelMeter.h
        Source/gui/CMain.cpp
        Source/gui/CMain.h
        Source/gui/CMainWindow.cpp
        Source/gui/CMainWindow.h
        Source/gui/CParamToggleButton.cpp
        Source/gui/CParamToggleButton.h
        Source/gui/CSpeedControl.cpp
        Source/gui/CSpeedControl.h)

target_include_directories(${TargetName} PUBLIC
        Extern/VFLib
        Extern/VFLib/AppConfigTemplate
        Source/core)

if (CMAKE_SYSTEM_NAME MATCHES "^(Darwin|Linux|Windows)")
    #enables chooser->browseForFileToOpen()
    target_compile_definitions(${TargetName} PRIVATE JUCE_MODAL_LOOPS_PERMITTED=1)
elseif (CMAKE_SYSTEM_NAME MATCHES "^(iOS|Android)")
    target_compile_definitions(${TargetName} PRIVATE JUCE_CONTENT_SHARING=1)
endif()

target_compile_definitions(${TargetName} PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${TargetName},JUCE_PROJECT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${TargetName},JUCE_VERSION>"
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_BUNDLE_ID="com.kcoul.SimpleDJ"
        MICROPHONE_PERMISSION_ENABLED TRUE
        MICROPHONE_PERMISSION_TEXT="This app requires permission for Microphone access"
        BLUETOOTH_PERMISSION_ENABLED TRUE
        BLUETOOTH_PERMISSION_TEXT="This app requires bluetooth access"
        )

if (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set_xcode_property(${TargetName} PRODUCT_BUNDLE_IDENTIFIER "com.kcoul.SimpleDJ" All)
endif()

target_link_libraries(${TargetName} PRIVATE
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_osc
        juce::juce_gui_basics
        juce::juce_gui_extra
        vf::vf_concurrent
        vf::vf_core
        vf::vf_freetype
        vf::vf_gui
        vf::vf_taglib
        #Beyond here is the sandbox
        #vf::vf_audio
        #vf::vf_bzip2
        #vf::vf_db
        #vf::vf_lua
        #vf::vf_luabridge
        #vf::vf_sqlite
        #vf::vf_unfinished
        )
