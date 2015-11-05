/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmGlobalVisualStudio10Generator_h
#define cmGlobalVisualStudio10Generator_h

#include "cmGlobalVisualStudio8Generator.h"
#include "cmVisualStudio10ToolsetOptions.h"

/** \class cmGlobalVisualStudio10Generator
 * \brief Write a Unix makefiles.
 *
 * cmGlobalVisualStudio10Generator manages UNIX build process for a tree
 */
class cmGlobalVisualStudio10Generator : public cmGlobalVisualStudio8Generator
{
public:
  cmGlobalVisualStudio10Generator(cmake* cm, const std::string& name,
                                  const std::string& platformName);
  static cmGlobalGeneratorFactory* NewFactory();

  bool MatchesGeneratorName(const std::string& name) const override;

  bool SetSystemName(std::string const& s, cmMakefile* mf) override;
  bool SetGeneratorPlatform(std::string const& p, cmMakefile* mf) override;
  bool SetGeneratorToolset(std::string const& ts, cmMakefile* mf) override;

  void GenerateBuildCommand(std::vector<std::string>& makeCommand,
                            const std::string& makeProgram,
                            const std::string& projectName,
                            const std::string& projectDir,
                            const std::string& targetName,
                            const std::string& config, bool fast, int jobs,
                            bool verbose,
                            std::vector<std::string> const& makeOptions =
                              std::vector<std::string>()) override;

  ///! create the correct local generator
  cmLocalGenerator* CreateLocalGenerator(cmMakefile* mf) override;

  /**
   * Try to determine system information such as shared library
   * extension, pthreads, byte order etc.
   */
  void EnableLanguage(std::vector<std::string> const& languages, cmMakefile*,
                      bool optional) override;
  void WriteSLNHeader(std::ostream& fout) override;

  bool IsCudaEnabled() const { return this->CudaEnabled; }

  /** Generating for Nsight Tegra VS plugin?  */
  bool IsNsightTegra() const;
  std::string GetNsightTegraVersion() const;

  /** The toolset name for the target platform.  */
  const char* GetPlatformToolset() const;
  std::string const& GetPlatformToolsetString() const;

  /** The toolset version.  */
  const char* GetPlatformToolsetVersion() const;
  std::string const& GetPlatformToolsetVersionString() const;

  /** The toolset host architecture name (e.g. x64 for 64-bit host tools).  */
  const char* GetPlatformToolsetHostArchitecture() const;

  /** The cuda toolset version.  */
  const char* GetPlatformToolsetCuda() const;
  std::string const& GetPlatformToolsetCudaString() const;

  /** Return whether we need to use No/Debug instead of false/true
      for GenerateDebugInformation.  */
  bool GetPlatformToolsetNeedsDebugEnum() const
  {
    return this->PlatformToolsetNeedsDebugEnum;
  }

  /** Return the CMAKE_SYSTEM_NAME.  */
  std::string const& GetSystemName() const { return this->SystemName; }

  /** Return the CMAKE_SYSTEM_VERSION.  */
  std::string const& GetSystemVersion() const { return this->SystemVersion; }

  /** Return the Windows version targeted on VS 2015 and above.  */
  std::string const& GetWindowsTargetPlatformVersion() const
  {
    return this->WindowsTargetPlatformVersion;
  }

  /** Return true if building for WindowsCE */
  bool TargetsWindowsCE() const { return this->SystemIsWindowsCE; }

  /** Return true if building for WindowsPhone */
  bool TargetsWindowsPhone() const { return this->SystemIsWindowsPhone; }

  /** Return true if building for Android */
  bool TargetsAndroidMDD() const
    { return this->SystemIsAndroidMDD; }

  /** Return true if building for WindowsStore */
  bool TargetsWindowsStore() const { return this->SystemIsWindowsStore; }

  const char* GetCMakeCFGIntDir() const override { return "$(Configuration)"; }
  bool Find64BitTools(cmMakefile* mf);

  /** Generate an <output>.rule file path for a given command output.  */
  std::string GenerateRuleFile(std::string const& output) const override;

  void PathTooLong(cmGeneratorTarget* target, cmSourceFile const* sf,
                   std::string const& sfRel);

