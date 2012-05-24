/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCER_PROJECTEXPORT_ANDROID_JUCEHEADER__
#define __JUCER_PROJECTEXPORT_ANDROID_JUCEHEADER__

#include "jucer_ProjectExporter.h"


//==============================================================================
class AndroidProjectExporter  : public ProjectExporter
{
public:
    //==============================================================================
    static const char* getNameAndroid()         { return "Android Project"; }
    static const char* getValueTreeTypeName()   { return "ANDROID"; }

    static AndroidProjectExporter* createForSettings (Project& project, const ValueTree& settings)
    {
        if (settings.hasType (getValueTreeTypeName()))
            return new AndroidProjectExporter (project, settings);

        return nullptr;
    }

    //==============================================================================
    AndroidProjectExporter (Project& project_, const ValueTree& settings_)
        : ProjectExporter (project_, settings_)
    {
        name = getNameAndroid();

        if (getTargetLocationString().isEmpty())
            getTargetLocationValue() = getDefaultBuildsRootFolder() + "Android";

        if (getActivityClassPath().isEmpty())
            getActivityClassPathValue() = createDefaultClassName();

        if (getSDKPathString().isEmpty())       getSDKPathValue() = "${user.home}/SDKs/android-sdk";
        if (getNDKPathString().isEmpty())       getNDKPathValue() = "${user.home}/SDKs/android-ndk";

        if (getMinimumSDKVersionString().isEmpty())
            getMinimumSDKVersionValue() = 8;

        if (getInternetNeededValue().toString().isEmpty())
            getInternetNeededValue() = true;

        if (getKeyStoreValue().getValue().isVoid())         getKeyStoreValue()      = "${user.home}/.android/debug.keystore";
        if (getKeyStorePassValue().getValue().isVoid())     getKeyStorePassValue()  = "android";
        if (getKeyAliasValue().getValue().isVoid())         getKeyAliasValue()      = "androiddebugkey";
        if (getKeyAliasPassValue().getValue().isVoid())     getKeyAliasPassValue()  = "android";
    }

    //==============================================================================
    int getLaunchPreferenceOrderForCurrentOS()
    {
       #if JUCE_ANDROID
        return 1;
       #else
        return 0;
       #endif
    }

    bool isAndroid() const                      { return true; }
    bool isPossibleForCurrentProject()          { return projectType.isGUIApplication(); }
    bool usesMMFiles() const                    { return false; }
    bool canCopeWithDuplicateFiles()            { return false; }

    void launchProject()
    {
    }

    void createPropertyEditors (PropertyListBuilder& props)
    {
        ProjectExporter::createPropertyEditors (props);

        props.add (new TextPropertyComponent (getActivityClassPathValue(), "Android Activity class name", 256, false),
                   "The full java class name to use for the app's Activity class.");

        props.add (new TextPropertyComponent (getSDKPathValue(), "Android SDK Path", 1024, false),
                   "The path to the Android SDK folder on the target build machine");

        props.add (new TextPropertyComponent (getNDKPathValue(), "Android NDK Path", 1024, false),
                   "The path to the Android NDK folder on the target build machine");

        props.add (new TextPropertyComponent (getMinimumSDKVersionValue(), "Minimum SDK version", 32, false),
                   "The number of the minimum version of the Android SDK that the app requires");

        props.add (new BooleanPropertyComponent (getCPP11EnabledValue(), "Enable C++11 features", "Enable the -std=c++0x flag"),
                   "If enabled, this will set the -std=c++0x flag for the build.");

        props.add (new BooleanPropertyComponent (getInternetNeededValue(), "Internet Access", "Specify internet access permission in the manifest"),
                   "If enabled, this will set the android.permission.INTERNET flag in the manifest.");

        props.add (new BooleanPropertyComponent (getAudioRecordNeededValue(), "Audio Input Required", "Specify audio record permission in the manifest"),
                   "If enabled, this will set the android.permission.RECORD_AUDIO flag in the manifest.");

        props.add (new TextPropertyComponent (getOtherPermissionsValue(), "Custom permissions", 2048, false),
                   "A space-separated list of other permission flags that should be added to the manifest.");

        props.add (new TextPropertyComponent (getKeyStoreValue(), "Key Signing: key.store", 2048, false),
                   "The key.store value, used when signing the package.");
        props.add (new TextPropertyComponent (getKeyStorePassValue(), "Key Signing: key.store.password", 2048, false),
                   "The key.store password, used when signing the package.");
        props.add (new TextPropertyComponent (getKeyAliasValue(), "Key Signing: key.alias", 2048, false),
                   "The key.alias value, used when signing the package.");
        props.add (new TextPropertyComponent (getKeyAliasPassValue(), "Key Signing: key.alias.password", 2048, false),
                   "The key.alias password, used when signing the package.");
    }

