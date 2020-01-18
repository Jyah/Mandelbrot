#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <array>
#include <opencv2/imgproc.hpp> // applyColorMap

using namespace std;

static void meshgrid(const cv::Mat& xgv, const cv::Mat& ygv, cv::Mat1i& X, cv::Mat1i& Y)
{
    cv::repeat(xgv.reshape(1, 1), ygv.total(), 1, X);
    cv::repeat(ygv.reshape(1, 1).t(), 1, xgv.total(), Y);
}

// helper function (maybe that goes somehow easier)
static void meshgridTest(const cv::Range& xgv, const cv::Range& ygv, cv::Mat1i& X, cv::Mat1i& Y)
{
    std::vector<int> t_x, t_y;
    for (int i = xgv.start; i <= xgv.end; i++) t_x.push_back(i);
    for (int i = ygv.start; i <= ygv.end; i++) t_y.push_back(i);
    meshgrid(cv::Mat(t_x), cv::Mat(t_y), X, Y);
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int max_iter = atoi(argv[2]);
    double px[n], py[n];
    for (int k = 0; k < n; k++) {
        px[k] = (2. - (-2.)) / (n - 1.) * k-2;
        py[k] = (2. - (-2.)) / (n - 1.) * k-2;
    }
    // meshgrid
    cv::Mat1i xGrid, yGrid;
    meshgridTest(cv::Range(0, n-1), cv::Range(0,n-1), xGrid,yGrid);
    uint8_t im[n][n];
    for (int xk = 0; xk < n; xk++) {
        for (int yk = 0; yk < n; yk++) {
            int x0 = xGrid[xk][yk];
            int y0 = yGrid[xk][yk];
            double x = 0, y = 0;
            int iter = 0;
            while (x * x + y * y <= 2 * 2 && iter < max_iter) {
                double x_temp = x * x - y * y + px[x0];
                y = 2 * x * y + py[y0];
                x = x_temp;
                iter++;
                im[xk][yk] = 255*iter / max_iter;
            }
        }

    }

    cv::Mat image(n,n,CV_8UC1,im);
    cv::Mat cm_img0;
    applyColorMap(image, cm_img0, cv::COLORMAP_HOT);
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window",cm_img0);
    cv::waitKey(0);
    return 0;
}
