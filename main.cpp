#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

class Resource {
  public:
    explicit Resource(const std::string &name) : name_(name) {
        std::cout << "open " << name_ << "\n";
    }
    ~Resource() { std::cout << "close " << name_ << "\n"; }
    const std::string &name() const { return name_; }

  private:
    std::string name_;
};

// Hands a fresh, solely-owned Resource to the caller.
std::unique_ptr<Resource> build(const std::string &name) {
    return std::make_unique<Resource>(name);
}

int main() {
    std::map<std::string, std::shared_ptr<Resource>> handles;
    std::map<std::string, std::weak_ptr<Resource>> observers;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream in(line);
        std::string cmd, a, b;
        in >> cmd >> a >> b; // unused words stay empty

        if (cmd == "open") {
            // TODO: refuse a name that is already open, otherwise build it and
            // take ownership
            if (handles.count(a)) {
                std::cout << "error " << a << " exists\n";
            } else {
                handles[a] = std::shared_ptr<Resource>(build(a));
            }
        } else if (cmd == "share") {
            // TODO: b joins the ownership of a
            auto source = handles.find(a);

            if (source == handles.end() || !source->second) {
                std::cout << "error " << a << "missing\n";
            } else if (handles.count(b)) {
                std::cout << "error " << b << " exists\n";
            } else {
                handles[b] = source->second;
            }
        } else if (cmd == "drop") {
            // TODO: release the handle named a
            auto it = handles.find(a);
            if (it != handles.end()) {
                it->second.reset();
                handles.erase(it);
            }
        } else if (cmd == "watch") {
            // TODO: observer b watches the object behind a, without owning it
            auto source = handles.find(a);
            if (source == handles.end() || !source->second) {
                std::cout << "error " << a << "missing\n";
            } else {
                observers[b] = source->second;
            }
        } else if (cmd == "peek") {
            // TODO: report what observer a sees
            auto observer = observers.find(a);
            if (observer == observers.end()) {
                std::cout << "error " << a << " unknown\n";
            } else if (auto resource = observer->second.lock()) {
                std::cout << "alive " << resource->name()
                          << " owners=" << resource.use_count() - 1 << "\n";
            } else {
                std::cout << "expired\n";
            }
        } else if (cmd == "owners") {
            // TODO: report how many handles own a
            auto it = handles.find(a);
            std::cout << "owners " << a << "="
                      << (it == handles.end() ? 0 : it->second.use_count())
                      << "\n";
        }
    }

    // TODO: release every remaining handle, in sorted-name order
    for (auto &i : handles) {
        i.second.reset();
    }
    return 0;
}
