#include <cstdlib>
#include <iostream>

#include "ceng391/image.hpp"

using namespace std;
typedef unsigned char uchar;
using ceng391::Image;

int main(int /*argc*/, char** /*argv*/)
{
        Image img(320, 240, 3);
        cout << "Created image of size (" << img.w()
             << "x" << img.h() << ")!" << "channels: " << img.channel() << endl;
        uchar value[1] = {255};
        img.set(value);
        uchar value2[1] = {0};
        img.set_rect(100, -50, 1000, 150, 1, value2);
        img.xsave_pnm("/tmp/test_img");
        return EXIT_SUCCESS;
}

/// Local Variables:
/// mode: c++
/// compile-command: "make -C ../build image-test"
/// End:
