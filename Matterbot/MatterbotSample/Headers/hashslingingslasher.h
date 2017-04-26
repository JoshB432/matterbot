#pragma once
#include <string>
#include "Matterbot.h"
#include "Md5Utilities.h"


namespace lospi {

	struct
		MakeTableCommand : ICommand {
		std::wstring get_name() override {
			return L"Tablefy";
		}

		std::wstring get_help() override {
			return L"`Tablefy`: `Tablefy` Will generate a table of MD5 Hashes to compare to.";
		}
		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			size_t level = 1;
			std::string password = "y2kihu";
			/*
			if (command_text == L"password")
			{

				password = (wstring_to_string(command_text));
			}
			else if (command_text == L"level")
			{
				level = std::stoi(command_text);
			}
			*/
			
				Combinator hashlister{ "hsoj", level };

				while (hashlister.has_next())
				{
					auto salt = hashlister.next();
					salt.insert(salt.end(), password.begin(), password.end());
					auto md5 = compute_md5(salt.data(), salt.size());
					hashlist.insert(std::make_pair(md5, salt));
				}
			}
		std::string restatement = "Table Complete";

		return restatement;
	}

	}
}
