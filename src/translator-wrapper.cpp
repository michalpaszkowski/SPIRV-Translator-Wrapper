#include "translator-wrapper.h"

#include "llvm/IR/Module.h"
#include "LLVMSPIRVLib.h"

#include <string>
#include <sstream>

using namespace llvm;

extern "C" ITranslator_Result *generateBitcode(const char *SpirvBuffer,
                                               size_t SpirvSize)
{

  std::string SpirvBufferDeepCopy(SpirvBuffer, SpirvSize);
  std::istringstream SpirvStream(SpirvBufferDeepCopy);
  std::string Errors;

  LLVMContext Context;
  Module *Module;

  llvm::readSpirv(Context, SpirvStream, Module, Errors);

  std::string Bitcode;
  raw_string_ostream BitcodeStream(Bitcode);
  BitcodeStream << *Module;
  BitcodeStream.flush();

  delete Module;
  return new ITranslator_Result(Bitcode, Errors);
}
