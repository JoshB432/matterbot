#pragma once
#pragma once
#include "Matterbot.h"
#include "Md5Utilities.h"
#include <string>
#include <map>
#include "hashslingingslasher.h"



/*
TODO
implement{
command(s) for:
level
challenge
iteration
hash comparison
}
add password

*/
namespace lospi {

	struct
		challengeCommand : ICommand {
		explicit challengeCommand(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override {
			return L"challenges";
		}

		std::wstring get_help() override {
			return L"`challenges`: `challenges` is for testing only. Please leave it alone.";
		}
		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			std::vector<std::string> list;
			std::vector<std::string> anskey;
			auto challenges = wstring_to_string(command_text);
			auto current = challenges.substr(0, challenges.find(" "));
			auto rest = challenges;

			if (challenges.find(" ") == std::string::npos)
			{
				list.push_back(current);
				current = "";
			}
			while (!current.empty())
			{
				list.push_back(current);
				if (rest.empty())
				{
					current = rest;	
				} 
				rest = challenges.substr(challenges.find(" ") + 1, challenges.size() - current.size() + 1);
				current = rest.substr(0, rest.find(" "));
				challenges = rest;
				if (rest.find(" ") == std::string::npos)
				{
					list.push_back(current);
					rest = "";
					current = rest;
				}
			}

			for (auto it = list.begin(); it != list.end();)
			{
				auto converted = get_md5_from_str(string_to_wstring(*it));
				auto answer = hashlist.find(converted)->second;
				anskey.push_back(std::string(answer.begin(), answer.end()));
				anskey.push_back(" ");
				if (it == list.end() - 1) {
					anskey.pop_back();
				}
				it++;
			}
			std::wstring answerkey{ L"rivestment try " };
			for (auto it = anskey.begin(); it != anskey.end(); it++)
			{
			answerkey = answerkey.append(string_to_wstring(*it));

			}
			_sleep(1000);
			bot->post_message(answerkey);
			_sleep(2000);
			std::wstring goagain(L"rivestment challenge");
			return goagain;

		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}

