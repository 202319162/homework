#include"main.h"
int main()
{
    Imagematrix img;
    string filename;
    int x, y, value, w, h, threshold;

    while (true) {
        cout << "\n请输入数字选择功能" << endl;
        cout << "1. 初始化" << endl;
        cout << "2. 判空" << endl;
        cout << "3. 读取" << endl;
        cout << "4. 保存" << endl;
        cout << "5. 显示" << endl;
        cout << "6. 二值化显示" << endl;
        cout << "7. 修改点" << endl;
        cout << "8. 绘制框" << endl;
        cout << "9. 给出阈值，过滤点" << endl;
        cout << "10. 翻转" << endl;
        cout << "11. 旋转" << endl;
        cout << "0. 退出" << endl;

        int n;
        cin >> n;

        if (n == 0) {
            break;
        }

        switch (n) {
            case 1:
                cout << "请输入图像宽和高：" << endl;
                cin >> w >> h;
                img = Imagematrix(w, h);
                cout << "图像已初始化。" << endl;
                break;

            case 2:
                if (img.isEmpty()) {
                    cout << "图像为空。" << endl;
                } else {
                    cout << "图像不为空。" << endl;
                }
                break;

            case 3:
                cout << "请输入要读取的文件名：" << endl;
                cin >> filename;
                img.read(filename);
                cout << "图像已读取。" << endl;
                break;

            case 4:
                cout << "请输入要保存的文件名：" << endl;
                cin >> filename;
                img.save(filename);
                cout << "图像已保存。" << endl;
                break;

            case 5:
                cout << "当前图像：" << endl;
                img.display();
                break;

            case 6:
                cout << "二值化显示：" << endl;
                img.binarydisplay();
                break;

            case 7:
                cout << "请输入要修改的点的坐标 (x, y) 和新值：" << endl;
                cin >> x >> y >> value;
                img.changepoint(x, y, value);
                cout << "点已修改。" << endl;
                break;

            case 8:
                cout << "请输入左上角坐标 (x, y)、宽度 w、高度 h 和框的值：" << endl;
                cin >> x >> y >> w >> h >> value;
                img.pointrectangle(x, y, w, h, value);
                cout << "框已绘制。" << endl;
                break;

            case 9:
                cout << "请输入阈值：" << endl;
                cin >> threshold;
                img.threshold(threshold);
                cout << "阈值过滤已完成。" << endl;
                break;

            case 10:
                cout << "图像水平翻转：" << endl;
                img.overturn();
                cout << "翻转完成。" << endl;
                break;

            case 11:
                cout << "图像旋转90度：" << endl;
                img.rotate();
                cout << "旋转完成。" << endl;
                break;

            default:
                cout << "无效选项，请重新输入。" << endl;
                break;
        }
    }

    return 0;
}
