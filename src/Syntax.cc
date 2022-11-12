/***********************************
 * File:     Syntax.cc
 *
 * Author:   caipeng
 *
 * Email:    iiicp@outlook.com
 *
 * Date:     2022/10/13
 *
 * Sign:     enjoy life
 ***********************************/
#include "Syntax.h"

namespace lcc::parser {
PrimaryType::PrimaryType(std::vector<lexer::TokenType> &&types) noexcept
    : mTypes(types) {}
PointerType::PointerType(std::unique_ptr<Type> &&type) noexcept
    : mType(std::move(type)) {}

Expr::Expr(std::unique_ptr<AssignExpr> &&assignExpr,
           std::vector<std::unique_ptr<AssignExpr>> &&optAssignExps) noexcept
    : mAssignExpr(std::move(assignExpr)),
      mOptAssignExps(std::move(optAssignExps)) {}

ConstantExpr::ConstantExpr(ConstantValue &value) : mValue(value) {}

AssignExpr::AssignExpr(std::unique_ptr<ConditionalExpr> &&condExpr,
                       lexer::TokenType tokenType,
                       std::unique_ptr<AssignExpr> &&assignExpr) noexcept
    : mCondExpr(std::move(condExpr)), mTokType(tokenType),
      mAssignExpr(std::move(assignExpr)) {}

ConditionalExpr::ConditionalExpr(
    std::unique_ptr<LogOrExpr> &&logOrExpr, std::unique_ptr<Expr> &&optExpr,
    std::unique_ptr<ConditionalExpr> &&optCondExpr) noexcept
    : mLogOrExpr(std::move(logOrExpr)), mOptExpr(std::move(optExpr)),
      mOptCondExpr(std::move(optCondExpr)) {}

LogOrExpr::LogOrExpr(
    std::unique_ptr<LogAndExpr> &&logAndExpr,
    std::vector<std::unique_ptr<LogAndExpr>> &&optLogAndExps) noexcept
    : mLogAndExpr(std::move(logAndExpr)),
      mOptLogAndExps(std::move(optLogAndExps)) {}

LogAndExpr::LogAndExpr(
    std::unique_ptr<BitOrExpr> &&bitOrExpr,
    std::vector<std::unique_ptr<BitOrExpr>> &&optBitOrExps) noexcept
    : mBitOrExpr(std::move(bitOrExpr)), mOptBitOrExps(std::move(optBitOrExps)) {
}

BitOrExpr::BitOrExpr(
    std::unique_ptr<BitXorExpr> &&bitXorExpr,
    std::vector<std::unique_ptr<BitXorExpr>> &&optBitXorExps) noexcept
    : mBitXorExpr(std::move(bitXorExpr)),
      mOptBitXorExps(std::move(optBitXorExps)) {}

BitXorExpr::BitXorExpr(
    std::unique_ptr<BitAndExpr> &&bitAndExpr,
    std::vector<std::unique_ptr<BitAndExpr>> &&optBitAndExps) noexcept
    : mBitAndExpr(std::move(bitAndExpr)),
      mOptBitAndExps(std::move(optBitAndExps)) {}

BitAndExpr::BitAndExpr(
    std::unique_ptr<EqualExpr> &&equalExpr,
    std::vector<std::unique_ptr<EqualExpr>> &&optEqualExps) noexcept
    : mEqualExpr(std::move(equalExpr)), mOptEqualExps(std::move(optEqualExps)) {
}

EqualExpr::EqualExpr(
    std::unique_ptr<RelationalExpr> &&relationalExpr,
    std::vector<std::pair<lexer::TokenType, std::unique_ptr<RelationalExpr>>>
        &&optRelationalExps) noexcept
    : mRelationalExpr(std::move(relationalExpr)),
      mOptRelationExps(std::move(optRelationalExps)) {}

RelationalExpr::RelationalExpr(
    std::unique_ptr<ShiftExpr> &&shiftExpr,
    std::vector<std::pair<lexer::TokenType, std::unique_ptr<ShiftExpr>>>
        &&optShiftExps) noexcept
    : mShiftExpr(std::move(shiftExpr)), mOptShiftExps(std::move(optShiftExps)) {
}

ShiftExpr::ShiftExpr(
    std::unique_ptr<AdditiveExpr> &&additiveExpr,
    std::vector<std::pair<lexer::TokenType, std::unique_ptr<AdditiveExpr>>>
        &&optAdditiveExps) noexcept
    : mAdditiveExpr(std::move(additiveExpr)),
      mOptAdditiveExps(std::move(optAdditiveExps)) {}

AdditiveExpr::AdditiveExpr(
    std::unique_ptr<MultiExpr> &&multiExpr,
    std::vector<std::pair<lexer::TokenType, std::unique_ptr<MultiExpr>>>
        &&optionalMultiExps) noexcept
    : mMultiExpr(std::move(multiExpr)),
      mOptionalMultiExps(std::move(optionalMultiExps)) {}

MultiExpr::MultiExpr(
    std::unique_ptr<CastExpr> &&castExpr,
    std::vector<std::pair<lexer::TokenType, std::unique_ptr<CastExpr>>>
        &&optCastExps) noexcept
    : mCastExpr(std::move(castExpr)), mOptCastExps(std::move(optCastExps)) {}

CastExpr::CastExpr(Variant &&unaryOrCast) noexcept
    : mVariant(std::move(unaryOrCast)) {}

UnaryExpr::UnaryExpr(Variant &&variant) noexcept
    : mVariant(std::move(variant)) {}

UnaryExprSizeOf::UnaryExprSizeOf(Variant &&variant) noexcept
    : mUnaryOrType(std::move(variant)) {}

UnaryExprPostFixExpr::UnaryExprPostFixExpr(
    std::unique_ptr<PostFixExpr> &&postExpr) noexcept
    : mPostExpr(std::move(postExpr)) {}

UnaryExprUnaryOperator::UnaryExprUnaryOperator(
    lexer::TokenType tokTy, std::unique_ptr<UnaryExpr> &&unaryExpr) noexcept
    : mTok(tokTy), mUnaryExpr(std::move(unaryExpr)) {}

PostFixExpr::PostFixExpr(Variant &&variant) noexcept
    : mVariant(std::move(variant)) {}

PostFixExprDecrement::PostFixExprDecrement(
    std::unique_ptr<PostFixExpr> &&postFixExpr) noexcept
    : mPostFixExpr(std::move(postFixExpr)) {}

PostFixExprIncrement::PostFixExprIncrement(
    std::unique_ptr<PostFixExpr> &&postFixExpr) noexcept
    : mPostFixExpr(std::move(postFixExpr)) {}

PostFixExprArrow::PostFixExprArrow(std::unique_ptr<PostFixExpr> &&postFixExpr,
                                   std::string identifier) noexcept
    : mPostFixExpr(std::move(postFixExpr)), mIdentifier(identifier) {}

PostFixExprDot::PostFixExprDot(std::unique_ptr<PostFixExpr> &&postFixExpr,
                               std::string identifier) noexcept
    : mPostFixExpr(std::move(postFixExpr)), mIdentifier(identifier) {}

PostFixExprFuncCall::PostFixExprFuncCall(
    std::unique_ptr<PostFixExpr> &&postFixExpr,
    std::vector<std::unique_ptr<AssignExpr>> &&optParams) noexcept
    : mPostFixExpr(std::move(postFixExpr)), mOptParams(std::move(optParams)) {}

PostFixExprSubscript::PostFixExprSubscript(
    std::unique_ptr<PostFixExpr> &&postFixExpr,
    std::unique_ptr<Expr> &&expr) noexcept
    : mPostFixExpr(std::move(postFixExpr)), mExpr(std::move(expr)) {}

ExprStmt::ExprStmt(std::unique_ptr<Expr> &&optExpr) noexcept
    : mOptExpr(std::move(optExpr)) {}

IfStmt::IfStmt(std::unique_ptr<Expr> &&expr, std::unique_ptr<Stmt> &&thenStmt,
               std::unique_ptr<Stmt> &&optElseStmt) noexcept
    : mExpr(std::move(expr)), mThenStmt(std::move(thenStmt)),
      mOptElseStmt(std::move(optElseStmt)) {}

PostFixExprPrimary::PostFixExprPrimary(
    std::unique_ptr<PrimaryExpr> &&primaryExpr) noexcept
    : mPrimaryExpr(std::move(primaryExpr)) {}

PrimaryExpr::PrimaryExpr(Variant &&variant) noexcept
    : mVariant(std::move(variant)) {}

PrimaryExprParent::PrimaryExprParent(std::unique_ptr<Expr> &&expr) noexcept
    : mExpr(std::move(expr)) {}

PrimaryExprIdentifier::PrimaryExprIdentifier(std::string identifier)
    : mIdentifier(identifier) {}

PrimaryExprConstant::PrimaryExprConstant(Variant variant) : mVariant(variant) {}

DoWhileStmt::DoWhileStmt(std::unique_ptr<Stmt> &&stmt,
                         std::unique_ptr<Expr> &&expr) noexcept
    : mStmt(std::move(stmt)), mExpr(std::move(expr)) {}

WhileStmt::WhileStmt(std::unique_ptr<Expr> &&expr,
                     std::unique_ptr<Stmt> &&stmt) noexcept
    : mExpr(std::move(expr)), mStmt(std::move(stmt)) {}

ForStmt::ForStmt(std::unique_ptr<Expr> &&initExpr,
                 std::unique_ptr<Expr> &&controlExpr,
                 std::unique_ptr<Expr> &&postExpr,
                 std::unique_ptr<Stmt> &&stmt) noexcept
    : mInitExpr(std::move(initExpr)), mControlExpr(std::move(controlExpr)),
      mPostExpr(std::move(postExpr)), mStmt(std::move(stmt)) {}

Declaration::Declaration(std::unique_ptr<Type> &&type, std::string name,
                         std::unique_ptr<Expr> &&optValue) noexcept
    : mType(std::move(type)), mName(name), mOptValue(std::move(optValue)) {}

ForDeclarationStmt::ForDeclarationStmt(std::unique_ptr<Declaration> &&initDecl,
                                       std::unique_ptr<Expr> &&controlExpr,
                                       std::unique_ptr<Expr> &&postExpr,
                                       std::unique_ptr<Stmt> &&stmt) noexcept
    : mInitDecl(std::move(initDecl)), mControlExpr(std::move(controlExpr)),
      mPostExpr(std::move(postExpr)), mStmt(std::move(stmt)) {}

ReturnStmt::ReturnStmt(std::unique_ptr<Expr> &&optExpr) noexcept
    : mOptExpr(std::move(optExpr)) {}

BlockStmt::BlockStmt(std::vector<std::unique_ptr<Stmt>> &&stmts) noexcept
    : mStmts(std::move(stmts)) {}

Function::Function(
    std::unique_ptr<Type> &&retType, std::string name,
    std::vector<std::pair<std::unique_ptr<Type>, std::string>> &&params,
    std::unique_ptr<BlockStmt> &&optBlockStmt) noexcept
    : mRetType(std::move(retType)), mName(name), mParam(std::move(params)),
      mOptBlockStmt(std::move(optBlockStmt)) {}

GlobalDecl::GlobalDecl(std::unique_ptr<Type> &&type, std::string name,
                       std::unique_ptr<ConstantExpr> &&optValue) noexcept
    : mType(std::move(type)), mName(name), mOptValue(std::move(optValue)) {}

Program::Program(
    std::vector<std::unique_ptr<ExternalDeclaration>> &&externalDecl) noexcept
    : mExternalDecl(std::move(externalDecl)) {}
} // namespace lcc::parser