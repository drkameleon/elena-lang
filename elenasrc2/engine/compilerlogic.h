//---------------------------------------------------------------------------
//		E L E N A   P r o j e c t:  ELENA Compiler
//
//		This file contains ELENA compiler logic class.
//
//                                              (C)2005-2020, by Alexei Rakov
//---------------------------------------------------------------------------

#ifndef compilerLogicH
#define compilerLogicH

#include "elena.h"
#include "compilercommon.h"

namespace _ELENA_
{

class CompilerLogic : public _CompilerLogic
{
   struct OperatorInfo
   {
      int         operatorId;

      ref_t       loperand;
      ref_t       roperand;
      ref_t       roperand2;
      LexicalType operationType;
      ref_t       result;

      OperatorInfo()
      {
         operatorId = 0;
         loperand = roperand = result = roperand2 = 0;
         operationType = lxNone;
      }
      OperatorInfo(int operatorId, ref_t loperand, ref_t roperand, LexicalType type, ref_t result)
      {
         this->operatorId = operatorId;
         this->loperand = loperand;
         this->roperand = roperand;
         this->operationType = type;
         this->result = result;
         this->roperand2 = 0;
      }
      OperatorInfo(int operatorId, ref_t loperand, ref_t roperand, ref_t roperand2, LexicalType type, ref_t result)
      {
         this->operatorId = operatorId;
         this->loperand = loperand;
         this->roperand = roperand;
         this->roperand2 = roperand2;
         this->operationType = type;
         this->result = result;
      }
   };

   typedef List<OperatorInfo> OperatorList;

   OperatorList operators;

   bool isSignatureCompatible(_ModuleScope& scope, _Module* targetModule, ref_t targetSignature, ref_t* sourceSignatures, size_t len);
   bool isSignatureCompatible(_ModuleScope& scope, ref_t targetSignature, ref_t* sourceSignatures, size_t len);

   void setSignatureStacksafe(_ModuleScope& scope, ref_t targetSignature, int& stackSafeAttr);
   void setSignatureStacksafe(_ModuleScope& scope, _Module* targetModule, ref_t targetSignature, int& stackSafeAttr);

////   bool loadBranchingInfo(_CompilerScope& scope, ref_t reference);
   bool injectImplicitConstructor(_ModuleScope& scope, SNode& node, _Compiler& compiler, ClassInfo& info, ref_t targetRef,
      /*ref_t elementRef, */ref_t* signatures, size_t paramCount, int& stackSafeAttr);

   ref_t getClassClassRef(_ModuleScope& scope, ref_t reference);

   bool isBoolean(_ModuleScope& scope, ref_t reference);

public:
   virtual bool isSignatureCompatible(_ModuleScope& scope, ref_t targetMessage, ref_t sourceMessage);

   virtual bool isMessageCompatibleWithSignature(_ModuleScope& scope, ref_t targetRef, ref_t targetMessage,
      ref_t* sourceSignatures, size_t len, int& stackSafeAttr);

   virtual int checkMethod(_ModuleScope& scope, ref_t reference, ref_t message, ChechMethodInfo& result, bool resolveProtected);
   virtual int checkMethod(ClassInfo& info, ref_t message, ChechMethodInfo& result, bool resolveProtected);

   virtual bool defineClassInfo(_ModuleScope& scope, ClassInfo& info, ref_t reference, bool headerOnly = false);

   virtual int defineStructSize(_ModuleScope& scope, ref_t reference, ref_t elementRef)
   {
      bool dummy = false;
      return defineStructSizeVariable(scope, reference, elementRef, dummy);
   }
   virtual int defineStructSizeVariable(_ModuleScope& scope, ref_t reference, ref_t elementRef, bool& variable);
   virtual int defineStructSize(ClassInfo& info, bool& variable);

//   virtual ref_t retrievePrimitiveReference(_ModuleScope& scope, ClassInfo& info);

   virtual int resolveCallType(_ModuleScope& scope, ref_t& classReference, ref_t message, ChechMethodInfo& result);
   virtual int resolveOperationType(_ModuleScope& scope, int operatorId, ref_t loperand, ref_t roperand, ref_t& result);
//   virtual int resolveOperationType(_ModuleScope& scope, int operatorId, ref_t loperand, ref_t roperand, ref_t roperand2, ref_t& result);
   virtual int resolveNewOperationType(_ModuleScope& scope, ref_t loperand, ref_t roperand);
   virtual bool resolveBranchOperation(_ModuleScope& scope, int operatorId, ref_t loperand, ref_t& reference);
   virtual ref_t definePrimitiveArray(_ModuleScope& scope, ref_t elementRef, bool structOne);

//   virtual bool isDeclared(_ModuleScope& scope, ref_t reference)
//   {
//      ClassInfo info;
//      return defineClassInfo(scope, info, reference, true);
//   }