    Value getActivityClassPathValue()      { return getSetting (Ids::androidActivityClass); }
    String getActivityClassPath() const    { return settings [Ids::androidActivityClass]; }
    Value getSDKPathValue()                { return getSetting (Ids::androidSDKPath); }
    String getSDKPathString() const        { return settings [Ids::androidSDKPath]; }
    Value getNDKPathValue()                { return getSetting (Ids::androidNDKPath); }
    String getNDKPathString() const        { return settings [Ids::androidNDKPath]; }

    Value getKeyStoreValue()               { return getSetting (Ids::androidKeyStore); }
    String getKeyStoreString() const       { return settings [Ids::androidKeyStore]; }
    Value getKeyStorePassValue()           { return getSetting (Ids::androidKeyStorePass); }
    String getKeyStorePassString() const   { return settings [Ids::androidKeyStorePass]; }
    Value getKeyAliasValue()               { return getSetting (Ids::androidKeyAlias); }
    String getKeyAliasString() const       { return settings [Ids::androidKeyAlias]; }
    Value getKeyAliasPassValue()           { return getSetting (Ids::androidKeyAliasPass); }
    String getKeyAliasPassString() const   { return settings [Ids::androidKeyAliasPass]; }

    Value getInternetNeededValue()         { return getSetting (Ids::androidInternetNeeded); }
    bool getInternetNeeded() const         { return settings [Ids::androidInternetNeeded]; }
    Value getAudioRecordNeededValue()      { return getSetting (Ids::androidMicNeeded); }
    bool getAudioRecordNeeded() const      { return settings [Ids::androidMicNeeded]; }
    Value getMinimumSDKVersionValue()      { return getSetting (Ids::androidMinimumSDK); }
    String getMinimumSDKVersionString() const { return settings [Ids::androidMinimumSDK]; }
    Value getOtherPermissionsValue()       { return getSetting (Ids::androidOtherPermissions); }
    String getOtherPermissions() const     { return settings [Ids::androidOtherPermissions]; }

    Value getCPP11EnabledValue()           { return getSetting (Ids::androidCpp11); }
    bool isCPP11Enabled() const            { return settings [Ids::androidCpp11]; }

    String createDefaultClassName() const
    {
        String s (project.getBundleIdentifier().toString().toLowerCase());

        if (s.length() > 5
            && s.containsChar ('.')
            && s.containsOnly ("abcdefghijklmnopqrstuvwxyz_.")
            && ! s.startsWithChar ('.'))
        {
            if (! s.endsWithChar ('.'))
                s << ".";
        }
        else
        {
            s = "com.yourcompany.";
        }

        return s + CodeHelpers::makeValidIdentifier (project.getProjectFilenameRoot(), false, true, false);
    }

    //==============================================================================
    void create (const OwnedArray<LibraryModule>& modules) const
    {
        const File target (getTargetFolder());
        const File jniFolder (target.getChildFile ("jni"));

        copyActivityJavaFiles (modules);
        createDirectoryOrThrow (jniFolder);
        createDirectoryOrThrow (target.getChildFile ("res").getChildFile ("values"));
        createDirectoryOrThrow (target.getChildFile ("libs"));
        createDirectoryOrThrow (target.getChildFile ("bin"));

        {
            ScopedPointer<XmlElement> manifest (createManifestXML());
            writeXmlOrThrow (*manifest, target.getChildFile ("AndroidManifest.xml"), "utf-8", 100, true);
        }

        writeApplicationMk (jniFolder.getChildFile ("Application.mk"));
        writeAndroidMk (jniFolder.getChildFile ("Android.mk"));

        {
            ScopedPointer<XmlElement> antBuildXml (createAntBuildXML());
            writeXmlOrThrow (*antBuildXml, target.getChildFile ("build.xml"), "UTF-8", 100);
        }

        writeProjectPropertiesFile (target.getChildFile ("project.properties"));
        writeLocalPropertiesFile (target.getChildFile ("local.properties"));
        writeStringsFile (target.getChildFile ("res/values/strings.xml"));

        const Image bigIcon (getBigIcon());
        const Image smallIcon (getSmallIcon());

        if (bigIcon.isValid() && smallIcon.isValid())
        {
            const int step = jmax (bigIcon.getWidth(), bigIcon.getHeight()) / 8;
            writeIcon (target.getChildFile ("res/drawable-xhdpi/icon.png"), getBestIconForSize (step * 8, false));
            writeIcon (target.getChildFile ("res/drawable-hdpi/icon.png"),  getBestIconForSize (step * 6, false));
            writeIcon (target.getChildFile ("res/drawable-mdpi/icon.png"),  getBestIconForSize (step * 4, false));
            writeIcon (target.getChildFile ("res/drawable-ldpi/icon.png"),  getBestIconForSize (step * 3, false));
        }
        else
        {
            writeIcon (target.getChildFile ("res/drawable-mdpi/icon.png"), bigIcon.isValid() ? bigIcon : smallIcon);
        }
    }

protected:
    //==============================================================================
    class AndroidBuildConfiguration  : public BuildConfiguration
    {
    public:
        AndroidBuildConfiguration (Project& project, const ValueTree& settings)
            : BuildConfiguration (project, settings)
        {
            if (getArchitectures().isEmpty())
                getArchitecturesValue() = "armeabi armeabi-v7a";
        }

