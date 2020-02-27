#pragma once

#include <string>
#include <vector>

#include "cinn/common/common.h"
#include "cinn/ir/function.h"
#include "cinn/ir/ir.h"
#include "cinn/ir/ir_printer.h"
#include "cinn/ir/lowered_func.h"
#include "cinn/lang/module.h"

namespace cinn {

namespace lang {
class Module;
}  // namespace lang

namespace backends {

class CodeGenC : public ir::IrPrinter {
 public:
  CodeGenC(std::ostream& os, Target target);

  void Compile(const lang::Module& module);

 protected:
  void Compile(const ir::LoweredFunc& function);
  void Compile(const ir::Buffer& buffer);

  std::string PrintType(Type type);
  void PrintCastExpr(const Type& type, Expr e);

#define __DEFINE_VISIT(op__) void Visit(const ir::op__* op) override;
  NODETY_FORALL(__DEFINE_VISIT)
#undef __DEFINE_VISIT

 private:
  Target target_;
};

}  // namespace backends
}  // namespace cinn