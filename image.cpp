#include "ceng391/image.hpp"

#include<fstream>
#include<cstring>
#include <cstdlib>


namespace ceng391 {

Image::Image(int width, int height, int n_channels, int step)
{
        m_width = width;
        m_height = height;
       
	if (step < m_width)
                step = m_width;

        m_n_channels = n_channels;
        m_step = step*m_n_channels;

        m_data = new uchar[m_step * m_height];
       // m_data = (uchar*) malloc(m_step * m_height * n_channels);

}

Image::~Image()
{
        delete [] m_data;
}

void Image::set_rect(int x_tl, int y_tl, int width, int height,uchar value[])
{

       if (x_tl < 0) {
                width += x_tl;
                x_tl = 0;
        }

        if (y_tl < 0) {
                height += y_tl;
                y_tl = 0;
        }
        
        int length = min(width, m_width - x_tl);
        int y_max = min(y_tl + height, m_height);

        for (int y = y_tl; y < y_max; ++y)
{        
                
		if ( m_n_channels > 1) 
		{       
                        for (int x = x_tl; x<length; ++x )
                        //uchar *r, *g, *b, *a = new uchar[y_max * length];
                        
                        {
                                //memset(&pixels.r, value[0], sizeof(uchar));
                        //        m_data[length * y + x] = value[0];
                        //        m_data[length * y + x + 1] = value[1];
                        //        m_data[length * y + x+ 2] = value[2];

                                //R = m_data[1:height,:] ;
                                //G = m_data[height!1: height*2,:] ;
                                //B = m_data[height*2+1:height*3,:];
                         
                         //       memset(&r, value[0], sizeof(uchar));
                         //       memset(&g, value[1], sizeof(uchar));
                         //       memset(&b, value[2], sizeof(uchar));
        
                         //      m_data[y * length * 3 + x * 3] = value[0];
                         //       m_data[y * length * 3 + x * 3 + 1] = value[1];
                         //       m_data[y * length * 3  + x* 3 + 2] = value[2];
                                uchar *row_y = data(y) + x*3;
                                memset(row_y, value[0], 1);
                                memset(row_y+1, value[1], 1);
                                memset(row_y+2, value[2], 1);

                         //       uchar alpha = 255;
                         //       if ( m_n_channels == 4 )
                         //       {
                         //               alpha = value[3];                               
                         //       }


                         //       memset(&a, alpha, sizeof(uchar)); 
                         //       memset(row_y, alpha, sizeof(uchar));;                 
                        }
                }
                else 
                {
                        uchar *row_y = data(y) + x_tl*m_n_channels;
            		memset(row_y, value[0], length); 
                }

        }
}


void Image::xsave_pnm(const  std::string& filename) const
{
        
        string magic_head = "P5";
        if (m_n_channels > 1) 
        {
                magic_head = "P6";
        }
        ofstream fout;
        string extended_name = filename + ".ppm";
        fout.open(extended_name.c_str(), ios::out | ios::binary);
        fout << magic_head << "\n";
        fout << m_width<< " " << m_height << " 255\n";

         for (int y = 0; y < m_height; ++y) {

                for(int x = 0; x<m_width; ++x){
                        
                 const uchar *row_data = this->data(y) +x*3;
                fout.write(reinterpret_cast<const char*>(row_data),
                           sizeof(uchar)*3);
                }
         }
        // }



        // 		for (int x = 0; x < m_width * m_height * m_n_channels; ++x) {
	// 		uchar value = m_data[x];
        //                 fout.write(reinterpret_cast<const char*>(value),sizeof(uchar));	
	// 	}
	
       // for ( int y =0; y<m_height; ++y){
       //         for(int x=0; x<m_width; ++x){
       //                 fout.write(reinterpret_cast<const char*>(pixels[y * m_width + x].r),
       //                    sizeof(uchar));
       //                 fout.write(reinterpret_cast<const char*>(pixels[y * m_width + x].g),
       //                    sizeof(uchar));
       //                 fout.write(reinterpret_cast<const char*>(pixels[y * m_width + x].b),
       //                    sizeof(uchar));

        //        }

        //}


        fout.close();

}


}