   virtual bool isCompatible(_ModuleScope& scope, ref_t targetRef, ref_t sourceRef, bool ignoreNils);
//   virtual ref_t resolvePrimitive(ClassInfo& info, ref_t& element);
//   virtual bool isWrapper(ClassInfo& info)
//   {
//      return test(info.header.flags, elWrapper);
//   }
   virtual bool isEmbeddableArray(ClassInfo& info);
   virtual bool isVariable(_ModuleScope& scope, ref_t targetRef);
   virtual bool isVariable(ClassInfo& info);
   virtual bool isArray(_ModuleScope& scope, ref_t targetRef);
   virtual bool isArray(ClassInfo& info);
   virtual bool isValidType(_ModuleScope& scope, ref_t targetRef, bool ignoreUndeclared, bool allowRole);
   virtual bool isValidType(ClassInfo& info, bool allowRole);
   virtual bool doesClassExist(_ModuleScope& scope, ref_t targetRef);
   virtual bool isEmbeddable(ClassInfo& info);
   virtual bool isEmbeddable(_ModuleScope& scope, ref_t reference)
   {
      ClassInfo info;
      if(!defineClassInfo(scope, info, reference, true))
         return false;

      return isEmbeddable(info);
   }
   virtual bool isStacksafeArg(ClassInfo& info);
   virtual bool isStacksafeArg(_ModuleScope& scope, ref_t reference)
   {
      ClassInfo info;
      if (!defineClassInfo(scope, info, reference, true))
         return false;

      return isStacksafeArg(info);
   }
   virtual bool isRole(ClassInfo& info);
   virtual bool isAbstract(ClassInfo& info);
//   virtual bool isMethodStacksafe(ClassInfo& info, ref_t message);
   virtual bool isMethodGeneric(ClassInfo& info, ref_t message);
   virtual bool isMixinMethod(ClassInfo& info, ref_t message);
   virtual bool isMethodAbstract(ClassInfo& info, ref_t message);
   virtual bool isMethodYieldable(ClassInfo& info, ref_t message);
//   virtual bool isMethodInternal(ClassInfo& info, ref_t message);
   virtual bool isMethodPrivate(ClassInfo& info, ref_t message);
   virtual bool isMultiMethod(ClassInfo& info, ref_t message);
   virtual bool isMultiMethod(_ModuleScope& scope, ref_t reference, ref_t message);
//   virtual bool isFunction(ClassInfo& info, ref_t message);
   virtual bool isMethodEmbeddable(ClassInfo& info, ref_t message);
   virtual bool isMethodEmbeddable(_ModuleScope& scope, ref_t reference, ref_t message);
////   virtual bool isDispatcher(ClassInfo& info, ref_t message);
   virtual bool isReadonly(ClassInfo& info);
   virtual bool isReadonly(_ModuleScope& scope, ref_t reference)
   {
      ClassInfo info;
      defineClassInfo(scope, info, reference, true);

      return isReadonly(info);
   }
   virtual bool isWithEmbeddableDispatcher(_ModuleScope& scope, SNode node);
   virtual bool validateAutoType(_ModuleScope& scope, ref_t& reference);

   virtual bool isSealedOrClosed(ClassInfo& info);
   virtual bool isSealedOrClosed(_ModuleScope& scope, ref_t reference)
   {
      ClassInfo info;
      defineClassInfo(scope, info, reference, true);

      return isSealedOrClosed(info);
   }

