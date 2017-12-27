#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet("background-color:#fff1dc");

    this->setFixedSize(1024,720);

    on_langEng_clicked();
    ui->stackedWidget->setCurrentIndex(0);

    chips_add();
    chip_player1 = 0;
    chip_player2 = 1;

    //set chips
    ui->player1_choose->setStyleSheet("background: transparent");
    ui->player1_choose->setIcon(QIcon(chip_icons.at(chip_player1)));
    ui->player1_choose->setIconSize(QSize(145,145));

    ui->player2_choose->setStyleSheet("background: transparent");
    ui->player2_choose->setIcon(QIcon(chip_icons.at(chip_player2)));
    ui->player2_choose->setIconSize(QSize(145,145));

    //set buttons style
    ui->langEng->setStyleSheet("background: transparent");
    ui->langEng->setIcon(QIcon(":/resources/images/usa_flag.png"));
    ui->langEng->setIconSize(QSize(90,53));

    ui->langRus->setStyleSheet("background: transparent");
    ui->langRus->setIcon(QIcon(":/resources/images/russian flag.png"));
    ui->langRus->setIconSize(QSize(100,53));

    ui->sound_button->setStyleSheet("background: transparent");
    ui->sound_button->setIcon(QIcon(":/resources/images/sound_on.png"));
    ui->sound_button->setIconSize(QSize(40, 40));

    //background music
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl(qApp->applicationDirPath() + "/resources/background_music.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chips_add()
{
    chip_icons.clear();

    for(int i = 1; i <= 8; i++)
    {
        chip_icons.push_back(":/resources/images/chips/" + QString::number(i) + "chip.png");
    }
}

void MainWindow::on_player1_choose_clicked()
{
    chip_player1++;

    if(chip_player1 % 8 == chip_player2)
    {
        chip_player1++;
    }

    chip_player1 = chip_player1 % 8;

    ui->player1_choose->setIcon(QIcon(chip_icons.at(chip_player1)));
    ui->player1_pic->setIcon(QIcon(chip_icons.at(chip_player1)));
}

void MainWindow::on_player2_choose_clicked()
{
    chip_player2++;

    if(chip_player2 % 8 == chip_player1)
    {
        chip_player2++;
    }

    chip_player2 = chip_player2 % 8;

    ui->player2_choose->setIcon(QIcon(chip_icons.at(chip_player2)));
    ui->player2_pic->setIcon(QIcon(chip_icons.at(chip_player1)));
}

void MainWindow::on_exit_button_clicked()
{
    close();
}

void MainWindow::on_langRus_clicked()
{
    translator.load("QtLanguage_ru_RU");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);

    ui->exit_button->setStyleSheet("background: transparent");
    ui->exit_button->setIcon(QIcon(":/resources/images/exit_rus.png"));
    ui->exit_button->setIconSize(QSize(100,100));

    ui->play_button->setStyleSheet("background: transparent");
    ui->play_button->setIcon(QIcon(":/resources/images/start_ru.png"));
    ui->play_button->setIconSize(QSize(145,145));

    ui->back_menu_button->setStyleSheet("background: transparent");
    ui->back_menu_button->setIcon(QIcon(":/resources/images/back_rus.png"));
    ui->back_menu_button->setIconSize(QSize(145,145));

    ui->save_size_button->setStyleSheet("background: transparent");
    ui->save_size_button->setIcon(QIcon(":/resources/images/save_rus.png"));
    ui->save_size_button->setIconSize(QSize(145,145));
}

void MainWindow::on_langEng_clicked()
{
    translator.load("QtLanguage_en_US");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);

    this->setWindowTitle("4 in A Row");

    ui->exit_button->setStyleSheet("background: transparent");
    ui->exit_button->setIcon(QIcon(":/resources/images/exit_eng.png"));
    ui->exit_button->setIconSize(QSize(100,100));

    ui->play_button->setStyleSheet("background: transparent");
    ui->play_button->setIcon(QIcon(":/resources/images/start_en.png"));
    ui->play_button->setIconSize(QSize(145,145));

    ui->back_menu_button->setStyleSheet("background: transparent");
    ui->back_menu_button->setIcon(QIcon(":/resources/images/back_en.png"));
    ui->back_menu_button->setIconSize(QSize(145,145));

    ui->save_size_button->setStyleSheet("background: transparent");
    ui->save_size_button->setIcon(QIcon(":/resources/images/save_en.png"));
    ui->save_size_button->setIconSize(QSize(145,145));
}