        Value getArchitecturesValue()           { return getValue (Ids::androidArchitectures); }
        String getArchitectures() const         { return config [Ids::androidArchitectures]; }

        void createPropertyEditors (PropertyListBuilder& props)
        {
            createBasicPropertyEditors (props);

            props.add (new TextPropertyComponent (getArchitecturesValue(), "Architectures", 256, false),
                       "A list of the ARM architectures to build (for a fat binary).");
        }
    };

    BuildConfiguration::Ptr createBuildConfig (const ValueTree& settings) const
    {
        return new AndroidBuildConfiguration (project, settings);
    }

private:
    //==============================================================================
    XmlElement* createManifestXML() const
    {
        XmlElement* manifest = new XmlElement ("manifest");

        manifest->setAttribute ("xmlns:android", "http://schemas.android.com/apk/res/android");
        manifest->setAttribute ("android:versionCode", "1");
        manifest->setAttribute ("android:versionName", "1.0");
        manifest->setAttribute ("package", getActivityClassPackage());

        XmlElement* screens = manifest->createNewChildElement ("supports-screens");
        screens->setAttribute ("android:smallScreens", "true");
        screens->setAttribute ("android:normalScreens", "true");
        screens->setAttribute ("android:largeScreens", "true");
        //screens->setAttribute ("android:xlargeScreens", "true");
        screens->setAttribute ("android:anyDensity", "true");

        manifest->createNewChildElement ("uses-sdk")->setAttribute ("android:minSdkVersion", getMinimumSDKVersionString());

        {
            const StringArray permissions (getPermissionsRequired());

            for (int i = permissions.size(); --i >= 0;)
                manifest->createNewChildElement ("uses-permission")->setAttribute ("android:name", permissions[i]);
        }

        if (project.isModuleEnabled ("juce_opengl"))
        {
            XmlElement* feature = manifest->createNewChildElement ("uses-feature");
            feature->setAttribute ("android:glEsVersion", "0x00020000");
            feature->setAttribute ("android:required", "true");
        }

        XmlElement* app = manifest->createNewChildElement ("application");
        app->setAttribute ("android:label", "@string/app_name");
        app->setAttribute ("android:icon", "@drawable/icon");

        XmlElement* act = app->createNewChildElement ("activity");
        act->setAttribute ("android:name", getActivityName());
        act->setAttribute ("android:label", "@string/app_name");
        act->setAttribute ("android:configChanges", "keyboardHidden|orientation");

        XmlElement* intent = act->createNewChildElement ("intent-filter");
        intent->createNewChildElement ("action")->setAttribute ("android:name", "android.intent.action.MAIN");
        intent->createNewChildElement ("category")->setAttribute ("android:name", "android.intent.category.LAUNCHER");

        return manifest;
    }

    StringArray getPermissionsRequired() const
    {
        StringArray s;
        s.addTokens (getOtherPermissions(), ", ", "");

        if (getInternetNeeded())         s.add ("android.permission.INTERNET");
        if (getAudioRecordNeeded())      s.add ("android.permission.RECORD_AUDIO");

        s.trim();
        s.removeDuplicates (false);
        return s;
    }

