#pragma once

#include <cstdlib>
#include <cstring>
#include <list>
#include <memory>
#include <optional>

namespace raxpp {

extern "C" {
#include <rax.h>
}

template<class T>
class Radix_Tree {
    struct Rax_Deleter {
        void operator()(rax* rt) { raxFree(rt); }
    };

private:
    std::unique_ptr<rax, Rax_Deleter> c_rax_;
    std::list<std::unique_ptr<T>> data_;

public:
    Radix_Tree() : c_rax_(raxNew(), Rax_Deleter{})
    {
        if (c_rax_.get() == nullptr) {
            throw std::bad_alloc();
        }
    }
    Radix_Tree(Radix_Tree&& other) = default;
    Radix_Tree& operator=(Radix_Tree&&) = default;
    ~Radix_Tree() = default;

    /// TODO(michal)
    Radix_Tree(Radix_Tree const&) = delete;
    Radix_Tree& operator=(const Radix_Tree&) = delete;

    auto insert(std::string const& key, T&& value) -> std::pair<T&, bool>
    {
        auto key_proxy = const_cast<std::string&>(key);  // NOLINT: remove after changes to rax
        data_.push_back(std::make_unique<T>(value));
        void* data = data_.back().get();
        int result = raxInsert(c_rax_.get(),
                               reinterpret_cast<unsigned char*>(&key_proxy[0]),
                               key.size(),
                               data,
                               nullptr);
        if (result == 0 && errno == ENOMEM) {
            std::clog << "Out of memory\n";
            std::abort();
        }
        return std::pair<T&, bool>(*data_.back(), result);
    }

    auto insert(std::string const& key, T const& value) -> std::pair<T&, bool>
    {
        T copy = value;
        return insert(key, std::move(value));
    }

    template<class = std::enable_if_t<not std::is_same_v<T, void>>>
    [[nodiscard]] auto at(std::string const& key) -> T&
    {
        auto key_proxy = const_cast<std::string&>(key);  // NOLINT: remove after changes to rax
        void* data = raxFind(
            c_rax_.get(), reinterpret_cast<unsigned char*>(&key_proxy[0]), key.size());
        if (data == raxNotFound) {
            throw std::out_of_range("no such element: " + key);
        }
        return *reinterpret_cast<T*>(data);
    }

    template<class = std::enable_if_t<not std::is_same_v<T, void>>>
    [[nodiscard]] auto at(std::string const& key) const -> T const&
    {
        auto key_proxy = const_cast<std::string&>(key);  // NOLINT: remove after changes to rax
        void* data = raxFind(
            c_rax_.get(), reinterpret_cast<unsigned char*>(&key_proxy[0]), key.size());
        if (data == raxNotFound) {
            throw std::out_of_range("no such element: " + key);
        }
        return *reinterpret_cast<T const*>(data);
    }

    [[nodiscard]] auto operator[](std::string const& key) -> T&
    {
        auto key_proxy = const_cast<std::string&>(key);  // NOLINT: remove after changes to rax
        void* data = raxFind(
            c_rax_.get(), reinterpret_cast<unsigned char*>(&key_proxy[0]), key.size());
        if (data == raxNotFound) {
            return insert(key, T()).first;
        }
        return *reinterpret_cast<T*>(data);
    }

    template<class = std::enable_if_t<not std::is_same_v<T, void>>>
    [[nodiscard]] auto find(std::string key) const -> std::optional<T>
    {
        void* data = raxFind(
            c_rax_.get(), reinterpret_cast<unsigned char*>(key.data()), key.size());
        if (data == raxNotFound) {
            return std::nullopt;
        }
        return std::make_optional(*reinterpret_cast<T*>(data));
    }

    [[nodiscard]] auto contains(std::string key) const -> bool
    {
        void* data = raxFind(c_rax_.get(), reinterpret_cast<unsigned char*>(&key[0]), key.size());
        return data != raxNotFound;
    }

    [[nodiscard]] constexpr auto size() const noexcept -> std::ptrdiff_t { return c_rax_->numele; }
    [[nodiscard]] constexpr auto empty() const noexcept -> bool { return size() == 0; }
};

}  // namespace raxpp
