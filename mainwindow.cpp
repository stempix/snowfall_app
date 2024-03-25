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
                    snowflake->move(    QRandomGenerator::global()->bounded(0, this->width() - snowflake->width())
                                    ,   QRandomGenerator::global()->bounded(100));
                    snowflake->show();
                    // Создание таймера интервала перемещения снежинки
                    QTimer* snowflake_timer = new QTimer(snowflake);
                    // Установка скорости снежинки
                    int snowflake_speed = QRandomGenerator::global()->bounded(30, 100);
                    snowflake_timer->setInterval(snowflake_speed);
                    snowflake_timer->start();
                    // Подключение сигнала на удаление снежинки при нажатии на нее
                    QObject::connect(snowflake, &QPushButton::clicked, [snowflake]{snowflake->deleteLater();});
                    // Подключение сигнала на обработку наведения курсора на снежинку и обработку ее позиции
                    QObject::connect(
                                snowflake_timer,
                                &QTimer::timeout,
                                this,
                                [this, snowflake, snowflake_timer, snowflake_speed]{
                                    // Получение координат курсора в окне
                                    QPoint cursorPos = this->mapFromGlobal(QCursor::pos());
                                    int xCursor = cursorPos.x();
                                    int yCursor = cursorPos.y();
                                    int xSnowflake = snowflake->x();
                                    int ySnowflake = snowflake->y();
                                    // Сравнение положения курсора с положением снежинки
                                    if (xCursor >= xSnowflake
                                            && xCursor <= xSnowflake + snowflake->width()
                                            && yCursor >= ySnowflake
                                            && yCursor <= ySnowflake + snowflake->height())
                                        // Увеличение скорости снежинки при наведении курсора на нее
                                        snowflake_timer->setInterval(snowflake_speed / 2);
                                    else
                                        snowflake_timer->setInterval(snowflake_speed);
                                    // Перемещение снежинки на один пиксель вниз
                                    snowflake->move(xSnowflake, ySnowflake + 1);
                                    // Проверка достижения снежинки низа окна приложения
                                    if (ySnowflake + snowflake->height() >= this->height())
                                    {
                                        this->setWindowTitle(QStringLiteral("YOU LOSE"));
                                        this->setPalette(QPalette(Qt::red));
                                        snowflake->deleteLater();
                                    }
                                    // Перезапуск таймера перемещения снежинки
                                    snowflake_timer->start();
                                    }
                    );
                    this->m_timer->setInterval(QRandomGenerator::global()->bounded(100, 1000));
                    this->m_timer->start();
                }
    );
}

MainWindow::~MainWindow()
{
}
