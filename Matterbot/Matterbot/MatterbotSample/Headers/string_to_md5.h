#pragma once
#include "Matterbot.h"
#include "Md5Utilities.h"
namespace lospi {

	struct
		EmDeeFiveCommand : ICommand {
		std::wstring get_name() override {
			return L"givemd5";
		}

		std::wstring get_help() override {
			return L"`givemd5`: `givemd5` is for testing only. Please leave it alone.";
		}
		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {
			auto original = command_text;
			auto origin2 = wstring_to_string(original);
			auto size1 = origin2.size();
			auto md5origin = compute_md5(origin2.c_str(), size1);

			auto md5string = get_str_from_md5(md5origin);
			

			return md5string;
		}

	};
}
