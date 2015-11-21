#include "call.h"

namespace suara {

Call::Call(pj::Account &account, int callId) :
    pj::Call{account, callId},
    m_account{static_cast<Account*>(&account)},
    m_callId{callId}
{
}

void Call::onCallState(pj::OnCallStateParam &param)
{
    Q_UNUSED(param);

    pj::CallInfo callInfo = getInfo();
    if (callInfo.state == PJSIP_INV_STATE_DISCONNECTED) {
        m_account->removeCall(this);
        delete this;
    }
}

}

