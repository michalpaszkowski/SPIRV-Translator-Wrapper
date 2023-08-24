#pragma once

#include <string>

// Shared interface for the resulting bitcode.
struct ITranslator_Result
{
  ITranslator_Result(std::string ResultBitcode, std::string Errors)
      : resultBitcode(ResultBitcode), errors(Errors) {}

  // Returns the pointer to the bitcode buffer.
  virtual const char *GetBitcode() { return resultBitcode.data(); }
  // Returns the size in bytes of the bitcode buffer.
  virtual const size_t GetBitcodeSize() { return resultBitcode.size(); }

  // Returns the pointer to the error log string.
  virtual const char *GetErrorLog() { return errors.c_str(); }

  // Releases the resulting bitcode.
  virtual void Release() { delete this; }

protected:
  virtual ~ITranslator_Result() {}

private:
  std::string resultBitcode;
  std::string errors;
};

extern "C" ITranslator_Result *generateBitcode(const char *SpirvBuffer,
                                               size_t SpirvSize);
