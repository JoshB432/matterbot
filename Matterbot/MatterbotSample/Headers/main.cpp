#include "Matterbot.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "ConsoleLogger.h"
#include "EchoCommand.h"
#include "ReverseCommand.h"
#include "Weather.h"
#include "CheckTime.h"	
#include "string_to_md5.h"
#include "Md5Utilities.h"
#include "Md5.h"
#include "Hashmaker.h"
#include "hashslingingslasher.h"
#define ERROR_SUCCESS 0
#define ERROR_FAILURE -1

using namespace std;
using namespace lospi;

int main() {
  wstring mattermost_url = L"https://hooks.slack.com",
    incoming_hook_route = L"services/T4Z1QAKSS/B50MZR12B/V2zmDwAt50jBgR6fCMLacE5K",
    outgoing_hook_route = L"http://127.0.0.1:9001/",
    outgoing_hook_token = L"yscFGgX0seG4iIHamfwDJIZT",
    welcome_message = L"bot is running.";

  try {


    auto bot = make_shared<Matterbot>(mattermost_url, incoming_hook_route, outgoing_hook_route, outgoing_hook_token);
    bot->set_logger(make_unique<ConsoleLogger>());
    bot->register_command(make_shared<EchoCommand>());
	bot->register_command(make_shared<WeatherCommand>());
	bot->register_command(make_shared<TimeCommand>());
	bot->register_command(make_shared<EmDeeFiveCommand >());
	bot->register_command(make_shared<MakeTableCommand >());
	bot->register_command(make_shared<ReverseCommand>(bot));
	bot->register_command(make_shared<HashTableCommand>(bot));
	bot->post_message(welcome_message);




    wstring console;
    wclog << ">> Type \'quit\' to quit. Any other input will be sent to the bot." << endl;
    while (getline(wcin, console)) {
      if (L"quit" == console) {
        wclog << ">> Quitting." << endl;
        return ERROR_SUCCESS;
      }
      if (L"" != console) { bot->post_message(console); }
    }
  }
  catch (exception e) {
    wcerr << "[-] Unhandled exception:" << e.what() << endl;
    return ERROR_FAILURE;
  }
}
