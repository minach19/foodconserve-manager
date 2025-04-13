#include "messagingwindow.h"
#include <QVBoxLayout>
#include <QDateTime>
#include <QApplication>




MessagingWindow::MessagingWindow(QWidget *parent)
    : QWidget(parent) {
    // UI Setup
    QVBoxLayout *layout = new QVBoxLayout(this);

    messageDisplay = new QTextBrowser(this);
    messageInput = new QLineEdit(this);
    sendButton = new QPushButton("Send", this);

    layout->addWidget(messageDisplay);
    layout->addWidget(messageInput);
    layout->addWidget(sendButton);

    connect(sendButton, &QPushButton::clicked, this, &MessagingWindow::onSendMessageClicked);
}


MessagingWindow::~MessagingWindow() {}
void MessagingWindow::onSendMessageClicked() {
    QString message = messageInput->text();
    if (!message.isEmpty()) {
        emit messageSent(message);
        messageInput->clear();
    }
}

void MessagingWindow::onMessageReceived(const QString &message) {
    messageDisplay->append(message);
    emit messageReceivedExternally(message);  // Emit for external listeners
}

