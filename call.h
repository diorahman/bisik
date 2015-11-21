#ifndef CALL_H
#define CALL_H

#include <pjsua2.hpp>

#include "account.h"

namespace suara {

class Call : public pj::Call
{

public:
    explicit Call(pj::Account &account, int callId = PJSUA_INVALID_ID);
    virtual void onCallState(pj::OnCallStateParam &param);

private:
    Account *m_account;
    int m_callId;
};

}

#endif // CALL_H
