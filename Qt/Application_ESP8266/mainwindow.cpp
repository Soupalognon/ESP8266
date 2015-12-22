#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include <QString>
#include <QDebug>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Fait la liste des ports ouvrables
    QextSerialEnumerator enumerateur;
    QList<QextPortInfo> ports = enumerateur.getPorts();

    //Affiche la liste des ports ouvrables
    for(int i=0; i<ports.size(); i++)
       ui->listePorts->addItem(ports.at(i).portName);

    //Affiche la liste des vitesses de transmissions
    ui->listVitesse->addItem("4800");
    ui->listVitesse->addItem("9600");
    ui->listVitesse->addItem("19200");
    ui->listVitesse->addItem("57600");
    ui->listVitesse->addItem("115200");
    ui->listVitesse->setCurrentIndex(1);

    //Créer l'objet port série
    port = new QextSerialPort();

    //QShortcut *Enter = new QShortcut(Qt::Key_Enter);

    connect(ui->Envoyer, SIGNAL(clicked()),this,SLOT(sendData()));
    ui->Envoyer->setShortcut(Qt::Key_Return);
    //ui->Envoyer->setShortcut(Qt::Key_Enter);
    //connect(Enter, activated(), this, SLOT(sendData()));
}

MainWindow::~MainWindow()
{
    if(port->isOpen())
    {
        port->close();
        delete port;
    }
    delete ui;
}

void MainWindow::on_btnconnexion_clicked() {
    //deux cas de figures à gérer, soit on coche (connecte), soit on décoche (déconnecte)

    //on coche -> connexion
    if(ui->btnconnexion->isChecked())
    {
        //on règle le port utilisé (sélectionné dans la liste déroulante)
        port->setPortName(ui->listePorts->currentText());
        //on règle la vitesse utilisée
        port->setBaudRate(getBaudRateFromString(ui->listVitesse->currentText()));
        //quelques règlages pour que tout marche bien
        port->setParity(PAR_NONE);//parité
        port->setStopBits(STOP_1);//nombre de bits de stop
        port->setDataBits(DATA_8);//nombre de bits de données
        port->setFlowControl(FLOW_OFF);//pas de contrôle de flux
        //on démarre !
        port->open(QextSerialPort::ReadWrite);
        //change le message du bouton
        ui->btnconnexion->setText("Deconnecter");

        //on fait la connexion pour pouvoir obtenir les évènements
        connect(port,SIGNAL(readyRead()), this, SLOT(readData()));
    }
    else
    {
        //on se déconnecte de la carte Arduino
        port->close();
        ui->btnconnexion->setText("Connecter");
    }
}


BaudRateType MainWindow::getBaudRateFromString(QString baudRate) {
    int vitesse = baudRate.toInt();
    switch(vitesse)
    {
        case(300):return BAUD300;
        case(1200):return BAUD1200;
        case(2400):return BAUD2400;
        case(4800):return BAUD4800;
        case(9600):return BAUD9600;
        case(14400):return BAUD14400;
        case(19200):return BAUD19200;
        case(38400):return BAUD38400;
        case(57600):return BAUD57600;
        case(115200):return BAUD115200;
        default:return BAUD9600;
    }
}


void MainWindow::sendData()
{
    if(port->isOpen())  //On vérifie si le port est ouvert
    {

        QString caractere = "\n";   //On rajoute un saut de ligne
        caractere += ui->boxEmission->text();
        //caractere += ui->boxEmission->toPlainText();    //On récupère le dernier caractère tapé

        port->write(caractere.toLatin1());  //on envoi la chaîne de caractères

        ui->boxEmission->clear();   //On nettoie la box
    }
}


void MainWindow::readData()
{
    QString data = port->readAll();
    ui->boxReception->insertPlainText(data);
}

/*
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter)
    {
        qDebug() << "aaaaa";
    }
}
*/
