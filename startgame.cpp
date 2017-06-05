#include "startgame.h"
#include "connectfourboard.h"
#include "othelloboard.h"
#include "tictactoeboard.h"
#include "scoremenu.h"
#include <QApplication>
#include <QFont>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>

StartGame::StartGame(QWidget *parent) : QWidget(parent){

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

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

    //welcome->setGeometry(200,20,250,25);
    //group->setGeometry(230,100,200,200);
    //score->setGeometry(20,300,100,30);
    //start->setGeometry(520,300,100,30);

    layout->addWidget(welcome,0,1);
    layout->addWidget(group,1,1);
    layout->addWidget(score,2,0);
    layout->addWidget(start,2,2);

    this->setLayout(layout);

    connect(score, &QPushButton::clicked, this, &StartGame::goScoreMenu);
    connect(start, &QPushButton::clicked, this, &StartGame::onStartGame);
}

void StartGame::onStartGame(){
    if(connectfour->isChecked()){
        connectfourWidget = new ConnectfourBoard();
        connectfourWidget->show();
        this->close();
    }
    else if(othello->isChecked()){
        othelloWidget = new OthelloBoard();
        othelloWidget->show();
        this->close();
    }
    else if(tictactoe->isChecked()){
        tictactoeWidget = new TictactoeBoard();
        tictactoeWidget->show();
        this->close();
    }
}

void StartGame::goScoreMenu(){
    scoreMenu = new ScoreMenu();
    scoreMenu->show();
    this->close();
}