    //==============================================================================
    void findAllFilesToCompile (const Project::Item& projectItem, Array<RelativePath>& results) const
    {
        if (projectItem.isGroup())
        {
            for (int i = 0; i < projectItem.getNumChildren(); ++i)
                findAllFilesToCompile (projectItem.getChild(i), results);
        }
        else
        {
            if (projectItem.shouldBeCompiled())
                results.add (RelativePath (projectItem.getFile(), getTargetFolder(), RelativePath::buildTargetFolder));
        }
    }

    //==============================================================================
    String getActivityName() const
    {
        return getActivityClassPath().fromLastOccurrenceOf (".", false, false);
    }

    String getActivityClassPackage() const
    {
        return getActivityClassPath().upToLastOccurrenceOf (".", false, false);
    }

    String getJNIActivityClassName() const
    {
        return getActivityClassPath().replaceCharacter ('.', '/');
    }

    static LibraryModule* getCoreModule (const OwnedArray<LibraryModule>& modules)
    {
        for (int i = modules.size(); --i >= 0;)
            if (modules.getUnchecked(i)->getID() == "juce_core")
                return modules.getUnchecked(i);

        return nullptr;
    }

    void copyActivityJavaFiles (const OwnedArray<LibraryModule>& modules) const
    {
        const String className (getActivityName());
        const String package (getActivityClassPackage());
        String path (package.replaceCharacter ('.', File::separator));

        if (path.isEmpty() || className.isEmpty())
            throw SaveError ("Invalid Android Activity class name: " + getActivityClassPath());

        const File classFolder (getTargetFolder().getChildFile ("src")
                                                 .getChildFile (path));
        createDirectoryOrThrow (classFolder);

        LibraryModule* const coreModule = getCoreModule (modules);

        if (coreModule == nullptr)
            throw SaveError ("To build an Android app, the juce_core module must be included in your project!");

        File javaDestFile (classFolder.getChildFile (className + ".java"));

        File javaSourceFile (coreModule->getFolder().getChildFile ("native")
                                                    .getChildFile ("java")
                                                    .getChildFile ("JuceAppActivity.java"));

        MemoryOutputStream newFile;
        newFile << javaSourceFile.loadFileAsString()
                                 .replace ("JuceAppActivity", className)
                                 .replace ("package com.juce;", "package " + package + ";");

        overwriteFileIfDifferentOrThrow (javaDestFile, newFile);
    }

    void writeApplicationMk (const File& file) const
    {
        MemoryOutputStream mo;

        mo << "# Automatically generated makefile, created by the Introjucer" << newLine
           << "# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!" << newLine
           << newLine
           << "APP_STL := gnustl_static" << newLine
           << "APP_CPPFLAGS += -fsigned-char -fexceptions -frtti" << newLine
           << "APP_PLATFORM := " << getAppPlatform() << newLine;

        overwriteFileIfDifferentOrThrow (file, mo);
    }

    void writeAndroidMk (const File& file) const
    {
        Array<RelativePath> files;

        for (int i = 0; i < groups.size(); ++i)
            findAllFilesToCompile (groups.getReference(i), files);

        MemoryOutputStream mo;
        writeAndroidMk (mo, files);

        overwriteFileIfDifferentOrThrow (file, mo);
    }

    void writeAndroidMk (OutputStream& out, const Array<RelativePath>& files) const
    {
        out << "# Automatically generated makefile, created by the Introjucer" << newLine
            << "# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!" << newLine
            << newLine
            << "LOCAL_PATH := $(call my-dir)" << newLine
            << newLine
            << "include $(CLEAR_VARS)" << newLine
            << newLine
            << "LOCAL_MODULE := juce_jni" << newLine
            << "LOCAL_SRC_FILES := \\" << newLine;

        for (int i = 0; i < files.size(); ++i)
            out << "  ../" << escapeSpaces (files.getReference(i).toUnixStyle()) << "\\" << newLine;

        String debugSettings, releaseSettings;

        out << newLine
            << "ifeq ($(CONFIG),Debug)" << newLine;
        writeConfigSettings (out, true);
        out << "else" << newLine;
        writeConfigSettings (out, false);
        out << "endif" << newLine
            << newLine
            << "include $(BUILD_SHARED_LIBRARY)" << newLine;
    }

