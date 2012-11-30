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
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../Extern/JUCE -I ../../../Extern/VFLib
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../Extern/JUCE -I ../../../Extern/VFLib
  TARGET := SimpleDJ
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../Extern/JUCE -I ../../../Extern/VFLib
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../Extern/JUCE -I ../../../Extern/VFLib
  TARGET := SimpleDJ
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/Deck_686cfd35.o \
  $(OBJDIR)/FileManager_dc66768f.o \
  $(OBJDIR)/Mixer_cb6b02c7.o \
  $(OBJDIR)/Param_4afad4b.o \
  $(OBJDIR)/ParamImp_fcf3820b.o \
  $(OBJDIR)/Params_94fa09d2.o \
  $(OBJDIR)/ReaderPlayable_6662cc3d.o \
  $(OBJDIR)/CApp_a6a0f0ca.o \
  $(OBJDIR)/CDeckFader_369ae7f6.o \
  $(OBJDIR)/CDeck_c5074ea.o \
  $(OBJDIR)/CDeckLevelMeter_e25baaf.o \
  $(OBJDIR)/CDeckMixer_a57ff909.o \
  $(OBJDIR)/CLevelMeter_dce733a6.o \
  $(OBJDIR)/CMain_ea0975fa.o \
  $(OBJDIR)/CMainWindow_74116e4a.o \
  $(OBJDIR)/CParamToggleButton_9950f37c.o \
  $(OBJDIR)/CSpeedControl_cfde1cd7.o \
  $(OBJDIR)/vf_core_a9705a20.o \
  $(OBJDIR)/vf_concurrent_9058d90.o \
  $(OBJDIR)/vf_freetype_2c80e1ae.o \
  $(OBJDIR)/vf_gui_6c67182.o \
  $(OBJDIR)/vf_taglib_9a30f6f8.o \

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

$(OBJDIR)/Deck_686cfd35.o: ../../Sources/Deck.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Deck.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FileManager_dc66768f.o: ../../Sources/FileManager.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FileManager.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Mixer_cb6b02c7.o: ../../Sources/Mixer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Mixer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Param_4afad4b.o: ../../Sources/Param.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Param.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ParamImp_fcf3820b.o: ../../Sources/ParamImp.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ParamImp.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Params_94fa09d2.o: ../../Sources/Params.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Params.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ReaderPlayable_6662cc3d.o: ../../Sources/ReaderPlayable.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ReaderPlayable.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CApp_a6a0f0ca.o: ../../Sources/CApp.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CApp.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CDeckFader_369ae7f6.o: ../../Sources/CDeckFader.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CDeckFader.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CDeck_c5074ea.o: ../../Sources/CDeck.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CDeck.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CDeckLevelMeter_e25baaf.o: ../../Sources/CDeckLevelMeter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CDeckLevelMeter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CDeckMixer_a57ff909.o: ../../Sources/CDeckMixer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CDeckMixer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CLevelMeter_dce733a6.o: ../../Sources/CLevelMeter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CLevelMeter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CMain_ea0975fa.o: ../../Sources/CMain.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CMain.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CMainWindow_74116e4a.o: ../../Sources/CMainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CMainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CParamToggleButton_9950f37c.o: ../../Sources/CParamToggleButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CParamToggleButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CSpeedControl_cfde1cd7.o: ../../Sources/CSpeedControl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CSpeedControl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_core_a9705a20.o: ../../../Extern/VFLib/modules/vf_core/vf_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_concurrent_9058d90.o: ../../../Extern/VFLib/modules/vf_concurrent/vf_concurrent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_concurrent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_freetype_2c80e1ae.o: ../../../Extern/VFLib/modules/vf_freetype/vf_freetype.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_freetype.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_gui_6c67182.o: ../../../Extern/VFLib/modules/vf_gui/vf_gui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_gui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vf_taglib_9a30f6f8.o: ../../../Extern/VFLib/modules/vf_taglib/vf_taglib.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vf_taglib.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
