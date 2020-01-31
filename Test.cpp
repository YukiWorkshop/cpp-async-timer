/*
    This file is part of CPPAsyncTimer.
    Copyright (C) 2020 ReimuNotMoe

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "AsyncTimer.hpp"

using namespace YukiWorkshop::AsyncTimer;

int main() {
	boost::asio::io_service iosvc;

	int cnt = 0, cnt2 = 0;

	TimerContext *t = setInterval(iosvc, [&](){
		puts("aaaa");
		cnt++;
		if (cnt == 5) clearInterval(t);
	}, 1000);


	TimerContext *t2 = setInterval(iosvc, [&](){
		puts("bbbb");
		cnt2++;
		if (cnt2 == 5) clearInterval(t2);
	}, 1200);

	setTimeout(iosvc, [&](){
		puts("cccc");
	}, 1300);

	TimerContext *t4 = setTimeout(iosvc, [&](){
		puts("dddd"); // You won't see this
	}, 1400);

	clearTimeout(t4);

	iosvc.run();
}