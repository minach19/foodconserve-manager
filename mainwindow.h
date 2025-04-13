#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"employees.h"
#include <QMainWindow>
#include <arduino.h>
#include <QLineEdit>
#include <QStackedWidget>
#include <QTextEdit>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QString>
#include <QList>
QT_BEGIN_NAMESPACE

struct Delivery { QString phoneNumber;};
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Yassmine
    QSqlQueryModel* getDeliveriesModel();
    QString getSelectedDeliveryClientPhoneNumber();
    //Mayssem
    void load_list_view_employee();
    QSerialPort *serialPort;
    QByteArray serialData;
    QString serialbuffer;
    Arduino *arduino;
    void connect_rfid();
    void readarduino();
    //yassine
    void load_list_view();
signals:
    void loginSuccessful(const QString &role);

private slots:
    void on_confirm_add_clicked();
    void on_delete_clicked();
    void on_edit_clicked();
    void on_confirm_edit_clicked();
    void recherche_emp();
    void on_cancel_search_button_clicked();
    void on_log_out_button_clicked();
    void on_Login_Button_clicked();
    //void on_export_pdf_button_clicked();
    void exportToPDF();
    void on_Sort_Button_clicked();
    void displayStatistics();
    void on_Recover_Button_clicked();
    bool getAnsw1AndAnsw2(int id, QString &answ1, QString &answ2);
    void on_confirm_changed_psw_Button_clicked();
    //bool sendEmail(const QString &to, const QString &password);
    bool getEmailAndPassword(int id, QString &email, QString &password);
    void on_send_email_button_clicked();
    //void readRFIDTag();
    //void checkUIDInDatabase(const QString &rfidTag);
    ////
    /// \brief ui
    ///

    //yassine
    void on_confirm_add_client_clicked();
    void on_delete_client_clicked();
    void on_edit_client_clicked();
    void on_confirm_edit_client_clicked();
    void on_Sort_Button_client_clicked();
    void on_cancel_search_client_clicked();
    // Search for a client
    void recherche_client();
    void exportTableToPDF();
    void displayStatistics_client();

    //Yassmine
    void loadClientData(int clientId) ;
    void validateClientId(const QString &text);
    void checkClientIdExists(const QString &text);
    void addDELIVERY(bool isConfirm);
    void clearInputFields();
    void displayDeliveries();
    void validateID(const QString &text);
    void validateFields(const QString &text);
    void deleteDelivery();
    void editDelivery();
    void checkIdExists(const QString &text);
    void highlightField(QLineEdit *field, bool isValid);
    void searchDelivery();
    void trie();
    void displayStatistics_livraison();
    void displayHistorique();
    void exportPDF();
    void onSmsButtonClicked();


private:
    Ui::MainWindow* ui;
    int currentIdForEditing = -1; // Variable à suivre pour l'édition
    QStackedWidget *stat;
    QList<Delivery> deliveries;
    int currentSelectedIndex;
};
#endif // MAINWINDOW_H
