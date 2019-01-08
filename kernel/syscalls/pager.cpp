// Copyright 2018 The Fuchsia Authors
//
// Use of this source code is governed by a MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT

#include "priv.h"

#include <fbl/ref_ptr.h>
#include <ktl/move.h>
#include <object/pager_dispatcher.h>
#include <object/vm_object_dispatcher.h>
#include <vm/vm_object_paged.h>


// Single debug VMO. Not protected by a lock or anything.
// Be careful with this.
static fbl::RefPtr<VmObject> debugVmo;
static fbl::RefPtr<VmObjectDispatcher> debugVmoDispatch;

// Global mechanism to set a VMO in the kernel for debug purposes.
// This circumvents all security mechanisms that would otherwise prevent this sort of "global namespace"
// and should never be included in a production build.
zx_status_t sys_debugger_set_vmo(zx_handle_t vmo) {
    auto up = ProcessDispatcher::GetCurrent();
    fbl::RefPtr<VmObjectDispatcher> pVmo;
    zx_status_t status = up->GetDispatcherWithRights(vmo, ZX_RIGHT_READ, &pVmo);
    if(status != ZX_OK) {
        return status;
    }
    debugVmoDispatch = pVmo;
    debugVmo = pVmo->vmo();
    return ZX_OK;
}

zx_status_t sys_debugger_get_vmo(user_out_handle* out) {
    if(!debugVmo.get()) {
        return ZX_ERR_BAD_STATE;
    }
    return out->make(debugVmoDispatch, ZX_RIGHT_READ | ZX_RIGHT_MAP);
    
}

// zx_status_t zx_pager_create
zx_status_t sys_pager_create(uint32_t options, user_out_handle* out) {
    if (options) {
        return ZX_ERR_INVALID_ARGS;
    }

    fbl::RefPtr<Dispatcher> dispatcher;
    zx_rights_t rights;
    zx_status_t result = PagerDispatcher::Create(&dispatcher, &rights);
    if (result != ZX_OK) {
        return result;
    }

    return out->make(ktl::move(dispatcher), rights);
}

// zx_status_t zx_pager_create_vmo
zx_status_t sys_pager_create_vmo(zx_handle_t pager, zx_handle_t port, uint64_t key,
                                 uint64_t size, uint32_t options, user_out_handle* out) {
    if (options) {
        return ZX_ERR_INVALID_ARGS;
    }

    auto up = ProcessDispatcher::GetCurrent();
    fbl::RefPtr<PagerDispatcher> pager_dispatcher;
    zx_status_t status = up->GetDispatcher(pager, &pager_dispatcher);
    if (status != ZX_OK) {
        return status;
    }

    fbl::RefPtr<PortDispatcher> port_dispatcher;
    status = up->GetDispatcherWithRights(port, ZX_RIGHT_WRITE, &port_dispatcher);
    if (status != ZX_OK) {
        return status;
    }

    fbl::RefPtr<PageSource> src;
    status = pager_dispatcher->CreateSource(ktl::move(port_dispatcher), key, &src);
    if (status != ZX_OK) {
        return status;
    }

    fbl::RefPtr<VmObject> vmo;
    status = VmObjectPaged::CreateExternal(ktl::move(src), size, &vmo);
    if (status != ZX_OK) {
        return status;
    }

    fbl::RefPtr<Dispatcher> dispatcher;
    zx_rights_t rights;
    status = VmObjectDispatcher::Create(vmo, &dispatcher, &rights);
    if (status != ZX_OK) {
        return status;
    }

    return out->make(ktl::move(dispatcher), rights);
}
