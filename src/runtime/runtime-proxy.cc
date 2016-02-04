// Copyright 2014 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/runtime/runtime-utils.h"

#include "src/arguments.h"
#include "src/factory.h"
#include "src/objects-inl.h"

namespace v8 {
namespace internal {

RUNTIME_FUNCTION(Runtime_CreateJSFunctionProxy) {
  HandleScope scope(isolate);
  DCHECK(args.length() == 5);
  CONVERT_ARG_HANDLE_CHECKED(JSReceiver, target, 0);
  CONVERT_ARG_HANDLE_CHECKED(JSReceiver, handler, 1);
  CONVERT_ARG_HANDLE_CHECKED(JSReceiver, call_trap, 2);
  RUNTIME_ASSERT(call_trap->IsJSFunction() || call_trap->IsJSFunctionProxy());
  CONVERT_ARG_HANDLE_CHECKED(JSFunction, construct_trap, 3);
  CONVERT_ARG_HANDLE_CHECKED(Object, prototype, 4);
  if (!prototype->IsJSReceiver()) prototype = isolate->factory()->null_value();
  return *isolate->factory()->NewJSFunctionProxy(target, handler, call_trap,
                                                 construct_trap, prototype);
}


RUNTIME_FUNCTION(Runtime_IsJSProxy) {
  SealHandleScope shs(isolate);
  DCHECK(args.length() == 1);
  CONVERT_ARG_CHECKED(Object, obj, 0);
  return isolate->heap()->ToBoolean(obj->IsJSProxy());
}


RUNTIME_FUNCTION(Runtime_IsJSFunctionProxy) {
  SealHandleScope shs(isolate);
  DCHECK(args.length() == 1);
  CONVERT_ARG_HANDLE_CHECKED(Object, obj, 0);
  return isolate->heap()->ToBoolean(obj->IsJSFunctionProxy());
}


RUNTIME_FUNCTION(Runtime_GetHandler) {
  SealHandleScope shs(isolate);
  DCHECK(args.length() == 1);
  CONVERT_ARG_CHECKED(JSProxy, proxy, 0);
  return proxy->handler();
}


RUNTIME_FUNCTION(Runtime_GetCallTrap) {
  SealHandleScope shs(isolate);
  DCHECK(args.length() == 1);
  CONVERT_ARG_CHECKED(JSFunctionProxy, proxy, 0);
  return proxy->call_trap();
}


RUNTIME_FUNCTION(Runtime_GetConstructTrap) {
  SealHandleScope shs(isolate);
  DCHECK(args.length() == 1);
  CONVERT_ARG_CHECKED(JSFunctionProxy, proxy, 0);
  return proxy->construct_trap();
}

}  // namespace internal
}  // namespace v8
