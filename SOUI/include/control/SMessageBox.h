/**
* Copyright (C) 2014-2050 SOUI团队
* All rights reserved.
* 
* @file       SMessageBox.h
* @brief      
* @version    v1.0      
* @author     soui      
* @date       2014-07-06
* 
* Describe     
*/
#pragma once
#include "core/shostdialog.h"

namespace SOUI
{
    //下面是几个在msgbox模板中必须指定的ID。
    #define NAME_MSGBOX_BTNSWITCH       L"btnSwitch"    //一个包含3个页面的tabctrl
    #define NAME_MSGBOX_TEXT            L"msgtext"      //文本控件，只需要指定两个坐标
    #define NAME_MSGBOX_TITLE           L"msgtitle"     //标题ID
    #define NAME_MSGBOX_ICON            L"msgicon"      //图标显示控件
    #define NAME_MSGBOX_BTN1            L"button1st"    //第1个按钮ID，按钮ID在显示时会自动修改为如IDOK,IDCANCEL这样的ID。
    #define NAME_MSGBOX_BTN2            L"button2nd"    //第2个按钮ID
    #define NAME_MSGBOX_BTN3            L"button3rd"    //第3个按钮ID
    
    BOOL SOUI_EXP SetMsgTemplate(pugi::xml_node xmlNode);

    pugi::xml_node SOUI_EXP GetMsgTemplate();

    int SOUI_EXP SMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);

}//end of namespace 

