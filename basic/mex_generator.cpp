//
// Created by idan on 1/1/24.
//

#include "mex_generator.h"

mex_generator::mex_generator() : largest(0) {}

id mex_generator::generate_new_id() {
    id_value next_val;
    if (!freed.empty()) {
        next_val = freed.front();
        freed.pop();
    } else {
        next_val = largest;
        largest++;
    }

    return {this, next_val};
}

void mex_generator::free_id(id_value id) {
    freed.push(id);
}

id::id() : master(nullptr), value(ID_MAX_VAL) {

}
id::id(mex_generator *master, id_value value) : master(master), value(value) {}

id::~id() {
    if (master != nullptr)
        master->free_id(value);
}

id &id::operator=(id &&id) noexcept {
    value = id.value;
    master = id.master;

    id.master = nullptr;

    return *this;
}


