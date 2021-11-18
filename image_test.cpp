#include <cstdlib>
#include <iostream>

#include "ceng391/image.hpp"

using namespace std;
typedef unsigned char uchar;
using ceng391::Image;

int main(int /*argc*/, char** /*argv*/)
{
     
     // ------------   EXERCISE 1   ------------ //
     Image img(320, 240, 3);
     Image img_2(320, 240, 4);

     uchar value[3] = {255, 100, 50};
     uchar value_2[3] = {120, 55, 55};
     uchar value2[4] = {255, 50, 50, 0};
     uchar value2_2[4] = {120, 255, 55, 0};


     // EXERCISE 1 - RGB Example//

     cout << "Created image of size (" << img.w()
          << "x" << img.h() << ")!" << " Channels: " << img.channel() << endl;
             
     img.set(value);
     img.set_rect(100, -50, 1000, 150,value_2);
     img.xsave_ppm("./ex1_rgb");
         

     // EXERCISE 1 - RGBA Example //

     cout << "Created image of size (" << img_2.w()
          << "x" << img_2.h() << ")!" << " Channels: " << img_2.channel() << endl;
             
     img_2.set(value2);
     img_2.set_rect(100, -50, 1000, 150,value2_2);
     img_2.xsave_ppm("./ex1_rgba");
     

     // ------------   EXERCISE 2   ------------ //
     Image img_3(320,240,4);
     img_3.read_pnm("./ex1_rgb.ppm");
     img_3.xsave_ppm("./ex2_check");
     

     // ------------   EXERCISE 3   ------------ //
     uchar grayscale[1] = {255};
     uchar grayscale_2[1] = {0};

     uchar rgb[3] = {255,100,55};
     uchar rgb_2[3] = {100,0,255};

     uchar rgba[4] = {255,100,100,255};
     uchar rgba_2[4] = {0,255,0,255};

     Image img_grayscale(320, 240);
     img_grayscale.set(grayscale);
     img_grayscale.set_rect(100, -50, 1000, 150,grayscale_2);

     Image img_rgb(320, 240, 3);
     img_rgb.set(rgb);
     img_rgb.set_rect(100, -50, 1000, 150,rgb_2);

     Image img_rgba(320, 240, 4);
     img_rgba.set(rgba);
     img_rgba.set_rect(100, -50, 1000, 150,rgba_2);


     //EXERCISE 3 : grayscale to rgb//
     img_grayscale.to_rgb();
     img_grayscale.xsave_ppm("./ex3_grayscale_to_rgb");

     //EXERCISE 3 :  rgb to rgba //
     img_rgb.to_rgba();
     img_rgb.xsave_ppm("./ex3_rgb_to_rgba");

     //EXERCISE 3 :  rgba to grayscale //
     img_rgb.to_grayscale();
     img_rgb.xsave_ppm("./ex3_rgba_to_grayscale");


     //EXERCISE 3 :  rgba to rgb //
     img_rgba.to_rgb();
     img_rgba.xsave_ppm("./ex3_rgba_to_rgb");
     

     //EXERCISE 3 : rgb to grayscale //
     img_rgba.to_grayscale();
     img_rgba.xsave_ppm("./ex3_rgb_to_grayscale");

     //EXERCISE 3 :  grayscale to rgba //
     img_rgba.to_rgba();
     img_rgba.xsave_ppm("./ex3_grayscale_to_rgba");

        return EXIT_SUCCESS;
}

/// Local Variables:
/// mode: c++
/// compile-command: "make -C ../build image-test"
/// End:
