//
// Aspia Project
// Copyright (C) 2020 Dmitry Chapyshev <dmitry@aspia.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef ROUTER__MANAGER__ROUTER_WINDOW_H
#define ROUTER__MANAGER__ROUTER_WINDOW_H

#include "net/client_authenticator.h"

namespace proto {
class PeerList;
class PeerResult;
class ProxyList;
class UserList;
class UserResult;
} // namespace proto

namespace router {

class RouterWindow
{
public:
    virtual ~RouterWindow() = default;

    virtual void onConnected(const base::Version& peer_version) = 0;
    virtual void onDisconnected(net::Channel::ErrorCode error_code) = 0;
    virtual void onAccessDenied(net::ClientAuthenticator::ErrorCode error_code) = 0;
    virtual void onPeerList(std::shared_ptr<proto::PeerList> peer_list) = 0;
    virtual void onPeerResult(std::shared_ptr<proto::PeerResult> peer_result) = 0;
    virtual void onProxyList(std::shared_ptr<proto::ProxyList> proxy_list) = 0;
    virtual void onUserList(std::shared_ptr<proto::UserList> user_list) = 0;
    virtual void onUserResult(std::shared_ptr<proto::UserResult> user_result) = 0;
};

} // namespace router

#endif // ROUTER__MANAGER__ROUTER_WINDOW_H
