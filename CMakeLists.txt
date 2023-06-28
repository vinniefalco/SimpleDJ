cmake_minimum_required(VERSION 3.16.3)

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

juce_add_module(lib/vflib/modules/vf_audio ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_bzip2 ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_concurrent ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_core ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_db ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_freetype ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_gui ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_lua ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_luabridge ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_sqlite ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_taglib ALIAS_NAMESPACE vf)
juce_add_module(lib/vflib/modules/vf_unfinished ALIAS_NAMESPACE vf)

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
        src/core/AutoLimiter.h #Add headers so they show up in Xcode
        src/core/Deck.cpp
        src/core/Deck.h
        src/core/FileManager.cpp
        src/core/FileManager.h
        src/core/Mixer.cpp
        src/core/Mixer.h
        src/core/Param.cpp
        src/core/Param.h
        src/core/ParamImp.cpp
        src/core/ParamImp.h
        src/core/Params.cpp
        src/core/Params.h
        src/core/PeakDetector.h
        src/core/Playable.h
        src/core/ReaderPlayable.cpp
        src/core/ReaderPlayable.h
        src/core/StandardIncludes.h
        src/gui/CApp.cpp
        src/gui/CApp.h
        src/gui/CDeck.cpp
        src/gui/CDeck.h
        src/gui/CDeckFader.cpp
        src/gui/CDeckFader.h
        src/gui/CDeckLevelMeter.cpp
        src/gui/CDeckLevelMeter.h
        src/gui/CDeckMixer.cpp
        src/gui/CDeckMixer.h
        src/gui/CLevelMeter.cpp
        src/gui/CLevelMeter.h
        src/gui/CMain.cpp
        src/gui/CMain.h
        src/gui/CMainWindow.cpp
        src/gui/CMainWindow.h
        src/gui/CParamToggleButton.cpp
        src/gui/CParamToggleButton.h
        src/gui/CSpeedControl.cpp
        src/gui/CSpeedControl.h)

target_include_directories(${TargetName} PUBLIC
        lib/vflib
        lib/vflib/AppConfigTemplate
        src/core)

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
        #Beyond here be dragons...
        #vf::vf_audio
        #vf::vf_bzip2
        #vf::vf_db
        #vf::vf_lua
        #vf::vf_luabridge
        #vf::vf_sqlite
        #vf::vf_unfinished
        )
