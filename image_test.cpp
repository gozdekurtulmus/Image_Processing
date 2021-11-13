#include <cstdlib>
#include <iostream>

#include "ceng391/image.hpp"

using namespace std;
using ceng391::Image;

int main(int /*argc*/, char** /*argv*/)
{
        Image img(320, 240);
        cout << "Created image of size (" << img.w()
             << "x" << img.h() << ")!" << endl;
        img.set(255);
        img.set_rect(100, -50, 1000, 150, 0);
        img.xsave_pnm("/tmp/test_img");
        return EXIT_SUCCESS;
}

/// Local Variables:
/// mode: c++
/// compile-command: "make -C ../build image-test"
/// End:
