/* This file is part of Korvahk.
 *
 * Korvahk is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Korvahk is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Korvahk.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "plConfig.h"

#include <cstdarg>
#include <string_theory/string>

#include "Plasma/BitVector.h"
#include "Plasma/Key.h"
#include "Plasma/KeyedObject.h"
#include "Plasma/Types.h"

namespace Plasma
{
    class Message;
    class NetMessage;
    class SynchedObject;

    class Loggable
    {
    public:
        // Variables
        class StatusLog* fStatusLog;
        bool fWeCreatedLog, fComplainAboutMissingLog;

#ifdef PLASMA_TPOTS
    private:
        int fTpotsUnknown1;

    public:
#endif

        // VFTable functions
        virtual void ICreateStatusLog() const {}

        Loggable() {}
        virtual ~Loggable() {}

#ifndef PLASMA_HAVE_STRING_THEORY
        virtual bool Log(char*) const {}
        virtual bool LogF(char*, ...) const {}
        virtual bool LogV(char*, va_list) const {}
        virtual bool ErrorMsgV(char*, va_list) const {}
        virtual bool DebugMsgV(char*, va_list) const {}
        virtual bool WarningMsgV(char*, va_list) const {}
        virtual bool AppMsgV(char*, va_list) const {}
        virtual bool ErrorMsg(char*, ...) const {}
        virtual bool DebugMsg(char*, ...) const {}
        virtual bool WarningMsg(char*, ...) const {}
        virtual bool AppMsg(char*, ...) const {}
#else
        virtual bool Log(const ST::string&) const {}
        virtual bool ErrorMsg(const ST::string&) const {}
        virtual bool DebugMsg(const ST::string&) const {}
        virtual bool WarningMsg(const ST::string&) const {}
        virtual bool AppMsg(const ST::string&) const {}
        virtual bool ErrorMsg(const char*) const {}
        virtual bool DebugMsg(const char*) const {}
        virtual bool WarningMsg(const char*) const {}
        virtual bool AppMsg(const char*) const {}
#endif
    };

    class NetApp : public KeyedObject, public Loggable
    {
    public:
        enum FlagBits
        {
            kNullSend, kNetCoreSingleThreaded, kScreenMessages,
            FLAG_CEILING = 10
        };

    public:
        BitVector fFlagsVec;

    public:
        PLASMA_CREATABLE(NetApp)

        virtual void Shutdown() {}
    };

    class NetClientApp : public NetApp
    {
    public:
        enum ClientFlagBits
        {
            kDeferMsgs = NetApp::FLAG_CEILING,
            kDisabled, kDisableOnNextUpdate, kLocalTriggers, kEchoVoice, kRequestP2P,
            kIndirectMember, kSendingVoice, kSendingActions, kAllowTimeOut,
            kAllowAuthTimeOut, kPlayingGame, kShowLists, kShowRooms, kShowAvatars,
            kShowRelevanceRegions, kConnectedToVault, kBanLinking, kSilencePlayer,
            kConsoleOutput, kLoadingInitialAgeState, kLaunchedFromSetup,
            kCCRVaultConnected, kNetClientCommInited, kNeedToSendInitialAgeStateLoadedMsg,
            kNeedToSendAgeLoadedMsg, kDemoMode, kNeedInitialAgeStateCount,
            kLinkingTOOfflineAge
        };

    public:
        int fCCRLevel;

    public:
        PLASMA_CREATABLE(NetClientApp)

        virtual Boolean ISendGameMessage(Message*) {}
        virtual Boolean SendMsg(NetMessage*) = 0;
        virtual unsigned long GetPlayerID() const = 0;
        virtual const char* GetPlayerName(Key) const = 0;
        virtual float GetCurrentAgeTimeOfDayPercent() const {}
        virtual bool ObjectInLocalAge(const SynchedObject*) const {}
        virtual unsigned char GetJoinOrder() const {}
        virtual Boolean IsRemotePlayerKey(Key, int*) {}
        virtual Key GetLocalPlayerKey() const {}
        virtual SynchedObject* GetLocalPlayer(int) const {}
        virtual NetGroupId SelectNetGroup(SynchedObject*, Key) {}
        virtual Boolean IsLocallyOwned(const Uoid&) const {}
        virtual Boolean IsLocallyOwned(const SynchedObject*) const {}
        virtual NetGroupId GetEffectiveNetGroup(const SynchedObject*) const {}
        virtual int Update(double) {}
        virtual const char* GetServerLogTimeAsString(LegacyStdString&) const {}
        virtual Uoid GetAgeSDLObjectUoid(const char*) const {}
        virtual void StayAlive(double) {}
        virtual void QueueDisableNet(bool, const char* const) {}
    };
};
