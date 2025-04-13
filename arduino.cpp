#include "arduino.h"
#include<iostream>

#include <chrono>
#include <thread>

using namespace std;

Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial = new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
    return serial;
}
int Arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    if (serial->isOpen()) {
        serial->close();
        qDebug() << "Serial port reset.";
    }
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Checking port:" << info.portName();
        qDebug() << "Vendor ID:" << info.vendorIdentifier();
        qDebug() << "Product ID:" << info.productIdentifier();

        if (info.vendorIdentifier() == arduino_uno_vendor_id &&
            info.productIdentifier() == arduino_uno_producy_id) {
            arduino_port_name = info.portName();
            arduino_is_available = true;
            break;
        }
    }

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        qDebug() << "Attempting to connect to port:" << arduino_port_name;

        if (!serial->open(QSerialPort::ReadWrite)) {
            qDebug() << "Failed to open port:" << serial->errorString();
            return 1; // Error opening port
        }


        /*foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                                                                                    == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name=serial_port_info.portName();
            } } }
    qDebug() << "arduino_port_name is :" << arduino_port_name;
    if(arduino_is_available){ // configuration de la communication ( débit...)
        serial->setPortName(arduino_port_name);
        if(serial->open(QSerialPort::ReadWrite)){*/
        serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
        serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
        serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
        serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
        serial->setFlowControl(QSerialPort::NoFlowControl);
        //serial->open(QIODevice::ReadWrite);
        //QObject::connect(serial, SIGNAL(readyRead()),this,SLOT(read_from_arduino()));
        qDebug() << "Arduino connected successfully to port:" << arduino_port_name;
        return 0; // Success
    }

    qDebug() << "Arduino not found.";
    return -1; // Arduino not available
}

int Arduino::close_arduino()

{

    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;


}
/*QByteArray readFromArduino() {
    QByteArray data;
    if (serial->isReadable()) {
        data = serial->readAll();
    }
    return data;
}*/

QByteArray Arduino::read_from_arduino(){

    if(serial->isReadable()){

        serial->waitForReadyRead(200);
        data=serial->readAll(); //récupérer les données reçues

        return data;
    }

    // cout << "Reading 1 ..." << endl;

    // if (!serial->isOpen()) {
    //     qDebug() << "Arduino is not connected.";
    // }

    // cout << "Reading 2 ..." << endl;

    // static QByteArray buffer;
    // buffer.append(serial->readAll());
    // cout << "Buffer: " << buffer.toStdString() << endl;

    // if (serial->waitForReadyRead(20000)) { // Wait up to 2 seconds for data
    //     QByteArray rawData = serial->readAll().trimmed();
    //     qDebug() << "Data received from Arduino:" << rawData;
    // }else {
    //     qDebug() << "No data received from Arduino within the timeout period.";
    // }
}



//QByteArray data;
// static bool lock = false;
// if (!lock){
//     lock = true;
//     while (serial->canReadLine()) {
//         QByteArray data = serial->readLine()
//         QString uid = QString(data).trimmed();
//         if (uid.startsWith("UID:")) {
//             QString rfidUID = uid.mid(4); // Extract UID after "UID:"
//             qDebug() << "Received UID:" << rfidUID;
//         }
//     }
// }
//     cout << "Not crashing yet.." << endl;
// if(serial->isReadable()){
//     data=serial->readAll(); //récupérer les données reçues
//     cout<<"data:"<<data.toStdString()<<endl;
//     return data;
//  }}




void Arduino::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}

