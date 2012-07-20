/*  
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>. 
*/

#include "libs/Kernel.h"
#include "Panel.h"
#include "PanelScreen.h"
#include "MainMenuScreen.h"
#include "WatchScreen.h"
#include "FileScreen.h"
#include "ControlScreen.h"
#include "libs/nuts_bolts.h"
#include "libs/utils.h"
#include "I2CLCD.h"
#include <string>
using namespace std;

MainMenuScreen::MainMenuScreen(){}

void MainMenuScreen::on_enter(){
    this->panel->enter_menu_mode();
    this->panel->setup_menu(6, 4);  // 6 menu items, 4 lines

    this->refresh_screen();
    
    // Children screens
    this->watch_screen   = (new WatchScreen()   )->set_parent(this);
    this->file_screen    = (new FileScreen()    )->set_parent(this);
    this->control_screen = (new ControlScreen() )->set_parent(this); 

}

void MainMenuScreen::on_refresh(){
    if( this->panel->menu_change() ){
        this->refresh_screen();
    }
    if( this->panel->click() ){
        this->clicked_menu_entry(this->panel->menu_selected_line);
    }


}

void MainMenuScreen::refresh_screen(){
    this->refresh_menu();
}

void MainMenuScreen::display_menu_line(uint16_t line){
    switch( line ){
        case 0: this->panel->lcd->printf("Watch"); break;  
        case 1: this->panel->lcd->printf("File"); break; 
        case 2: this->panel->lcd->printf("Control"); break; 
        case 3: this->panel->lcd->printf("Prepare"); break; 
        case 4: this->panel->lcd->printf("Configure"); break; 
        case 5: this->panel->lcd->printf("Tune"); break; 
    }


}

void MainMenuScreen::clicked_menu_entry(uint16_t line){
    switch( line ){
        case 0: this->panel->enter_screen(this->watch_screen   ); break;
        case 1: this->panel->enter_screen(this->file_screen    ); break;
        case 2: this->panel->enter_screen(this->control_screen ); break;
    }


}


