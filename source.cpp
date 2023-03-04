#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // Создание объекта VideoCapture для захвата видеопотока с камеры
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Ошибка открытия камеры" << endl;
        return -1;
    }

    // Создание окна для отображения видео
    namedWindow("Video", WINDOW_AUTOSIZE);

    // Определение координат начала координат и двух других точек
    Point origin(0, 0);
    Point point1(50, 50);
    Point point2(100, 100);

    // Создание объекта Scalar для определения цвета клика
    Scalar clickColor(0, 0, 255);

    while (true)
    {
        // Захват каждого кадра из видеопотока
        Mat frame;
        cap.read(frame);

        // Рисование трех точек на кадре
        circle(frame, origin, 5, Scalar(255, 0, 0), -1);
        circle(frame, point1, 5, Scalar(0, 255, 0), -1);
        circle(frame, point2, 5, Scalar(0, 0, 255), -1);

        // Определение разницы между текущим кадром и предыдущим кадром
        static Mat previousFrame;
        if (previousFrame.empty())
        {
            frame.copyTo(previousFrame);
        }
        Mat diff;
        absdiff(previousFrame, frame, diff);

        // Обновление предыдущего кадра
        frame.copyTo(previousFrame);

        // Проверка наличия клика
        double maxVal;
        Point maxLoc;
        minMaxLoc(diff, NULL, &maxVal, NULL, &maxLoc);
        if (maxVal > 50)
        {
            circle(frame, maxLoc, 20, clickColor, 2);
        }

        // Отображение текущего кадра в окне
        imshow("Video", frame);

        // Ожидание нажатия клавиши для выхода из программы
        if (waitKey(10) == 27)
        {
            break;
        }
    }

    // Освобождение ресурсов
    cap.release();
    destroyAllWindows();

    return 0;
}
