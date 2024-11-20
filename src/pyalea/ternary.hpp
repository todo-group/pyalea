#pragma once
#include <alps/alea/transformer.hpp>

namespace alps { namespace alea {
    template <typename T> struct scalar_ternary_transformer;
}}

namespace alps { namespace alea {

template <typename T>
scalar_ternary_transformer<T> make_transformer(std::function<T(T,T,T)> fn)
{
    return scalar_ternary_transformer<T>(fn);
}

template <typename T>
struct scalar_ternary_transformer
    : public transformer<T>
{
public:
    scalar_ternary_transformer(const std::function<T(T,T,T)> &fn) : fn_(fn) { }

    size_t in_size() const { return 3; }

    size_t out_size() const { return 1; }

    column<T> operator() (const column<T> &in) const
    {
        if (in.size() != in_size())
            throw size_mismatch();

        column<T> ret(1);
        ret(0) = fn_(in(0), in(1), in(2));
        return ret;
    }

private:
    std::function<T(T,T,T)> fn_;
};

}}  /* namespace alps::alea */
