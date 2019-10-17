/*
    touchscreen-calibrator

    Copyright (C) 2019  Enrique Medina Gremaldos <quiqueiii@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <xcb/xcb.h>
#include <xcb/xinput.h>

#include <iostream>

using namespace std;


int main(int argc,char* argv[])
{
    xcb_connection_t *connection = xcb_connect (NULL, NULL);
    
    clog<<"xinput devices:"<<endl;
    
    xcb_input_list_input_devices_cookie_t device_list_cookie;
    xcb_input_list_input_devices_reply_t* device_list;
    xcb_generic_error_t* error;
    
    device_list_cookie=xcb_input_list_input_devices(connection);
    
    device_list=xcb_input_list_input_devices_reply(connection,device_list_cookie,&error);
    
    xcb_input_device_info_t* device_info;
    
    device_info=xcb_input_list_input_devices_devices(device_list);
    
    while (device_info!=NULL) {
        
    }
    
    
    
    free(device_list);
    
    
    return 0;
}