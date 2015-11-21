#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QMap>

#include <pjsua2.hpp>

namespace suara {

class Account : public QObject, public pj::Account
{
    Q_OBJECT
public:
    explicit Account(QObject *parent = 0);
    ~Account();

public:
    void registerAsClient(const QString &account);

    pj::Call* getCall(int callId);
    bool removeCall(pj::Call* call);

    virtual void onRegState(pj::OnRegStateParam &param);
    virtual void onIncomingCall(pj::OnIncomingCallParam &param);

    QList<pj::Call*> calls;

signals:
    void incomingCall(pj::OnIncomingCallParam *param);
};

}

#endif // ACCOUNT_H
