#include "challenger/chDialog.hpp"
#include <cassert>

namespace challenger {
    filelist_iterator begin(const filelist_iterator::pointer ptr) noexcept {
        assert(!!ptr);
        return filelist_iterator(ptr);
    };
    filelist_iterator end(const filelist_iterator::pointer ptr) noexcept {
        assert(!!ptr);
        filelist_iterator::pointer last = ptr;
        while(*last) { ++last; }
        return filelist_iterator(last);
    };
}
