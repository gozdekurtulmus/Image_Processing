#include "ceng391/image.hpp"

#include<fstream>
#include<cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

namespace ceng391 {

Image::Image(int width, int height, int n_channels,int red, int green, int blue, int alpha, int step)
{
        if (n_channels != 1 || n_channels!= 3 ||  n_channels!= 4 )
        {
                cout << "Number of channels should be 1, 3 or 4. ";
                EXIT_FAILURE;
        }

        m_width = width;
        m_height = height;
       
	if (step < m_width)
                step = m_width;
        m_step = step;

        m_data = new uchar[m_step * m_height];

        m_n_channels = n_channels;

}

Image::~Image()
{
        delete [] m_data;
}

void Image::set_rect(int x_tl, int y_tl, int width, int height,int n_channels, uchar value[])
{
        if (x_tl < 0) {
                width += x_tl;
                x_tl = 0;
        }

        if (y_tl < 0) {
                height += y_tl;
                y_tl = 0;
        }

        size_t length = min(width, m_width - x_tl);
        int y_max = min(y_tl + height, m_height);
        for (int y = y_tl; y < y_max; ++y) {
                uchar *row_y = data(y) + x_tl;

		if ( n_channels > 1) 
		{
                        for (int x = x_tl; x<length; x++)
                        {
                                memset(m_red, value[0], sizeof(uchar));
                                memset(m_green, value[1], sizeof(uchar));
                                memset(m_blue, value[2], sizeof(uchar));

                                row_y[y*m_n_channels ] = value[0] ;
                                row_y[y*m_n_channels + 1 ] = value[1] ;
                                row_y[y*m_n_channels + 2] = value[2] ; 

                                if ( m_n_channels == 4 )
                                {
                                        memset(m_alpha, value[3], sizeof(uchar)); 
                                        row_y[y*m_n_channels + 3 ] = value[3] ; 
                                }                 
                        }


                }
                else 
                {
            		memset(row_y, value[0], length);   
                }

        }
}


void Image::xsave_pnm(const  std::string& filename) const
{
        const string magic_head = "P5";
        ofstream fout;
        string extended_name = filename + ".ppm";
        fout.open(extended_name.c_str(), ios::out | ios::binary);
        fout << magic_head << "\n";
        fout << m_width << " " << m_height << " 255\n";

        for (int y = 0; y < m_height; ++y) {
                const uchar *row_data = this->data(y);
                fout.write(reinterpret_cast<const char*>(row_data),
                           m_width*sizeof(uchar)*m_n_channels);
        }

        fout.close();
}


}


