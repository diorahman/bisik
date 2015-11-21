#include "account.h"
#include "call.h"

#include <QDebug>


namespace suara {

Account::Account(QObject *parent) :
    QObject{parent}
{

}

Account::~Account()
{
    // Remove all calls
    qDeleteAll(this->calls);
}

void Account::registerAsClient(const QString& account)
{
    pj::AccountConfig accountConfig;
    accountConfig.idUri = ("sip:" + account + "@pjsip.org").toStdString();
    accountConfig.regConfig.registrarUri = "sip:pjsip.org";
    accountConfig.sipConfig.authCreds.push_back(pj::AuthCredInfo("digest", "*", account.toStdString(), 0, account.toStdString()));
    this->create(accountConfig);
}

pj::Call* Account::getCall(int callId)
{
    for (int i = 0; i < this->calls.length(); i++) {
        if (this->calls.at(i)->getId() == callId) {
            return this->calls.at(i);
        }
    }
    return nullptr;
}

bool Account::removeCall(pj::Call *call)
{
    return this->calls.removeOne(call);
}

void Account::onRegState(pj::OnRegStateParam &param)
{
    qDebug() << "\n==";
    pj::AccountInfo accountInfo = getInfo();
    if (accountInfo.regIsActive) {
        qDebug() << "active";
    } else {
        qDebug() << "inactive";
    }
    qDebug() << param.code;
}

void Account::onIncomingCall(pj::OnIncomingCallParam &param)
{
    pj::Call *call = new Call(*this, param.callId);
    this->calls.append(call);

    qDebug() << "\n==";
    qDebug() << "on incoming call";

    emit incomingCall(&param);
}

}