   virtual void injectVirtualCode(_ModuleScope& scope, SNode node, ref_t classRef, ClassInfo& info, _Compiler& compiler, bool closed);
   virtual void injectVirtualFields(_ModuleScope& scope, SNode node, ref_t classRef, ClassInfo& info, _Compiler& compiler);
   virtual void injectVirtualMultimethods(_ModuleScope& scope, SNode node, _Compiler& compiler, 
      List<ref_t>& implicitMultimethods, LexicalType methodType, ClassInfo& info);
   virtual void injectOperation(SNode& node, _CompileScope& scope, _Compiler& compiler, int operatorId, int operation, 
      ref_t& reference, ref_t elementRef, int tempLocal);
   virtual bool injectConstantConstructor(SNode& node, _ModuleScope& scope, _Compiler& compiler, ref_t targetRef, ref_t messageRef);
   virtual bool injectImplicitConversion(_CompileScope& scope, SNode& node, _Compiler& compiler, ref_t targetRef, ref_t sourceRef,
      ref_t elementRef, bool noUnboxing, int& stackSafeAttr, int fixedArraySize);
   virtual ref_t resolveImplicitConstructor(_ModuleScope& scope, ref_t targetRef, ref_t signRef, size_t signLen, 
      int& stackSafeAttr, bool ignoreMultimethod);

   virtual void injectNewOperation(SNode& node, _ModuleScope& scope, int operation, ref_t targetRef, ref_t elementRef);
   virtual ref_t generateOverloadList(_ModuleScope& scope, _Compiler& compiler, ref_t message, 
      ClassInfo::CategoryInfoMap& list, void* param, ref_t(*resolve)(void*, ref_t), int flags);
   virtual void injectOverloadList(_ModuleScope& scope, ClassInfo& info, _Compiler& compiler, ref_t classRef);

   virtual void injectInterfaceDispatch(_ModuleScope& scope, _Compiler& compiler, SNode node, ref_t parentRef);

   virtual void tweakClassFlags(_ModuleScope& scope, _Compiler& compiler, ref_t classRef, ClassInfo& info, bool classClassMode);
   virtual void tweakPrimitiveClassFlags(ref_t classRef, ClassInfo& info);

   virtual bool validateNsAttribute(int attrValue, Visibility& visibility);
   virtual bool validateClassAttribute(int& attrValue, Visibility& visibility);
   virtual bool validateMethodAttribute(int& attrValue, bool& explicitMode);
   virtual bool validateImplicitMethodAttribute(int& attrValue/*, bool complexName*/);
   virtual bool validateFieldAttribute(int& attrValue, FieldAttributes& attrs);
   virtual bool validateExpressionAttribute(ref_t attrValue, ExpressionAttributes& attributes, bool& newVariable);
   virtual bool validateSymbolAttribute(int attrValue, bool& constant, bool& staticOne, bool& preloadedOne, 
      Visibility& visibility);
   virtual bool validateMessage(_ModuleScope& scope, ref_t message, int hints);
   virtual bool validateArgumentAttribute(int attrValue, bool& byRefArg, bool& paramsArg);

   virtual void validateClassDeclaration(_ModuleScope& scope, ClassInfo& info, bool& withAbstractMethods, 
      bool& disptacherNotAllowed, bool& emptyStructure);

//   virtual bool isDefaultConstructorEnabled(ClassInfo& info)
//   {
//      return !test(info.header.flags, elDynamicRole);
//   }

   virtual ref_t resolveEmbeddableRetMessage(_CompileScope& scope, _Compiler& compiler, ref_t target,
      ref_t message, ref_t expectedRef);

   virtual bool recognizeEmbeddableIdle(SNode node, bool extensionOne);
   virtual bool recognizeEmbeddableMessageCall(SNode node, ref_t& messageRef);

   virtual bool optimizeEmbeddable(SNode node, _ModuleScope& scope);
//   virtual bool optimizeReturningStructure(_ModuleScope& scope, _Compiler& compiler, SNode node, bool argMode);
   virtual bool optimizeEmbeddableOp(_ModuleScope& scope, _Compiler& compiler, SNode node);
   virtual bool optimizeBranchingOp(_ModuleScope& scope, SNode node);

   virtual ref_t resolveMultimethod(_ModuleScope& scope, ref_t multiMessage, ref_t targetRef, ref_t implicitSignatureRef, 
      int& stackSafeAttr, bool selfCall);
   virtual void verifyMultimethods(_ModuleScope& scope, SNode node, ClassInfo& info, List<ref_t>& implicitMultimethods);
   virtual ref_t resolveExtensionTemplate(_ModuleScope& scope, _Compiler& compiler, ident_t pattern, 
      ref_t signatureRef, ident_t ns, ExtensionMap* outerExtensionList);
   virtual ref_t resolveArrayElement(_ModuleScope& scope, ref_t reference);

   CompilerLogic();
};

} // _ELENA_

#endif // compilerLogicH