    void writeConfigSettings (OutputStream& out, bool forDebug) const
    {
        for (ConstConfigIterator config (*this); config.next();)
        {
            if (config->isDebug() == forDebug)
            {
                const AndroidBuildConfiguration& androidConfig = dynamic_cast <const AndroidBuildConfiguration&> (*config);

                out << "  LOCAL_CPPFLAGS += " << createCPPFlags (androidConfig)
                    << (" " + replacePreprocessorTokens (androidConfig, getExtraCompilerFlagsString()).trim()).trimEnd()
                    << newLine
                    << getDynamicLibs (androidConfig);

                break;
            }
        }
    }

    String getDynamicLibs (const AndroidBuildConfiguration& config) const
    {
        String flags ("  LOCAL_LDLIBS :=");

        flags << config.getGCCLibraryPathFlags();

        {
            StringArray libs;
            libs.add ("log");
            libs.add ("GLESv2");

            for (int i = 0; i < libs.size(); ++i)
                flags << " -l" << libs[i];
        }

        return flags + newLine;
    }

    String createIncludePathFlags (const BuildConfiguration& config) const
    {
        String flags;
        StringArray searchPaths (extraSearchPaths);
        searchPaths.addArray (config.getHeaderSearchPaths());
        searchPaths.removeDuplicates (false);

        for (int i = 0; i < searchPaths.size(); ++i)
            flags << " -I " << FileHelpers::unixStylePath (replacePreprocessorTokens (config, searchPaths[i])).quoted();

        return flags;
    }

    String createCPPFlags (const BuildConfiguration& config) const
    {
        StringPairArray defines;
        defines.set ("JUCE_ANDROID", "1");
        defines.set ("JUCE_ANDROID_API_VERSION", getMinimumSDKVersionString());
        defines.set ("JUCE_ANDROID_ACTIVITY_CLASSNAME", getJNIActivityClassName().replaceCharacter ('/', '_'));
        defines.set ("JUCE_ANDROID_ACTIVITY_CLASSPATH", "\\\"" + getJNIActivityClassName() + "\\\"");

        String flags ("-fsigned-char -fexceptions -frtti");

        if (config.isDebug())
        {
            flags << " -g";
            defines.set ("DEBUG", "1");
            defines.set ("_DEBUG", "1");
        }
        else
        {
            defines.set ("NDEBUG", "1");
        }

        flags << createIncludePathFlags (config)
              << " -O" << config.getGCCOptimisationFlag();

        if (isCPP11Enabled())
            flags << " -std=c++0x";

        defines = mergePreprocessorDefs (defines, getAllPreprocessorDefs (config));
        return flags + createGCCPreprocessorFlags (defines);
    }

    //==============================================================================
    XmlElement* createAntBuildXML() const
    {
        XmlElement* proj = new XmlElement ("project");
        proj->setAttribute ("name", projectName);
        proj->setAttribute ("default", "debug");

        proj->createNewChildElement ("loadproperties")->setAttribute ("srcFile", "local.properties");
        proj->createNewChildElement ("loadproperties")->setAttribute ("srcFile", "project.properties");

        XmlElement* path = proj->createNewChildElement ("path");
        path->setAttribute ("id", "android.antlibs");
        path->createNewChildElement ("pathelement")->setAttribute ("path", "${sdk.dir}/tools/lib/anttasks.jar");
        path->createNewChildElement ("pathelement")->setAttribute ("path", "${sdk.dir}/tools/lib/sdklib.jar");
        path->createNewChildElement ("pathelement")->setAttribute ("path", "${sdk.dir}/tools/lib/androidprefs.jar");

        XmlElement* taskdef = proj->createNewChildElement ("taskdef");
        taskdef->setAttribute ("name", "setup");
        taskdef->setAttribute ("classname", "com.android.ant.SetupTask");
        taskdef->setAttribute ("classpathref", "android.antlibs");

        {
            XmlElement* target = proj->createNewChildElement ("target");
            target->setAttribute ("name", "clean");

            XmlElement* executable = target->createNewChildElement ("exec");
            executable->setAttribute ("executable", "${ndk.dir}/ndk-build");
            executable->setAttribute ("dir", "${basedir}");
            executable->setAttribute ("failonerror", "true");

            executable->createNewChildElement ("arg")->setAttribute ("value", "clean");
        }

        {
            XmlElement* target = proj->createNewChildElement ("target");
            target->setAttribute ("name", "-pre-build");

            addDebugConditionClause (target, "makefileConfig", "Debug", "Release");
            addDebugConditionClause (target, "ndkDebugValue", "NDK_DEBUG=1", "NDK_DEBUG=0");

            String debugABIs, releaseABIs;

            for (ConstConfigIterator config (*this); config.next();)
            {
                const AndroidBuildConfiguration& androidConfig = dynamic_cast <const AndroidBuildConfiguration&> (*config);

                if (config->isDebug())
                    debugABIs = androidConfig.getArchitectures();
                else
                    releaseABIs = androidConfig.getArchitectures();
            }

            addDebugConditionClause (target, "app_abis", debugABIs, releaseABIs);

            XmlElement* executable = target->createNewChildElement ("exec");
            executable->setAttribute ("executable", "${ndk.dir}/ndk-build");
            executable->setAttribute ("dir", "${basedir}");
            executable->setAttribute ("failonerror", "true");

            executable->createNewChildElement ("arg")->setAttribute ("value", "--jobs=2");
            executable->createNewChildElement ("arg")->setAttribute ("value", "CONFIG=${makefileConfig}");
            executable->createNewChildElement ("arg")->setAttribute ("value", "${ndkDebugValue}");
            executable->createNewChildElement ("arg")->setAttribute ("value", "APP_ABI=${app_abis}");

            target->createNewChildElement ("delete")->setAttribute ("file", "${out.final.file}");
            target->createNewChildElement ("delete")->setAttribute ("file", "${out.packaged.file}");
        }

        proj->createNewChildElement ("import")->setAttribute ("file", "${sdk.dir}/tools/ant/build.xml");

        return proj;
    }

