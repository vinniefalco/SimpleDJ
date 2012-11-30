# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_8068DBC5=1" -I /usr/include -I /usr/include/freetype2 -I ../Jucer/JuceLibraryCode -I ../../Extern/JUCE -I ../../Extern/VFLib -I ../../Source/gui -I ../../Source/core
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_8068DBC5=1" -I /usr/include -I /usr/include/freetype2 -I ../Jucer/JuceLibraryCode -I ../../Extern/JUCE -I ../../Extern/VFLib -I ../../Source/gui -I ../../Source/core
  TARGET := SimpleDJ
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_8068DBC5=1" -I /usr/include -I /usr/include/freetype2 -I ../Jucer/JuceLibraryCode -I ../../Extern/JUCE -I ../../Extern/VFLib -I ../../Source/gui -I ../../Source/core
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_8068DBC5=1" -I /usr/include -I /usr/include/freetype2 -I ../Jucer/JuceLibraryCode -I ../../Extern/JUCE -I ../../Extern/VFLib -I ../../Source/gui -I ../../Source/core
  TARGET := SimpleDJ
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/Deck_fa091e3a.o \
  $(OBJDIR)/FileManager_917915ea.o \
  $(OBJDIR)/Mixer_6d530262.o \
  $(OBJDIR)/Param_a697ace6.o \
  $(OBJDIR)/ParamImp_31dd9890.o \
  $(OBJDIR)/Params_3011fd97.o \
  $(OBJDIR)/ReaderPlayable_8812b02.o \
  $(OBJDIR)/CDeck_b40f9f39.o \
  $(OBJDIR)/CDeckFader_c094d707.o \
  $(OBJDIR)/CDeckLevelMeter_cb0b8e3e.o \
  $(OBJDIR)/CDeckMixer_2f79e81a.o \
  $(OBJDIR)/CLevelMeter_922b26b5.o \
  $(OBJDIR)/CMain_91c8a049.o \
  $(OBJDIR)/CMainWindow_29556159.o \
  $(OBJDIR)/CParamToggleButton_d677418d.o \
  $(OBJDIR)/CSpeedControl_43f18826.o \
  $(OBJDIR)/CApp_723bc09b.o \
  $(OBJDIR)/vf_core_cae091f1.o \
  $(OBJDIR)/vf_concurrent_61d393e1.o \
  $(OBJDIR)/vf_gui_33d46993.o \
  $(OBJDIR)/vf_freetype_20a238bf.o \
  $(OBJDIR)/vf_taglib_962ede49.o \
  $(OBJDIR)/juce_audio_basics_454b9ecb.o \
  $(OBJDIR)/juce_audio_devices_a68a6cc9.o \
  $(OBJDIR)/juce_audio_formats_d50bb669.o \
  $(OBJDIR)/juce_audio_processors_a2067d83.o \
  $(OBJDIR)/juce_core_f6491dad.o \
  $(OBJDIR)/juce_data_structures_d80ae1a9.o \
  $(OBJDIR)/juce_events_698aeba1.o \
  $(OBJDIR)/juce_graphics_5c9f1285.o \
  $(OBJDIR)/juce_gui_basics_f79baf81.o \
  $(OBJDIR)/juce_gui_extra_d475cd49.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking SimpleDJ
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning SimpleDJ
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

strip:
	@echo Stripping SimpleDJ
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/Deck_fa091e3a.o: ../../Source/core/Deck.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Deck.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FileManager_917915ea.o: ../../Source/core/FileManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FileManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Mixer_6d530262.o: ../../Source/core/Mixer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Mixer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Param_a697ace6.o: ../../Source/core/Param.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Param.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ParamImp_31dd9890.o: ../../Source/core/ParamImp.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ParamImp.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Params_3011fd97.o: ../../Source/core/Params.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Params.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ReaderPlayable_8812b02.o: ../../Source/core/ReaderPlayable.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ReaderPlayable.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CDeck_b40f9f39.o: ../../Source/gui/CDeck.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CDeck.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CDeckFader_c094d707.o: ../../Source/gui/CDeckFader.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CDeckFader.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CDeckLevelMeter_cb0b8e3e.o: ../../Source/gui/CDeckLevelMeter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CDeckLevelMeter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CDeckMixer_2f79e81a.o: ../../Source/gui/CDeckMixer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CDeckMixer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CLevelMeter_922b26b5.o: ../../Source/gui/CLevelMeter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CLevelMeter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CMain_91c8a049.o: ../../Source/gui/CMain.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CMain.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CMainWindow_29556159.o: ../../Source/gui/CMainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CMainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CParamToggleButton_d677418d.o: ../../Source/gui/CParamToggleButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CParamToggleButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CSpeedControl_43f18826.o: ../../Source/gui/CSpeedControl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CSpeedControl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CApp_723bc09b.o: ../../Source/gui/CApp.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CApp.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_core_cae091f1.o: ../../Extern/VFLib/modules/vf_core/vf_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_concurrent_61d393e1.o: ../../Extern/VFLib/modules/vf_concurrent/vf_concurrent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_concurrent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_gui_33d46993.o: ../../Extern/VFLib/modules/vf_gui/vf_gui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_gui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_freetype_20a238bf.o: ../../Extern/VFLib/modules/vf_freetype/vf_freetype.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_freetype.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_taglib_962ede49.o: ../../Extern/VFLib/modules/vf_taglib/vf_taglib.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_taglib.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_454b9ecb.o: ../../Extern/JUCE/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a68a6cc9.o: ../../Extern/JUCE/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d50bb669.o: ../../Extern/JUCE/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_a2067d83.o: ../../Extern/JUCE/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_f6491dad.o: ../../Extern/JUCE/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_d80ae1a9.o: ../../Extern/JUCE/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_698aeba1.o: ../../Extern/JUCE/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_5c9f1285.o: ../../Extern/JUCE/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_f79baf81.o: ../../Extern/JUCE/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_d475cd49.o: ../../Extern/JUCE/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
