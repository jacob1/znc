/*
 * Copyright (C) 2004-2015 ZNC, see the NOTICE file for details.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <znc/Modules.h>
#include <znc/IRCNetwork.h>
#include <znc/IRCSock.h>

class CChanPrefixStrip : public CModule {
public:
	MODCONSTRUCTOR(CChanPrefixStrip) {}
	virtual ~CChanPrefixStrip() {}

	EModRet OnChanMessage(CTextMessage& Message) override {
		CString sChanName = Message.GetTarget();
		CString sPrefixes = Message.GetNetwork()->GetIRCSock()->GetISupport("STATUSMSG", "");

		if (sChanName.TrimLeft(sPrefixes))
		{
			Message.SetTarget(sChanName);
		}

		return CONTINUE;
	}
};

template<> void TModInfo<CChanPrefixStrip>(CModInfo& Info) {
	Info.AddType(CModInfo::NetworkModule);
}

NETWORKMODULEDEFS(CChanPrefixStrip, "Strip +/@ prefix from channel name before sending to client, to fix clients which show such messages in a PM instead of the channel")

