#include "shared_ptr_convert.h"

#include <stdio.h>
#include <assert.h>

struct DUMMY {
    int dummy;

    ~DUMMY() {
        printf("destroy dummy object\n");
    }
};

void test_convert_boost_to_std() {
    boost::shared_ptr<DUMMY> boost_sp(new DUMMY);

    assert(boost_sp.use_count() == 1);

    {
        std::shared_ptr<DUMMY> std_sp = convert_boost_sp_to_std<DUMMY>(boost_sp);

        assert(boost_sp.use_count() == 2);
        assert(std_sp.use_count() == 1);
    }

    assert(boost_sp.use_count() == 1);
}

void test_convert_std_to_boost() {
    std::shared_ptr<DUMMY> std_sp(new DUMMY);

    assert(std_sp.use_count() == 1);

    {
        boost::shared_ptr<DUMMY> boost_sp = convert_std_sp_to_boost<DUMMY>(std_sp);

        assert(std_sp.use_count() == 2);
        assert(boost_sp.use_count() == 1);
    }

    assert(std_sp.use_count() == 1);
}

int main() {
    test_convert_boost_to_std();
    test_convert_std_to_boost();

    return 0;
}