void MainWindow::on_sound_button_clicked()
{
    if(is_music_play == true)
    {
        music->pause();
        ui->sound_button->setStyleSheet("background: transparent");
        ui->sound_button->setIcon(QIcon(":/resources/images/sound_off.png"));
        ui->sound_button->setIconSize(QSize(40, 40));
        is_music_play = false;
    }
    else
    {
        music->play();
        ui->sound_button->setStyleSheet("background: transparent");
        ui->sound_button->setIcon(QIcon(":/resources/images/sound_on.png"));
        ui->sound_button->setIconSize(QSize(40, 40));
        is_music_play = true;
    }
}

void MainWindow::on_back_menu_button_clicked()
{
    ui->line_comboBox->setEnabled(true);
    scene->deleteLater();
    ui->stackedWidget->setCurrentIndex(0);
    is_start = false;
}

void MainWindow::on_play_button_clicked()
{
    ui->player1_pic->setStyleSheet("background: transparent");
    ui->player1_pic->setIcon(QIcon(chip_icons.at(chip_player1)));
    ui->player1_pic->setIconSize(QSize(145,145));

    ui->player2_pic->setStyleSheet("background: transparent");
    ui->player2_pic->setIcon(QIcon(chip_icons.at(chip_player2)));
    ui->player2_pic->setIconSize(QSize(145,145));

    ui->stackedWidget->setCurrentIndex(1);
    create_choose();
    ui->graphicsView->setFixedSize(270, 270);
    ui->turn2_label->setVisible(false);

    scene = new QGraphicsScene();
}

void MainWindow::create_choose()
{
    ui->line_comboBox->clear();
    QStringList list = {"5", "6", "7", "8", "9", "10"};
    ui->line_comboBox->addItems(list);
}

void MainWindow::on_save_size_button_clicked()
{
    ui->line_comboBox->setEnabled(false);
    num_lines = ui->line_comboBox->currentText().toInt();
    num_rows = ui->line_comboBox->currentText().toInt();

    ui->graphicsView->setScene(scene);

    for(int i = 1; i < num_lines; i++)
    {
        scene->addLine(0, 250 / num_lines * i, 250, 250 / num_lines * i, QPen(Qt::black));
    }

    for(int i = 1; i < num_rows; i++)
    {
        scene->addLine(250 / num_rows * i, 0, 250 / num_rows * i, 250, QPen(Qt::black));
    }

    field = new int*[num_lines];
    for(int i = 0; i < num_lines; i++)
    {
        field[i] = new int[num_rows];
    }

    for(int i = 0; i < num_lines; i++)
    {
        for(int j = 0; j < num_rows; j++)
        {
            field[i][j] = 0;
        }
    }

    num_of_free = num_lines * num_rows;
    is_start = true;
}

