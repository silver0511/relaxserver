/*
 * file_name: ServerManger.cpp
 * file_detail:implementation of ServerManager.h
 * created by silver0511
 */


#include "ServerManager.h"
#include "package/protobuf/hpb/business.pb.h"

USING_RELAX_NAMESPACE

ServerManager::ServerManager()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

ServerManager::~ServerManager()
{
    google::protobuf::ShutdownProtobufLibrary();
}
