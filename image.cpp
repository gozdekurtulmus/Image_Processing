#include "ceng391/image.hpp"

#include<fstream>
#include<cstring>

using namespace std;

namespace ceng391 {

Image::Image(int width, int height, int step)
{
        m_width = width;
        m_height = height;
        if (step < m_width)
                step = m_width;
        m_step = step;

        m_data = new uchar[m_step * m_height];
}

Image::~Image()
{
        delete [] m_data;
}

void Image::set_rect(int x_tl, int y_tl, int width, int height, uchar value)
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
                memset(row_y, value, length);
        }
}

void Image::xsave_pnm(const  std::string& filename) const
{
        const string magic_head = "P5";
        ofstream fout;
        string extended_name = filename + ".pgm";
        fout.open(extended_name.c_str(), ios::out | ios::binary);
        fout << magic_head << "\n";
        fout << m_width << " " << m_height << " 255\n";
        for (int y = 0; y < m_height; ++y) {
                const uchar *row_data = this->data(y);
                fout.write(reinterpret_cast<const char*>(row_data),
                           m_width*sizeof(uchar));
        }
        fout.close();
}

}
