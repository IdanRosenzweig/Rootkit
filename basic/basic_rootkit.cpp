//
// Created by idan on 1/1/24.
//

#include "basic_rootkit.h"

bool operator<(const std::unique_ptr<basic_plugin> &a, const std::unique_ptr<basic_plugin> &b) {
    return a->getMyId().value < b->getMyId().value;
};

bool operator<(const std::unique_ptr<basic_plugin> &a, const id_value& id_val) {
    return a->getMyId().value < id_val;
}

bool operator<(const id_value& id_val, const std::unique_ptr<basic_plugin> &a) {
    return id_val < a->getMyId().value;
}

id_value basic_rootkit::load_plugin(std::unique_ptr<basic_plugin> &&plugin) {
    // generate new id
    id new_id = id_generator.generate_new_id();
    id_value id_val = new_id.value;

    // get type hash
    size_t type_hash = get_type_hash(*plugin);

    // assign id to plugin and load it to th set
    plugin->setMyId(std::move(new_id));
    plugins.insert(
            std::unique_ptr<basic_plugin>(
                    plugin.release()
            )
    );

    // add the new id value to the map
    plugins_ids[type_hash].insert(id_val);

    return id_val;
}

void basic_rootkit::unload_plugin(id_value id_val) {
    // find corresponding plugin in the plugins' set
    auto plug = plugins.find(id_val);

    if (plug != plugins.end()) { // if found
        // get the type hash
        size_t hash = get_type_hash(**plug);

        // unload plugin from the set
        plugins.erase(plug);

        // erase id from the map
        auto& it = plugins_ids[hash];
        it.erase(id_val);

        if (it.empty())
            plugins_ids.erase(hash);
    }
}


const std::unique_ptr<basic_plugin> &basic_rootkit::find_plugin(id_value id_val) {
    auto it = plugins.find(id_val);

    if (it == plugins.end())
        throw;

    return *it;
}

const std::set<std::unique_ptr<basic_plugin>, std::less<>> &basic_rootkit::find_all_loaded_plugins() const {
    return plugins;
}


void basic_rootkit::run_plugin(id_value id_val, bool in_new_thread) {
    const std::unique_ptr<basic_plugin> &plug = find_plugin(id_val);

    if (in_new_thread) {
        std::thread new_thread(&basic_plugin::run, plug.get());
        new_thread.detach();
    } else {
        plug->run();
    }
}

void basic_rootkit::run_all(bool in_new_thread) {
    for (const std::unique_ptr<basic_plugin> &plug: plugins) {
        if (in_new_thread) {
            std::thread new_thread(&basic_plugin::run, plug.get());
            new_thread.detach();
        } else {
            plug->run();
        }
    }
}

