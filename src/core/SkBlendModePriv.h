/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkBlendModePriv_DEFINED
#define SkBlendModePriv_DEFINED

#include "SkBlendMode.h"
#include "SkPM4f.h"

class SkRasterPipeline;

bool SkBlendMode_SupportsCoverageAsAlpha(SkBlendMode);

static inline bool SkBlendMode_CaresAboutRBOrder(SkBlendMode mode) {
    return (mode > SkBlendMode::kLastSeparableMode);
}

void SkBlendMode_AppendStagesNoClamp(SkBlendMode, SkRasterPipeline*);
void SkBlendMode_AppendClampIfNeeded(SkBlendMode, SkRasterPipeline*);

static inline void SkBlendMode_AppendStages(SkBlendMode mode, SkRasterPipeline* p) {
    // Only plus clamps, so maybe append a clamping plus here instead of a second stage?
    SkBlendMode_AppendStagesNoClamp(mode, p);
    SkBlendMode_AppendClampIfNeeded(mode, p);
}

enum class SkBlendModeCoeff {
    kZero, /** 0 */
    kOne,  /** 1 */
    kSC,   /** src color */
    kISC,  /** inverse src color (i.e. 1 - sc) */
    kDC,   /** dst color */
    kIDC,  /** inverse dst color (i.e. 1 - dc) */
    kSA,   /** src alpha */
    kISA,  /** inverse src alpha (i.e. 1 - sa) */
    kDA,   /** dst alpha */
    kIDA,  /** inverse dst alpha (i.e. 1 - da) */

    kCoeffCount
};

bool SkBlendMode_AsCoeff(SkBlendMode mode, SkBlendModeCoeff* src, SkBlendModeCoeff* dst);

SkPM4f SkBlendMode_Apply(SkBlendMode, const SkPM4f& src, const SkPM4f& dst);

#if SK_SUPPORT_GPU
#include "GrXferProcessor.h"
const GrXPFactory* SkBlendMode_AsXPFactory(SkBlendMode);
#endif

#endif
