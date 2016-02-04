// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_COMPILER_ESCAPE_ANALYSIS_REDUCER_H_
#define V8_COMPILER_ESCAPE_ANALYSIS_REDUCER_H_

#include "src/compiler/escape-analysis.h"
#include "src/compiler/graph-reducer.h"

namespace v8 {
namespace internal {
namespace compiler {

// Forward declarations.
class JSGraph;


class EscapeAnalysisReducer final : public AdvancedReducer {
 public:
  EscapeAnalysisReducer(Editor* editor, JSGraph* jsgraph,
                        EscapeAnalysis* escape_analysis, Zone* zone);

  Reduction Reduce(Node* node) final;

 private:
  Reduction ReduceLoadField(Node* node);
  Reduction ReduceStoreField(Node* node);
  Reduction ReduceAllocate(Node* node);
  Reduction ReduceFinishRegion(Node* node);
  Reduction ReduceReferenceEqual(Node* node);

  Reduction ReplaceWithDeoptDummy(Node* node);

  JSGraph* jsgraph() const { return jsgraph_; }
  EscapeAnalysis* escape_analysis() const { return escape_analysis_; }
  Zone* zone() const { return zone_; }

  JSGraph* const jsgraph_;
  EscapeAnalysis* escape_analysis_;
  Zone* const zone_;

  DISALLOW_COPY_AND_ASSIGN(EscapeAnalysisReducer);
};

}  // namespace compiler
}  // namespace internal
}  // namespace v8

#endif  // V8_COMPILER_ESCAPE_ANALYSIS_REDUCER_H_
