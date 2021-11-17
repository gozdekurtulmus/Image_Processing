#include <string>
#include <iostream>

namespace ceng391 {
typedef unsigned char uchar;
using namespace std;

class Image
{
public:
        Image(int width, int height, int n_channels=1, int step=-1);
        ~Image();

        int w() const { return m_width; }
        int h() const { return m_height; }
        int step() const { return m_step; }
        int channel() const 
        {         
                if (m_n_channels != 1 &&  m_n_channels!= 3 &&  m_n_channels!= 4 )
                {
                        cout << "Number of channels should be 1, 3 or 4. \n";
                        exit(EXIT_FAILURE);
                }

        return m_n_channels; 
        }


        const uchar *data() const { return m_data; }
        uchar *      data()       { return m_data; }
        const uchar *data(int y) const { return m_data + y*m_step; }
        uchar *      data(int y)       { return m_data + y*m_step; }

        void set(uchar value[]){ set_rect(0, 0, m_width, m_height, value);};
        void set_rect(int x_tl, int y_tl, int width, int height, uchar value[]);
        void xsave_ppm(const std::string& filename) const;
        void read_pnm ( std::string filename);
private:
        int m_width;
        int m_height;
        int m_step;
	int m_n_channels;


        uchar *m_data;

};

}
