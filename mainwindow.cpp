#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_timer{new QTimer}
{
    resize(300, 300);
    setWindowTitle(QStringLiteral("Snowfall game"));

    m_timer->setInterval(0);
    m_timer->start();
    QObject::connect(
                m_timer,
                &QTimer::timeout,
                this,
                [this]{
                    QPushButton* snowflake = new QPushButton("*", this);
                    // Задание размеров снежинки
                    snowflake->resize(25, 25);
                    // Задание позиции снежники
                    snowflake->move(    QRandomGenerator::global()->bounded(0, width() - snowflake->width())
                                    ,   QRandomGenerator::global()->bounded(100));
                    snowflake->show();
                    // Создание таймера интервала перемещения снежинки
                    QTimer* snowflake_timer = new QTimer(snowflake);
                    // Установка скорости снежинки
                    snowflake_timer->setInterval(QRandomGenerator::global()->bounded(30, 100));
                    snowflake_timer->start();
                    // Подключение сигнала на удаление снежинки при нажатии на нее
                    QObject::connect(snowflake, &QPushButton::clicked, snowflake, &QObject::deleteLater);
                    // Подключение сигнала на обработку наведения курсора на снежинку и обработку ее позиции
                    QObject::connect(
                                snowflake_timer,
                                &QTimer::timeout,
                                snowflake,
                                [this, snowflake, snowflake_timer]{
                                    // Определение скорости снежинки в зависимости от положения курсора
                                    const int speed = snowflake->underMouse() ? 2 : 1;
                                    // Перемещение снежинки на один пиксель вниз
                                    snowflake->move(snowflake->x(), snowflake->y() + speed);
                                    // Проверка достижения снежинки низа окна приложения
                                    if (snowflake->y() + snowflake->height() >= height())
                                    {
                                        setWindowTitle(QStringLiteral("YOU LOSE"));
                                        setPalette(QPalette(Qt::red));
                                        snowflake->deleteLater();
                                    }
                                }
                    );
                    m_timer->setInterval(QRandomGenerator::global()->bounded(100, 1000));
                }
    );
}

MainWindow::~MainWindow()
{
}
