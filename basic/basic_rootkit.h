//
// Created by idan on 12/24/23.
//

#ifndef ROOTKIT_BASIC_ROOTKIT_H
#define ROOTKIT_BASIC_ROOTKIT_H

#include "basic_plugin.h"
#include "mex_generator.h"

#include <set>
#include <memory>
#include <vector>
#include <thread>
#include <iostream>
#include <map>

#define get_type_hash(x) typeid(x).hash_code()

bool operator<(const std::unique_ptr<basic_plugin> &a, const std::unique_ptr<basic_plugin> &b);

bool operator<(const std::unique_ptr<basic_plugin> &a, const id_value &id_val);

bool operator<(const id_value &id_val, const std::unique_ptr<basic_plugin> &a);

class basic_rootkit {
protected:
    mex_generator id_generator;
    std::set<std::unique_ptr<basic_plugin>, std::less<>> plugins; // storing loaded plugins, each one holds uniquely assigned id
    std::map<size_t, std::set<id_value>, std::less<>> plugins_ids; // each type and its implementation's ids

public:

//    template<class T>
//    void load_plugin(std::unique_ptr<T>&& plugin) {
//        static_assert(std::is_base_of<basic_plugin, T>());
//
//        features.push_back(
//                std::unique_ptr<basic_plugin>(
//                        static_cast<basic_plugin *>(plugin.release()) // todo change to dynamic cast if it doesn't work
//                )
//        );
//    }

    // load new plugin to the set, assign a unique id to it and save the id in the map
    id_value load_plugin(std::unique_ptr<basic_plugin> &&plugin);


    void unload_plugin(id_value id_val);

    template<class T>
    void unload_all_type_plugins() {
        for (const id_value& id_val : find_type_loaded_ids<T>()) {
            unload_plugin(id_val);
        }
    }


    const std::unique_ptr<basic_plugin> &find_plugin(id_value id_val);

    template<class T>
    const std::set<id_value> &find_type_loaded_ids() {
        size_t type_hash = get_type_hash(T);

        return plugins_ids[type_hash];
    }

    const std::set<std::unique_ptr<basic_plugin>, std::less<>> &find_all_loaded_plugins() const;


    void run_plugin(id_value id_val, bool in_new_thread = true);

    template<class T>
    void run_all_type_plugins(bool in_new_thread) {
        for (const id_value& id_val : find_type_loaded_ids<T>()) {
            run_plugin(id_val, in_new_thread);
        }
    }

    void run_all(bool in_new_thread = true);


//    virtual void stop_rootkit() {}
//
//    void stop_all() {
//        for (const std::unique_ptr<basic_plugin> &item: features) {
//            item->stop();
//        }
//    }

};

#endif //ROOTKIT_BASIC_ROOTKIT_H
