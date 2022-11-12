/***********************************
 * File:     CodeGen.h
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2022/10/21
 *
 * Sign:     enjoy life
 ***********************************/
#ifndef LCC_CODEGEN_H
#define LCC_CODEGEN_H
#include "Syntax.h"

namespace lcc::codegen {
class CodeGen {
public:
  explicit CodeGen(std::unique_ptr<parser::Program> &&program,
                   lcc::CodeGenContext &context) {
    program->Codegen(context);
  };
};
} // namespace lcc::codegen

#endif // LCC_CODEGEN_H
