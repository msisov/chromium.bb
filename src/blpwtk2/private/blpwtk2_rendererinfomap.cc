/*
 * Copyright (C) 2013 Bloomberg Finance L.P.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <blpwtk2_rendererinfomap.h>

#include <blpwtk2_constants.h>

#include <base/logging.h>  // for DCHECK
#include <content/browser/renderer_host/render_process_host_impl.h>
#include <content/public/browser/site_instance.h>

namespace blpwtk2 {

RendererInfoMap::RendererInfoMap()
{
}

RendererInfoMap::~RendererInfoMap()
{
}

int RendererInfoMap::obtainHostAffinity(int renderer)
{
    DCHECK(renderer == Constants::ANY_OUT_OF_PROCESS_RENDERER
        || renderer >= 0);

    if (renderer == Constants::ANY_OUT_OF_PROCESS_RENDERER) {
        return content::SiteInstance::kNoProcessAffinity;
    }
    else {
        base::AutoLock guard(d_lock);
        RendererInfo& info = d_map[renderer];
        if (-1 == info.d_hostId) {
            info.d_hostId = content::RenderProcessHostImpl::GenerateUniqueId();
        }
        return info.d_hostId;
    }
}

bool RendererInfoMap::dcheckProfileForRenderer(int renderer, Profile* profile)
{
    DCHECK(renderer >= 0);

    base::AutoLock guard(d_lock);
    RendererInfo& info = d_map[renderer];
    return info.dcheckProfile(profile);
}

}  // close namespace blpwtk2