void MainWindow::mousePressEvent(QMouseEvent* pe)
{
    if(is_start == false)
    {
        return;
    }

    int x, y;
    QPoint bsc = ui->graphicsView->pos();
    QPoint press;

    press.setX(pe->x() - bsc.x() - 20);
    press.setY(pe->y() - bsc.y() - 20);

    if(press.x() > 0 && press.x() < ui->graphicsView->size().width() && press.y() > 0 && press.y() < ui->graphicsView->height())
    {
        int press_row = press.x() / (250 / num_rows);
        if(press_row == num_rows)
        {
            press_row--;
        }

        for(int i = num_lines - 1; i >= 0; i--)
        {

            if(field[i][press_row] == 0)
            {
                x = press_row;
                y = i;

                field[i][press_row] = player_turn;
                player_turn++;

                if(player_turn == 3)
                {
                    player_turn = 1;
                }

                double r = 250 / num_rows, l = 250 / num_lines;

                QGraphicsPixmapItem *item = new QGraphicsPixmapItem();

                if(player_turn == 1)
                {
                    item->setPixmap(QPixmap::fromImage(QImage(chip_icons.at(chip_player1))));
                }
                else if(player_turn == 2)
                {
                    item->setPixmap(QPixmap::fromImage(QImage(chip_icons.at(chip_player2))));
                }

                double mult = r * l * 3;
                mult /= QImage(chip_icons.at(chip_player2)).size().width() * QImage(chip_icons.at(chip_player2)).size().height();

                item->setScale(mult);

                item->setPos(press_row * (250 / num_rows), i * (250 / num_lines));
                scene->addItem(item);

                if(player_turn == 1)
                {
                    ui->turn2_label->setVisible(false);
                    ui->turn1_label->setVisible(true);
                }
                else if(player_turn == 2)
                {
                    ui->turn1_label->setVisible(false);
                    ui->turn2_label->setVisible(true);
                }
                num_of_free--;
                break;
            }
        }

        if(check_for_win(x, y) == true)
        {
            QMessageBox::about(this, "Win", "Win");
            on_back_menu_button_clicked();
        }

        if(num_of_free == 0)
        {
            QMessageBox::about(this, "Draw", "Nobody wins");
            on_back_menu_button_clicked();
        }
    }
}

bool MainWindow::check_for_win(int x, int y)
{
    int count = 1;
    int real_row = x, real_line = y;

    //from left to right
    while(true)
    {
        if(real_row == 0)
        {
            break;
        }
        else if(field[real_line][real_row] == field[real_line][real_row-1])
        {
            real_row -= 1;
        }
        else
        {
            break;
        }
    }
    while(true)
    {
        if(real_row == num_rows - 1)
        {
            break;
        }
        else if(field[real_line][real_row] == field[real_line][real_row+1])
        {
            count++;
            real_row++;
        }
        else
        {
            break;
        }
    }

    if(count == 4)
    {
        return true;
    }

    count = 1;
    real_row = x, real_line = y;

    //from top to bot
    while(true)
    {
        if(real_line == 0)
        {
            break;
        }
        else if(field[real_line][real_row] == field[real_line-1][real_row])
        {
            real_line -= 1;
        }
        else
        {
            break;
        }
    }
    while(true)
    {
        if(real_line == num_lines - 1)
        {
            break;
        }
        else if(field[real_line][real_row] == field[real_line+1][real_row])
        {
            count++;
            real_line++;
        }
        else
        {
            break;
        }
    }

    if(count == 4)
    {
        return true;
    }

    count = 1;
    real_row = x, real_line = y;

    //from left top to right bottom
    while(true)
    {
        if(real_line == 0 || real_row == 0)
        {
            break;
        }
        else if(field[real_line][real_row] == field[real_line-1][real_row-1])
        {
            real_line -= 1;
            real_row -= 1;
        }
        else
        {
            break;
        }
    }
    while(true)
    {
        if(real_line == num_lines - 1 || real_row == num_rows - 1)
        {
            break;
        }
        else if(field[real_line][real_row] == field[real_line+1][real_row+1])
        {
            count++;
            real_line++;
            real_row++;
        }
        else
        {
            break;
        }
    }

    if(count == 4)
    {
        return true;
    }

    count = 1;
    real_row = x, real_line = y;

    //from right top to left bottom
    while(true)
    {
        if(real_line == 0 || real_row == num_rows - 1)
        {
            break;
        }
        else if(field[real_line][real_row] == field[real_line-1][real_row+1])
        {
            real_line -= 1;
            real_row += 1;
        }
        else
        {
            break;
        }
    }
    while(true)
    {
        if(real_line == num_rows - 1 || real_row == 0)
        {
            break;
        }
        else if(field[real_line][real_row] == field[real_line+1][real_row-1])
        {
            count++;
            real_line++;
            real_row--;
        }
        else
        {
            break;
        }
    }

    if(count == 4)
    {
        return true;
    }

    return false;
}
