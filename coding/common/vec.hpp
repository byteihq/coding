#pragma once

#include <vector>
#include <initializer_list>
#include <ostream>

class vec final
{
public:
    using value_type = size_t;
    using container = std::vector<value_type>;
    using iterator = container::iterator;
    using const_iterator = container::const_iterator;
    using reverse_iterator = container::reverse_iterator;
    using const_reverse_iterator = container::const_reverse_iterator;

private:
    container _data;
    mutable bool _as_row = true;

public:
    vec() = default;
    vec(const std::initializer_list<value_type> &list);
    vec(const container &data);
    vec(container &&data);
    vec(size_t sz, size_t value);
    vec(const_iterator begin, const_iterator end);

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;

    value_type &front();
    value_type &back();

    value_type &operator[](size_t pos);
    const value_type &operator[](size_t pos) const;

    size_t size() const noexcept;
    void resize(size_t sz, value_type value);
    void reserve(size_t cap);

    value_type *data() noexcept;
    const value_type *data() const noexcept;

    void push_back(value_type value);

    void as_row() const noexcept;
    void as_col() const noexcept;

    ~vec() = default;

public:
    friend bool operator==(const vec &lhs, const vec &rhs);
    friend std::ostream &operator<<(std::ostream &out, const vec &v);
};
