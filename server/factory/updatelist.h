#pragma once

#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "../user.h"

class UpdateList{
public:
    QJsonObject build(const QSet<User*>& users){
        QJsonArray arr;
        for(auto user:users){
            QJsonObject j;
            j["name"]=user->name;
            j["status"]=user->status;
            if(!user->name.isEmpty()){
                arr.append(j);
            }
        }
        QJsonObject json;
        json["type"]="update_list";
        json["users"]=arr;
        return json;
    }
};
