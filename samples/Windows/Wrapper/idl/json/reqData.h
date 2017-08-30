#pragma once 

#include <string>
#include <vector>

#include "JsonObjectBase.h"

using namespace std;


namespace MessageService 
{
    class GroupData : public CJsonObjectBase
	{
	public:
        string id;                  //群的唯一名称;
        string name;                //群组名称，此属性为必须的;
        string desc;                //群组描述，此属性为必须的;
        bool isPublic;              //是否是公开群，此属性为必须的;
        int maxUsers;               //群组成员最大数（包括群主），值为数值类型，默认值200，此属性为可选的;
        string owner;               //群组的管理员，此属性为必须的;
        vector <string> admins;     //管理员;
        vector <string> members;    //普通成员，此属性为可选的;

        GroupData() { SetPropertys(); }

        virtual void SetPropertys()
		{
            SetProperty("id", asString, &id);
            SetProperty("name", asString, &name);
            SetProperty("desc", asString, &desc);
            SetProperty("thePublic", asBool, &isPublic);
            SetProperty("maxUsers", asInt, &maxUsers);
            SetProperty("owner", asString, &owner);
            SetProperty("admins", asVectorArray, &admins, asString);
            SetProperty("members", asVectorArray, &members, asString);
        }
    };
    
	class ResponseRet : public CJsonObjectBase
    {
	public:
    	int status;                  //响应状态码
        string message;                //响应结果状态
 
        ResponseRet() { SetPropertys(); }

        virtual void SetPropertys() 
        {
            SetProperty("status", asInt, &status);
            SetProperty("message", asString, &message);
        }
    };
    
	//class GroupDetailRet : public CJsonObjectBase
 //   {
	//public:
	//	string id;                  //群的唯一名称
 //       string name;                //群组名称，此属性为必须的
	//	string desc;
	//	bool isPublic;				//是否是公开群，此属性为必须的
 //       int maxUsers;               //群组成员最大数（包括群主），值为数值类型，默认值200，此属性为可选的
 //       string owner;               //群组的管理员，此属性为必须的
 //       vector <string> admins;     //管理员
 //       vector <string> members;    //普通成员，此属性为可选的
 //       
 //       int status;                  //响应状态码
 //       string message;                //响应结果状态

 //       GroupDetailRet()
	//	{
	//		SetPropertys();
	//	}

 //       virtual void SetPropertys() 
 //       {
 //           SetProperty("id", asString, &id);
 //           SetProperty("name", asString, &name);
 //           SetProperty("desc", asString, &desc);
 //           SetProperty("thePublic", asBool, &isPublic);
 //           SetProperty("maxUsers", asInt, &maxUsers);
 //           SetProperty("owner", asString, &owner);
 //           SetProperty("admins", asVectorArray, &admins, asString);
 //           SetProperty("members", asVectorArray, &members, asString);
 //           
 //           SetProperty("status", asInt, &status);
 //           SetProperty("message", asString, &message);
 //       }
 //   }; 
}