    void addDebugConditionClause (XmlElement* target, const String& property,
                                  const String& debugValue, const String& releaseValue) const
    {
        XmlElement* condition = target->createNewChildElement ("condition");
        condition->setAttribute ("property", property);
        condition->setAttribute ("value", debugValue);
        condition->setAttribute ("else", releaseValue);

        XmlElement* equals = condition->createNewChildElement ("equals");
        equals->setAttribute ("arg1", "${ant.project.invoked-targets}");
        equals->setAttribute ("arg2", "debug");
    }

    String getAppPlatform() const
    {
        int ndkVersion = getMinimumSDKVersionString().getIntValue();
        if (ndkVersion == 9)
            ndkVersion = 10; // (doesn't seem to be a version '9')

        return "android-" + String (ndkVersion);
    }

    void writeProjectPropertiesFile (const File& file) const
    {
        MemoryOutputStream mo;
        mo << "# This file is used to override default values used by the Ant build system." << newLine
           << "# It is automatically generated - DO NOT EDIT IT or your changes will be lost!." << newLine
           << newLine
           << "target=" << getAppPlatform() << newLine
           << newLine;

        overwriteFileIfDifferentOrThrow (file, mo);
    }

    void writeLocalPropertiesFile (const File& file) const
    {
        MemoryOutputStream mo;
        mo << "# This file is used to override default values used by the Ant build system." << newLine
           << "# It is automatically generated by the Introjucer - DO NOT EDIT IT or your changes will be lost!." << newLine
           << newLine
           << "sdk.dir=" << escapeSpaces (replacePreprocessorDefs (getAllPreprocessorDefs(), getSDKPathString())) << newLine
           << "ndk.dir=" << escapeSpaces (replacePreprocessorDefs (getAllPreprocessorDefs(), getNDKPathString())) << newLine
           << "key.store=" << getKeyStoreString() << newLine
           << "key.alias=" << getKeyAliasString() << newLine
           << "key.store.password=" << getKeyStorePassString() << newLine
           << "key.alias.password=" << getKeyAliasPassString() << newLine
           << newLine;

        overwriteFileIfDifferentOrThrow (file, mo);
    }

    void writeIcon (const File& file, const Image& im) const
    {
        if (im.isValid())
        {
            createDirectoryOrThrow (file.getParentDirectory());

            PNGImageFormat png;
            MemoryOutputStream mo;

            if (! png.writeImageToStream (im, mo))
                throw SaveError ("Can't generate Android icon file");

            overwriteFileIfDifferentOrThrow (file, mo);
        }
    }

    void writeStringsFile (const File& file) const
    {
        XmlElement strings ("resources");
        XmlElement* name = strings.createNewChildElement ("string");
        name->setAttribute ("name", "app_name");
        name->addTextElement (projectName);

        writeXmlOrThrow (strings, file, "utf-8", 100);
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE (AndroidProjectExporter);
};


#endif   // __JUCER_PROJECTEXPORT_ANDROID_JUCEHEADER__
