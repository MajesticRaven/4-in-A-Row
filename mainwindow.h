#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QTranslator>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_player1_choose_clicked();

    void on_player2_choose_clicked();

    void on_exit_button_clicked();

    void on_langRus_clicked();

    void on_langEng_clicked();

    void on_sound_button_clicked();

    void on_back_menu_button_clicked();

    void on_play_button_clicked();

    void on_save_size_button_clicked();

    void create_choose();

    void mousePressEvent(QMouseEvent* pe);

    bool check_for_win(int x, int y);

private:
    Ui::MainWindow *ui;

    QTranslator translator;
    QMediaPlaylist *playlist;
    QMediaPlayer *music;

    QGraphicsScene *scene;

    QVector<QString> chip_icons;
    int chip_player1;
    int chip_player2;

    bool is_music_play = true;
    int num_rows;
    int num_lines;
    int num_of_free;

    int player_turn = 1;

    bool is_start = false;
    void chips_add();
    int** field;
};

#endif // MAINWINDOW_H
