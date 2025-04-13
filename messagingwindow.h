#ifndef MESSAGINGWINDOW_H
#define MESSAGINGWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

#include <QTextBrowser>

class MessagingWindow : public QWidget {
    Q_OBJECT

public:
    MessagingWindow(QWidget *parent = nullptr);
    ~MessagingWindow();
    void onMessageReceived(const QString &message);

signals:
    void messageSent(const QString &message);
    void messageReceivedExternally(const QString &message);  // New signal for external communication

protected slots:
    void onSendMessageClicked();
        // Keep it protected

private:
    QLineEdit *messageInput;
    QPushButton *sendButton;
    QTextBrowser *messageDisplay;
};





#endif // MESSAGINGWINDOW_H
