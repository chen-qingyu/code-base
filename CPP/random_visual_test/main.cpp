#include <fstream>
#include <iostream>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <pyincpp.hpp>

using namespace boost;
using namespace pyincpp;

int main()
{
    // 创建一个512x512的图像，像素格式为RGB8
    gil::rgb8_image_t img(512, 512);
    auto view = gil::view(img);

    // 生成随机半白半黑的图像
    for (int y = 0; y < view.height(); ++y)
    {
        for (int x = 0; x < view.width(); ++x)
        {
            if (Int::random(0, 1).is_zero())
            {
                view(x, y) = gil::rgb8_pixel_t(255, 255, 255); // 设置像素为白色
            }
            // 否则保持背景色（黑色，因为gil::rgb8_image_t默认初始化为黑色）
        }
    }

    // 将图像写入PNG文件
    gil::write_view("output.png", gil::const_view(img), gil::png_tag{});

    std::cout << "Image generated and saved as output.png" << std::endl;

    // 随机性检验
    std::stringstream ss;
    for (int i = 0; i < 1024 * 1024; i++)
    {
        ss << Int::random(0, 1);
    }
    std::ofstream f("bits.txt");
    f << ss.str();
    f.close();

    return 0;
}
