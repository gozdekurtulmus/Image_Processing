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
        
        size_t length = min(width, m_width - x_tl);
        int y_max = min(y_tl + height, m_height);

        for (int y = y_tl; y < y_max; ++y)
{        
                
		if ( m_n_channels > 1) 
		{       
                        for (size_t x = x_tl; x<length; ++x )
                        {

                                uchar *row_y = data(y) + x * m_n_channels;
                                memset(row_y, value[0], sizeof(uchar)); //R
                                memset(row_y+1, value[1], sizeof(uchar)); //G
                                memset(row_y+2, value[2], sizeof(uchar));  //B
                                
                                if( m_n_channels == 4){
                                        memset(row_y+3, (uchar)255, sizeof(uchar)); //A
                                }         
                        }
                
                }
                else 
                {
                        uchar *row_y = data(y) + x_tl;
            		memset(row_y, value[0], length); 
                }

        }
}


void Image::xsave_ppm(const  std::string& filename) const
{
        string magic_head = "P6";
        string extended_name = filename + ".ppm";

        if(m_n_channels == 1){
                magic_head = "P5";
                extended_name = filename + ".pgm";
        }
        ofstream fout;
        fout.open(extended_name.c_str(), ios::out | ios::binary);
        fout << magic_head << "\n";
        fout << m_width<< " " << m_height << " 255\n";

        int mult_coef = m_n_channels;
        if(m_n_channels == 4){
                mult_coef = 3;
        }
         for (int y = 0; y < m_height; ++y) {

                for(int x = 0; x<m_width; ++x){
                        
                 const uchar *row_data = this->data(y) + x * m_n_channels;
                fout.write(reinterpret_cast<const char*>(row_data),
                           sizeof(uchar)* mult_coef);
                           
                }
         }

        fout.close();

}
void Image::read_pnm(std::string filename)
{
        
          ifstream fin(filename);
          string line;
          int width, height = 0;
          uchar *data ;
          if( fin.is_open()){

                  getline(fin, line);

                  if(line == "P6" || line == "P5" ||  line == "P4")
                  {
                       
                        getline(fin,line);
                        string whm[3];
                        int counter = 0;
                        for( int i=0; i<line.length(); i++){
                                if(line[i] == ' '){
                                        counter ++;
                                }
                                else
                                whm[counter] += line[i];
                          }
                          
                        width = stoi(whm[0]);
                        height =stoi(whm[1]);
                        int max_value = stoi(whm[2]);

                        getline(fin,line);
                        data = new uchar[width * height * 4];
                        uchar values[width * height * 4];
                        strcpy( (char*) values, line.c_str());
                          
                        for ( int i = 0; i< width * height; ++i) 
                        {
                                memset(data+i*4, values[i * 3 ], sizeof(uchar));
                                memset(data+i*4 + 1, values[i * 3 + 1], sizeof(uchar));
                                memset(data+i*4 + 2, values[i * 3 + 2], sizeof(uchar));
                                memset(data+i*4 + 3, (uchar) 255, sizeof(uchar));
                             
                        }
                 }    
                 else { cout << "Wrong version."; };


         }
         else {
                 cout << "Couldn't open the file.";
         }
        m_data = data; //Just to check and see if it is reading true by writing out in the test file.

 }

 void Image::to_rgb()
 {
        if (m_n_channels == 3)
        {
                return;
        }

        int n_channels = 3;
        uchar * new_data = new uchar[m_width * m_height * n_channels];

        if ( m_n_channels == 1)
        {
                for ( int i = 0; i< m_width * m_height; ++i) 
                {
                        memset(new_data+i*3, m_data[i], sizeof(uchar));
                        memset(new_data+i*3 + 1, m_data[i], sizeof(uchar));
                        memset(new_data+i*3 + 2, m_data[i], sizeof(uchar));
                }       

        }

        else if (m_n_channels == 4)
        {
                for ( int i = 0; i< m_width * m_height; ++i) 
                {
                        memset(new_data+i*3, m_data[i * 4 ], sizeof(uchar));
                        memset(new_data+i*3 + 1, m_data[i * 4 + 1 ], sizeof(uchar));
                        memset(new_data+i*3 + 2, m_data[i * 4 + 1], sizeof(uchar));
                }       

        }
        m_data = new_data;
        m_n_channels = n_channels;
        m_step = m_n_channels * m_width;
        return;
 }


 void Image::to_grayscale()
 {
        if ( m_n_channels == 1)
        {  
                return;
        }
        int n_channels = 1;
        uchar * new_data = new uchar[m_width * m_height];

        if (m_n_channels == 3)
        {
                for (int i =0; i<m_width* m_height; ++i)
                {
                        uchar value = m_data[i*3] * 0.3 + m_data[i*3+1] * 0.59 + m_data[i*3+2]*0.11;
                        memset(new_data+i, value, sizeof(uchar));
                }
        }
        if(m_n_channels == 4)
        {
                for (int i =0; i<m_width* m_height; ++i)
                {
                        uchar value = m_data[i*4] * 0.3 + m_data[i*4+1] * 0.59 + m_data[i*4+2]*0.11;
                        memset(new_data+i, value, sizeof(uchar));
                }
        }

        m_data = new_data;
        m_n_channels = n_channels;
        m_step = m_n_channels * m_width;
        return;
 }


 void Image::to_rgba()
 {      
         if( m_n_channels == 4)
        {
                return;
        }

        int n_channels = 4;
        uchar * new_data = new uchar[m_width * m_height * n_channels];

        if ( m_n_channels == 1)
        {
                for ( int i = 0; i< m_width * m_height; ++i) 
                {
                        memset(new_data+i*4, m_data[i], sizeof(uchar));
                        memset(new_data+i*4 + 1, m_data[i], sizeof(uchar));
                        memset(new_data+i*4 + 2, m_data[i], sizeof(uchar));
                        memset(new_data+i*4 + 3, (uchar) 255, sizeof(uchar));
                }       
        }

        else if (m_n_channels == 3)
        {
                for ( int i = 0; i< m_width * m_height; ++i) 
                {
                        memset(new_data+i*4, m_data[i*3], sizeof(uchar));
                        memset(new_data+i*4 + 1, m_data[i*3 + 1], sizeof(uchar));
                        memset(new_data+i*4 + 2, m_data[i*3 + 2], sizeof(uchar));
                        memset(new_data+i*4 + 3, (uchar) 255, sizeof(uchar));
                }    
        }
       
        m_data = new_data;
        m_n_channels = n_channels;
        m_step = m_n_channels * m_width;
        return;
 }




}


