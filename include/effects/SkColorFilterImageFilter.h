/*
 * Copyright 2012 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkColorFilterImageFilter_DEFINED
#define SkColorFilterImageFilter_DEFINED

#include "SkFlattenable.h"
#include "SkImageFilter.h"

class SkColorFilter;

class SK_API SkColorFilterImageFilter : public SkImageFilter {
public:
    static sk_sp<SkImageFilter> Make(sk_sp<SkColorFilter> cf,
                                     sk_sp<SkImageFilter> input,
                                     const CropRect* cropRect = nullptr);

    void toString(SkString* str) const override;

    Factory getFactory() const override { return CreateProc; }

protected:
    void flatten(SkWriteBuffer&) const override;
    sk_sp<SkSpecialImage> onFilterImage(SkSpecialImage* source, const Context&,
                                        SkIPoint* offset) const override;
    sk_sp<SkImageFilter> onMakeColorSpace(SkColorSpaceXformer*) const override;
    bool onIsColorFilterNode(SkColorFilter**) const override;
    bool onCanHandleComplexCTM() const override { return true; }
    bool affectsTransparentBlack() const override;

private:
    SkColorFilterImageFilter(sk_sp<SkColorFilter> cf,
                             sk_sp<SkImageFilter> input,
                             const CropRect* cropRect);
    static sk_sp<SkFlattenable> CreateProc(SkReadBuffer&);
    friend class SkFlattenable::PrivateInitializer;

    sk_sp<SkColorFilter> fColorFilter;

    typedef SkImageFilter INHERITED;
};

#endif
