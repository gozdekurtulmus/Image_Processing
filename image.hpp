#include <string>

namespace ceng391 {
typedef unsigned char uchar;

class Image
{
public:
        Image(int width, int height, int step=-1);
        ~Image();

        int w() const { return m_width; }
        int h() const { return m_height; }
        int step() const { return m_step; }

        const uchar *data() const { return m_data; }
        uchar *      data()       { return m_data; }
        const uchar *data(int y) const { return m_data + y*m_step; }
        uchar *      data(int y)       { return m_data + y*m_step; }

        void set(uchar value) { set_rect(0, 0, m_width, m_height, value); }
        void set_rect(int x_tl, int y_tl, int width, int height, uchar value);

        void xsave_pnm(const std::string& filename) const;
private:
        int m_width;
        int m_height;
        int m_step;

        uchar *m_data;
};

}
