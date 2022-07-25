#ifndef __SHARED_PTR_CONVERT_H__
#define __SHARED_PTR_CONVERT_H__

#include <boost/shared_ptr.hpp>
#include <memory>

template<typename T, typename SP>
struct ConvertSpDeleter {
    SP sp;

    ConvertSpDeleter(const SP &rhs) : sp(rhs){
    }

    ConvertSpDeleter(const ConvertSpDeleter &rhs) : sp(rhs.sp) {
    }

    ConvertSpDeleter(ConvertSpDeleter &&rhs) : sp(rhs.sp) {
    }

    void operator() (T *) {
        sp.reset();
    }
};

template<typename T>
std::shared_ptr<T> convert_boost_sp_to_std(const boost::shared_ptr<T> &boost_sp) {
    ConvertSpDeleter<T, boost::shared_ptr<T>> deleter(boost_sp);
    return boost_sp ? (std::shared_ptr<T>(boost_sp.get(), deleter)) : nullptr;
}

template<typename T>
boost::shared_ptr<T> convert_std_sp_to_boost(const std::shared_ptr<T> &std_sp) {
    ConvertSpDeleter<T, std::shared_ptr<T>> deleter(std_sp);
    return std_sp ? (boost::shared_ptr<T>(std_sp.get(), deleter)) : nullptr;
}

#endif
