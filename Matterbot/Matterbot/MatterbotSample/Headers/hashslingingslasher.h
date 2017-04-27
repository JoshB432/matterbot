#pragma once
#include <string>
#include "Matterbot.h"
#include "Md5Utilities.h"
#include <map>


namespace lospi {
	std::map <lospi::Md5Digest, std::vector<char>>hashlist;
	struct
		MakeTableCommand : ICommand {
		std::wstring get_name() override {
			return L"Tablefy";
		}

		std::wstring get_help() override {
			return L"`Tablefy`: `Tablefy` Will generate a table of MD5 Hashes to compare to.\nPlease note that there is no user input validation in place at this time. Watch what you type!\n `Tablefy password [PASSWORD]` Will change your password and generate your table.\n `Tablefy level [level]` Will change your level and generate your table.\n";
		}
		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			size_t level = 4;
			std::string password = "9y7clq";

			if (command_text.find(L"password") != std::string::npos)
			{

				auto newPass = (wstring_to_string(command_text));
				auto password = newPass.substr(newPass.find(" "), newPass.back());

			}

			else if (command_text.find(L"level") != std::string::npos)
			{

				std::string newLevel = (wstring_to_string(command_text));
				std::string placeholder = newLevel.substr(newLevel.find(" "), newLevel.back());
				level = std::stoi(placeholder);
			}

			int i;
			for (i = 0; i < 10 + level; i++) {
				Combinator hashlister("hsoj", i);

				while (hashlister.has_next())
				{
					auto salt = hashlister.next();
					salt.insert(salt.end(), password.begin(), password.end());

					auto md5 = compute_md5(salt.data(), salt.size());
					hashlist.emplace(md5, salt);
				}
			}

			std::wstring restatement = L"Table Complete";
			return restatement;
		}
	};
}
