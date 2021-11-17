#include <cstdlib>
#include <iostream>

#include "ceng391/image.hpp"

using namespace std;
typedef unsigned char uchar;
using ceng391::Image;

int main(int /*argc*/, char** /*argv*/)
{
        // exercise 1 - RGB Example//
        Image img(320, 240, 3);
        img.channel();
        cout << "Created image of size (" << img.w()
             << "x" << img.h() << ")!" << " Channels: " << img.channel() << endl;
             
        uchar value[3] = {255, 100, 50};
        img.set(value);
        uchar value2[3] = {120, 55, 55};
        img.set_rect(100, -50, 1000, 150,value2);
        img.xsave_ppm("./ex1_rgb");
        //

        // exercise 1 - RGBA Example //
        Image img_2(320, 240, 4);
        img_2.channel();
        cout << "Created image of size (" << img_2.w()
             << "x" << img_2.h() << ")!" << " Channels: " << img_2.channel() << endl;
             
        uchar value_2[4] = {255, 50, 50, 0};
        img_2.set(value_2);
        uchar value2_2[4] = {120, 255, 55, 0};
        img_2.set_rect(100, -50, 1000, 150,value2_2);
        img_2.xsave_ppm("./ex1_rgba");
        //

        // exercise 2 //
        Image img_3(320,240,4);
        img_3.read_pnm("./ex1_rgb.ppm");
        img_3.xsave_ppm("./ex2_check");
        //






        return EXIT_SUCCESS;
}

/// Local Variables:
/// mode: c++
/// compile-command: "make -C ../build image-test"
/// End:
