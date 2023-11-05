#include "vec.hpp"
#include <utils.hpp>

vec::vec(const std::initializer_list<vec::value_type> &list): _data(list) {}
vec::vec(const container &data): _data(data) {}
vec::vec(container &&data): _data(std::move(data)) {}
vec::vec(size_t sz, size_t value): _data(sz, value) {}
vec::vec(const_iterator begin, const_iterator end): _data(begin, end) {}

vec::iterator vec::begin() noexcept
{
    return _data.begin();
}

vec::iterator vec::end() noexcept
{
    return _data.end();
}

vec::const_iterator vec::begin() const noexcept
{
    return _data.begin();
}

vec::const_iterator vec::end() const noexcept
{
    return _data.end();
}

vec::reverse_iterator vec::rbegin() noexcept
{
    return _data.rbegin();
}

vec::reverse_iterator vec::rend() noexcept
{
    return _data.rend();
}

vec::const_reverse_iterator vec::rbegin() const noexcept
{
    return _data.rbegin();
}

vec::const_reverse_iterator vec::rend() const noexcept
{
    return _data.rend();
}

vec::value_type &vec::front()
{
    return _data.front();
}

vec::value_type &vec::back()
{
    return _data.back();
}

vec::value_type &vec::operator[](size_t pos)
{
    return _data[pos];
}

const vec::value_type &vec::operator[](size_t pos) const
{
    return _data[pos];
}

size_t vec::size() const noexcept
{
    return _data.size();
}

void vec::resize(size_t sz, value_type value)
{
    _data.resize(sz, value);
}

void vec::reserve(size_t cap)
{
    _data.reserve(cap);
}

vec::value_type *vec::data() noexcept
{
    return _data.data();
}

const vec::value_type *vec::data() const noexcept
{
    return _data.data();
}

void vec::push_back(value_type value)
{
    _data.push_back(value);
}

void vec::as_row() const noexcept
{
    _as_row = true;
}

void vec::as_col() const noexcept
{
    _as_row = false;
}

std::ostream &operator<<(std::ostream &out, const vec &v)
{
    char delim = v._as_row ? ' ' : '\n';
    bool first = true;
    for (const auto &d : v._data)
    {
        if (!first)
            out << delim;
        out << d;
        first = false;
    }

    return out;
}

bool operator==(const vec &lhs, const vec &rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    
    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (lhs[i] != rhs[i])
            return false;
    }

    return true;
}
