#pragma once
#include "Matterbot.h"
#include <chrono>
#include <ctime>
namespace lospi
{
	struct TimeCommand : ICommand {
		std::wstring get_name() override {
			return L"time";
		}

		std::wstring get_help() override {
			return L"`time`: `time` will tell the time.";
		}
			std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {
			
				using namespace std;
				using namespace chrono;

				auto today = system_clock::now();
				auto tt = system_clock::to_time_t(today);
				std::string time_str{ ctime(&tt) };
				auto lunch = 11;

				auto tp = system_clock::now();
				auto tHours = duration_cast<hours>(tp.time_since_epoch()).count() - 5;
				auto hourCount = tHours % 24;
				auto difference = lunch - hourCount;
				auto diffStr = to_wstring(difference);
				wstring time_wstr{ time_str.begin(), time_str.end() };
				time_wstr.append(L"\n");
				time_wstr.append(diffStr);
				time_wstr.append(L" hours till lunch!(roughly)");
				return time_wstr;

			}
	};
}