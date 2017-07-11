#include <QApplication>
#include <QFont>
#include <QGroupBox>
#include <QComboBox>
#include <QDebug>
#include <QDir>

#include "StartWindow.h"
#include "BoardWindow.h"
#include "ScoresWindow.h"
#include "../Boards/ConnectFourBoard.h"
#include "../Boards/OthelloBoard.h"
#include "../Boards/TicTacToeBoard.h"

StartWindow::StartWindow(QWidget *parent) : QWidget(parent){

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("GenBoard beta 3");
    setWindowIcon(QIcon("Ressources" + QString(QDir::separator()) + "genboard.png"));

    QGridLayout *layout = new QGridLayout();

    QGroupBox *group = new QGroupBox("Select a game ", this);
    connectfour = new QRadioButton("Connect Four");
    othello = new QRadioButton("Othello");
    tictactoe = new QRadioButton("Tic Tac Toe");

    connectfour-> setChecked(true);
    QVBoxLayout *list = new QVBoxLayout;
    list->addWidget(connectfour);
    list->addWidget(othello);
    list->addWidget(tictactoe);
    group->setLayout(list);

    QFont *fontTitle = new QFont("Courier New");
    fontTitle->setBold(true);
    fontTitle->setPixelSize(30);

    welcome = new QLabel("Welcome to GenBoard !", this);
    welcome->setFont(*fontTitle);

    start = new QPushButton("Start game !", this);
    score = new QPushButton("Score",this);

    layout->addWidget(welcome,0,1);
    layout->addWidget(group,1,1);
    layout->addWidget(score,2,0);
    layout->addWidget(start,2,2);

    this->setLayout(layout);

    connect(score, &QPushButton::clicked, this, &StartWindow::goScoreMenu);
    connect(start, &QPushButton::clicked, this, &StartWindow::onStartGame);

    // Fixing size issue when back from game
    this->setMaximumHeight(480);
    this->setMaximumWidth(640);
}

void StartWindow::onStartGame(){

    if(connectfour->isChecked()) {
        query.exec("UPDATE games SET numberPlay = numberPlay + 1 where name = 'Connect Four'");

        Board *board = new ConnectFourBoard();
        connectfourWidget = new BoardWindow(*board);
        connectfourWidget->show();

        this->close();
    }
    else if(othello->isChecked()) {
        query.exec("UPDATE games SET numberPlay = numberPlay + 1 where name = 'Othello'");

        Board *board = new OthelloBoard();
        othelloWidget = new BoardWindow(*board);
        othelloWidget->show();

        this->close();
    }
    else if(tictactoe->isChecked()){
        query.exec("UPDATE games SET numberPlay = numberPlay + 1 where name = 'Tic Tac Toe'");

        Board *board = new TicTacToeBoard();
        tictactoeWidget = new BoardWindow(*board);
        tictactoeWidget->show();

        this->close();
    }
}

void StartWindow::goScoreMenu(){
    scoreMenu = new ScoresWindow();
    scoreMenu->show();
    this->close();
}
