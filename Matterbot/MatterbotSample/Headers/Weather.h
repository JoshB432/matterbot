#pragma once
#include "Matterbot.h"


namespace lospi
{

	struct WeatherCommand : ICommand {
		std::wstring get_name() override {
			return L"weather";
		}

		std::wstring get_help() override {
			return L"`weather [CMD]`: \n`weather rain`: Make it rain\n`weather sunny`: I'm walkin\' on sunshine!\n`weather report`: Print the Status";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) 
			override {
			if (command_text == L"sunny")
			{
				is_raining = false;
				return L"It's not raining!";
			}
			else if (command_text == L"rain")
			{
				is_raining = true;
				return L"It's raining outside.";
			}
			else if (command_text == L"report")
			{
				if (is_raining)
				{
					return L"It's raining outside.";
				}
				else {
					return L"It's not raining!";
				}

			}
			else 
			{
				return L"What weather?";
			}
		}
	private:
		bool is_raining;
	};
}