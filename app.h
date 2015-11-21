#ifndef APP_H
#define APP_H

#include <QObject>
#include <QList>
#include <pjsua2.hpp>

namespace suara {

class Account;

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = 0);

    Q_INVOKABLE void initAccount(const QString& account);
    Q_INVOKABLE void call(const QString& account);

    Q_INVOKABLE void answer();
    Q_INVOKABLE void reject();

signals:
    void incomingCall(const QString &info);

private slots:
    void onIncomingCall(pj::OnIncomingCallParam *param);

private:
    Account *m_account;
    pj::Endpoint m_endpoint;

    QList<pj::OnIncomingCallParam*> m_activeCallParams;
};

}

#endif // APP_H
