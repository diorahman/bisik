#include "app.h"
#include "account.h"
#include "call.h"
#include <pjsua2.hpp>

#include <QDebug>

namespace suara {

App::App(QObject *parent) : QObject(parent), m_account(new Account(this))
{
    // endpoint init
    try {
        m_endpoint.libCreate();
    } catch (pj::Error &err) {
        // FIXME: handle this
        Q_UNUSED(err)
    }
    pj::EpConfig endpointConfig;
    endpointConfig.logConfig.level = 4;

    m_endpoint.libInit(endpointConfig);

    // transport init
    pj::TransportConfig transportConfig;
    transportConfig.port = 5000;

    m_endpoint.transportCreate(PJSIP_TRANSPORT_UDP, transportConfig);

    m_endpoint.libStart();

    qDebug() << "PJSUA started!";

    connect(m_account, SIGNAL(incomingCall(pj::OnIncomingCallParam*)), this, SLOT(onIncomingCall(pj::OnIncomingCallParam*)));
}

void App::initAccount(const QString& account)
{
    // TODO: add server information here
    m_account->registerAsClient(account);
}

void App::call(const QString& account)
{
    pj::Call *call = new Call(*m_account);
    this->m_account->calls.append(call);

    pj::CallOpParam param(true);
    param.opt.audioCount = 1;
    param.opt.videoCount = 0;
    call->makeCall(("sip:" + account + "@pjsip.org").toStdString(), param);
}

void App::answer()
{
    pj::OnIncomingCallParam *param = m_activeCallParams.at(0);
    pj::Call* call = m_account->getCall(param->callId);

    pj::CallOpParam callOpParam;
    callOpParam.statusCode = (pjsip_status_code) 200;
    call->answer(callOpParam);
}

void App::reject()
{

}

void App::onIncomingCall(pj::OnIncomingCallParam *param)
{
    // append to call active calls
    m_activeCallParams.append(param);

    // emit to front end we have incoming calls, here we can manage multiple calls.
    // we should make m_activeCallParams and m_account.calls in sync
}

}

