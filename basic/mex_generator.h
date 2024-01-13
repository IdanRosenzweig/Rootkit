//
// Created by idan on 1/1/24.
//

#ifndef ROOTKIT_MEX_GENERATOR_H
#define ROOTKIT_MEX_GENERATOR_H

#include <queue>
#include <climits>

typedef unsigned int id_value;
#define ID_MAX_VAL UINT_MAX

class mex_generator;
struct id {
private:
    mex_generator* master;

public:
    id_value value;

    id();
    id(mex_generator *master, id_value value);

    id& operator=(id&& id) noexcept;

    virtual ~id();

    operator id_value () {
        return value;
    }
};

class mex_generator {
private:
    id_value largest;
    std::queue<id_value> freed;

public:
    mex_generator();

    id generate_new_id();
    void free_id(id_value);
};


#endif //ROOTKIT_MEX_GENERATOR_H