  std::string Encoding() override;
  virtual const char* GetToolsVersion() { return "4.0"; }

  virtual bool IsDefaultToolset(const std::string& version) const;
  virtual std::string GetAuxiliaryToolset() const;

  bool FindMakeProgram(cmMakefile* mf) override;

  bool IsIPOSupported() const override { return true; }

  static std::string GetInstalledNsightTegraVersion();

  const char* GetAndroidMDDVersion();
  virtual bool IsAndroidMDDInstalled();

  cmIDEFlagTable const* GetClFlagTable() const;
  cmIDEFlagTable const* GetCSharpFlagTable() const;
  cmIDEFlagTable const* GetRcFlagTable() const;
  cmIDEFlagTable const* GetLibFlagTable() const;
  cmIDEFlagTable const* GetLinkFlagTable() const;
  cmIDEFlagTable const* GetCudaFlagTable() const;
  cmIDEFlagTable const* GetCudaHostFlagTable() const;
  cmIDEFlagTable const* GetMasmFlagTable() const;
  cmIDEFlagTable const* GetNasmFlagTable() const;

protected:
  void Generate() override;
  virtual bool InitializeSystem(cmMakefile* mf);
  virtual bool InitializeWindows(cmMakefile* mf);
  virtual bool InitializeWindowsCE(cmMakefile* mf);
  virtual bool InitializeWindowsPhone(cmMakefile* mf);
  virtual bool InitializeWindowsStore(cmMakefile* mf);
  virtual bool InitializeAndroidMDD(cmMakefile* mf);

  virtual bool ProcessGeneratorToolsetField(std::string const& key,
                                            std::string const& value);

  virtual std::string SelectWindowsCEToolset() const;
  virtual bool SelectWindowsPhoneToolset(std::string& toolset) const;
  virtual bool SelectWindowsStoreToolset(std::string& toolset) const;

  const char* GetIDEVersion() override { return "10.0"; }

  std::string const& GetMSBuildCommand();

  std::string GeneratorToolset;
  std::string GeneratorToolsetVersion;
  std::string GeneratorToolsetHostArchitecture;
  std::string GeneratorToolsetCuda;
  std::string DefaultPlatformToolset;
  std::string WindowsTargetPlatformVersion;
  std::string SystemName;
  std::string SystemVersion;
  std::string NsightTegraVersion;
  cmIDEFlagTable const* DefaultClFlagTable;
  cmIDEFlagTable const* DefaultCSharpFlagTable;
  cmIDEFlagTable const* DefaultLibFlagTable;
  cmIDEFlagTable const* DefaultLinkFlagTable;
  cmIDEFlagTable const* DefaultCudaFlagTable;
  cmIDEFlagTable const* DefaultCudaHostFlagTable;
  cmIDEFlagTable const* DefaultMasmFlagTable;
  cmIDEFlagTable const* DefaultNasmFlagTable;
  cmIDEFlagTable const* DefaultRcFlagTable;
  bool SystemIsWindowsCE;
  bool SystemIsWindowsPhone;
  bool SystemIsWindowsStore;
  bool SystemIsAndroidMDD;


private:
  class Factory;
  struct LongestSourcePath
  {
    LongestSourcePath()
      : Length(0)
      , Target(0)
      , SourceFile(0)
    {
    }
    size_t Length;
    cmGeneratorTarget* Target;
    cmSourceFile const* SourceFile;
    std::string SourceRel;
  };
  LongestSourcePath LongestSource;

  std::string MSBuildCommand;
  bool MSBuildCommandInitialized;
  cmVisualStudio10ToolsetOptions ToolsetOptions;
  virtual std::string FindMSBuildCommand();
  std::string FindDevEnvCommand() override;
  std::string GetVSMakeProgram() override { return this->GetMSBuildCommand(); }

  bool PlatformToolsetNeedsDebugEnum;

  bool ParseGeneratorToolset(std::string const& ts, cmMakefile* mf);

  std::string VCTargetsPath;
  bool FindVCTargetsPath(cmMakefile* mf);

  bool CudaEnabled;

  // We do not use the reload macros for VS >= 10.
  std::string GetUserMacrosDirectory() override { return ""; }
};
#endif
